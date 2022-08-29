#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <sys/types.h>
#include <unistd.h>

int MatrixT (int tam)
{
    // falta hacer generacion por punteros o variables globales 
   int matrix[tam][tam];
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matrix[fil][col]= rand() % 11;
       }
   }
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
int multuplicacionMatrices (int tam)
{
    // funciona la multiplicacion falta que reciba las matrices por parametro 
    int matrix1[tam][tam];
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matrix1[fil][col]= rand() % 11;
       }
   }

    for(int fil = 0; fil < tam; fil++){
      for(int col=0; col < tam; col++){
           printf("%d ", matrix1[fil][col]);
       }
        printf("\n");
   }
    printf("\n");

     int matrix2[tam][tam];
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matrix2[fil][col]= rand() % 11;
       }
   }

    for(int fil = 0; fil < tam; fil++){
      for(int col=0; col < tam; col++){
           printf("%d ", matrix2[fil][col]);
       }
        printf("\n");
   }
    printf("\n");

   int matrizRes[tam][tam];
    for (int i = 0; i < tam; i++) {//se itera através de cada fila de matriz1
            for (int j = 0; j < tam; j++) {//se itera através de cada columna de matriz2
                int suma = 0;//es donde se almacenará el valor final 
                for (int k = 0; k < tam; k++) {
                    suma += matrix1[i][k] * matrix2[k][j];//se acumula en suma
                }
                matrizRes[i][j] = suma;
            }
        }


   for(int fil = 0; fil < tam; fil++){
      for(int col=0; col < tam; col++){
           printf("%d ",matrizRes[fil][col]);
       }
        printf("\n");
   }
   return 0;
}

 
int main(void){
   /*double tiempoMatrixT= 0.0;
   clock_t inicioMatrixT = clock();
   for(int i = 0; i < 100; i++){
       fork (); 
       MatrixT(10);
   }
   clock_t finMatrixT= clock();
   tiempoMatrixT += (double)(finMatrixT - inicioMatrixT) / CLOCKS_PER_SEC;
   printf("Tiempo matrixT %f segundos", tiempoMatrixT);
   printf("\n");
 
   double tiempoMatrixP= 0.0;
   clock_t inicioMatrixP = clock();
   for(int i = 0; i < 100; i++){
       MatrixP(10);
   }
   clock_t finMatrixP= clock();
   tiempoMatrixP += (double)(finMatrixP - inicioMatrixP) / CLOCKS_PER_SEC;
   printf("Timpo matrixP %f segundos", tiempoMatrixP);
    */
   multuplicacionMatrices (3);
return 0;
}
