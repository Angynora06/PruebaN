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
       fscanf(fich,"%d %d", &perc.nuCapas,&perc.NuEntrada);
       printf("\nEl numero de capas es:  %d\n", perc.nuCapas);
       printf("\nEl numero de entradas es: %d\n", perc.nuEntrada);

       for(k=0;k<perc.nuCapas; k++)
        {
            printf("\n");
            fscanf(fich, "%d", &perc.capa[k].nuNeu);
            printf("Cargando capa %d\n",k);
            printf("Numero de entradas :%d\n", perc.nuEntrada);
            printf("Numero de neuronas :%d\n", perc.capa[k].nuNeu);
            printf("Matriz de pesos:\n");
            for(j=0;j<perc.nuEntrada;j++)
                {
                    for(i=0;i<perc.capa[k].nuNeu;i++)
                        {
                            fscanf(fich,"%f", &perc.capa[k].pesos[j][i]);
                            printf("W[%d][%d]:%f\n", j,i,perc.capa[k].pesos[j][i]);
                        }
                }
            printf("\nUmbrales\n");
            for(j=0;j<perc.capa[k].nuNeu;j++)
                {
                    fscanf(fich,"%f",&perc.capa[k].umbral[j]);
                    printf(" Umbral[%d] : %f\n", j, perc.capa[k].umbral[j]);
                }
            printf("\n");

        }
        return(perc);

 float f(float x)
    return(1/(1+expf(-20*x)));
}
  int cuentaentradas(File *fichero)
  {
      int aux=0;
      char filas[26];

      while(fgets(linea,26,fich))
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
       for(i=0;i<perc.capa[c].nuNeu;i++){
        for(j=0;j<perc.nuEntradant;j++){
            for(k=0, suma=0;k<perc.capa[c].nuNeu;k++) {
                suma += perc.salida[i] * perc.capa[c].pesos[j][k];
            }
        }
        perc.salida[i] = suma;
       }

        for(j=0;j<perc.capa[c].nuNeu;j++){
        perc.salida[j] = perc.salida[j] - perc.capa[c].umbral[j];
        }
        for(j=0;j<perc.capa[c].nuNeu;j++){
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
    if(!(fich=fopen("configuracion.txt","rb"))){
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
                for(k=0;k<perc.nuEnt-1;k++){
                    fscanf(fich,"%f", &perc.entrada[k]);
                    printf("%f, ", perc.entrada[k]);
                }
                fscanf(fich,"%f", &perc.entrada[k]);
                printf("%f)\t - > \t", perc.entrada[k]);
            }

            perc=proceso(perc, j);
            if(j==perc.nuCapas-1){
                printf("SALIDA : (");
                for(k=0;k<perc.capa[j].nuNeu-1;k++)
                    printf("%f, ", perc.salida[k]);
                printf("%f)\n", perc.salida[k]);
            }



        }
    }

}
