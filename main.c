#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int nuCapas, nuEnt, nuNeu;
FILE *f_in, *f_conf;

typedef struct
{
    int nuNeu;
    float entrada [5];
    float matrizPesos  [5] [5];
    float umbral [5];

}CAPA;

typedef struct
{
      CAPA capas [5];
      float entrada [5];
      float resultado [5]
}PERCEPTRON;

PERCEPTRON perc;

double expo(double exponente)
{
    int i;
    double resultado = 1;
    for(i=0;i<exponente;i++){
        resultado = M_E * resultado;
    }

    return(resultado);
}
 CAPA carga_capa()
 {
     CAPA res;
     fscanf(f_conf, "%d", &res.nuNeu);
     printf("\nCargando capa\n");
     int j,k;
     printf(" Numero de entradas: %d\n", nuEnt);
     printf(" Numero de neuronas: %d\n", res.nuNeu);
     for(j=0;j<nEnt;j++){
        for(k=0;k<res.nuNeu;k++){
        fscanf(f_conf, "%6f", &res.matrizPesos[j][k]);
        printf("w[%d][%d]=%6f\n", j,k, res.matrizPesos[j][k]);
        }
     }
     printf("\nUmbrales\n");
     for(j=0;j<res.nNeu;j++){
        fscanf(f_conf, "%6f", ¬res.umbral[j]);
        printf("umbral[%d]=%6f\n",j,res.umbral[j]);
     }
     return res;
 }

 void tratar_capa(int n){
 int j;
 for(j=0;j<nuNeu;j++){
    int k;
    float suma;
    for(k=0;k<nent;k++){
        suma +=perc.resultado[j] * perc.capas[n].matriz[j][k];
    }
    perc.resultado[j] =1/(1 + expo((-20) * (suma - perc.capas[n].umbral[j])));
 }
   if(n==ncapas-1){
    printf("Entrada: ("); //Por que es asi?
    for(j=0;j<nEnt-1;j++){
    printf("%6f, ", perc.entrada[j]);
    }
     printf("%6f)     ->      Salida: (", perc.entrada[j]);
    for(j=0;j<nuNeu-1;j++){
        printf("%6f, ", perc.entrada[j]);
    }
     return:
}

int main()
 {
     if(!(f_conf=fopen("configuracion.txt", "rb"))){
        printf("\nError en la lectura del fichero (1)");
        return(1);
     }
     if(!(f_in=fopen("entrada.txt", "rb"))){
        printf("\nError en la lectura del fichero(2)");
        fclose(f_conf);
        return(2);
     }//Se han abierto ambos ficheros

      printf("Carga del Perceptron\n");
      printf("====================\n");
      fscanf(f_conf,"%d %d", &ncapas, &nuEnt);
      printf("Numero Capas: %d\n", ncapas);
      printf("Numero de Entradas: %d\n", nuEnt);






      int j;
      char linea[512];

      for(j=0;j<ncapas;j++){
        perc.capas[j] = carga_capa();
      }
      printf("\n \n \n \nEjecucion del Perceptron\n");
      printf("======================\n");
      while(fgets(linea,sizeof(linea),f_in) != NULL){
        for(j=0;j<nuEnt;j++){
            fscanf(f_in,"%2f", &perc.entrada[j]);
            perc.resultado[j] = perc.entrada[j];
        }
        for(j=0; j<ncapas;j++){
            tratar_capa(j);
        }


        fclose(f_in);
        fclose(f_conf);
      }














 }

