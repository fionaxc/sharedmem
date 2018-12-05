#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[]){
  key_t key;
  int shmid;
  char * stuff;
  int mode;

  //make the key
  key = ftok("mem", 'R');

  //allocate shared memory segment
  shmid = shmget(key, 200, 0644 | IPC_CREAT);

  //get pointer to segment
  stuff = shmat(shmid, (void *)0, 0);

  if(stuff[0]){
    printf("Here be the segment: %s\n", stuff);
  }
  else{
    printf("Segment was just created!\n");
  }

  char input[200];
  printf("What would you like to do? Yes-Add to segment OR No-Delete segment\n");
  fgets(input, 200, stdin);

  if(!strcmp(input, "Yes\n")){
    printf("Please enter new string to put into segment: \n" );
    fgets(input, 200, stdin);
    input[strlen(input)-1] = 0;
    strcpy(stuff, input);
  }
  else if(!strcmp(input, "No\n")){
    shmdt(stuff);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Segment deleted\n");
  }

  return 0;


}
