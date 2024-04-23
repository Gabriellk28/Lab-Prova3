#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINHA 4228

// Função para calcular o grau de um vértice
int GrauVertice(char *linha)
{
    // Variável para armazenar o grau dos vértices
    int grau = 0;

    // Laço de repetição para percorrer o vetor que contém a linha da matriz
    for (int i = 0; linha[i] != '\0'; i++)
    {
        // Verifica se o índice do vetor contém o caracter 1
        if (linha[i] == '1')
        {
            // Incrementa em 1 o grau do vértice
            grau++;
        }
    }
    // Retorna o grau do vétice.
    return grau;
}

// Função que Calcula o Maior vértice da matriz de adjacencia do grafo
int MaiorGrauVertice(char *nomeArquivo)
{
    int contadorLinha = 0;          // Variável para contabilizar as linhas lidas
    int maiorGrau = 0;              // Variável para armazenar o Maior grau
    int numeroVerticeMaiorGrau = 0; // Variável para armazenar o número do vétice com maior grau
    int grau = 0;                   // váriável para armazenar os graus dos vértices
    char linhaArquivo[LINHA];       // Vetor para armazenar uma linha do arquivo

    // Ponteiro para o arquivo
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
    {
        // Informa se ocorreu um erro ao abrir o arquivo
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Laço de repetição para percorrer o vetor que contém a linha da matriz
    while (fgets(linhaArquivo, LINHA, fp) != NULL)
    {
        // Verifica se está na primeira linha
        if (contadorLinha == 0)
        {
            // Incrementa o contador de linha em 1
            contadorLinha++;

            // Continua a execução
            continue;
        }

        // Calcula o grau do vértice
        grau = GrauVertice(linhaArquivo);

        // Verifica se o o grau do vértice da linha é o maior
        if (grau > maiorGrau)
        {
            // O grau do vértice passa a ser o maior
            maiorGrau = grau;

            // Armazena o número do vértice de maior grau
            numeroVerticeMaiorGrau = contadorLinha;
        }

        // Incrementa o contador de linha em 1
        contadorLinha++;
    }

    // Informa a resposta
    printf("Resposta: Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);
}

// Função para escrevero número do vértices seguido pelo seu respectivo grau em um arquivo
void escreveGrausVertices(char *nomeArquivo)
{
    FILE *paEntrada, *paSaida;// Ponteiros para os arquivos de entrada e saída
    char linhaArquivo[LINHA]; // Vetor para armazenar uma linha do arquivo
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

    printf("Resposta: Arquivo \"dados_grafos_graus.txt\" Gerado.\n");

    fclose(paEntrada);
    fclose(paSaida);
}

void verticesIsolados(char *nomeArquivo)
{
    int verticesIsolados = 0; // Variável para armazenar a quantidade de vértices isolados no grafo
    char linha[4228];
    int linhaAtual = 1;  // Para acompanhar o número da linha
    int vertice = 0; // Variável para indicar se encontrou algum '1' na linha
    FILE *pa;
    pa = fopen(nomeArquivo, "r");
    if (pa == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), pa) != NULL)
    {
        vertice = 0; // Reinicializa a variável para cada nova linha

        for (int i = 0; linha[i] != '\0'; i++)
        {
            if (linha[i] == '1')
            {
                vertice = 1; // Se encontrar um '1', atualiza a flag
                break;           // Sai do loop assim que encontrar um '1'
            }
        }

        if (!vertice)
        {
            printf("Vértice isolado encontrado na linha %d.\n", linhaAtual);
            verticesIsolados++;
        }

        linhaAtual++; // Atualiza o número da linha
    }

    fclose(pa);

    if (verticesIsolados == 0)
    {
        printf("Resposta: Nenhum vértice isolado encontrado.\n");
    }
    else
    {
        printf("Resposta: Total de vértices isolados: %d.\n", verticesIsolados);
    }
}

void MatrizComplementar(char *nomeArquivo) 
{
    FILE *paEntrada, *paSaida; // Ponteiros para os arquivos de entrada e saída
    char linhaArquivo[LINHA]; // Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0; // Contador de linhas
    int i = 0;

    // Abre o arquivo "dados_matriz.txt" para leitura 
    paEntrada = fopen(nomeArquivo, "r");
    if (paEntrada == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    // Abre o arquivo "matriz_complementar.txt" para escrita
    paSaida = fopen("matriz_complementar.txt", "w");
    if (paSaida == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(paEntrada);
        return;
    }

    // Laço de repetição para percorrer o arquivo
    while (fgets(linhaArquivo, sizeof(linhaArquivo), paEntrada) != NULL) 
    {   
        // Ignora a primeira linha do arquivo (número de vértices)
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        // Laço de repetição para percorrer a linha da matriz
        for (i = 1; linhaArquivo[i] != '\0'; i++)
        {   
            // Verifica se o índice do vetor está na diagonal principal
            if (i == contadorLinha) // Não modifica a diagonal principal
            {
                continue;
            }
            else
            {
                // Inverte os valores 0 e 1
                if (linhaArquivo[i] == '1')
                {
                    linhaArquivo[i] = '0';
                }
                else if (linhaArquivo[i] == '0')
                {
                    linhaArquivo[i] = '1';
                }
            }
        }

    // Escreve a linha modificada no arquivo de saída
    fprintf(paSaida, "%s", linhaArquivo);

    // Adiciona quebra de linha se necessário
    if (linhaArquivo[i] != '\n') fputs("\n", paSaida);

        contadorLinha++;
    }

    fclose(paEntrada);
    fclose(paSaida);
    printf("Resposta: Arquivo \"matriz_complementar.txt\" gerado.\n");
}

// Função para imprimir os vértices do grafo que sejam multiplos de 5
void VerticesMultiplosDeCinco(char *arquivo)
{
    FILE *paEntrada = NULL, *paSaida = NULL; // Ponteiros para os arquivos de entrada e saída
    char linhaArquivo[LINHA];                // Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0;                   // Contador de linhas

    // Abre o arquivo "dados_matriz.txt" para leitura
    paEntrada = fopen(arquivo, "r");
    if (paEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    // Abre o arquivo "dados_grafo_gerador.txt" para escrita
    paSaida = fopen("dados_grafo_gerador.txt", "w");
    if (paSaida == NULL)
    {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(paEntrada);
        return;
    }

    // Laço de repetição para percorrer o arquivo
    while (fgets(linhaArquivo, LINHA, paEntrada) != NULL)
    {
        // Veririca se não é a primeira linha do arquivo
        if (contadorLinha != 0)
        {
            // Verifica se o número armazenado pelo contador de linhas é multiplo de 5
            if (contadorLinha % 5 == 0)
            {
                // Implique a linha no arquivo "dados_grafo_gerador.txt"
                fprintf(paSaida, "%s", linhaArquivo);
            }
        }

        // Incrementa o contador de linhas em 1
        contadorLinha++;
    }

    // Fecha os arquivos
    fclose(paEntrada);
    fclose(paSaida);

    // Imprime a resposta da questão
    printf("Resposta: Arquivo \"dados_grafo_gerador.txt\" Gerado.\n");
}

// Função para verificar se o primeiro e último vértices do grafo estão conectados
int PrimeiroUltimoVertice(char *nomeArquivo)
{
    int contadorLinha = 0;    // Contador de linhas
    int conectados = 0;       // Variável para indicar se o primeiro e o último vértice estão conectados
    char linhaArquivo[LINHA]; // Vetor para armazenar uma linha do arquivo
    FILE *pa;                 // Poneteiro para o arquivo

    // Abre o arquivo "dados_matriz.txt" para leitura
    pa = fopen(nomeArquivo, "r");

    // Verifica se houver algum erro ao abrir o arquivo
    if (pa == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Laço de repetição para percorrer o arquivo
    while (fgets(linhaArquivo, LINHA, pa) != NULL)
    {
        // Ignora a primeira linha do arquivo (número de vértices)
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        // Verifica se está é a primeira linha
        if (contadorLinha == 1)
        {
            // Verifica se o primeiro vértice (linha 1) está conectado com o último (última linha)
            if (linhaArquivo[strlen(linhaArquivo) - 3] == '1')
            {
                // A variável recebe 1 caso estejam conectados
                conectados = 1;
            }
        }

        // Incrementa o contador de linhas em 1
        contadorLinha++;
    }

    // Fecha o arquivo
    fclose(pa);

    // Imprime a resposta da questão
    if (conectados == 1)
    {
        printf("Respoat: O Primeiro e o Último Vértice Estão Conectados.\n");
    }
    else
    {
        printf("Resposta: O Primeiro e o Último Vértice Não Estão Conectados.\n");
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
    printf("Resposta: NA (Não se aplica)\n");
    printf("Questão 5.\n");
    printf("Resposta: NA (Não se aplica)\n");
    printf("Questão 6.\n");
    printf("Resposta: NA (Não se aplica)\n");
    printf("Questão 7 e 9.\n");
    MatrizComplementar("dados_matriz.txt");
    printf("Questão 8.\n");
    printf("Resposta: NA (Não se aplica)\n");
    printf("Questão 10.\n");
    VerticesMultiplosDeCinco("dados_matriz.txt");
    printf("Questão 11.\n");
    printf("Resposta:\n");
    printf("Questão 12.\n");
    PrimeiroUltimoVertice("dados_matriz.txt");
    return 0;
}
