#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main(char * arquivo){
	
	

	system(" clear || cls");

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

	FILE * f;

	int j = 0;
	if((f = fopen(arquivo, "r+b")) == NULL){
		printf(" Erro! Nao foi possivel realizar a operacao\n");
		
	}else{
		
		rewind(f);
		fread(&guy, sizeof(Aluno), 1,f);
		strcpy(nomeBest,guy.nome);
		
		if(modo == 2){
			best = (float) guy.matricula;
		}else{
			best = (float) (guy.notas[0] + guy.notas[1] + guy.notas[2])/ 3 ;
		}
		
		// Total alunos eh a ultima posicao do arquivo que contem cras desorganizados.
		// j é o numero de alunos organizados
		// ao final, o arquivo deve conter no maximo 2 * totalAlunos alunos.
		
		while(j <= totalAlunos){
			
			i = 0;
			
			while(!feof(f) && i <= totalAlunos){
				
				fread(&guy, sizeof(Aluno), 1, f);
				
				if(guy.existe){
					
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
							curr = (float) (guy.nota[0] + guy.nota[1] + guy.nota[2]) / 3 ;
							break;
					}
					
					if(curr < best && modo != 1){
						best = curr;
						posBest = i;
					}
				}
				i++;
			}
			
			// colocando o aluno melhor ordenado no fim do arquivo.
			
			fseek(f ,posBest * sizeof(Aluno), SEEK_SET);
			fread(&guy, sizeof(Aluno), 1, f);
			
			fclose(f);
			
			f = fopen(arquivo, "ab");
			//fseek(f,0,SEEK_END);
			fwrite(&guy, sizeof(Aluno), 1, f);
			
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
	
}