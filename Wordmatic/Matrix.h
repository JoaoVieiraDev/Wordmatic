#include <stdio.h>
#include "Defs.h"

struct _celula;
struct _celulaPath;
struct _Dados;
struct _Word;

celula_matrix* AlocaCelula(int l, int c, int v, char* str);
celula_path* AlocaCelulaPath(int l, int c);
celula_matrix* InsereLista(celula_matrix* l, celula_matrix* t);
celula_path* InsereListaPath(celula_path* l, celula_path* t);
celula_matrix* Search_Matrix(int l, int c, celula_matrix* b);
int Search_path(int l, int c, celula_path* path);
celula_path* CopyPath(celula_path* p, celula_path* caminho);
celula_path* EliminaCelula(celula_path* path);
celula_matrix* Le_Problema(FILE* fp);
void EliminaPath(celula_path* path);
void EliminaMatrix(celula_matrix* b);
int CalculaComprimento(celula_matrix* b);
