typedef struct _celula{
	char letra[4];
	int valor, linha, coluna;
	struct _celula* next;
} celula_matrix;

typedef struct _celulaPath{
	int linha, coluna;
	struct _celulaPath* next;
} celula_path;

typedef struct _Dados{
	int size_tabela[19];
	char** lista[19];
	int variante;
	int k;
	int size_total;
}Dados;

typedef struct _Word{
	char word[19];
	int valor;
	celula_path* path;
	struct _Word* next;
}Word;
