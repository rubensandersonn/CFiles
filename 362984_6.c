#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// compilou as 22:42 de terça feira. 

typedef struct aluno{
	char nome[20];
	int matricula;
	int notas[3];
	int faltas;
	int existe;
}Aluno;


int totalAlunos = 0;
int alunosValidos = 0;


// funcao reordena

FILE * reordena(char arquivo[20]){
	
	FILE * f;
	
	Aluno guy;
	int modo = 0;
				
	while(modo < 1 || modo > 3){
		printf(" Qual o Modo de ordenacao?\n 1 - ordem alfabetica;\n 2 - numeros de matricula crescentes\n 3 - Mediaa das notas crescentes\n");
		scanf("%d", &modo);
	}

	int i = 0;
	int posBest = 0;

	float best;
	float curr;

	char nomeCurr[20];
	char nomeBest[20];

	

	int j = 0;
	if((f = fopen(arquivo, "r+b")) == NULL){
		printf(" Erro! Nao foi possivel realizar a operacao\n");
		
	}else{
		printf(" arquivo aberto\n");
		
		// Total alunos eh a ultima posicao do arquivo que contem cras desorganizados.
		// j é o numero de alunos organizados
		// ao final, o arquivo deve conter no maximo 2 * totalAlunos alunos.
		strcpy(nomeBest,"zzzzzzzzzzzz");
		best = 9999999;
		
		
		while(j <= totalAlunos){
			
			i = 0;
			
			
			rewind(f);
			while(!feof(f) && i <= totalAlunos){
				
				fread(&guy, sizeof(Aluno), 1, f);
				
				strcpy(nomeBest,"zzzzzzzzzzzz");
				best = 9999999;
				
				if(guy.existe){
					
					
					printf(" Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
			
					
					switch(modo){
						// um modo de fazer: pegar cada aluno ja ordenado e colocar no fim do arquivo. depois, colocar os alunos ordenados em cima dos nao ordenados.
						
						case 1:
							// alfabetica, esse vai ter que ser separado.
							if(strcmp(nomeCurr, nomeBest) < 0){
								strcpy(nomeBest, nomeCurr);
								posBest = i;
							}
							break;
						
						case 2:// matriculas
							curr = (float) guy.matricula;
							break;
						case 3:// medias
							curr = (float) (guy.notas[0] + guy.notas[1] + guy.notas[2]) / 3 ;
							break;
					}
					
					if(curr < best && modo != 1){
						best = curr;
						posBest = i;
					}
				}
				i++;
			}
			
			// AQUI QUE DEU PAU. MELÇHORAR AMANHA!
			// colocando o aluno melhor ordenado no fim do arquivo.
			rewind(f);
			fseek(f ,(posBest) * sizeof(Aluno), SEEK_SET);
			fread(&guy, sizeof(Aluno), 1, f);
			guy.existe = 0;
			
			printf("\n o melhor: Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
			
			fseek(f ,(posBest) * sizeof(Aluno), SEEK_SET);
			fwrite(&guy, sizeof(Aluno), 1, f);
			
			// o melhor nao existe mais nos desorganizados.
			
			guy.existe = 1;
			
			fclose(f);
			
			f = fopen(arquivo, "ab");
			fwrite(&guy, sizeof(Aluno), 1, f);
			
			// o melhor foi adicionado no fim do arquivo.
			
			fclose(f);
			f = fopen(arquivo, "r+b");
			
			j++;
		}
		
		// limpando a bagunça
		// j <= totalAlunos
		
		i = 0;
		totalAlunos = j;
		
		while(i <= j){
			
			fseek(f, (j + i + 1) * sizeof(Aluno), SEEK_SET);
			fread(&guy, sizeof(Aluno), 1, f);
			
			fseek(f, (i) * sizeof(Aluno), SEEK_SET);
			fwrite(&guy, sizeof(Aluno), 1, f);
			
			i++;
		}
	}
	return f;
}

// aqui comeca a main!



void main(){
	system(" cls || clear");
	
	Aluno guy;
	
	
	FILE * f;
	char arquivo[20];
	
	int opcao = -1;
	
	int i = 0;
	
	printf("\n Entre com o nome do arquivo\n");
	gets(arquivo);
	
	int mat = -1;
	if((f = fopen(arquivo, "r+b")) == NULL){
		printf(" erro ao ler o arquivo.\n");
		f = fopen(arquivo, "wb");
		
	}else{
		printf(" arquivo valido\n");
		
		// aqui, vemos claramente uma gambiarra para tapar o buraco do erro do feof
		/*
		
		guy.existe = 0;
		strcpy(guy.nome, "nulo");
		
		fseek(f,0,SEEK_END);
		fwrite(&guy, sizeof(Aluno), 1, f);
		*/
		
		while(!feof(f)){
			fread(&guy, sizeof(Aluno), 1, f);
			totalAlunos++;
			if(guy.existe == 1){
				alunosValidos++;
			}
		}
		
	}
	// SEMPRE VAI OCORRER ERRO NA CONTAGEM DE ALUNOS POR CAUSA DO !FEOF(F) QUE NAO FAZ O QUE DEVIA...
	totalAlunos = totalAlunos - 1;
	
	printf(" Total de alunos existentes: %d\n", totalAlunos);
	
	while(opcao != 0){
		printf("\n Digite a opcao desejada.\n 1 - Inserir novo aluno\n 2 - excluir aluno\n 3 - alterar dados do aluno\n 4 - consultar dados do aluno\n 5 - reordenar arquivo\n 6 - Listar alunos\n 7 - Imprimir relatorio\n 0 - Sair\n\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				printf(" Inserir Aluno\n");
				// Insere um registro de aluno no fim do documento
				
				if((f = fopen(arquivo, "r+b")) == NULL){
					printf(" Erro! arquivo invalido\n");
					exit(1);
				}
				
				
				printf(" Digite a matricula do aluno\n");
				scanf("%d", &mat);
				rewind(f);
				while(!feof(f) && mat != guy.matricula){
					fread(&guy, sizeof(Aluno), 1, f);
					
				}
				
				if(mat == guy.matricula){
					printf(" Matricula %d ja existe!\n", guy.matricula);
				}else{
					
					guy.matricula = mat;
					getchar();
					printf(" Digite o nome do aluno\n");
					gets(guy.nome);
					
					printf(" Digite a nota 1 do aluno\n");
					scanf("%d", &guy.notas[0]);
					
					printf(" Digite a nota 2 do aluno\n");
					scanf("%d", &guy.notas[1]);
					
					printf(" Digite a nota 3 do aluno\n");
					scanf("%d", &guy.notas[2]);
					
					printf(" Digite o numero de faltas do aluno\n");
					scanf("%d", &guy.faltas);
					
					guy.existe = 1;
					
					
					// aqui que mora o problema!
					rewind(f);
					fseek(f, 0, SEEK_END);
					fwrite(&guy, sizeof(Aluno), 1, f);
					
					if(ferror(f)){
						printf(" Erro na gravação do arquivo!\n");
					}
					else{
						totalAlunos++;
						alunosValidos++;
						printf(" Aluno Inserido com sucesso!\n\n");
					}
				}
				
				fclose(f);
				break;
				
			case 2:
				printf(" excluir Aluno\n");
				
				
				if((f = fopen(arquivo, "r+b")) == NULL){
					printf(" Erro! arquivo invalido\n");
					exit(1);
				}
				rewind(f);
				
				
				printf(" Digite a matricula do aluno a ser removido\n");
				scanf("%d", &mat);
				
				i = 0;
				
				while(!feof(f) && guy.matricula != mat){
					// Eu sei, aqui ha um codigo supérfluo, mas EU NAO CONFIO NO C! :)
					fseek(f, sizeof(Aluno) * (i), SEEK_SET);
					fread(&guy, sizeof(Aluno), 1, f);
					i++;
				}
				if(guy.matricula != mat){
					printf(" Aluno nao encontrado\n");
				}else{
					
					printf(" Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
					guy.existe = 0;
					
					rewind(f);
					
					// aqui, nao sei POR QUE FUNCIONA! MAS FUNCIONA
					// AQUI QUE MORA O PROBLEMA 2! QUANDO EU COLOCO i ELE NAO EXCLUI O PENULTIMO (ALVO), E SIM O ULTIMO. QUANDO COLOCO O i - 1 ELE NAO EXCLUI O ULTIMO (ALVO), E SIM O PENULTIMO!
					// DEIXEI i - 1 PORQUE DA MENOS PROBLEMAS! ELE EXCLUI CORRETAMENTE QUALQUER UM, EXCETO O ULTIMO.
					
					fseek(f, sizeof(Aluno) * (i -1), SEEK_SET);
					
					fwrite(&guy, sizeof(Aluno), 1,f);
					alunosValidos--;
					printf(" Aluno removido!\n\n");
				}
				fclose(f);
				 break;
			case 3:
				printf(" alterar dados do Aluno\n");
				
				
				
				if((f = fopen(arquivo, "r+b")) == NULL){
					printf(" Erro! arquivo invalido\n");
					exit(1);
				}
				rewind(f);
				
				
				printf(" Digite a matricula do aluno a ser ALTERADO\n");
				scanf("%d", &mat);
				
				i = 0;
				while(!feof(f) && guy.matricula != mat){
					// Eu sei, aqui ha um codigo supérfluo, mas EU NAO CONFIO NO C! :)
					//fseek(f, sizeof(Aluno) * (i), SEEK_SET);
					fread(&guy, sizeof(Aluno), 1, f);
					
					i++;
				}
				
				if(guy.matricula != mat){
					printf(" Aluno nao encontrado\n");
				}else if(guy.existe){
					
					fseek(f, sizeof(Aluno) * (i), SEEK_SET);
					fread(&guy, sizeof(Aluno), 1,f);
					
					printf(" Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
					getchar();
					printf(" Digite o nome do aluno\n");
					gets(guy.nome);
					
					printf(" Digite a nota 1 do aluno\n");
					scanf("%d", &guy.notas[0]);
					
					printf(" Digite a nota 2 do aluno\n");
					scanf("%d", &guy.notas[1]);
					
					printf(" Digite a nota 3 do aluno\n");
					scanf("%d", &guy.notas[2]);
					
					printf(" Digite o numero de faltas do aluno\n");
					scanf("%d", &guy.faltas);
					
					fseek(f, sizeof(Aluno) * (i), SEEK_SET);
					fwrite(&guy, sizeof(Aluno), 1,f);
					
					printf(" Aluno alterado!\n\n");
				}else{
					printf(" Este aluno nao faz parte da turma\n");
				}
				
				fclose(f);
				
				
				break;
			case 4:
				printf(" consultar dados do Aluno\n");
				
				
				
				if((f = fopen(arquivo, "rb")) == NULL){
					printf(" Erro! arquivo invalido\n");
					exit(1);
				}
				rewind(f);
				
				
				printf(" Digite a matricula do aluno a ser consultado\n");
				scanf("%d", &mat);
				
				i = 0;
				while(!feof(f) && guy.matricula != mat){
					// Eu sei, aqui ha um codigo supérfluo, mas EU NAO CONFIO NO C! :)
					//fseek(f, sizeof(Aluno) * (i), SEEK_SET);
					fread(&guy, sizeof(Aluno), 1, f);
					i++;
				}
				
				if(guy.matricula != mat){
					printf(" Aluno nao encontrado\n");
				}else{
					
					printf(" Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
					if(!guy.existe){
						printf(" Aviso: Este aluno nao faz parte da turma\n");
					}
				}
				fclose(f);
				
				break;
			case 5:
				printf(" Reordenar arquivo\n");
				int modo = 0;
				
				f = reordena(arquivo);
				
				fclose(f);
				break;
			case 6:
				printf("\n Listar Alunos\n");
				
				if((f = fopen(arquivo, "rb")) == NULL){
					printf(" Erro! arquivo invalido\n");
					exit(1);
				}
				rewind(f);
				
				i = 0;
				while(!feof(f) && i < totalAlunos){
					fread(&guy, sizeof(Aluno), 1, f);
					if(guy.existe == 1){
						printf(" Matricula: %d, Nome: %s, Faltas: %d, notas: 1 - %d - %d - %d, media: %.2f\n\n", guy.matricula, guy.nome, guy.faltas, guy.notas[0], guy.notas[1], guy.notas[2], (float) (guy.notas[0]+ guy.notas[1]+ guy.notas[2])/3 );
					}
					i++;
				}
				fclose(f);
				printf(" Fim da lista\n\n");
				
				break;
				
			case 7:
				printf(" Imprimir Relatorio\n");
				break;
			case 8:
				printf(" Dados: total de alunos %d\n alunos validos: %d\n", totalAlunos, alunosValidos);
				break;
		}
	}
	fclose(f);
	
	/*
	// limpando a bagunça
	i = 0;
	
	f = fopen(arquivo,"r+b");
	
	FILE * novo;
	
	if((novo = fopen("holder.bin", "wb")) == NULL ){
		novo = fopen("holder.bin", "w+b");
	}
	rewind(f);
	rewind(novo);
	
	while(!feof(f)){
		fread(&guy, sizeof(Aluno), 1, f);
		if(guy.existe){
			fseek(novo, i * sizeof(Aluno), SEEK_SET);
			fwrite(&guy, sizeof(Aluno), 1, novo);;
		}
	}
	
	fclose(f);
	fclose(novo);
	
	
	
	system("del testando.bin");
	
	// reabrindo para copiar os alunos validos.
	
	i = 0;
	
	f = fopen(arquivo,"r+b");
	if((novo = fopen("holder.bin", "rb")) == NULL){
		printf(" Nao foi possivel limpar a bagunca\n\n");
		exit(1);
	}
	
	rewind(f);
	rewind(novo);
	
	while(!feof(f)){
		fread(&guy, sizeof(Aluno), 1, novo);
		
		fseek(f, i * sizeof(Aluno), SEEK_SET);
		fwrite(&guy, sizeof(Aluno), 1, f);
		
	}
	printf(" Total de alunos inseridos: %d\n\n fim\n", i - 1);
	
	fclose(f);
	fclose(novo);
	
	system("del holder.bin");*/
	
}