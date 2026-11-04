#include "kernel/types.h"
#include "user/user.h"

void sieve(int left){
    int p;
    if(read(left, &p, sizeof(int)) != sizeof(int)){
        exit(0);
    }
    printf("prime %d\n", p);
    int n;
    int c[2];
    pipe(c);
    int pid = fork();
    if(pid == 0){
        close(c[1]);
        close(left);
        sieve(c[0]);
        exit(0);
    }
    else{
        close(c[0]);
        while(read(left, &n, 4)){
            if(n % p != 0){
                write(c[1], &n, 4);
            }
        }
        close(c[1]);
        wait(0);
    }
}

int
main(){
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid == 0){
        close(p[1]);
        sieve(p[0]);
        exit(0);
    }
    else{
        close(p[0]);
        for(int i = 2; i <= 35; i++){
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
}