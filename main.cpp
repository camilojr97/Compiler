#include <iostream>
#include <list>
#include<stdio.h>
#include<string.h>
#include"scan.h"
#include <stdlib.h>

using namespace std;
void analiseLexica();
void loadId();

Tk* Lista;
list <Tk*> simbolos;
list <Tk*> pReservadas;
list <Tk*> listId;
int contId;
//extern Tk *getTokens(char *nome);
/*********************************
 * Nome: main
 * desc:
 * returno:
 ********************************/
int main(int argc, char *argv[])
{

    //simbolos.push_back();

    //Tk *Lista;
    contId = 0;
    char nome [50];

    if (argc ==2)
    {
        strcpy (nome, argv[1]);
    }else
    {
        printf("Enter file name: ");
        scanf("%s",nome);
    }
    Lista = getTokens(nome);
    exibeTk(Lista);
    loadId();
    analiseLexica();

    return 0;
}

void analiseLexica(){
    //list <Tk*>::iterador it;

    Tk *list;

    for(list = Lista; list != NULL; list=list->prox){

    }

}


void loadId(){

    char nome[][15]={"int","char","float","double","short","long"};
    Tk *l;

    for(int i=0;i<6;i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome,nome[i]);
        l->id = contId;
        contId++;
        simbolos.push_front(l);
    }
    //pReservadas;


}
void loadRd(){

    char nome[][15]={"do","if","for","switch"};
    Tk *l;

    for(int i=0;i<6;i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome,nome[i]);
        l->id = contId;
        contId++;
    }
    //pReservadas;


}
