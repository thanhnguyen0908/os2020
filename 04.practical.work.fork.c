#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int pid1, pid2;
  printf("Main before fork()\n");
  pid1 = fork();
  if(pid1 == 0){
    printf("\t Executing the first child process\"ps -ef\"\n");
    char* args[] = {"/bin/ps", "-ef", NULL};
    if(execvp("/bin/ps", args) < 0){
      printf("Execution failed \"ps -ef\"\n");
    }
  }
  else {
    waitpid(pid1, NULL, 0);
    printf("I am the parent after fork, the child is %d\n\tContinue to create another child\n", pid1);
    pid2 = fork();
    if(pid2 == 0){
      printf("\t Executing the second child process \"free -h\"\n");
      char* args[] = {"/usr/bin/free", "-h", NULL};
      if(execvp("/usr/bin/free", args) < 0){
        printf("Execution failed \"free -h\"\n");
      }
    }
    else {
      printf("This is the parent after 2 forks, the second one is %d\nExecution finished.\n", pid2);
      waitpid(pid2, NULL, 0);
    }
  }
  return 0;
}
