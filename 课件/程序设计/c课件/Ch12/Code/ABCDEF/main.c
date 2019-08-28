#include <stdio.h>
int main(){
  int A, B, C, D, E, F;
  int C1,C2,C3,C4,C5,C6;

  for(A=0;A<=1;A++)
     for(B=0;B<=1;B++)
        for(C=0;C<=1;C++)
           for(D=0;D<=1;D++)
              for(E=0;E<=1;E++)
                 for(F=0;F<=1;F++){
                   C1= A || B;
                   C2=(A&&E) || (A&&F) || (E&&F);
                   C3=!(A&&D); C4=(B&&C) || (!B&&!C);
                   C5=(C&&!D) || (!C&&D);
                   C6=(!D && !E) || D;
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
