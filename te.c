#include <stdio.h>
#include <stdlib.h>

struct aluno{
    int matricula;
	int notas[3];
	int faltas;
    char nome[30];
};

typedef struct aluno Aluno;


struct lista {
   Aluno info;
   struct lista* prox;
};

typedef struct lista Lista;

Lista* aloca_novo(void){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL){
        printf("Erro na criação de novo elemento");
    }
    return novo;
}

void main(){
	Lista * l = aloca_novo();
	printf("%d\n", l->info.matricula);
}