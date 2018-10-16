#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "scan.h"

// variaveis globais
int linha = 1;
int coluna = 1;
char look; // proximo caractere em look
char token[256];
int ntoken = 0;
Tk *TkList;


// funções locais
FILE *abreArq(char *nome);
void nextChar(FILE *p);
void scan(FILE *P);
void skipWhite(FILE *p);
void newLine(FILE *p);
void getWord(FILE *p);
void getNum(FILE *p);
void getOp(FILE *p);
void skipComment(FILE *p);
void getOp(FILE *p);
int isOp(char c);
int isKeys(char c);
void getNum(FILE *p);
void criarElementoTk();
void limparToken();

/***********************************************
 * Nome: getTokens
 * desc: obtém todos os tokens do arquivo nome
 * returno: ponteiro para a lista de tokens
 ***********************************************/
Tk *getTokens(char *nome)
{
    TkList=NULL;
    FILE *p;
    p = abreArq(nome); // o aruivo é atribuido à p, p recebe o conteúdo do arquivo
    nextChar(p);
    while (!feof(p))
    {
        scan(p); // Nesta linha, vai ter um token em token
    }
    return TkList;
}

/*********************************
 * Nome: scan
 * desc:
 * returno:
 ********************************/
void scan(FILE *p)
{
    limparToken();


    if (look == ' ' || look=='\t' )
    {
        skipWhite(p);
    }

    if (look == '\n' || look==13 )
    {
        newLine(p);
    }

    //Verifica se é letra
    if  ((look > 64 && look <91) || (look >96 && look < 123 ))
    {
        // Obtem-se a palvara inteira
        getWord(p);
        criarElementoTk();
    }
    //Verifica se é um operador
    if(isOp(look)){
        getOp(p);
        criarElementoTk();
    }

    if(isKeys(look)){
        getOp(p);
        criarElementoTk();
    }
    // Avança para o próximo Caractere
    nextChar(p);

}

/*********************************
 * Nome: abreArq
 * desc:
 * returno:
 ********************************/
FILE *abreArq(char *nome)
{
    char *var;
    FILE *in;
    // aqui tem um exemplo do uso da função strstr

    var = strstr(nome,".c");
    if(var == NULL)
    {
        printf("Arquivo : %s invalido!\n",nome);
        exit(1); // Cada erro será tratado com uma saída diferente de 0.
    }
    in = fopen(nome,"r");
    if(in == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s \n",nome);
        exit(3);
    }
    return in;
}

void criarElementoTk(){
    //Aqui é criado um novo endereço para aramazenamento do token
    Tk *elemento=NULL;
    char *str;
    str = (char*) malloc(sizeof(char)* strlen(token)+1);
    strcpy(str,token);
    elemento = (Tk*) malloc(sizeof(Tk));
    elemento ->nome = str;
    elemento ->linha = linha;
    elemento ->coluna = coluna++;
    elemento -> id = ntoken++;
    elemento -> prox= NULL;
    // Inserindo o token
    insereTk(elemento);
}


/*********************************
 * Nome: insereTk
 * desc:
 * returno: void
 ********************************/
void insereTk( Tk *TkElemento)
{

    Tk *ptr;
    if (TkList == NULL){
        TkList = TkElemento;
    }
    else {
        //Está apontando para o primeiro item de TkList
        ptr = TkList;
        while(ptr->prox != NULL){
            //Percorre TkList até encontrar o ptr apontando para NULL
            ptr = ptr -> prox;
        }
        // Adiciona o elemento em TkList
        ptr->prox = TkElemento;
    }

}

/*********************************
 * Nome: exibeTk
 * desc:
 * returno: void
 ********************************/
void exibeTk(Tk *TkList)
{
    Tk *ptr;

    printf("\n\t================================= INFORMA%c%cES DOS TOKEN's =================================\n",128,229);
    for (ptr = TkList; ptr!=NULL; ptr = ptr -> prox)    {
        printf("\n\t\t\t\t\t\tToken '%s' \n",ptr->nome);
              printf("\n\t\t\t\t\t%c",245);printf("\tId: %d\t", ptr->id); printf("\t%c",245);
              printf("\n\t\t\t\t\t%c",245);printf("\tValor: %s", ptr->nome); printf("\t%c\n",245);
    }
    printf("\n\t================================================================================================\n");

}

/*********************************
 * Nome: removeTk
 * desc:
 * returno: void
 ********************************/
void liberaTk(Tk *TkList)
{
    Tk *T,*ptr;

}

/*********************************
 * Nome: buscaTk
 * desc:
 * returno: void
 ********************************/
void removeTk(Tk *TkList, int chave)
{

}

/*********************************
 * Nome: nextChar
 * desc:
 * returno:
 ********************************/
void nextChar(FILE *p)
{
    if(look !=EOF) // EOF --> End Of File
    {
        look = getc(p);
    }
}

/*********************************
 * Nome: removeSpace
 * desc:
 * returno:
 ********************************/
void skipWhite(FILE *p)
{
    while (look == ' ' || look == '\t'){
        // Realiza a contagem de uma nova coluna
        coluna++;
        nextChar(p);
    }
}

/*********************************
 * Nome: removeSpace
 * desc:
 * returno:
 ********************************/
void newLine(FILE *p)
{
    // Zera as colunas da nova linha
    coluna = 1;
    while (look == '\n' || look == 13)
    {
        nextChar(p);
        if (look == '\n' || look == 13){
            linha++;
        }
    }

}

/*********************************
 * Nome: skipComment
 * desc:
 * returno:
 ********************************/
void skipComment(FILE *p)
{
    ntoken++;
}

/*********************************
 * Nome: getNum
 * desc:
 * returno:
 ********************************/
void getNum(FILE *p)
{
    int i;

}

/*********************************
 * Nome: getWord
 * desc:
 * returno:
 ********************************/
void getWord(FILE *p)
{
    int i = 0;
    int isWord = 1;
    while (isalnum(look)|| look=='_')
    {
        token [i] = look;
        nextChar(p);
        i++;
    }
    token [i] ='\0'; // ATENÇÃO: Sempre é necessário adicionar o '/0' após obeter a palavra para sinalizar onde ela termina. Caso contrário poderá ter problemas.
}

/*********************************
 * Nome: getOp
 * desc:
 * returno:
 ********************************/
void getOp(FILE *p)
{
    limparToken();
    int i =0;
    token[i] = look;

}

/*********************************
 * Nome: limparToken
 * desc:
 * returno:
 ********************************/
void limparToken(){
    memset(token, 0, 255);
}

/*********************************
 * Nome: isOp
 * desc:
 * returno:
 ********************************/
int isOp(char c)
{
    return (strchr("#.+-*/<>:=!", c) != NULL); //Returns a pointer to the first occurrence of character in the C string str.
}

int isKeys(char c)
{
    return (strchr("{}[]()\"", c) != NULL); //Returns a pointer to the first occurrence of character in the C string str.
}

