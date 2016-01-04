#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED

extern int iM; extern int jM; extern int **flag;

void Marcar(int **flag, char**flagchar,int iM, int jM);
char** leArquivo(void);
char** leArquivoDim(void);
char** escreveArquivo(double **u, double **v);

#endif
