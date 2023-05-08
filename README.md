# Thread-pool
## Oria Zadok & Yohanan Kling

## Project Description
This project is a C implementation for encrypting and decrypting data.
It takes standard input data and encrypts it using a received key.
The data is then split into 1024 chars buffers for the threads to encrypt them.
One thread is responsible for printing the encrypted data in the right order, and one more for cleaning the memory data. 

The decryption process follows a similar pattern.
The encrypted data is received through standard input and is decrypted using a received key.
The data is then split into 1024 chars buffers for the threads to decrypt them.
One thread is responsible for printing the decrypted data in the right order, and one more for cleaning the memory data. 

## Getting Started
To get started with this project, you should clone the repository to your local machine.
git clone https://github.com/oriazadok/threadPool.git
After cloning the repository, you should navigate to the project directory and build the executable file using the make command.

## Usage
Once the executable file has been built, you can use it to encrypt or decrypt data using a specified key.

## Encryption
To encrypt data, you can use the following command.

./coder [key] -e < original_file > encripted_file
In this command, <coder> is the name of the executable file you built using the make command.
[key] is the key number that will be used to encrypt the data.
<-e> is the flag that say the program to encrypt.
<original_file> is the file you want to encrypt.
<encripted_file> is the file you want to create with the result of the encrypt.

## Decryption
To decrypt data, you can use the following command.

./coder [key] -d < encripted_file > decripted_file
In this command, <coder> is the name of the executable file you built using the make command.
[key] is the key number that will be used to decrypt the data.
<-e> is the flag that say the program to decrypt.
<original_file> is the file you want to decrypt.
<encripted_file> is the file you want to create with the result of the decrypt.
