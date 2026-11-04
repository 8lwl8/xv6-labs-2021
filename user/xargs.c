#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    char *eargv[32];
    char buf[512];
    char *args[16];
    int k;
    int i;
    int n;
    int m;
    int eof;
    char c;
    while(1){
        n = 0; i = 0; k = 0; m = 0;
        eof = 0;
        while(1){
            if(read(0, &c, 1) != 1){
                    eof = 1;
                    break;
                }
                if(c == '\n'){
                    break;
                }
                buf[n++] = c;
            }
        if(n == 0 && eof) break;
        buf[n] = 0;
        while(buf[i] != 0){
            while(buf[i] == ' '){
                i++;
            }
            if(buf[i] == 0){
                break;
            }
            args[k++] = buf + i;
            while(buf[i] != 0 && buf[i] != ' '){
                i++;
            }
            if(buf[i] == ' '){
                buf[i++] = 0;
            }
        }
        args[k] = 0;
        
        for(int j = 1; j < argc; j++){
            eargv[m++] = argv[j];
        }
        for(int j = 0; j < k; j++){
            eargv[m++] = args[j];
        }
        eargv[m] = 0;
        int pid = fork();
        if(pid == 0){
            exec(eargv[0], eargv);
            printf("xargs: exec failed\n");
            exit(1);
        }
        else{
            wait(0);
        }
        if(eof) break;
    }
    exit(0);
}