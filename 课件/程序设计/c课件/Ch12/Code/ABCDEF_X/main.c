#include <stdio.h>

int main()
{
    char X, A, B, C, D, E, F, C1, C2, C3, C4, C5, C6;

    for (X=0;X<64;X++){
      A= X & 1;  B=(X & 2) >> 1;
      C= (X & 4) >> 2;  D=(X & 8) >> 3;
      E= (X & 16) >> 4; F=(X & 32) >> 5;

      C1= A || B;   C2=(A&&E) || (A&&F) || (E&&F);
      C3=!(A&&D);   C4=(B&&C) || (!B&&!C);
      C5=(C&&!D) || (!C&&D);  C6=(!D && !E) || D;

      if(C1 && C2 && C3 && C4 && C5 && C6){
         A?printf("A是案犯\n"):printf("A不是案犯\n");
         B?printf("B是案犯\n"):printf("B不是案犯\n");
         C?printf("C是案犯\n"):printf("C不是案犯\n");
         D?printf("D是案犯\n"):printf("D不是案犯\n");
         E?printf("E是案犯\n"):printf("E不是案犯\n");
         F?printf("F是案犯\n"):printf("F不是案犯\n");
      }
    }
    return 0;
}
