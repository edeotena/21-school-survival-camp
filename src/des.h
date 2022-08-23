#ifndef SRC_DES_H_
#define SRC_DES_H_

void create16Keys();
void convertCharToBit(long int n, char *file_name);
void encrypt(long int n);
long int findFileSize(char *file_name);

#endif  // SRC_DES_H_
