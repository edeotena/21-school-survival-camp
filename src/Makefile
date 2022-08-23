CC = gcc
CFLAGS = -Wall -Wextra -Werror

cipher:
	$(CC) $(CFLAGS) cipher.c des.c -o ../build/cipher

run: cipher 
	leaks --quiet --atExit -- ./../build/cipher

logging_cipher:
	$(CC) $(CFLAGS) cipher.c logger.c des.c -o ../build/logging_cipher -D LOG

run_log: logging_cipher
	leaks --quiet --atExit -- ./../build/logging_cipher
