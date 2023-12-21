/* Programa: Visualiza��o de uma �rvore geral.
   Descri��o: Esse programa realiza a Visualiza��o de uma �rvore geral.
   Programador: Cau� Mendon�a Magela do �.
   RGM: 43558.
   Data da ultima modifica��o: 14/11/2023 */
  
/* LINHA DE EXECU��O: 
gcc main.c arvore.c -o main.exe -Wall -Wextra -pedantic -Werror
gcc avl.c  -o main.exe -Wall -Wextra -pedantic -Werror
main < (nomedoarquivo).txt*/

#include "arvore.h" /* no,fila ,P_noInserir,P_noBuscar,NumeroDigitos,MaxValor,MaiorLargura,ContarFilhos,ImprimirEspacos,ImprimirLinhaSuperior,ImprimirLinhaInferior,ImprimirValorNo,ImprimrConexaoEntreIrmaos,enfileirar,P_no_desenfileirar,filaVazia,ImprmirArvore*/
#include <stdio.h> /* printf,fprintf,scanf*/
#include <stdlib.h> /* malloc,free,exit*/

 int main(int argc, char *argv[])
{
  int valor, valor_raiz, num_filhos; /* Vari�veis para armazenar valores lidos do usu�rio */
  int i; 
  int *valores_filhos; /* Ponteiro para armazenar valores dos filhos dinamicamente */
  int nivel = 0; /* Vari�vel para rastrear o n�vel atual da �rvore */
  P_no raiz = NULL, pai; /* Ponteiros para a raiz da �rvore e o n� pai */
  argc = argc;
  argv = argv;

  /* Loop infinito at� que o usu�rio decida encerrar com o valor -1 */
  while (1)
  {
    /* o valor do n� pai */
    scanf("%d", &valor);

    /* Verifica se o usu�rio deseja encerrar o programa */
    if (valor == -1)
    {
      break;
    }
    /* raiz da �rvore */
    else 
	if (valor == 0)
    {
      /* Insere a raiz se ela ainda n�o existe */
      if (raiz == NULL)
      {
        scanf("%d", &valor_raiz);
        raiz = Inserir(NULL, valor_raiz, 0);
      }
      else
      {
        /* Informa ao usu�rio que a raiz j� foi criada */
        printf("A raiz j� existe.\n");
      }
    }
    else
    {
      /* Busca o pai com o valor fornecido pelo usu�rio */
      pai = Buscar(raiz, valor);

      /* Se o pai n�o for encontrado, informa ao usu�rio */
      if (pai == NULL)
      {
        printf("N� pai com valor %d n�o encontrado.\n", valor);
      }
      else
      {
        /* Incrementa o n�vel para a pr�xima inser��o de filho */
        nivel++;
        /* Solicita ao usu�rio para inserir o n�mero de filhos e seus valores */
        scanf("%d", &num_filhos);

        /* Aloca mem�ria para armazenar os valores dos filhos */
        valores_filhos = malloc(num_filhos * sizeof(int));
        if (valores_filhos == NULL)
        {
          /* Se a aloca��o falhar, exibe uma mensagem de erro e encerra o programa */
          fprintf(stderr, "Erro ao alocar mem�ria\n");
          exit(1);
        }

        /* L� os valores dos filhos e os insere na �rvore */
        for (i = 0; i < num_filhos; i++)
        {
          scanf("%d", &valores_filhos[i]);
          Inserir(pai, valores_filhos[i], nivel);  
        }

        /* Libera a mem�ria alocada para os valores dos filhos */
        free(valores_filhos);
      }
    }
  }

  /* Ap�s construir a �rvore, imprime a estrutura da �rvore */
  ImprimirArvore(raiz);

  /* Encerra o programa */
  return 0;
}