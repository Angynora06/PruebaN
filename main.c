#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int nuCapas, nuEnt, nuNeu;
FILE *f_in, *f_conf;

typedef struct
{
    int nuNeu;
    float matrizPesos  [5] [5];
    float umbral [5];

}CAPA;

typedef struct
{
      int nuCapas;
      int nuEntrada;
      CAPA capas [5];
      float entrada [5];
      float salida[5];
}PERCEPTRON;

PERCEPTRON cargaperceptron(PERCEPTRON perc, FILE *fichero)
{
       int i,j,k;
       fscanf(fichero,"%d %d", &perc.nuCapas,&perc.nuEntrada);
       printf("\nEl numero de capas es:  %d\n", perc.nuCapas);
       printf("\nEl numero de entradas es: %d\n", perc.nuEntrada);

       for(k=0;k<perc.nuCapas; k++)
        {
            printf("\n");
            fscanf(fichero, "%d", &perc.capas[k].nuNeu);
            printf("Cargando capa %d\n",k);
            printf("Numero de entradas :%d\n", perc.nuEntrada);
            printf("Numero de neuronas :%d\n", perc.capas[k].nuNeu);
            printf("Matriz de pesos:\n");
            for(j=0;j<perc.nuEntrada;j++)
                {
                    for(i=0;i<perc.capas[k].nuNeu;i++)
                        {
                            fscanf(fichero,"%f", &perc.capas[k].matrizPesos[j][i]);
                            printf("W[%d][%d]:%f\n", j,i,perc.capas[k].matrizPesos[j][i]);
                        }
                }
            printf("\nUmbrales\n");
            for(j=0;j<perc.capas[k].nuNeu;j++)
                {
                    fscanf(fichero,"%f",&perc.capas[k].umbral[j]);
                    printf(" Umbral[%d] : %f\n", j, perc.capas[k].umbral[j]);
                }
            printf("\n");

        }
        return(perc);

}
  int cuentaentradas(FILE *fichero)
  {
      int aux=0;
      char filas[26];

      while(fgets(filas,26,fichero))
        aux++;
      return(aux);
  }

   PERCEPTRON procesamiento(PERCEPTRON perc, int c)
   {
       int i,j,k;
       float suma;
       if(!c)
        {
            for(j=0;j<perc.nuEntrada;j++)
                {
                    perc.salida[j] = perc.entrada[j];
                }
        }
       for(i=0;i<perc.capas[c].nuNeu;i++){
        for(j=0;j<perc.nuEntrada;j++){
            for(k=0, suma=0;k<perc.capas[c].nuNeu;k++) {
                suma += perc.salida[i] * perc.capas[c].matrizPesos[j][k];
            }
        }
        perc.salida[i] = suma;
       }

        for(j=0;j<perc.capas[c].nuNeu;j++){
        perc.salida[j] = perc.salida[j] - perc.capas[c].umbral[j];
        }
        for(j=0;j<perc.capas[c].nuNeu;j++){
        perc.salida[j] = 1/(1+expf((-20)*perc.salida[j]));
        }
        for(k=0;k<5;k++)
        perc.entrada[k] = perc.salida[k];
        return(perc);


   }


int main(){
    PERCEPTRON perc;
    FILE *fichero;
    int i, j, k, nuEnt;
    if(!(fichero=fopen("configuracion.txt","rb"))){
        printf("ERROR EN LA APERTURA DEL FICHERO. (1)\n");
        return(1);
    }

    printf("CARGA DEL PERCEPTRON\n");
    printf("====================\n");
    perc=cargaperceptron(perc, fichero);
    fclose(fichero);
    if(!(fichero=fopen("entrada.txt","rb"))){
        printf("ERROR EN LA LECTURA DEL FICHERO DE ENTRADAS. (2)");
        return(2);
    }
    nuEnt=cuentaentradas(fichero);
    rewind(fichero);


    printf("EJECUCION DEL PERCEPTRON\n");
    printf("========================\n");

    for(i=0;i<nuEnt;i++){
        for(j=0;j<perc.nuCapas;j++){
            if(!j){
                printf("ENTRADA : (");
                for(k=0;k<perc.nuEntrada-1;k++){
                    fscanf(fichero,"%f", &perc.entrada[k]);
                    printf("%f, ", perc.entrada[k]);
                }
                fscanf(fichero,"%f", &perc.entrada[k]);
                printf("%f)\t - > \t", perc.entrada[k]);
            }

            perc=procesamiento(perc, j);
            if(j==perc.nuCapas-1){
                printf("SALIDA : (");
                for(k=0;k<perc.capas[j].nuNeu-1;k++)
                    printf("%f, ", perc.salida[k]);
                printf("%f)\n", perc.salida[k]);
            }



        }
    }

}
