#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#include "queue.h"
#include "codec.h"

pthread_mutex_t queueMutex;
pthread_mutex_t mutex;
pthread_cond_t startCond;
pthread_cond_t cond;

pQueue q;
pQueueNode n;

int done = 0;

int getData() {

	char data[DATA_SIZE];
	char c;
	int counter = 0;

	while( ( c = getchar() ) != EOF ) {
		data[counter] = c;
		counter++;

		if (counter == DATA_SIZE){
			pthread_mutex_lock(&queueMutex);
			enQueue(q, data);
			pthread_cond_signal(&startCond);
			pthread_mutex_unlock(&queueMutex);
			counter = 0;
		}
	}

	if (counter > 0) {
		data[counter] = '\0';
		pthread_mutex_lock(&queueMutex);
		enQueue(q, data);
		pthread_mutex_unlock(&queueMutex);
	}

	// printQueue(q);

	done = 1;

	return 0;
}

void* enc(void* key) {

	pQueueNode node;

	pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

	while( 1 ) {

		if( n ) {

			pthread_mutex_lock(&mutex);
			node = n;
			n = n->prev;
			pthread_mutex_unlock(&mutex);

			encrypt(node->data, *(int*)key);
			node->isDone = 1;
		}

		if(done && isEmpty(q)) {
			break;
		}
	}


	return NULL;
}

void* dec(void* key) {

	// printf("Thread %lu is waiting on condition variable...\n", pthread_self());

	// pthread_mutex_lock(&mutex);
    // pthread_cond_wait(&cond, &mutex);
    // pthread_mutex_unlock(&mutex);

	// printf("Thread %lu got the signal!\n", pthread_self());

	pQueueNode node;

	pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

	while( 1 ) {

		if( n ) {

			pthread_mutex_lock(&mutex);
			node = n;
			n = n->prev;
			pthread_mutex_unlock(&mutex);

			decrypt(node->data, *(int*)key);
			node->isDone = 1;
		}

		if(done && isEmpty(q)) {
			break;
		}
	}
	return NULL;
}

void* clean() {

	pthread_mutex_lock(&queueMutex);
    pthread_cond_wait(&startCond, &queueMutex);
	n = q->top;
    pthread_mutex_unlock(&queueMutex);

	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

	pQueueNode del = NULL;
	// int f = 0;
	while( 1 ) {

		if( q->top ) {
			if( q->top->isDone ) {

				pthread_mutex_lock(&queueMutex);
				del = deQueue(q);
				pthread_mutex_unlock(&queueMutex);

				// int f = 0;
				// for(int i = 0; i < DATA_SIZE; i++) {
				// 	printf("%c", del->data[i]);
				// 	f++;
				// }

				// if(f == 1024) {
				// 	printf("\n");
				// 	f = 0;
				// }
				// printf("f: %d\n", f);
				printf("%s", del->data);
				fflush(stdout);

				free(del);
			}

		}

		if(done && isEmpty(q)) {
			break;
		}
	}

	// printf("f: %d\n", f);

	return NULL;
}

int main( int argc, char *argv[] ) {

	if ( argc != 3 ) {
	    printf("usage: key < file \n");
	    printf("!! data more than 1024 char will be ignored !!\n");
	    return 1;
	}

	// get command's data
	int key = atoi(argv[1]);
	char flag = argv[2][1];

	void* (*op)(void* key);
	if(flag == 'e') {
		op = &enc;
	} else if(flag == 'd') {
		op = &dec;
	} else {
		printf("Unrecognaized flag, use -e for encription or -d for decription\n");
		return 1;
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&queueMutex, NULL);
	pthread_cond_init(&startCond, NULL);
	pthread_cond_init(&cond, NULL);

	q = createQueue();

	int cores = get_nprocs_conf();
	pthread_t threads[cores];

	int i;
	for(i = 0; i < cores - 2; i++) {
		if(pthread_create(&threads[i], NULL, op, &key) != 0) {
            perror("Error: can not create thread!");
        }
	}

	if(pthread_create(&threads[i], NULL, &clean, &key) != 0) {
		perror("Error: can not create thread!");
	}

	usleep(500);
	// get data to encrypt/decrypt
	getData();

	for(int i = 0; i < cores - 1; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("Error: can not join the thread!");
        }
    }

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&queueMutex);
	pthread_cond_destroy(&startCond);
	pthread_cond_destroy(&cond);

	return 0;
}



