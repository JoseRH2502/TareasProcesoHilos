#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>








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



struct parametros
{
    int **matriz;
    int **matriz1;
    int **matriz2;
    int tam;
    int i;
    int k;
};

int guardarMatrix(int **matriz, int pos, int tam){
FILE *fichero = fopen( "Mat_R.txt", "a" );
    fprintf( fichero, "%d ", pos);
    fprintf( fichero, "\n\n" );
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



void multiFilaCol( void * arg ){
    struct parametros *p ;
    p = ( struct parametros *) arg ;
    float temporal = 0;
    for (int j = 0 ; j < p->tam ; j++ ) //j para realizar la multiplicacion de 
                                        {                                          //los elementos   de la matriz
                temporal += p->matriz1[p->i][j] * p->matriz2[j][p->k];
               
    }    
    p->matriz[p->i][p->k] = temporal;

}


int **multiMatriz(int **matriz1, int **matriz2, int tam){
    struct parametros p;
    p.matriz1 = matriz1;
    p.matriz2 = matriz2;
    p.tam = tam;
    int **matriz;
   matriz = calloc(tam, sizeof(int *));
    for(int i = 0; i < tam; i++){
        matriz[i] = (int *) calloc(tam, sizeof(int)); 
    }

        for (int i = 0 ; i < tam ; i++ ) //i para las filas de la matriz resultante
    {
        for (int k = 0 ; k < tam ; k++ ) // k para las columnas de la matriz resultante
        {
            p.matriz = matriz;
            p.i = i;
            p.k = k;
            pthread_t hilo;
            pthread_create(&hilo,NULL, &multiFilaCol, ( void *) &p );
            pthread_join(hilo,NULL);
        }
    }
    return matriz;
}


int MatrixT (int tam)
{   
    double promedioTiempo = 0.0;
        
    for (int i = 0; i < 100; i++)
    {
    int **matriz1, **matriz2, **matrizFinal;

    double tiempo= 0.0;
    matriz1 = generarMatriz(tam);
    matriz2 = generarMatriz(tam);
    //clock_t inicio = clock();
    time_t inicio =  time(NULL);
    matrizFinal = multiMatriz(matriz1,matriz2, tam);
    //clock_t fin= clock();
    time_t fin =  time(NULL);
    promedioTiempo += fin - inicio;
    guardarMatrix(matrizFinal, i, tam);
    guardarTiempos(fin - inicio);

    }
    guardarTiempos(promedioTiempo/100);

}


 
int main(void){
    int tam;
    printf("Ingrese el tamaño de la matriz: ");
    scanf("%d", &tam);  
    MatrixT(tam);


return 0;
}
