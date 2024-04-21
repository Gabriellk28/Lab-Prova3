#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para calcular o grau de um vértice
int GrauVertice(char *linha)
{
    int grau = 0; //Variável para armazenar o grau dos vértices

    for (int i = 0; linha[i] != '\0'; i++) //Laço de repetição para percorrer o vetor que contém a linha da matriz
    {
        if (linha[i] == '1') //Verifica se o índice do vetor contém o caracter 1
        {
            grau++; //Incrementa em 1 o grau do vértice
        }
    }
    return grau; //Retorna o grau do vétice.
}

//Função que Calcula o Maior vértice da matriz de adjacencia do grafo
int MaiorGrauVertice(char *nomeArquivo)
{
    int contadorLinha = 0; //Variável para contabilizar as linhas lidas
    int maiorGrau = 0; //Variável para armazenar o Maior grau 
    int numeroVerticeMaiorGrau = 0; //Variável para armazenar o número do vétice com maior grau
    int grau = 0; //váriável para armazenar os graus dos vértices
    char str[4228]; //Vetor para armazenar uma linha do arquivo

    FILE *fp = fopen(nomeArquivo, "r"); //Ponteiro para o arquivo
    if (fp == NULL) //
    {
        printf("Erro ao abrir o arquivo.\n");  // Se o arquivo não for aberto com sucesso
        return 1;
    }
    while (fgets(str, sizeof(str), fp) != NULL)// Loop para ler cada linha do arquivo
    {
        if (contadorLinha == 0)// Ignora a primeira linha do arquivo (número de vértices)
        {
            contadorLinha++;
            continue;
        }

        grau = GrauVertice(str);// Calcula o grau do vértice atual
        if (grau > maiorGrau)// Atualiza o maior grau e o número do vértice com maior grau se necessário
        {
            maiorGrau = grau;
            numeroVerticeMaiorGrau = contadorLinha;
        }
        contadorLinha++;
    }

    printf("Questão 1 - Vértice de Maior Grau: d(V%d) = %d.\n", numeroVerticeMaiorGrau, maiorGrau);// Imprime o resultado

}

void verticesIsolados(char *nomeArquivo)// Variável para contar os vértices isolados
{
    int verticesIsolados = 0;
    FILE *fp = fopen(nomeArquivo, "r");// Abre o arquivo no modo leitura
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");// Se o arquivo não for aberto com sucesso
        return;
    }

    char linha[4228];// Variável para armazenar a linha atual do arquivo
    int linhaAtual = 1; // Para acompanhar o número da linha
    int encontrouUm = 0; // Flag para indicar se encontrou algum '1' na linha

    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        encontrouUm = 0; // Reinicializa a flag para cada nova linha

        for (int i = 0; linha[i] != '\0'; i++)// Loop para percorrer cada caractere da linha
        {
            if (linha[i] == '1')// Se encontrar um '1', atualiza a flag e sai do loop interno
            {
                encontrouUm = 1; // Se encontrar um '1', atualiza a flag
                break; // Sai do loop assim que encontrar um '1'
            }
        }

        if (!encontrouUm)
        {
            printf("Vértice isolado encontrado na linha %d.\n", linhaAtual);// Se não encontrar nenhum '1', significa que a linha é de um vértice isolado
            verticesIsolados++;
        }

        linhaAtual++; // Atualiza o número da linha
    }

    fclose(fp);// Fecha o arquivo

    if (verticesIsolados == 0)
    {
        printf("Nenhum vértice isolado encontrado.\n");
    }
    else
    {
        printf("Total de vértices isolados: %d.\n", verticesIsolados);// Imprime o resultado
    }
}

void escreveGrausVertices(char *nomeArquivo)
{
    FILE *fp, *fp_graus;// Ponteiros para os arquivos de leitura e escrita
    char str[4228];// Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0;// Contador de linhas
    int grau = 0;// Variável para armazenar o grau do vértice

    fp = fopen(nomeArquivo, "r");// Abre o arquivo original para leitura
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");// Se o arquivo não for aberto com sucesso
        return;
    }

    fp_graus = fopen("dados_grafos_graus.txt", "w");// Abre o arquivo "dados_grafos_graus.txt" para escrita
    if (fp_graus == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n"); // Se o arquivo para escrita não for aberto com sucesso
        fclose(fp);
        return;
    }

    while (fgets(str, sizeof(str), fp) != NULL)// Lê a primeira linha do arquivo original (número de vértices) e ignora
    {
        if (contadorLinha == 0)// Calcula o grau do vértice atual
        {
            contadorLinha++;
            continue;
        }

        grau = GrauVertice(str);
        fprintf(fp_graus, "V%d: %d\n", contadorLinha, grau); // Escreve o grau do vértice no arquivo de saída no formato "V<número_vértice>: <grau>"
        contadorLinha++;
    }

    printf("Arquivo \"dados_grafos_graus.txt\" Gerado.\n");

    fclose(fp);// Fecha os arquivos
    fclose(fp_graus);
}

int PrimeiroUltimoVertice(char *nomeArquivo)
{
    int contadorLinha = 0;// Contador de linhas
    int conectados = 0;// Variável para indicar se o primeiro e o último vértice estão conectados
    char str[4228];// Vetor para armazenar uma linha do arquivo
    FILE *fp = fopen(nomeArquivo, "r");// Abre o arquivo no modo leitura
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");// Se o arquivo não for aberto com sucesso
        return 1;
    }
    while (fgets(str, sizeof(str), fp) != NULL)// Loop para ler cada linha do arquivo
    {
        if (contadorLinha == 0)// Ignora a primeira linha do arquivo (número de vértices)
        {
            contadorLinha++;
            continue;
        }

        if (contadorLinha == 1)
        {
            if (str[strlen(str) - 3] == '1')// Verifica se o primeiro vértice (linha 1) está conectado com o último (última linha)
            {
                conectados = 1;
            }
        }

        contadorLinha++;
    }

    if (conectados == 1)
    {
        printf("Questão 12 - O Primeiro e o Último Vértice Estão Conectados.\n");// Imprime o resultado
    } else {
        printf("Questão 12 - O Primeiro e o Último Vértice Não Estão Conectados.\n");
    }
}

void MatrizComplementar(char *nomeArquivoOriginal) {
    FILE *fp_original, *fp_complementar;// Ponteiros para os arquivos original e complementar
    char str[4228// Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0;// Contador de linhas

    fp_original = fopen(nomeArquivoOriginal, "r");// Abre o arquivo original para leitura
    if (fp_original == NULL) {// Se o arquivo não for aberto com sucesso
        printf("Erro ao abrir o arquivo original.\n");
        return;
    }

    fp_complementar = fopen("matriz_complementar.txt", "w");// Abre o arquivo "matriz_complementar.txt" para escrita
    if (fp_complementar == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");// Se o arquivo para escrita não for aberto com sucesso
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

void VerticesMultiplosDeCinco() 
{
    FILE *fp_entrada, *fp_saida;// Ponteiros para os arquivos de entrada e saída
    char str[4228];// Vetor para armazenar uma linha do arquivo
    int contadorLinha = 0;// Contador de linhas

    fp_entrada = fopen("dados_matriz.txt", "r");// Abre o arquivo "dados_matriz.txt" para leitura
    if (fp_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");// Se o arquivo não for aberto com sucesso
        return;
    }

    fp_saida = fopen("dados_grafo_gerador.txt", "w");// Abre o arquivo "dados_grafo_gerador.txt" para escrita
    if (fp_saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");// Se o arquivo para escrita não for aberto com sucesso
        fclose(fp_entrada);
        return;
    }

    while (fgets(str, sizeof(str), fp_entrada) != NULL) {// Loop para ler cada linha do arquivo de entrada
        if (contadorLinha != 0) {
            if (contadorLinha % 5 == 0) {// Verifica se não é a primeira linha (número de vértices) e se o número da linha é múltiplo de 5
                fprintf(fp_saida, "%s", str);// Copia a linha do vértice múltiplo de 5 para o arquivo de saída
            }
        }
        contadorLinha++;
    }

    fclose(fp_entrada);
    fclose(fp_saida);
}

int main(void)
{
    //Resposta do Tabalho:
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
    VerticesMultiplosDeCinco();
    printf("Questão 11.\n");
    printf("Resposta:\n");
    printf("Questão 12.\n");
    PrimeiroUltimoVertice("dados_matriz.txt");
    return 0;
}
