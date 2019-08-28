#include <stdio.h>
#include <stdlib.h>

union X{
   char i;
   struct{
      int A:1;
      int B:1;
      int C:1;
      int D:1;
      int E:1;
      int F:1;
   };
};

int main()
{
    char i;
    char C1, C2, C3, C4, C5, C6;
    union X x;

    for(x.i=0;x.i<64;x.i++){
      C1= x.A || x.B;  C2=(x.A&&x.E) || (x.A&&x.F) || (x.E&&x.F);
      C3=!(x.A&&x.D);   C4=(x.B&&x.C) || (!x.B&&!x.C);
      C5=(x.C&&!x.D) || (!x.C&&x.D);  C6=(!x.D && !x.E) || x.D;

      if(C1 && C2 && C3 && C4 && C5 && C6){
           x.A?printf("A是案犯\n"): printf("A不是案犯\n");
           x.B?printf("B是案犯\n"): printf("B不是案犯\n");
           x.C?printf("C是案犯\n"): printf("C不是案犯\n");
           x.D?printf("D是案犯\n"): printf("D不是案犯\n");
           x.E?printf("E是案犯\n"): printf("E不是案犯\n");
           x.F?printf("F是案犯\n"): printf("F不是案犯\n");
      }
    }
    return 0;
}
