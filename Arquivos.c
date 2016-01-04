#include <stdlib.h>
#include <stdio.h>
#include "Arquivos.h"

//Change the filename between "" to read another file
//Troque o nome do arquivo entre "" para ler outro arquivo
#define Arquivo "Dom48x48.txt"

//Marks the flag array according to file
//Marca a matriz de flags de acordo com o arquivo
void Marcar(int **flag, char**flagchar,int iM, int jM){
    int i, j;
        for (i=0; i<=iM; i++) {
              for (j = 0; j<=jM; j++){

               if (flagchar[i][j]=='w'){
                    flag[j][iM-i]=3;
               }
               if (flagchar[i][j]=='s'){
                    flag[j][iM-i]=2;
               }
               if (flagchar[i][j]=='x'){
                    flag[j][iM-i]=10;
               }
               if (flagchar[i][j]=='d'){
                    flag[j][iM-i]=8;
               }
               if (flagchar[i][j]=='e'){
                    flag[j][iM-i]=1;
               }
               if (flagchar[i][j]=='y'){
                    flag[j][iM-i]=5;
               }
               if (flagchar[i][j]=='i'){
                    flag[j][iM-i]=4;
               }
               if (flagchar[i][j]=='z'){
                    flag[j][iM-i]=12;
               }
               if (flagchar[i][j]=='.'){
                    flag[j][iM-i]=0;
               }
               //fprintf(stderr, "%c", M[i][j]);
               //printf("\n");
            }
        }
    }

//Reads the problem dimension from file
//Lê dimensão do problema a partir do arquivo
char** leArquivoDim(void){

        FILE *geometria;
        geometria = fopen(Arquivo, "r");

        int interioresCol=0, interioresLin=0, contt=0;

        int ch, n=0, cont=0,tam, i, j, k;

        if (geometria == NULL){
            printf("Erro\n");
            return NULL;
        }

        while ((ch = fgetc(geometria) != EOF)){
           cont++;
        }

        tam = cont;
        char *flagfile = (char*) calloc(tam, sizeof(char));
        rewind(geometria);

        printf("Geometria lida:\n\n");

        for(i=0; i<tam; i++)
           fscanf(geometria, "%c ", &flagfile[i]);

        j=0;i=0;
        for(k=0; k<tam; k++){

            if (contt==0 && flagfile[k]!=' ' && flagfile[k]!='l'){
                    interioresCol=interioresCol+1;
            }

           if (flagfile[k]=='l'){
                interioresLin=interioresLin+1;

                contt=1;

                j=0;
                i=i+1;
                printf("\n");
           }
           else{

               fprintf(stderr, "%c", flagfile[k]);
               j=j+1;
           }
           iM=interioresLin;
           jM=interioresCol;
        }
        fclose(geometria);
    }

//Reads file
char** leArquivo(void){
        FILE *geometria;
        geometria = fopen(Arquivo, "r");
        int i, j;

        char **flagchar;
        flagchar=CharMatriz(iM+1,jM+1);

        for (i = 0; i <= iM; i++) {
          for (j = 0; j <= jM; j++)
                flagchar[i][j] = 'o';
        }

        int interioresCol=0, interioresLin=0;

        int ch, n=0, cont=0,tam, k;

        if (geometria == NULL){
            printf("Erro\n");
            return NULL;
        }

        while ((ch = fgetc(geometria) != EOF)){
           cont++;
        }

        tam = cont;
        char *flagfile = (char*) calloc(tam, sizeof(char));
        rewind(geometria);

        for(i=0; i<tam; i++)
           fscanf(geometria, "%c ", &flagfile[i]);

        j=0;
        i=0;
        for(k=0; k<tam; k++){

            if (flagfile[k]!=' ' && flagfile[k]!='l'){

                    flagchar[i][j]=flagfile[k];

                    if (flagfile[k+1]=='l'){
                        flagchar[i][j]=flagfile[k];
                        j=0;
                        i=i+1;
                    }

                    j=j+1;
            }
            else{
                    j=0;
            }

            if (flagfile[k]=='f'){
                printf("\n\nfim\n lidos %d caracteres do arquivo\n\n",k);
                break;
           }
        }

        printf("\nMatriz de Flags inteira\n\n");
        Marcar(flag,flagchar,iM-1,jM-1);
        ImprimeFlag(flag,iM-1,jM-1);

        fclose(geometria);
    }

//Writes file with the results
//Escreve arquivo com os resultados
char** escreveArquivo(double **u, double **v){


        int i, j;

        FILE *saida;
        saida = fopen("SAIDA.txt", "w");

        if (saida == NULL){
            printf("Erro\n");
            return NULL;
        }

        fprintf(saida,"U=[");
        for (i = 0; i <iM+1; i=i+1) {
          for (j = 0; j <jM; j=j+1){
           if(j==0){
            fprintf(saida, "0 ");
           }


           fprintf(saida, "%.8lf ", u[i][j]);
          }
          fprintf(saida," 1;\n");
          }

        fprintf(saida,"]\n\n");

        fprintf(saida,"V=[");
        for (i = 0; i<iM+1; i=i+1) {
          for (j = 0; j<jM+1; j=j+1){

            if(i==0){
                fprintf(saida, "0 ");
            }
            else{
                fprintf(saida, "%.8lf ", v[i-1][j]);
            }

            }
            fprintf(saida,";\n");
            }
         for (j = 0; j<jM+1; j=j+1){
            fprintf(saida, "0 ");
         }
         fprintf(saida,";\n");
         fprintf(saida,"]\n\n");

       fclose(saida);

    }
