#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *fileName){
    char buf[512];
    int fd;
    struct stat st;
    struct stat st2;
    struct dirent de;
    fd = open(path, 0);
    if(fd < 0){
        printf("Can't open\n");
        exit(1);
    }
    if(fstat(fd, &st) < 0){
        printf("Error");
        exit(1);
    }
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0 || de.inum == 0){
            continue;
        }
        
        strcpy(buf, path);
        int len = strlen(buf);
        buf[len] = '/';
        memmove(buf + len + 1, de.name, 14);
        buf[len + 1 + 14] = 0;
        int fd2 = open(buf, 0);
        if(fd2 < 0){
            continue;
        }
        fstat(fd2, &st2);
        close(fd2);
        if(st2.type == T_DIR){
            find(buf, fileName);
        }
        else if(st2.type == T_FILE){
            if(strcmp(de.name, fileName) == 0){
                printf("%s\n", buf);
            }
        }
        else{
            continue;
        }
    }

    close(fd);
}

int
main(int argc, char *argv[]){
    if(argc < 3){
        printf("Argument Count Error");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}