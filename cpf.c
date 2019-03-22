#include "stdio.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_CHARS_TO_WRITE 2
struct stat attributes;

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("Not enough arguments!\n" );
    return 0;
  }

  printf("Opening files \n" );
  int fd = open(argv[1],O_RDONLY);
  if(fd < 0){
    printf("Failed opening first file\n" );
    return 0;
  }

  int fd2 = open(argv[2],O_WRONLY);

  if(fd2 < 0){
    fd2 = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    fd2 = open(argv[2],O_WRONLY);
    if(fd2 < 0) printf("Failed opening second file");
  }

  printf("Both files opened successfully!\n" );
  int running = 0;
  while(running == 0){
    char data[MAX_CHARS_TO_WRITE];
    printf("\n");

    int tmp = read(fd, data, sizeof(data));
    if(tmp != MAX_CHARS_TO_WRITE){
      running = -1;
    }

    for (size_t i = 0; i < tmp; i++) {
      printf("%c",data[i]);
    }
    write(fd2, data, tmp * sizeof(char));
  }
  close(fd);
  close(fd2);
  return 0;
}
