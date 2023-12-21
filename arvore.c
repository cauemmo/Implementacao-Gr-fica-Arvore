#include "arvore.h" /*No,Fila P_noInserir,P_noBuscar,NumeroDigitos,MaxValor,MaiorLargura,ContarFilhos,ImprimirEspacos,ImprimirLinhaSuperior,ImprimirLinhaInferior,ImprimirValorNo,ImprimrConexaoEntreIrmaos,enfileirar,P_no_desenfileirar,filaVazia,ImprmirArvore*/
#include <stdio.h> /*printf,fprintf,scanf*/
#include <stdlib.h> /*malloc,free,exit*/

/* Fun��o para inserir um novo n� na �rvore gen�rica */
P_no Inserir(P_no pai, int valor,int nivel)
{
  P_no novo_no, irmao;

  /* Aloca��o de mem�ria para um novo n� e verifica��o de sucesso */
  novo_no = (P_no)malloc(sizeof(T_no));
  if (!novo_no)
  {
    fprintf(stderr, "Erro ao alocar mem�ria\n");
    exit(1);
  }
  /* Inicializa��o do novo n� */
  novo_no->valor = valor;
  novo_no->nivel = nivel;  /** Defina o n�vel do novo n� */
  novo_no->primeiro_filho = NULL;
  novo_no->proximo_irmao = NULL;

  /* Se o pai � NULL, o novo n� � a raiz */
  if (pai == NULL)
  {
    return novo_no;
  }

  /* Inser��o do novo n� como filho ou irm�o no local apropriado */
  if (!pai->primeiro_filho)
  {
    pai->primeiro_filho = novo_no;
  }
  else
  {
    irmao = pai->primeiro_filho;
    while (irmao->proximo_irmao)
    {
      irmao = irmao->proximo_irmao;
    }
    irmao->proximo_irmao = novo_no;
  }

  return novo_no;
}

/* Fun��o para buscar um n� com um valor espec�fico na �rvore */
P_no Buscar(P_no no, int valor)
{
  P_no resultado;

  if (no == NULL)
  {
    return NULL;
  }

  /* Retorna o n� se o valor for encontrado */
  if (no->valor == valor)
  {
    return no;
  }

  /* Busca recursiva no primeiro filho e nos irm�os */
  resultado = Buscar(no->primeiro_filho, valor);
  if (resultado != NULL)
  {
    return resultado;
  }

  return Buscar(no->proximo_irmao, valor);
}

/* Fun��o para calcular o n�mero de d�gitos de um valor inteiro */
int NumeroDigitos(int valor)
{
  int digitos = 0;

  if (valor == 0)
    return 1;
  while (valor)
  {
    digitos++;
    valor /= 10;
  }
  return digitos;
}

/* Fun��o para encontrar o valor m�ximo armazenado na �rvore */
int MaxValor(P_no raiz)
{
  int max, filho_max;
  P_no filho;

  max = raiz->valor;
  filho = raiz->primeiro_filho;
  /* Verifica��o recursiva para encontrar o valor m�ximo */
  while (filho != NULL)
  {
    filho_max = MaxValor(filho);
    if (filho_max > max)
      max = filho_max;
    filho = filho->proximo_irmao;
  }
  return max;
}

/* Fun��o para calcular a largura necess�ria para imprimir a �rvore */
int MaiorLargura(P_no raiz)
{
  return NumeroDigitos(MaxValor(raiz));
}

/* Fun��o para contar o n�mero de filhos de um n� */
int ContarFilhos(P_no pai)
{
  int cont = 0;
  P_no atual;

  atual = pai->primeiro_filho;
  while (atual != NULL)
  {
    cont++;
    atual = atual->proximo_irmao;
  }
  return cont;
}

/* Fun��o auxiliar para imprimir espa�os em branco */
void ImprimirEspacos(int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf(" ");
}

/* Fun��o auxiliar para imprimir a linha superior de um n� */
void ImprimirLinhaSuperior(int largura)
{
  int i;
  printf(" ");
  for (i = 0; i < largura; i++)
    printf("_");
    printf(" ");
}

/* Fun��o auxiliar para imprimir a linha inferior de um n� */
void ImprimirLinhaInferior(int largura)
{
  int i;
  printf("|");
  for (i = 0; i < largura; i++)
    printf("_");
    printf("|");
  
}

/* Fun��o auxiliar para imprimir o valor de um n� dentro de uma caixa */
void ImprimirValorNo(int valor, int largura)
{
  int espaco_antes, espaco_depois;
  espaco_antes = (largura - NumeroDigitos(valor)) / 2;
  espaco_depois = largura - NumeroDigitos(valor) - espaco_antes;
  printf("|%*s%d%*s|", espaco_antes, "", valor, espaco_depois, ""); 
}

/* Fun��o para imprimir as conex�es entre irm�os na �rvore */
void ImprimirConexaoEntreIrmaos(int largura_no, int num_filhos)
{
  int i, j;
  if (num_filhos < 2)
    return; /** Se tiver menos de dois filhos, n�o h� conex�o a ser impressa. */

  printf(" "); /** Come�a com um espa�o para alinhar com o teto da caixa do primeiro filho */
  for (i = 0; i < num_filhos - 1; i++)
  {
    for (j = 0; j < largura_no; j++)
      printf(" "); 
    printf("___"); 
  }
  printf("\n");
}

void enfileirar(Fila **inicio, Fila **fim, P_no no) 
{
    Fila *novo = (Fila *)malloc(sizeof(Fila));
    if (!novo) 
	{
        fprintf(stderr, "Erro ao alocar mem�ria para a fila\n");
        exit(1);
    }
    novo->no = no;
    novo->proximo = NULL;

    if (*fim) 
	{
        (*fim)->proximo = novo;
    }
	else
	{
        *inicio = novo;
    }
    *fim = novo;
}

P_no desenfileirar(Fila **inicio, Fila **fim) 
{
    Fila *temp;
    P_no no;

    if (!*inicio) return NULL;

    temp = *inicio;
    no = temp->no;
    *inicio = (*inicio)->proximo;
    if (!*inicio) 
	{
        *fim = NULL;
    }
    free(temp);
    return no;
}

/* Fun��o para verificar se a fila est� vazia */
int filaVazia(Fila *inicio) 
{
    return inicio == NULL;
}

/* Fun��o para imprimir a �rvore */
void ImprimirArvore(P_no raiz) 
{
	int num_filhos, largura_no, largura_total_filhos, meio_total_filhos, meio_no_pai, posicao_raiz,i; /* Vari�veis para armazenar a contagem de filhos, largura dos n�s, e posi��es de impress�o */
    Fila *inicio = NULL, *fim = NULL; /* Ponteiros para o in�cio e fim da fila usada na travessia da �rvore */
    P_no no_atual, filho; /* Ponteiros para o n� atual e seus filhos */
    
    /* Se a �rvore estiver vazia, retorna sem fazer nada */
    if (raiz == NULL) return;

    /* Enfileira o n� raiz */
    enfileirar(&inicio, &fim, raiz);

    /* Processa a �rvore at� que a fila esteja vazia */
    while (!filaVazia(inicio)) 
	{
        /* Desenfileira o pr�ximo n� para processamento */
        no_atual = desenfileirar(&inicio, &fim);

        /* Obt�m o primeiro filho do n� atual */
        filho = no_atual->primeiro_filho;

        /* Conta o n�mero de filhos do n� atual */
        num_filhos = ContarFilhos(no_atual);

        /* Calcula a largura necess�ria para imprimir este n� e seus filhos */
        largura_no = MaiorLargura(raiz) + 4;
        largura_total_filhos = num_filhos * largura_no + (num_filhos - 1) * 3;

        /* Encontra a posi��o do meio para imprimir os n�s centralizados */
        meio_total_filhos = largura_total_filhos / 2;
        meio_no_pai = (MaiorLargura(raiz) + 4) / 2;

        /* Calcula a posi��o da raiz em rela��o aos seus filhos */
        posicao_raiz = meio_total_filhos - meio_no_pai;
        
        /* Imprime o n� raiz centralizado sobre seus filhos */
        if (no_atual == raiz) 
		{
            ImprimirEspacos(posicao_raiz);
            ImprimirLinhaSuperior(largura_no - 2);
            printf("\n");
            ImprimirEspacos(posicao_raiz);
            ImprimirValorNo(no_atual->valor, largura_no - 2);
            printf("\n");
            ImprimirEspacos(posicao_raiz);
            ImprimirLinhaInferior(largura_no - 2);
            printf("\n");
        }

        /* Se o n� atual tem filhos, imprime as conex�es e os filhos */
        if (num_filhos > 0) 
		{
            ImprimirEspacos(meio_total_filhos);
            printf("|\n");
            /* Imprime a parte superior das caixas dos filhos */
            for (i = 0; i < num_filhos; i++) 
			{
                if (i > 0) printf("___");
                ImprimirLinhaSuperior(largura_no - 2);
            }
            printf("\n");

            /* Imprime o valor de cada filho dentro das caixas */
            for (i = 0; i < num_filhos; i++) 
			{
                if (i > 0) ImprimirEspacos(3);
                ImprimirValorNo(filho->valor, largura_no - 2);
                filho = filho->proximo_irmao;
            }
            printf("\n");

            /* Imprime a parte inferior das caixas dos filhos */
            filho = no_atual->primeiro_filho;
            for (i = 0; i < num_filhos; i++) 
			{
                if (i > 0) ImprimirEspacos(3);
                ImprimirLinhaInferior(largura_no - 2);
            }
            printf("\n");
        }

        /* Enfileira todos os filhos do n� atual para processamento futuro */
        filho = no_atual->primeiro_filho;
        while (filho) 
		{
            enfileirar(&inicio, &fim, filho);
            filho = filho->proximo_irmao;
        }
    }   
}