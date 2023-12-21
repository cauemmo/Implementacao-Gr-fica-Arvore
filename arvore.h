#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/* Defini��o de uma estrutura de n� para uma �rvore gen�rica */
typedef struct no
{
  int valor;                 /* Valor armazenado no n� */
  int nivel;                /** Adicione um campo para o n�vel */
  struct no *primeiro_filho; /* Ponteiro para o primeiro filho do n� */
  struct no *proximo_irmao;  /* Ponteiro para o pr�ximo irm�o do n� */
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

