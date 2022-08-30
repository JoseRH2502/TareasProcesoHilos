#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <sys/types.h>
#include <unistd.h>





int **generarMatriz (int tam)
{
    // generaciòn de una matriz dinamica 
   int **matriz;
   matriz = calloc(tam, sizeof(int *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (int *) calloc(tam, sizeof(int)); 
    }

    // asiganaciòn de valores aleatorios
   for(int fil = 0; fil < tam; fil++){
       for(int col=0; col < tam; col++){
           matriz[fil][col]= rand() % 11;
       }
   }
   return matriz;
  
}

int **multuplicacionMatrices (int **matriz1, int **matriz2,int tam)
{
   int **matriz;
   matriz = calloc(tam, sizeof(int *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (int *) calloc(tam, sizeof(int)); 
    }

    for (int i = 0; i < tam; i++) {//se itera através de cada fila de matriz1
            for (int j = 0; j < tam; j++) {//se itera através de cada columna de matriz2
                int suma = 0;//es donde se almacenará el valor final 
                for (int k = 0; k < tam; k++) {
                    suma += matriz1[i][k] * matriz2[k][j];//se acumula en suma
                }
                matriz[i][j] = suma;
            }
        }

   return matriz;
}

void imprimirMatriz(int** matriz, int tam){
 for(int fil = 0; fil < tam; fil++){
      for(int col=0; col < tam; col++){
           printf("%d ",matriz[fil][col]);
       }
        printf("\n");
   }
   printf("\n");
}

void liberarMemoria (int** matriz, int tam){
 for(int i = 0; i < tam; i++)
     free(matriz[i]);
free(matriz);
  
}

int MatrixT (int tam)
{
    // implementar el programa de hilos
   return 0; 
}



double MatrixP (int tam)
{
   double tiempo= 0.0;
   int **matriz1, **matriz2;
   matriz1 = generarMatriz(tam);
   matriz2 = generarMatriz(tam);
   //clock_t inicio = clock();
   time_t inicio =  time(NULL);
   fork();
   multuplicacionMatrices(matriz1,matriz2, tam);
   //clock_t fin= clock();
   time_t fin =  time(NULL);
   //tiempo += (double)(fin - inicio) / CLOCKS_PER_SEC;
   tiempo = fin - inicio;
   liberarMemoria(matriz1,tam);
   liberarMemoria(matriz2,tam);
   return tiempo;
}

double matrizPciclo(int tam){
   double tiempoMatrixP, tiempoRes;
   for(int i = 0; i < 100; i++){
      tiempoMatrixP +=  MatrixP(tam);
   }
    tiempoRes =  tiempoMatrixP /100;
    return  tiempoRes;

}


 
int main(void){
   printf("Timpo matrixP %f segundos", matrizPciclo(10));

return 0;
}
