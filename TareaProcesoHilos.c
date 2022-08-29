#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
int MatrixT (int tam)
{
   int matrix[tam][tam];
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matrix[fil][col]= rand() % 11;
       }
   }
   //for(int fil = 0; fil < tam; fil++){
   //   for(int col=0; col < tam; col++){
   //        printf("%d ", matrix[fil][col]);
   //    }
   //     printf("\n");
   //}
   return 0;
  
}
int MatrixP (int tam)
{
   int matrix[tam][tam];
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matrix[fil][col]= rand() % 11;
       }
   }
   //for(int fil = 0; fil < tam; fil++){
   //   for(int col=0; col < tam; col++){
   //        printf("%d ", matrix[fil][col]);
   //    }
   //     printf("\n");
   //}
   return 0;
}
 
int main(void){
   double tiempoMatrixT= 0.0;
   clock_t inicioMatrixT = clock();
   for(int i = 0; i < 100; i++){
       MatrixT(1000);
   }
   clock_t finMatrixT= clock();
   tiempoMatrixT += (double)(finMatrixT - inicioMatrixT) / CLOCKS_PER_SEC;
   printf("Tiempo matrixT %f segundos", tiempoMatrixT);
   printf("\n");
 
   double tiempoMatrixP= 0.0;
   clock_t inicioMatrixP = clock();
   for(int i = 0; i < 100; i++){
       MatrixP(1000);
   }
   clock_t finMatrixP= clock();
   tiempoMatrixP += (double)(finMatrixP - inicioMatrixP) / CLOCKS_PER_SEC;
   printf("Timpo matrixP %f segundos", tiempoMatrixP);
 
return 0;
}
