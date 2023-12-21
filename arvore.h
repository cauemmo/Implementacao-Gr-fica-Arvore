#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/* Definição de uma estrutura de nó para uma árvore genérica */
typedef struct no
{
  int valor;                 /* Valor armazenado no nó */
  int nivel;                /** Adicione um campo para o nível */
  struct no *primeiro_filho; /* Ponteiro para o primeiro filho do nó */
  struct no *proximo_irmao;  /* Ponteiro para o próximo irmão do nó */
} T_no, *P_no;

typedef struct fila 
{
    P_no no;
    struct fila *proximo;
} Fila;

P_no Inserir(P_no pai, int ,int );

P_no Buscar(P_no no, int );

int NumeroDigitos(int );

int MaxValor(P_no raiz);

int MaiorLargura(P_no raiz);

int ContarFilhos(P_no pai);

void ImprimirEspacos(int );

void ImprimirLinhaSuperior(int);

void ImprimirLinhaInferior(int );

void ImprimirValorNo(int , int );

void ImprimirConexaoEntreIrmaos(int , int );

void enfileirar(Fila **, Fila **, P_no no);

P_no desenfileirar(Fila **, Fila **) ;

int filaVazia(Fila *) ;

void ImprimirArvore(P_no raiz) ;

#endif

