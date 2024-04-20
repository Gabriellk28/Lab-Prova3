#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculaGrauVertice(char *linha)
{
    int grau = 0;
    for (int i = 0; linha[i] != '\0'; i++)
    {
        if (linha[i] == '1')
        {
            grau++;
        }
    }
    return grau;
}

int verticeIsolado(char *linha)
{
    for (int i = 0; linha[i] != '\0'; i++)
    {
        if (linha[i] == '1')
        {
            return 0;
        }
    }
    return 1;
}

// Função para escrever o grafo complementar no arquivo
void escreverGrafoComplementar(FILE *arquivoSaida, int nVertices, int **matrizComplementar) {
  int i, j;
  fprintf(arquivoSaida, "%d %d\n", nVertices, 0); // Assume-se que o grafo complementar não possui arestas

  for (i = 0; i < nVertices; i++) {
    for (j = 0; j < nVertices; j++) {
      if (matrizComplementar[i][j] == 0 && i != j) {
        fprintf(arquivoSaida, "%d %d\n", i, j);
      }
    }
  }
}

int main(void)
{
    FILE *fp;
    char str[4227];
    int conectados = 0;
    int maiorGrau = 0;
    int numeroVerticeMaiorGrau = 0;
    int contadorLinha = 0;
    int quantidadeVerticesIsolados = 0;
    int grau = 0;

    fp = fopen("dados_matriz.txt", "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(str, sizeof(str), fp) != NULL)
    {
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        if (contadorLinha == 1)
        {
            if (str[strlen(str) - 2] == '1')
            {
                conectados = 1;
            }
        }

        if (verticeIsolado(str) == 1)
        {
            quantidadeVerticesIsolados++;
        }
        grau = calculaGrauVertice(str);
        if (grau > maiorGrau)
        {
            maiorGrau = grau;
            numeroVerticeMaiorGrau = contadorLinha;
        }
        contadorLinha++;
    }

    fclose(fp);

    printf("Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);
    printf("Total de vértices isolados: %d.\n", quantidadeVerticesIsolados);
    if (conectados == 1)
    {
        printf("O Primeiro e o Último Vértice Estão Conectados.\n");
    }

    return 0;
}
