#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE   512

int main(int argc, char *argv[]) {
  uint8_t buffer[BUFFER_SIZE];
  uint8_t current[BUFFER_SIZE];
  uint32_t current_size = 0;
  int index;

  int fd = open(argv[1], O_RDONLY);
	if(fd != 0)
		printf("opened the file\n");

  while(1) {
    int rc = read(fd, buffer, BUFFER_SIZE);

    for(index = 0; index < rc; index++) {
      if(isascii(buffer[index])) {

        if(buffer[index] != '\n' && buffer[index] != '\0')
          current[current_size++] = buffer[index];

        else if(current_size > 4){
          current[current_size] = '\0';
          printf("%s\n", current);
          current_size = 0;
        }
        else
          current_size = 0;
      }
      else
        current_size = 0;
    }
    if(rc != BUFFER_SIZE)
      break;
  }

  return 0;
}
