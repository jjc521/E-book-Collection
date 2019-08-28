#include <stdio.h>
struct REG{
  char al,ah;
};
union X{
  short ax;
  struct REG r;
};
int main(){
    union X x;
    x.ax=0x6162;
    printf("%c %c\n",x.r.al,x.r.ah);

    return 0;
}
