#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projecto.h"

int main(int argc, char *argv[]){

	FILE* fp_sol;
	FILE* fp_prob;
    FILE* fp_dic;
	char* nome, *ficheiro;
	int n_prob, i, status=1, v=0, l, g, c;
    char str1[100];
    Dados* d = AlocaDados();
    celula_matrix* b=NULL, *m=NULL;
    char palavra[19]="";
    char** dicionario;
    int* tabela_indice;
    int comp;

	if(argc < 3){
        fprintf(stderr, "This program must have at least two arguments besides the exec name.\n");
        fp_sol=fopen("default.sol", "w");
        fprintf(fp_sol, "-1");
        fclose(fp_sol);
        free(fp_sol);
        exit(0);
    }

    fp_prob=fopen(argv[2], "r");
    ficheiro = (char *) malloc((strlen(argv[2])-3) * sizeof (char));
    strncpy(ficheiro, argv[2], (strlen(argv[2])-4));  /* ******* */
    nome =  (char *) malloc((strlen(argv[2]) + 2) * sizeof (char));
    strcpy ( nome, ficheiro );
	strcat ( nome, ".sol" );
    fp_sol=fopen(nome, "w");

    if(fp_prob==(FILE *)NULL){
        fprintf(stderr, "Puzzle file %s does not exist or cannot be read\n", argv[2]);
        Error(fp_sol, nome);
        free(ficheiro);
        FreeDados(d);
        exit(0);
    }

    if(fscanf(fp_prob, "%d", &n_prob)==1);
	if(fgets(str1, sizeof(str1), fp_prob)==NULL);

	if(n_prob==0){
		Error(fp_sol, nome);
		fprintf(stderr, "Puzzle file contains 0 puzzles\n");
		exit(0);
	}

	fp_dic=fopen(argv[1], "r");

    if(fp_dic==(FILE *)NULL){
        fprintf(stderr, "Dictionary file %s does not exist or cannot be read\n", argv[1]);
        Error(fp_sol, nome);
        exit(0);
    }

    d->size_total = LeDicionario(fp_dic, d);
    dicionario = AlocaDicionario(d->size_total);
    PreencheDicionario(dicionario, fp_dic);
    tabela_indice = AlocaTabelaIndice(d->size_total);
    quicksort(dicionario, tabela_indice, 0, (d->size_total)-1);
    AlocaTabelas(d);
	PreencheTabelas(d, dicionario, tabela_indice);
	FreeDicionario(dicionario, d->size_total);
	free(tabela_indice);

	for(i=0; i<n_prob; i++)
	{
		Word* wb=NULL;
		celula_path* p=NULL;
		if(fscanf(fp_prob, "%d %d", &d->variante, &d->k)==2);
		if(fgets(str1, sizeof(str1), fp_prob)==NULL);

		b=Le_Problema(fp_prob);
		comp=CalculaComprimento(b);

		status=Verifica(d, fp_sol, comp);

		if(status==1){

			for(l=0, g=1; l<=3; l++, g++)
			{
				for(c=0; c<=3; c++, g++)
				{
					m=Search_Matrix(l, c, b);
					wb=Percorre_Matrix(m, palavra, v, p, b, d, wb);
				}
			}
			EscreveSol(fp_sol, d->variante, wb);
			FreeWord(wb);
			EliminaMatrix(b);
		}
		status=1;
	}
	free(ficheiro);
	free(nome);
	fclose(fp_dic);
	fclose(fp_prob);
	fclose(fp_sol);
	FreeDados(d);
	exit(0);
}
