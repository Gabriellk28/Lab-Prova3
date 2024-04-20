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
            return 0; // Se encontrar um '1', não é um vértice isolado
        }
    }
    return 1; // Se não encontrar nenhum '1', é um vértice isolado
}

void escreverGraus(char *nomeArquivo)
{
    FILE *fp, *fp_graus;
    char str[4228];
    int contadorLinha = 0;
    int grau = 0;

    fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fp_graus = fopen("dados_grafos_graus.txt", "w");
    if (fp_graus == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(fp);
        return;
    }

    while (fgets(str, sizeof(str), fp) != NULL)
    {
        if (contadorLinha == 0)
        {
            contadorLinha++;
            continue;
        }

        grau = calculaGrauVertice(str);
        fprintf(fp_graus, "V%d: %d\n", contadorLinha, grau);
        contadorLinha++;
    }

    fclose(fp);
    fclose(fp_graus);
}

void escreverMatrizComplementar(char *nomeArquivoOriginal) {
    FILE *fp_original, *fp_complementar;
    char str[4228];
    int contadorLinha = 0;

    fp_original = fopen(nomeArquivoOriginal, "r");
    if (fp_original == NULL) {
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    fp_complementar = fopen("matriz_complementar.txt", "w");
    if (fp_complementar == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        fclose(fp_original);
        return;
    }

    // Lê a primeira linha do arquivo original
    fgets(str, sizeof(str), fp_original);
    // Escreve a mesma linha no arquivo complementar
    fprintf(fp_complementar, "%s", str);

    // Para as linhas restantes do arquivo original
    while (fgets(str, sizeof(str), fp_original) != NULL) {
        // Contador de colunas
        int contadorColuna = 0;
        // Percorre cada caractere da linha
        for (int i = 0; str[i] != '\0'; i++) {
            // Se for um espaço em branco ou um número, escreve o caractere no arquivo complementar
            if (str[i] == ' ' || (str[i] >= '0' && str[i] <= '1')) {
                fprintf(fp_complementar, "%c", str[i]);
            }
            // Se for um número, incrementa o contador de colunas
            if (str[i] == '1' || str[i] == '0') {
                contadorColuna++;
            }
        }
        // Se for uma linha válida da matriz original
        if (contadorLinha != 0) {
            // Calcula o número de zeros que devem ser adicionados na linha complementar
            int numeroZeros = contadorLinha - contadorColuna;
            // Escreve os zeros faltantes na linha complementar
            for (int j = 0; j < numeroZeros; j++) {
                fprintf(fp_complementar, " 0");
            }
            // Pula para a próxima linha no arquivo complementar
            fprintf(fp_complementar, "\n");
        }
        // Incrementa o contador de linha
        contadorLinha++;
    }

    fclose(fp_original);
    fclose(fp_complementar);
}

int main(void)
{
    FILE *fp;
    char str[4228];
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
            if (str[strlen(str) - 3] == '1')
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

    printf("Questão 1 - Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);

    printf("Questão 2 - Total de vértices isolados: %d.\n", quantidadeVerticesIsolados);

    if (conectados == 1)
    {
        printf("Questão 12 - O Primeiro e o Último Vértice Estão Conectados.\n");
    }

    escreverGraus("dados_matriz.txt");

    escreverMatrizComplementar("dados_matriz.txt");

    return 0;
}
