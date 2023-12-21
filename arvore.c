#include "arvore.h" /*No,Fila P_noInserir,P_noBuscar,NumeroDigitos,MaxValor,MaiorLargura,ContarFilhos,ImprimirEspacos,ImprimirLinhaSuperior,ImprimirLinhaInferior,ImprimirValorNo,ImprimrConexaoEntreIrmaos,enfileirar,P_no_desenfileirar,filaVazia,ImprmirArvore*/
#include <stdio.h> /*printf,fprintf,scanf*/
#include <stdlib.h> /*malloc,free,exit*/

/* Função para inserir um novo nó na árvore genérica */
P_no Inserir(P_no pai, int valor,int nivel)
{
  P_no novo_no, irmao;

  /* Alocação de memória para um novo nó e verificação de sucesso */
  novo_no = (P_no)malloc(sizeof(T_no));
  if (!novo_no)
  {
    fprintf(stderr, "Erro ao alocar memória\n");
    exit(1);
  }
  /* Inicialização do novo nó */
  novo_no->valor = valor;
  novo_no->nivel = nivel;  /** Defina o nível do novo nó */
  novo_no->primeiro_filho = NULL;
  novo_no->proximo_irmao = NULL;

  /* Se o pai é NULL, o novo nó é a raiz */
  if (pai == NULL)
  {
    return novo_no;
  }

  /* Inserção do novo nó como filho ou irmão no local apropriado */
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

/* Função para buscar um nó com um valor específico na árvore */
P_no Buscar(P_no no, int valor)
{
  P_no resultado;

  if (no == NULL)
  {
    return NULL;
  }

  /* Retorna o nó se o valor for encontrado */
  if (no->valor == valor)
  {
    return no;
  }

  /* Busca recursiva no primeiro filho e nos irmãos */
  resultado = Buscar(no->primeiro_filho, valor);
  if (resultado != NULL)
  {
    return resultado;
  }

  return Buscar(no->proximo_irmao, valor);
}

/* Função para calcular o número de dígitos de um valor inteiro */
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

/* Função para encontrar o valor máximo armazenado na árvore */
int MaxValor(P_no raiz)
{
  int max, filho_max;
  P_no filho;

  max = raiz->valor;
  filho = raiz->primeiro_filho;
  /* Verificação recursiva para encontrar o valor máximo */
  while (filho != NULL)
  {
    filho_max = MaxValor(filho);
    if (filho_max > max)
      max = filho_max;
    filho = filho->proximo_irmao;
  }
  return max;
}

/* Função para calcular a largura necessária para imprimir a árvore */
int MaiorLargura(P_no raiz)
{
  return NumeroDigitos(MaxValor(raiz));
}

/* Função para contar o número de filhos de um nó */
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

/* Função auxiliar para imprimir espaços em branco */
void ImprimirEspacos(int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf(" ");
}

/* Função auxiliar para imprimir a linha superior de um nó */
void ImprimirLinhaSuperior(int largura)
{
  int i;
  printf(" ");
  for (i = 0; i < largura; i++)
    printf("_");
    printf(" ");
}

/* Função auxiliar para imprimir a linha inferior de um nó */
void ImprimirLinhaInferior(int largura)
{
  int i;
  printf("|");
  for (i = 0; i < largura; i++)
    printf("_");
    printf("|");
  
}

/* Função auxiliar para imprimir o valor de um nó dentro de uma caixa */
void ImprimirValorNo(int valor, int largura)
{
  int espaco_antes, espaco_depois;
  espaco_antes = (largura - NumeroDigitos(valor)) / 2;
  espaco_depois = largura - NumeroDigitos(valor) - espaco_antes;
  printf("|%*s%d%*s|", espaco_antes, "", valor, espaco_depois, ""); 
}

/* Função para imprimir as conexões entre irmãos na árvore */
void ImprimirConexaoEntreIrmaos(int largura_no, int num_filhos)
{
  int i, j;
  if (num_filhos < 2)
    return; /** Se tiver menos de dois filhos, não há conexão a ser impressa. */

  printf(" "); /** Começa com um espaço para alinhar com o teto da caixa do primeiro filho */
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
        fprintf(stderr, "Erro ao alocar memória para a fila\n");
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

/* Função para verificar se a fila está vazia */
int filaVazia(Fila *inicio) 
{
    return inicio == NULL;
}

/* Função para imprimir a árvore */
void ImprimirArvore(P_no raiz) 
{
	int num_filhos, largura_no, largura_total_filhos, meio_total_filhos, meio_no_pai, posicao_raiz,i; /* Variáveis para armazenar a contagem de filhos, largura dos nós, e posições de impressão */
    Fila *inicio = NULL, *fim = NULL; /* Ponteiros para o início e fim da fila usada na travessia da árvore */
    P_no no_atual, filho; /* Ponteiros para o nó atual e seus filhos */
    
    /* Se a árvore estiver vazia, retorna sem fazer nada */
    if (raiz == NULL) return;

    /* Enfileira o nó raiz */
    enfileirar(&inicio, &fim, raiz);

    /* Processa a árvore até que a fila esteja vazia */
    while (!filaVazia(inicio)) 
	{
        /* Desenfileira o próximo nó para processamento */
        no_atual = desenfileirar(&inicio, &fim);

        /* Obtém o primeiro filho do nó atual */
        filho = no_atual->primeiro_filho;

        /* Conta o número de filhos do nó atual */
        num_filhos = ContarFilhos(no_atual);

        /* Calcula a largura necessária para imprimir este nó e seus filhos */
        largura_no = MaiorLargura(raiz) + 4;
        largura_total_filhos = num_filhos * largura_no + (num_filhos - 1) * 3;

        /* Encontra a posição do meio para imprimir os nós centralizados */
        meio_total_filhos = largura_total_filhos / 2;
        meio_no_pai = (MaiorLargura(raiz) + 4) / 2;

        /* Calcula a posição da raiz em relação aos seus filhos */
        posicao_raiz = meio_total_filhos - meio_no_pai;
        
        /* Imprime o nó raiz centralizado sobre seus filhos */
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

        /* Se o nó atual tem filhos, imprime as conexões e os filhos */
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

        /* Enfileira todos os filhos do nó atual para processamento futuro */
        filho = no_atual->primeiro_filho;
        while (filho) 
		{
            enfileirar(&inicio, &fim, filho);
            filho = filho->proximo_irmao;
        }
    }   
}