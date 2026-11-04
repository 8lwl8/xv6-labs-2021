#include "kernel/types.h"
#include "user/user.h"

int
main(){
    char buf[1];
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    int pid = fork();
    if(pid == 0){
        close(p2c[1]);
        close(c2p[0]);
        read(p2c[0], buf, 1);
        printf("%d: received ping\n",getpid());
        write(c2p[1], buf, 1);
    }
    else{
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], buf, 1);
        read(c2p[0], buf, 1);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}