#include <stdio.h>

int imprimirMatriz() 
{

}

int main(void) 
{
        FILE *fp;
    char str[4226];

    fp = fopen("dados_matriz.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(str, sizeof(str), fp) != NULL) {
        printf("%s", str);
    }

    return 0;
}
