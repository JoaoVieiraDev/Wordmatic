#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Projecto.h"


FILE * AbreFicheiro(char * nome) {
  FILE *fp;

  fp = fopen(nome, "r");
  if (fp == NULL) {
    fprintf(stderr, "Ficheiro inválido: %s.", nome);
    exit(1);
  }

  return fp;
}

char * LePalavra(FILE * fp) {
  static char palavra[100];

  if(fscanf(fp, "%s", palavra)==1)
    return palavra;
  else
    return NULL;
}

int LeDicionario(FILE* fp_dic, Dados* h) {
  int size, n=0;
  char* palavra;

  while((palavra = LePalavra(fp_dic)) != NULL)
  {
	  n++;
	  size = strlen(palavra);
	  if(size<=18)
		(h->size_tabela[size])++;
  }
  return n;
}

void AlocaTabelas(Dados* h) {
	int i, l, n;

		for(i=1; i<=18; i++){
			h->lista[i]=(char**)malloc(sizeof(char*)*h->size_tabela[i]);
			n=(h->size_tabela[i]);
			for(l=0; l< n; l++){ 
				h->lista[i][l]=(char*)malloc(sizeof(char)*(i+1));
			}
		}


}

void PreencheTabelas(Dados* h, char** tabela, int* tabela_indice){
	int i, n=0, r;
	int y[19];

	for(r=0; r<=18; r++) y[r]=0;
	for(i=0; i < (h->size_total); i++){ /* -1 */
		if((n=strlen(tabela[tabela_indice[i]])) <= 18){
			strcpy(h->lista[n][y[n]], tabela[tabela_indice[i]]);
			y[n]++;
		}
	}
}

int search(char** tab, char* pal, int n, int l, int r){
	int str=0;

	while(r>=l){
		int m = (l+r)/2;

		if ((str = strncmp(pal, tab[m], n))==0) return m;
		if (str<0) r = m-1;
		else l = m+1;
	}
	return -1;
}

void EscreveSol(FILE* fp_sol, int v, Word* wb){

	Word* aux, *aux2=wb;
	int comp_total=0;

	if(wb==NULL){
        fprintf(fp_sol, "0\n");
        return;
	}

	if(v==1 || v==2 || v==3 || v==4){

        fprintf(fp_sol, "%s ", aux2->word);
        ImprimePath(fp_sol, aux2);
        fprintf(fp_sol, "%d", (int)strlen(aux2->word));
        fprintf(fp_sol, "\n");
        comp_total=comp_total+strlen(aux2->word);
        
        if(v==2 || v==3){

			for(aux=wb, aux2=wb->next; aux2!=NULL; aux=aux->next, aux2=aux2->next){

				if(strcmp(aux2->word, aux->word)==0);
				else{
					fprintf(fp_sol, "%s ", aux2->word);
					ImprimePath(fp_sol, aux2);
					fprintf(fp_sol, "%d", (int)strlen(aux2->word));
					fprintf(fp_sol, "\n");
					comp_total=comp_total+strlen(aux2->word);
				}
			}
		}
		fprintf(fp_sol, "%d\n\n", comp_total);
	}
	else{
		fprintf(fp_sol, "%s ", wb->word);
		ImprimePath(fp_sol, wb);
		fprintf(fp_sol, "%d", wb->valor);
		fprintf(fp_sol, "\n");
		fprintf(fp_sol, "%d\n\n", wb->valor);
		}
}

void ImprimePath(FILE* fp_sol, Word* wb){

	celula_path* aux;

	for(aux=wb->path; aux!=NULL; aux=aux->next){
		fprintf(fp_sol, "%d%d ", aux->linha+1, aux->coluna+1);
	}
}

char** AlocaDicionario(int n){

	char** tabela;
	int i;

	tabela=(char**)malloc(sizeof(char*)*n);

	for(i=0; i<n; i++)
		tabela[i]=(char*)malloc(sizeof(char)*40);

	return tabela;
}

void PreencheDicionario(char** tabela, FILE* fp_dic){

	char str[40];
	int i;

	rewind(fp_dic);
	for(i=0; fscanf(fp_dic, "%s", str)!=EOF; i++)
		strcpy(tabela[i], str);
}

int* AlocaTabelaIndice(int n){

	int* tabela_indice;
	int i;

	tabela_indice=(int*)malloc(sizeof(int)*n);

	for(i=0; i<n; i++)
		tabela_indice[i]=i;

	return tabela_indice;
}

void quicksort(char** tabela, int* tabela_indice, int first,int last){
    int pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(strcasecmp(tabela[tabela_indice[i]], tabela[tabela_indice[pivot]]) <= 0 && i<last)
                 i++;
             while(strcasecmp(tabela[tabela_indice[j]], tabela[tabela_indice[pivot]]) >0)
                 j--;
             if(i<j){
                 temp=tabela_indice[i];
                  tabela_indice[i]=tabela_indice[j];
                  tabela_indice[j]=temp;
             }
         }

         temp=tabela_indice[pivot];
         tabela_indice[pivot]=tabela_indice[j];
         tabela_indice[j]=temp;
         quicksort(tabela, tabela_indice, first,j-1);
         quicksort(tabela, tabela_indice, j+1,last);

    }
}

void FreeDicionario(char** tabela, int n){

	int i;

	for(i=0; i<n;i++)
		free(tabela[i]);

	free(tabela);
}

void FreeDados(Dados* d){
	
	int i, j;
	
	for(i=0; i<19; i++){
		
		for(j=0; j<d->size_tabela[i]; j++)
			free(d->lista[i][j]);
			
		free(d->lista[i]);
		
	}
	free(d->size_tabela);
}

void FreeWord(Word* wb){
	
	Word* aux=wb, *aux2;
	
	if(wb==NULL) return;
	
	for(aux2=wb->next; aux->next!=NULL; aux2=aux2->next){
		
		EliminaPath(aux->path);
		free(aux->word);
		aux=aux2;
	}
	EliminaPath(aux->path);
	free(aux->word);
}

void Error(FILE* fp_sol, char* nome){

	fprintf(fp_sol, "-1");
	fclose(fp_sol);
	free(nome);
}

Word* InsereWordValor(Word* w, Word* b){

	Word *aux, *aux2;

	if(b==NULL) return w;

	aux=b;
	if(((Word *) w)->valor > ((Word *) b)->valor){
		w->next=aux;
		aux=w;
		return aux;
	}

	for(aux=aux->next, aux2=b; aux!=NULL; aux=aux->next, aux2=aux2->next){
		if(((Word *) w)->valor > ((Word *) b)->valor){
			w->next=aux2->next;
			aux2->next=w;
			return b;
		}
	}
	aux2->next=w;
	return b;
}

Word* InsereWordCompA(Word* w, Word* b){

	Word *aux, *aux2;

	if(b==NULL) return w;

	aux=b;
	if(strlen(((Word *) w)->word) < strlen(((Word *) b)->word)){
		w->next=aux;
		aux=w;
		return aux;
	}

	for(aux=aux->next, aux2=b; aux!=NULL; aux=aux->next, aux2=aux2->next){
		if(strlen(((Word *) w)->word) < strlen(((Word *) b)->word)) {
			w->next=aux2->next;
			aux2->next=w;
			return b;
		}
	}
	aux2->next=w;
	return b;
}

Word* AlocaWord(char* palavra, int value, celula_path* caminho){

	Word* w;
	celula_path* p=NULL;

	w=(Word*)malloc(sizeof(Word));

	w->valor=value;
	strcpy(w->word, palavra);
	w->next=NULL;
	w->path=(celula_path*)CopyPath(p, caminho);

	return w;
}

Word* InsereWordAlfa(Word* w, Word* b){

	Word *aux, *aux2;

	if(b==NULL) return w;

	aux=b;
	if(strcasecmp(((Word*)w)->word, ((Word *) b)->word) < 0){
		w->next=aux;
		aux=w;
		return aux;
	}

	for(aux=aux->next, aux2=b; aux!=NULL; aux=aux->next, aux2=aux2->next){
		if(strcasecmp(((Word*)w)->word, ((Word *) aux)->word) < 0){
			w->next=aux2->next;
			aux2->next=w;
			return b;
		}
	}
	aux2->next=w;
	return b;
}

Word* InsereWordCompD(Word* w, Word* b){

	Word *aux, *aux2;

	if(b==NULL) return w;

	aux=b;
	if(strlen(((Word *) w)->word) > strlen(((Word *) b)->word)){
		w->next=aux;
		aux=w;
		return aux;
	}

	for(aux=aux->next, aux2=b; aux!=NULL; aux=aux->next, aux2=aux2->next){
		if(strlen(((Word *) w)->word) > strlen(((Word *) b)->word)){
			w->next=aux2->next;
			aux2->next=w;
			return b;
		}
	}
	aux2->next=w;
	return b;
}

Dados* AlocaDados(){

	Dados* aux;
	int i;

	aux=(Dados*)malloc(sizeof(Dados));

	for(i=0; i<=18; i++){
		aux->size_tabela[i]=0;
		aux->lista[i]=NULL;
	}
	aux->variante=0;
	aux->k=0;
	aux->size_total=0;
	return aux;
}

Word* Percorre_Matrix(celula_matrix* entry, char* pal, int value, celula_path* path, celula_matrix* b, Dados* d, Word* wb){

	celula_path* aux;
	Word* w;
	int r, q, i, status=0;
	static int stat=0;
	char* palavra;
	stat=0;
	
	palavra=(char*)malloc(sizeof(char)*(strlen(pal)+4));
	strcpy(palavra, pal);

	strcat(palavra, entry->letra);
	value=value+entry->valor;
	aux=AlocaCelulaPath(entry->linha, entry->coluna);
	path=InsereListaPath(path, aux);

	if(d->variante==3 || d->variante==4 || d->variante==6){

		if((r = strlen(palavra))<3);

		else
		{
			for(i=r; i<19; i++){
				q=search(d->lista[i], palavra, r, 0, d->size_tabela[i]-1);
					if(q!=-1){
						status=1;
						if(i==r){
							if(d->variante==6){
								if(value==d->k){
									w=AlocaWord(palavra, value, path);
									wb=InsereWordCompA(w, wb);
								}
							}
							else{
								w=AlocaWord(palavra, value, path);
								if(d->variante==3) wb=InsereWordAlfa(w, wb);
								if(d->variante==4) wb=InsereWordCompD(w, wb);
							}
						}
						else break;
					}
			}
			if(status==0){
				path=EliminaCelula(path);
				free(palavra);
				return wb;
			}
		}
	}
	else{

		if(strlen(palavra)< d->k && strlen(palavra)>2){
			q=search(d->lista[d->k], palavra, strlen(palavra), 0, d->size_tabela[d->k]-1);
				if(q==-1){
					free(palavra);
					path=EliminaCelula(path);
					return wb;
				}
		}

		if(strlen(palavra)== d->k)
		{
			q=search(d->lista[d->k], palavra, d->k, 0, d->size_tabela[d->k]-1);
					if(q!=-1){
						if(d->variante==1){
							w=AlocaWord(palavra, value, path);
							wb=InsereWordCompA(w, wb);
							stat=1;
							free(palavra);
							path=EliminaCelula(path);
							return wb;
						}
						if(d->variante==2){
							w=AlocaWord(palavra, value, path);
							wb=InsereWordAlfa(w, wb);
						}
						if(d->variante==5){
							w=AlocaWord(palavra, value, path);
							wb=InsereWordValor(w, wb);

						}
					}
            path=EliminaCelula(path);
            free(palavra);
			return wb;
		}
		if(strlen(palavra)> d->k){
            path=EliminaCelula(path);
            free(palavra);
            return wb;
		}
	}

	if(entry->linha-1 >= 0){
		if(Search_path(entry->linha-1, entry->coluna, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha-1, entry->coluna, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->linha-1 >= 0 && entry->coluna+1 <= 3){
		if(Search_path(entry->linha-1, entry->coluna+1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha-1, entry->coluna+1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->coluna+1 <= 3){
		if(Search_path(entry->linha, entry->coluna+1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha, entry->coluna+1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->linha+1 <= 3 && entry->coluna+1 <= 3){
		if(Search_path(entry->linha+1, entry->coluna+1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha+1, entry->coluna+1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->linha+1 <= 3){
		if(Search_path(entry->linha+1, entry->coluna, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha+1, entry->coluna, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->linha+1 <= 3 && entry->coluna-1 >= 0){
		if(Search_path(entry->linha+1, entry->coluna-1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha+1, entry->coluna-1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->coluna-1 >= 0){
		if(Search_path(entry->linha, entry->coluna-1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha, entry->coluna-1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	if(entry->linha-1 >= 0 && entry->coluna-1 >= 0){
		if(Search_path(entry->linha-1, entry->coluna-1, path)==0)
		{
			celula_matrix* cell;
			cell=Search_Matrix(entry->linha-1, entry->coluna-1, b);
			wb=Percorre_Matrix(cell, palavra, value, path, b, d, wb);
			if(stat==1){
				free(palavra);
				path=EliminaCelula(path);
				return wb;
			}
		}
	}

	path=EliminaCelula(path);
	free(palavra);
	return wb;
}

int Verifica( Dados* d, FILE* fp_sol, int comp){
	
	int status=1;
	
	if(d->variante>6 || d->variante<1) {
			status=0;
			fprintf(fp_sol, "-1\n\n");
        }
        else{

            if(d->variante==1 || d->variante==2 || d->variante==5){
                if(d->k>comp || d->k<3){
                    status=0;
                    fprintf(fp_sol, "-1\n\n");
                }
            }
            if(d->variante==6){
                if(d->k<3){
                    status=0;
                    fprintf(fp_sol, "-1\n\n");
                }
            }
        }
        return status;
}
