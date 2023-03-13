#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void onCtrlC(){
    printf("\n> ");
    if (fork() == 0) {
        execlp("/bin/bash", "bash","-c","kill `ps -e|grep firefox| head -1 |xargs|cut -d ' ' -f1`", (char *) NULL);
        _exit(0);
    }
    else {
        wait(0);
    }
    _exit(0);
}
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "ls") == 0) {
        if (fork() == 0) {
            execlp("/bin/ls", "ls", argv[2],(char *) NULL);
            _exit(0);
        }
        else {
            wait(0);
        }
    } else if (strcmp(argv[1], "cat") == 0) {

            if (fork() == 0) {
                execlp("/bin/cat", "cat", argv[2], (char *) NULL);
                _exit(0);
            }
            else {
               wait(0);
            }

    }else if (strcmp(argv[1], "finish-firefox") == 0) {
        signal(SIGINT, onCtrlC);
        printf("Нажмите Ctrl+C для завершения браузера Firefox\n");
        while (1){
        }
    }
    return 0;
}
