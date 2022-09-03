#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define READ_END    0    /* index pipe extremo escritura */
#define WRITE_END   1    /* index pipe extremo lectura */

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

int **multuplicacionMatrices (int **matriz1, int **matriz2, int tam)
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



int multuplicacionFilxCol (int **matriz1, int **matriz2, int tam, int i, int j){
    int suma = 0; 
    for (int k = 0; k < tam; k++) {
        suma += matriz1[i][k] * matriz2[k][j];
    }

    return suma;
           
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

int guardarMatrix(int **matriz, int tam){
FILE *fichero = fopen( "Mat_R.txt", "a" );
    for( int fila = 0; fila < tam; ++fila ) {
    for( int col = 0; col < tam; ++col ) 
        fprintf( fichero, "%d ", matriz[fila][col] );
        fprintf( fichero, "\n" );
  }
  fprintf( fichero, "\n" );
  fclose( fichero );
return 0;
}

int almacenarMatrix(int **matriz,int tam){
FILE *fichero = fopen( "Matriz.txt", "w" );
    for( int fila = 0; fila < tam; ++fila ) {
    for( int col = 0; col < tam; ++col ) 
        fprintf( fichero, "%d ", matriz[fila][col] );
        fprintf( fichero, "\n" );
  }
  fprintf( fichero, "\n" );
  fclose( fichero );
return 0;
}

int guardarTiempos(double tiempo){
FILE *fichero = fopen( "Stats.txt", "a" );
    fprintf( fichero, "%f ", tiempo );
    fprintf( fichero, "\n" );
    fclose( fichero );
return 0;
}


void liberarMemoria (int** matriz, int tam){
 for(int i = 0; i < tam; i++)
     free(matriz[i]);
free(matriz);
  
}

int MatrixP (int tam)
{
   
   int **matriz1, **matriz2, **matriz;
   matriz1 = generarMatriz(tam);
   matriz2 = generarMatriz(tam);
   guardarMatrix(matriz1,tam);
   guardarMatrix(matriz2,tam);
   matriz = calloc(tam, sizeof(int *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (int *) calloc(tam, sizeof(int)); 
    }

   //int fd1[2];
   int status, pid;
   //pipe(fd1);                
   for(int i = 0; i<tam; i++){
   for(int j = 0; j<tam; j++){
          pid = fork();   
          if(pid > 0)         /* padre */
            {  
            continue;
            }
            else               /* N hijos */
            {   
              //int indice;
              ///close(fd1[READ_END]);
              
              matriz[i][j] = multuplicacionFilxCol(matriz1,matriz2,tam, i,j);
              almacenarMatrix(matriz, tam);
              //write (fd1[WRITE_END],&indice ,sizeof(int));
              //close(fd1[WRITE_END]);
              
              //exit(0);
            }  
   }     
        
   }
   //wait(&status);
   liberarMemoria(matriz1,tam);
   liberarMemoria(matriz2,tam);
   return 1;
}

double matrizPciclo(int tam){
   double  tiempoRes;
   for(int i = 0; i < 10; i++){
      double tiempo= 0.0;
      time_t inicio =  time(NULL);
      MatrixP(tam);
       //clock_t fin= clock();
      time_t fin =  time(NULL);
   //tiempo += (double)(fin - inicio) / CLOCKS_PER_SEC;
      tiempo = fin - inicio;
      guardarTiempos(tiempo);
       tiempoRes += tiempo;
   }
    tiempoRes =  tiempoRes /100;
    FILE *fichero = fopen( "Stats.txt", "a" );
    fprintf( fichero, "Promedio: ");
    fprintf( fichero, "%f ",  tiempoRes);
    fprintf( fichero, "\n" );
    fclose( fichero );
    return  tiempoRes;

}


 
int main(void){
    
   matrizPciclo(2);
    //printf("Timpo matrixP %f segundos", tiempoMatrixP );

   /*int **matriz1, **matriz2, **matriz, tam;
   tam = 3;
   matriz1 = generarMatriz(tam);
   matriz2 = generarMatriz(tam);
   matriz = multuplicacionMatrices(matriz1, matriz2, tam);
   imprimirMatriz(matriz, tam);

   printf(" Numero %d", multuplicacionFilxCol(matriz1,matriz2,tam, 0,2) );
*/
return 0;
}
