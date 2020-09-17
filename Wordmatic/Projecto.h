#include <stdio.h>
#include "Matrix.h"

struct _celula;
struct _celulaPath;
struct _Dados;
struct _Word;

void Error(FILE* fp_sol, char* nome);
Word* AlocaWord(char* palavra, int value, celula_path* caminho);
FILE * AbreFicheiro(char * nome);
char * LePalavra(FILE * fp);
int LeDicionario(FILE* fp_dic, Dados* h);
void AlocaTabelas(Dados* h);
void PreencheTabelas(Dados* h, char** tabela, int* tabela_indice);
int search(char** tab, char* pal, int n, int l, int r);
char** AlocaDicionario(int n);
void PreencheDicionario(char** tabela, FILE* fp_dic);
int* AlocaTabelaIndice(int n);
void quicksort(char** tabela, int* tabela_indice, int first,int last);
void FreeDicionario(char** tabela, int n);
void ImprimePath(FILE* fp_sol, Word* wb);
void EscreveSol(FILE* fp_sol, int v, Word* wb);
Dados* AlocaDados();
void FreeDados(Dados* d);
void FreeWord(Word* wb);
int Verifica( Dados* d, FILE* fp_sol, int comp);
Word* Percorre_Matrix(celula_matrix* entry, char* palavra, int value, celula_path* path, celula_matrix* b, Dados* d, Word* wb);
