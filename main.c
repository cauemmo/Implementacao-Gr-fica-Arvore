/* Programa: Visualização de uma árvore geral.
   Descrição: Esse programa realiza a Visualização de uma árvore geral.
   Programador: Cauê Mendonça Magela do Ó.
   RGM: 43558.
   Data da ultima modificação: 14/11/2023 */
  
/* LINHA DE EXECUÇÃO: 
gcc main.c arvore.c -o main.exe -Wall -Wextra -pedantic -Werror
gcc avl.c  -o main.exe -Wall -Wextra -pedantic -Werror
main < (nomedoarquivo).txt*/

#include "arvore.h" /* no,fila ,P_noInserir,P_noBuscar,NumeroDigitos,MaxValor,MaiorLargura,ContarFilhos,ImprimirEspacos,ImprimirLinhaSuperior,ImprimirLinhaInferior,ImprimirValorNo,ImprimrConexaoEntreIrmaos,enfileirar,P_no_desenfileirar,filaVazia,ImprmirArvore*/
#include <stdio.h> /* printf,fprintf,scanf*/
#include <stdlib.h> /* malloc,free,exit*/

 int main(int argc, char *argv[])
{
  int valor, valor_raiz, num_filhos; /* Variáveis para armazenar valores lidos do usuário */
  int i; 
  int *valores_filhos; /* Ponteiro para armazenar valores dos filhos dinamicamente */
  int nivel = 0; /* Variável para rastrear o nível atual da árvore */
  P_no raiz = NULL, pai; /* Ponteiros para a raiz da árvore e o nó pai */
  argc = argc;
  argv = argv;

  /* Loop infinito até que o usuário decida encerrar com o valor -1 */
  while (1)
  {
    /* o valor do nó pai */
    scanf("%d", &valor);

    /* Verifica se o usuário deseja encerrar o programa */
    if (valor == -1)
    {
      break;
    }
    /* raiz da árvore */
    else 
	if (valor == 0)
    {
      /* Insere a raiz se ela ainda não existe */
      if (raiz == NULL)
      {
        scanf("%d", &valor_raiz);
        raiz = Inserir(NULL, valor_raiz, 0);
      }
      else
      {
        /* Informa ao usuário que a raiz já foi criada */
        printf("A raiz já existe.\n");
      }
    }
    else
    {
      /* Busca o pai com o valor fornecido pelo usuário */
      pai = Buscar(raiz, valor);

      /* Se o pai não for encontrado, informa ao usuário */
      if (pai == NULL)
      {
        printf("Nó pai com valor %d não encontrado.\n", valor);
      }
      else
      {
        /* Incrementa o nível para a próxima inserção de filho */
        nivel++;
        /* Solicita ao usuário para inserir o número de filhos e seus valores */
        scanf("%d", &num_filhos);

        /* Aloca memória para armazenar os valores dos filhos */
        valores_filhos = malloc(num_filhos * sizeof(int));
        if (valores_filhos == NULL)
        {
          /* Se a alocação falhar, exibe uma mensagem de erro e encerra o programa */
          fprintf(stderr, "Erro ao alocar memória\n");
          exit(1);
        }

        /* Lê os valores dos filhos e os insere na árvore */
        for (i = 0; i < num_filhos; i++)
        {
          scanf("%d", &valores_filhos[i]);
          Inserir(pai, valores_filhos[i], nivel);  
        }

        /* Libera a memória alocada para os valores dos filhos */
        free(valores_filhos);
      }
    }
  }

  /* Após construir a árvore, imprime a estrutura da árvore */
  ImprimirArvore(raiz);

  /* Encerra o programa */
  return 0;
}