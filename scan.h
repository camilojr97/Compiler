#include<stdio.h>

#ifndef SCAN_H
#define SCAN_H

// declara��o de constantes
#define MAXNUM 9
#define MAXOP 2
#define MAXNAME 255



// declara�� de tipos

typedef struct tokens{
int id;
int linha;
int coluna;
char *nome;
struct tokens *prox;
}Tk;


// declara��o das fun��es globais
Tk *getTokens(char *nome);
void insereTk(Tk *elemento );
void exibeTk(Tk *TkList);
void removeTk(Tk *TkList, int chave);
void liberaTk(Tk *TkList);
void buscaTk(char *var);

#endif
