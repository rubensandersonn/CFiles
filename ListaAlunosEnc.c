#include <stdio.h>
#include <stdlib.h>

/*
	Rubens anderson de sousa silva, Tarefa 9
*/


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

Lista* cria_lista(void){
    return NULL;
}


Lista* aloca_novo(void){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL){
        printf("Erro na criação de novo elemento");
    }
    return novo;
}

Aluno criaNovo(){
    Aluno novo;
    printf("\nDigite a matricula do aluno: ");
    scanf("%d",&novo.matricula);
	getchar();
    printf("Digite o nome do Aluno: ");
    gets(novo.nome);
	printf("Digite o nnumero de faltas do aluno: ");
    scanf("%d",&novo.faltas);
	printf("Digite a nota 1 do aluno: ");
    scanf("%d",&novo.notas[0]);
	printf("Digite a nota 2 do aluno: ");
    scanf("%d",&novo.notas[1]);
	printf("Digite a nota 3 do aluno: ");
    scanf("%d",&novo.notas[2]);
	
    return novo;
}

void imprime(Aluno Aa){
    printf(" Aluno %s: matricula: %d, faltas: %d. \n notas:\n	%d , %d , %d\n\n", Aa.nome, Aa.matricula, Aa.faltas, Aa.notas[0], Aa.notas[1], Aa.notas[2]);
}

Lista* insere_inicio(Lista* lst, Aluno Aa){
    Lista* novo = aloca_novo();
    if (novo == NULL) {
        return lst;
    }
    novo->info = Aa;
    novo->prox = lst;
    return novo;
}


Lista* insere_fim(Lista* lst, Aluno Aa){
	//essa nao faz muito sentido ser recursiva, pois se fosse iria ate o ultimo no,
		//criaria um novo, ligava e depois teria que retornar ao primeiro nó pra poder retornar o inicio da lista
	if(lista_vazia(lst)){
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return lst;
		}

		novo->info = Aa;
		novo->prox = NULL;
		
		return novo;
	}
		
	if(lst->prox == NULL){
	
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return lst;
		}

		novo->info = Aa;
		novo->prox = NULL;
		
		lst->prox = novo;
		
		return;
	}
	
	insere_fim(lst->prox, Aa);
	
	return lst;
	
}

int quantidade(Lista* lst, int qtd){
    
    if (lst == NULL){
		return qtd;
	}
	return quantidade(lst->prox, qtd + 1);
}



Lista* insere_posicao(Lista* lst, Lista *  ant, Aluno Aa, int posicao){
	
	if(lista_vazia(lst)){
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return lst;
		}

		novo->info = Aa;
		novo->prox = NULL;
		
		return novo;
	}
		
	if(lst->prox == NULL || posicao <= 1){
	
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return lst;
		}

		novo->info = Aa;
		if(ant != NULL){
			ant->prox = novo;
		}
		novo->prox = lst;
		
		
		return;
	}
	
	insere_posicao(lst->prox, lst, Aa, posicao - 1);
	
	return lst;
	
}




void imprime_lista(Lista* lst){
    
    if(lst != NULL){
        imprime(lst->info);
		imprime_lista(lst->prox);
    }
	else{
		printf("Final de lista\n");
	}
}

int lista_vazia(Lista* lst){
    return (lst == NULL);
}



Aluno buscar_lista(Lista* lst, int val){

	if(!lista_vazia(lst)){
		if(lst->info.matricula == val){
			return lst->info;
		}
		return buscar_lista(lst->prox, val);
	}

    Lista* ret;
    
	ret = aloca_novo();
	ret->info.matricula = 0;
    return ret->info;
}
int indice(Lista* lst, int val,int i){
	
    if(!lista_vazia(lst)){
        if (lst->info.matricula == val){
            return i;
        }
		return indice(lst->prox, val, i+1);
    }
	
    return -1;
}



Lista* remove_lista(Lista* lst, int val){
    if (lista_vazia(lst)){
        printf("Lista Vazia\n");
        return NULL;
    }
    Lista* ant = NULL;
    Lista* p = lst;

    while (p != NULL && p->info.matricula != val) {
        ant = p;
        p = p->prox;
    }

    if (p == NULL){
        return lst;
    }

    if (ant == NULL){
        lst = p->prox;
    } else{
        ant->prox = p->prox;
    }
    free(p);
    return lst;
}

void libera_lista (Lista* lst)
{
    Lista* p = lst;
    Lista* t = NULL;
    while (p != NULL) {
        t = p->prox;
        free(p);
        p = t;
    }
}

// nao eh possivel implementar alguns algoritmos de ordenacao pelo fato de a lista ser simplesmente encadeada. entao, usei o mais simples de todos.
 
Lista * ordenar(Lista * lst){
	if(lst == NULL){
		printf(" Lista vazia\n");
	}
	Lista * p1 = lst;
	Lista * p2;
	Lista * novo = aloca_novo();
	
	for(p1; p1 != NULL; p1 = p1->prox){
		p2 = p1->prox;
		for(p2; p2 != NULL; p2 = p2->prox){
			
			if(p2->info.matricula < p1->info.matricula){
				
				novo->info = p1->info;
				p1->info = p2->info;
				p2->info = novo->info;
				
			}
		}
	}
	return lst;
}

Lista* insere_ordenado(Lista* lst, Lista* ant, Aluno Aa){

    if(lista_vazia(lst)){
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return lst;
		}
		if(ant != NULL){
			ant->prox = novo;
		}
		novo->info = Aa;
		novo->prox = NULL;
		
		return novo;
	}
		
	if(Aa.matricula < lst->info.matricula){
	
		Lista* novo = aloca_novo();
		if (novo == NULL) {
			return;
		}

		novo->info = Aa;
		if(ant != NULL){
			ant->prox = novo;
		}
		novo->prox = lst;
		
		
		return;
	}
	
	insere_ordenado(lst->prox, lst, Aa);
	
	return lst;
}

void gerar_arquivo(Lista* lst){
	getchar();
	printf(" Digite o nome do arquivo\n");
	gets(arquivo);
	if((f = fopen(arquivo, "wb")) == NULL){
		printf(" Erro! Nao foi possivel realizar a operacao\n");
	}else{
		Lista * no, * anterior = minha_lista;
		while(anterior != NULL){
			
			fwrite(&anterior->info, sizeof(Aluno), 1, f);
			anterior = anterior->prox;
		}
	
	}
	fclose(f);
}

int main()
{
	system(" clear || cls ");
	
	FILE * f;
    int op = 0;
    int valor;
    int posicao;
    Aluno Aa;
    Lista* minha_lista = cria_lista();
	char arquivo[30];
	
    while(op!= 14){
        printf("\n1 - Insere Aluno no inicio da lista\n");
        printf("2 - Insere Aluno no final da lista\n");
        printf("3 - Insere Aluno na posicao entrada na lista\n");
		printf("4 - Insere Aluno de forma ordenada lista\n");
        printf("5 - Remove aluno da lista\n");
		printf("6 - Consultar dados do aluno.\n");
        printf("7 - Imprime lista\n");
		printf("8 - Mostrar numero de alunos cadastrados\n");
		printf("9 - Indicar o indice (posicao de um aluno na lista) de acordo com seu numero de matricula\n");
        printf("10 - Zera lista\n");
		printf("11 - Ordenar a lista de acordo com a ordem de matrícula dos alunos cadastrados\n");
		
        printf("12 - Gerar um arquivo com os dados dos alunos\n");
        printf("13 - Carregar a lista a partir de um arquivo existente\n");
		printf(" 14- Encerrar\n");
        scanf("%d",&op);
		
		
        switch (op){
            case 1 : // insere incicio
			
                Aa = criaNovo();
                minha_lista = insere_inicio(minha_lista, Aa);
                break;
            case 2 : // insere final
			
                Aa = criaNovo();
                minha_lista = insere_fim(minha_lista, Aa);
                break;
            case 3 : // insere posicao
			
                Aa = criaNovo();
                printf("\nDigite valor a posicao na lista\n");
                scanf("%d",&posicao);
                minha_lista = insere_posicao(minha_lista, NULL, Aa
                , posicao);
                break;
            case 4 : //  insere ordenado
			
                Aa = criaNovo();
                minha_lista = insere_ordenado(minha_lista,NULL, Aa);
                break;
            case 5 : // remover
			
				if (!lista_vazia(minha_lista)){
                    printf("\n Digite a matricula do aluno a remover na lista\n");
                    scanf("%d",&valor);
                    minha_lista = remove_lista(minha_lista, valor);
                } else {
                    printf("\n Lista Vazia!\n");
                }
                break;
			
            case 6 : // consultar
				printf("\n Digite a matricula do aluno a consultar na lista\n");
                scanf("%d",&valor);
                Aa = buscar_lista(minha_lista, valor);
				if(Aa.matricula != 0){
					printf(" Dados do aluno %s: matricula: %d, faltas: %d. \n notas:\n	%d , %d , %d\n\n", Aa.nome, Aa.matricula, Aa.faltas, Aa.notas[0], Aa.notas[1], Aa.notas[2]);
				}else{
					printf(" Matricula nao encontrada\n");
				}
				break;
            case 7 : // imprimir 
				if (lista_vazia(minha_lista)){
                    printf("\n Lista Vazia\n");
                } else
                    imprime_lista(minha_lista);
                break;
			 
            case 8 : // numero de alunos
                printf(" Total de alunos: %d\n", quantidade(minha_lista, 0));
                break;
				
			case 9: // indice do aluno
			
				printf(" Digite o numero de matricula do aluno a ser buscado\n");
				scanf("%d", &valor);
				valor = indice(minha_lista, valor,1);
				if(valor == -1){
					printf("\n Matricula nao encontrada\n");
				}else{
					printf("\n indice desta matricula: %d\n", valor);
				}
				valor = 0;
				break;
			case 10: // zerar lista
				if (!lista_vazia(minha_lista)){
                    libera_lista(minha_lista);
                    minha_lista = cria_lista();
                }
                break;
			
			case 11: // ordenar lista
				minha_lista = ordenar(minha_lista);
				break;
			case 12: // gerar arquivo
				
				gerar_arquivo(minha_lista);
				
				
				break;
			case 13: // carregar a partir de arquivo
				
				getchar();
				
				printf(" Digite o nome do arquivo\n");
				gets(arquivo);
				if((f = fopen(arquivo, "rb")) == NULL){
					printf(" Erro! Nao foi possivel realizar a operacao\n");
					
				}else{
					printf(" Arquivo aberto\n");
					
					Lista * no, * anterior = minha_lista;
					if(anterior != NULL){
						
						while(anterior->prox != NULL){
							anterior = anterior->prox;
						}
					
					}
					// ultimo no valido
					rewind(f);
					Aluno ant;
					while(!feof(f)){
						ant = Aa;
						fread(&Aa, sizeof(Aluno), 1, f);
						if(ant.matricula != Aa.matricula){
							minha_lista = insere_fim(minha_lista, Aa);
						}
						
					}
					printf(" Arquivo carregado\n");
				}
				
				fclose(f);
				break;
        }
    }
	gerar_arquivo(minha_lista);
	libera_lista(minha_lista);
	
    return 0;
}
