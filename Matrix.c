#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"

celula_matrix* AlocaCelula(int l, int c, int v, char* str){

	celula_matrix* b;

	b=(celula_matrix*)malloc(sizeof(celula_matrix));

	b->linha=l;
	b->coluna=c;
	b->valor=v;
	strcpy(b->letra, str);
	b->next=NULL;

	return b;
}

celula_path* AlocaCelulaPath(int l, int c){

	celula_path* b;

	b=(celula_path*)malloc(sizeof(celula_path));

	b->linha=l;
	b->coluna=c;
	b->next=NULL;

	return b;
}

celula_matrix* InsereLista(celula_matrix* l, celula_matrix* t){

	celula_matrix* aux;
	
	if(l==NULL)
		return t;

	aux=l;

	while(aux->next!=NULL)
		aux=aux->next;

	aux->next=t;
	return l;
}

celula_path* InsereListaPath(celula_path* l, celula_path* t){

	celula_path* aux;
	
	if(l==NULL)
		return t;

	aux=l;

	while(aux->next!=NULL)
		aux=aux->next;

	aux->next=t;
	return l;
}

celula_matrix* Search_Matrix(int l, int c, celula_matrix* b){

	celula_matrix* aux;;

	for(aux=b; aux!=NULL; aux=aux->next)
	{
		if(aux->linha==l && aux->coluna==c)
			return aux;
	}
	return 0;
}

int Search_path(int l, int c, celula_path* path){

	celula_path* aux;;

	for(aux=path; aux!=NULL; aux=aux->next)
	{
		if(aux->linha==l && aux->coluna==c)
			return 1;
	}
	return 0;
}

celula_path* CopyPath(celula_path* p, celula_path* caminho){

	celula_path* aux;
	celula_path* aux2;

	for(aux=caminho; aux!=NULL; aux=aux->next){
		aux2=AlocaCelulaPath(aux->linha, aux->coluna);
		p=InsereListaPath(p, aux2);
	}
	return p;
}

celula_path* EliminaCelula(celula_path* path){

	celula_path* aux=path, *ant;

	if(path==NULL) return path;

	if(aux->next==NULL){
        free(aux);
        path=NULL;
        return path;
	}


	for(ant=path, aux=path->next; aux->next!=NULL; aux=aux->next, ant=ant->next);

    free(aux);
    ant->next=NULL;
    return path;
}

celula_matrix* Le_Problema(FILE* fp){

	char str[17][4]={""};
	char str1[100];
	int v[17]={0};
	int c, l, i;
	celula_matrix* b=NULL;
	celula_matrix* t=NULL;

	if(fscanf(fp, "%s %s %s %s", str[1], str[2], str[3], str[4])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%s %s %s %s", str[5], str[6], str[7], str[8])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%s %s %s %s", str[9], str[10], str[11], str[12])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%s %s %s %s", str[13], str[14], str[15], str[16])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);

	if(fscanf(fp, "%d %d %d %d", &v[1], &v[2], &v[3], &v[4])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%d %d %d %d", &v[5], &v[6], &v[7], &v[8])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%d %d %d %d", &v[9], &v[10], &v[11], &v[12])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);
	if(fscanf(fp, "%d %d %d %d", &v[13], &v[14], &v[15], &v[16])==4);
	if(fgets(str1, sizeof(str1), fp)==NULL);

	for(l=0, i=1; l<=3; l++)
	{
		for(c=0; c<=3; c++, i++)
		{
			t=AlocaCelula(l, c, v[i], str[i]);
			b=InsereLista(b, t);
		}
	}

	return b;
}

void EliminaPath(celula_path* path){
	
	celula_path* aux=path, *aux2;
	
	for(aux2=path->next; aux->next!=NULL; aux2=aux2->next){
		
		free(aux);
		aux=aux2;
	}
	free(aux);
}

void EliminaMatrix(celula_matrix* b){
	
	celula_matrix* aux=b, *aux2;
	
	for(aux2=b->next; aux->next!=NULL; aux2=aux2->next){
		
		free(aux);
		aux=aux2;
	}
	free(aux);
}

/* Calcula o comprimento maximo que uma palavra pode tomar */
int CalculaComprimento(celula_matrix* b){
	
	celula_matrix* aux;
	int comp_total=0;
	
	for(aux=b; aux!=NULL; aux=aux->next)
		comp_total=comp_total+(strlen(aux->letra));

	return comp_total;
}
