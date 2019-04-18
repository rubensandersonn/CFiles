#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct alu{
	int matricula;
	int notas[3];
	char nome[12];
	int faltas;
	
}aluno;


int main(){
	
	// unsigned fread (void *buffer, int numero_de_bytes, int count, FILE *fp);
	// int fseek (FILE *fp, long numbytes, int origem);
	// unsigned fwrite(void *buffer,int numero_de_bytes,int count,FILE *fp);
	
	
	system(" clear || cls");
	
	int existe = 1;		// existe, por defalt
	aluno gui;
	aluno holder;
	int saiu = 0;
	char buffer[12];
	FILE * arquivo;
	
	char c;
	int mat;
	char name[12];
	
	int opcao = -1, i = 0;;
	printf(" Entre com o nome do arquivo a ser gerenciado\n");
	gets(buffer);
	

	arquivo = fopen(buffer,"ab");
	if((arquivo) == NULL){
		
		printf("Erro ao abrir o arquivo!\n");
		FILE * arq2 = fopen(buffer,"wb");
		if(arq2 != NULL){
			printf("Arquivo %s Criado!\n", buffer);
			fclose(arq2);
			arquivo = fopen(buffer, "ab");
		}
		else{
			printf(" Erro ao abrir e criar o arquivo\n");
		}
	}
	
	fclose(arquivo);
	
	// menu
	while(opcao != 0){
		printf(" Digite a opcao desejada.\n 1 - Inserir novo aluno\n 2 - excluir aluno\n 3 - alterar dados do aluno\n 4 - consultar dados do aluno\n 5 - reordenar arquivo\n 6 - Listar alunos\n 7 - Imprimir relatorio\n 0 - Sair\n\n");
		scanf("%d", &opcao);
		
		/*
			como nao consigo inserir/ler dados de uma struct diretamente
			cada dado sera inserido/lido separadamente, na seguinte ordem:
				
				existe? 0,1
				matricula
				nome
				nota i 
				faltas
		*/
		
		switch(opcao){
			case 1:
				printf(" Inserir Aluno\n");
				arquivo = fopen(buffer, "ab");
				
				if(arquivo == NULL){
					printf(" Erro ao abrir o arquivo\n");
				}else{
					// captando dados
					
					// exxiste!
					fwrite(&existe, sizeof(int), 1, arquivo);
					
					//matricuçla
					printf(" Entre com a matricula do aluno\n");
					scanf("%d", &mat);
					guy.matricula = mat;
					fwrite(&guy.matricula, sizeof(int), 1, arquivo);
					
					// nome
					printf(" Entre com o nome do aluno\n");
					gets(guy.nome);
					fwrite(&guy.nome, strlen(guy.nome) * sizeof(char), 1, arquivo);
					
					// notas
					printf(" Digite a nota 1 do aluno\n");
					scanf("%d", &guy.notas[0]);
					fwrite(&guy.nota[0], sizeof(int), 1, arquivo);
					
					printf(" Digite a nota 2 do aluno\n");
					scanf("%d", &guy.notas[1]);
					fwrite(&guy.nota[1], sizeof(int), 1, arquivo);
					
					printf(" Digite a nota 3 do aluno\n");
					scanf("%d", &guy.notas[2]);
					fwrite(&guy.nota[2], sizeof(int), 1, arquivo);
					
					// faltas
					printf(" Digite o numero de faltas do aluno\n");
					scanf("%d", &guy.faltas);
					fwrite(&guy.faltas, sizeof(int), 1, arquivo);
					
					printf(" %s, %d\n\n", guy.nome, guy.matricula);
					
					
					fclose(arquivo);
				}
				
				break;
				
				
			case 2:
				printf(" excluir Aluno\n");
				
				printf(" Digite a matricula do aluno\n");
				scanf("%d", &mat);
				
				int e = 0;
				saiu = 0;
				
				arquivo = fopen(buffer, "rb");
				
				while(arquivo != NULL && !saiu && (c = getc(arquivo) ) != EOF){
					fread(&holder, sizeof(aluno), 1,arquivo);
					if(mat == holder.matricula){
						saiu = 1;
					}
				}
				if(saiu){
					FILE * aux = fopen("aux.bin","wb");
					fclose(aux);
					aux = fopen("aux.bin", "ab");
					
					while(!feof(arquivo)){
						
						fread(&holder, sizeof(aluno), 1, arquivo);
						
						if(holder.matricula != mat){
							fwrite(&holder, sizeof(aluno), 1,aux);
						}
					}
					fclose(aux);
					fclose(arquivo);
					
					arquivo = fopen(buffer, "wb");
					fwrite("",0, 1, arquivo);
					fclose(arquivo);
					
					arquivo = fopen(buffer, "ab");
					
					aux = fopen("aux.bin", "rb");
					
					while(!feof(aux)){
						fread(&holder, sizeof(aluno), 1, aux);
						fwrite(&holder, sizeof(aluno), 1, arquivo);
					}
					
					fclose(arquivo);
					fclose(aux);
					
					//system("rm -r aux.bin || del aux.bin");
				}else{
					printf(" Matricula nao encontrada\n\n");
				}
				
				break;
			case 3:
				printf(" alterar dados do Aluno\n");
				break;
			case 4:
				printf(" consultar dados do Aluno\n");
				break;
			case 5:
				printf(" Reordenar arquivo\n");
				break;
			case 6:
				printf(" Listar Alunos\n");
				int matricula;
				
				if((arquivo = fopen(buffer, "rb")) == NULL) /* Abre o arquivo novamente para leitura */
					{
					   printf("Erro na abertura do arquivo");
					   exit(1);
					}
				while((c = getc(arquivo) ) != EOF){
					if(fread(&holder, sizeof(aluno), 1,arquivo) != 1){  /* Le em pilido o valor da variável armazenada anteriormente */
						//printf("Erro na leitura do arquivo");
						printf("\n %s. %d",holder.nome, holder.matricula);
					}
				}
				
				break;
			case 7:
				printf(" Imprimir Relatorio\n");
				break;
		}
	}
	return 0;
}