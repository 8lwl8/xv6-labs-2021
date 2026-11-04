#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//引入头文件：但为什么是这些？ :所用的函数在的地方
int
main(int argc, char *argv[]) //argc:参数数量， argv:参数数组(其中argv[0]是程序名)
{
  int i;

  for(i = 1; i < argc; i++){ //遍历参数数组
    write(1, argv[i], strlen(argv[i]));//打印到屏幕上
    if(i + 1 < argc){
      write(1, " ", 1); //没到最后一个就空格
    } else {
      write(1, "\n", 1);//最后一个换行
    }
  }
  exit(0);//退出
}
