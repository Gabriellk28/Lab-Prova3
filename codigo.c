#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINHA 4228

// Função para calcular o grau de um vértice
int GrauVertice(char *linha)
{
    int grau = 0; // Variável para armazenar o grau dos vértices

    for (int i = 0; linha[i] != '\0'; i++) // Laço de repetição para percorrer o vetor que contém a linha da matriz
    {
        if (linha[i] == '1') // Verifica se o índice do vetor contém o caracter 1
        {
            grau++; // Incrementa em 1 o grau do vértice
        }
    }
    return grau; // Retorna o grau do vétice.
}

// Função que Calcula o Maior vértice da matriz de adjacencia do grafo
int MaiorGrauVertice(char *nomeArquivo)
{
    int contadorLinha = 0;          // Variável para contabilizar as linhas lidas
    int maiorGrau = 0;              // Variável para armazenar o Maior grau
    int numeroVerticeMaiorGrau = 0; // Variável para armazenar o número do vétice com maior grau
    int grau = 0;                   // váriável para armazenar os graus dos vértices
    char linhaArquivo[LINHA];       // Vetor para armazenar uma linha do arquivo

    FILE *fp = fopen(nomeArquivo, "r"); // Ponteiro para o arquivo
    if (fp == NULL)                     //
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linhaArquivo, LINHA, fp) != NULL)
    {
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        grau = GrauVertice(linhaArquivo);
        if (grau > maiorGrau)
        {
            maiorGrau = grau;
            numeroVerticeMaiorGrau = contadorLinha;
        }
        contadorLinha++;
    }

    printf("Questão 1 - Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);
}

// Função para escrevero número do vértices seguido pelo seu respectivo grau em um arquivo
void escreveGrausVertices(char *nomeArquivo)
{
    FILE *paEntrada, *paSaida;
    char linhaArquivo[LINHA];
    int contadorLinha = 0;
    int grau = 0;

    paEntrada = fopen(nomeArquivo, "r");
    if (paEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    paSaida = fopen("dados_grafos_graus.txt", "w");
    if (paSaida == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(paEntrada);
        return;
    }

    while (fgets(linhaArquivo, LINHA, paEntrada) != NULL)
    {
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        grau = GrauVertice(linhaArquivo);

        fprintf(paSaida, "V%d: %d\n", contadorLinha, grau);

        contadorLinha++;
    }

    printf("Arquivo \"dados_grafos_graus.txt\" Gerado.\n");

    fclose(paEntrada);
    fclose(paSaida);
}

void verticesIsolados(char *nomeArquivo)
{
    char linhaArquivo[LINHA];
    int contadorLinha = 0; // Variável para contabilizar as linhas lidas
    int aresta = 0;        //
    int verticesIsolados = 0;
    int i = 0;
    FILE *pa;

    pa = fopen(nomeArquivo, "r");
    if (pa == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linhaArquivo, LINHA, pa) != NULL)
    {
        aresta = 0;

        for (i = 0; linhaArquivo[i] != '\0'; i++)
        {
            if (linhaArquivo[i] == '1')
            {
                aresta = 1; // Se encontrar um '1'
                printf("Vértice isolado encontrado na linha %d.\n", contadorLinha);
                verticesIsolados++;
                break; // Sai do loop assim que encontrar um '1'
            }
        }
        contadorLinha++; // Atualiza o número da linha
    }

    fclose(pa);

    if (verticesIsolados == 0)
    {
        printf("Nenhum vértice isolado encontrado.\n");
    } 
    else
    {
        printf("Total de vértices isolados: %d.\n", verticesIsolados);
    }
}

void MatrizComplementar(char *nomeArquivo)
{
    FILE *paEntrada = NULL, *paSaida = NULL;
    char linhaArquivo[LINHA];
    int contadorLinha = 0;
    int contadorColuna = 0;

    paEntrada = fopen(nomeArquivo, "r");
    if (paEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    paSaida = fopen("matriz_complementar.txt", "w");
    if (paSaida == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(paEntrada);
        return;
    }

    // Para as linhas restantes do arquivo original
    while (fgets(linhaArquivo, LINHA, paEntrada) != NULL)
    {
        // Percorre cada caractere da linha
        for (int i = 0; linhaArquivo[i] != '\0'; i++)
        {
            // Se for um espaço em branco ou um número, escreve o caractere no arquivo complementar
            if (linhaArquivo[i] == ' ' || (linhaArquivo[i] >= '0' && linhaArquivo[i] <= '1'))
            {
                fprintf(paSaida, "%c", linhaArquivo[i]);
            }
            // Se for um número, incrementa o contador de colunas
            if (linhaArquivo[i] == '1' || linhaArquivo[i] == '0')
            {
                contadorColuna++;
            }
        }
        // Se for uma linha válida da matriz original
        if (contadorLinha != 0)
        {
            // Calcula o número de zeros que devem ser adicionados na linha complementar
            int numeroZeros = contadorLinha - contadorColuna;
            // Escreve os zeros faltantes na linha complementar
            for (int j = 0; j < numeroZeros; j++)
            {
                fprintf(paSaida, " 0");
            }
            // Pula para a próxima linha no arquivo complementar
            fprintf(paSaida, "\n");
        }
        // Incrementa o contador de linha
        contadorLinha++;
    }

    fclose(paEntrada);
    fclose(paSaida);
}

void VerticesMultiplosDeCinco(char *arquivo)
{
    FILE *paEntrada = NULL, *paSaida = NULL; // Ponteiros para os arquivos de entrada e saída
    char linhaArquivo[LINHA]; // Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0; // Contador de linhas

    paEntrada = fopen(arquivo, "r"); // Abre o arquivo "dados_matriz.txt" para leitura
    if (paEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n"); // Se o arquivo não for aberto com sucesso
        return;
    }

    paSaida = fopen("dados_grafo_gerador.txt", "w"); // Abre o arquivo "dados_grafo_gerador.txt" para escrita
    if (paSaida == NULL)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(paEntrada);
        return;
    }

    while (fgets(linhaArquivo, LINHA, paEntrada) != NULL)
    {
        if (contadorLinha != 0)
        {
            if (contadorLinha % 5 == 0)
            {
                fprintf(paSaida, "%s", linhaArquivo);
            }
        }
        contadorLinha++;
    }

    fclose(paEntrada);
    fclose(paSaida);
}

int PrimeiroUltimoVertice(char *nomeArquivo)
{   
    int contadorLinha = 0; // Contador de linhas
    int conectados = 0; // Variável para indicar se o primeiro e o último vértice estão conectados
    char linhaArquivo[LINHA]; // Vetor para armazenar uma linha do arquivo
    FILE *pa;

    pa =  fopen(nomeArquivo, "r"); // Abre o arquivo no modo leitura
    if (pa == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(linhaArquivo, LINHA, pa) != NULL)// Loop para ler cada linha do arquivo
    {
        if (contadorLinha == 0)// Ignora a primeira linha do arquivo (número de vértices)
        {
            contadorLinha++;
            continue;
        }

        if (contadorLinha == 1)
        {
            if (linhaArquivo[strlen(linhaArquivo) - 3] == '1') // Verifica se o primeiro vértice (linha 1) está conectado com o último (última linha)
            {
                conectados = 1;
            }
        }

        contadorLinha++;
    }

    fclose(pa);

    if (conectados == 1)
    {
        printf("Questão 12 - O Primeiro e o Último Vértice Estão Conectados.\n");
    }
    else
    {
        printf("Questão 12 - O Primeiro e o Último Vértice Não Estão Conectados.\n");
    }
}

int main(void)
{
    // Resposta do Tabalho:
    printf("**RESPOSTAS**\n");
    printf("Questão 1.\n");
    MaiorGrauVertice("dados_matriz.txt");
    printf("Questão 2.\n");
    escreveGrausVertices("dados_matriz.txt");
    printf("Questão 3.\n");
    verticesIsolados("dados_matriz.txt");
    printf("Questão 4.\n");
    printf("NA (Não se aplica)\n");
    printf("Questão 5.\n");
    printf("NA (Não se aplica)\n");
    printf("Questão 6.\n");
    printf("NA (Não se aplica)\n");
    printf("Questão 7 e 9.\n");
    MatrizComplementar("dados_matriz.txt");
    printf("Questão 8.\n");
    printf("NA (Não se aplica)\n");
    printf("Questão 10.\n");
    VerticesMultiplosDeCinco("dados_matriz.txt");
    printf("Questão 11.\n");
    printf("Resposta:\n");
    printf("Questão 12.\n");
    PrimeiroUltimoVertice("dados_matriz.txt");
    return 0;
}
