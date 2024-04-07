//Gabriel Menezes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 5
#define MAX_TENTATIVAS 6
#define NUM_MAX_PALAVRAS 1000 // Número máximo de palavras a serem lidas do arquivo
#define DICIONARIO "dicionario.txt"
#define SCORES "scores.txt"

// Confere se a palavra está no dicionário
int palavranodicionario(char *palavra) {
    FILE *arquivo = fopen(DICIONARIO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo do dicionário.\n");
        return 0; // Erro ao abrir o arquivo
    }

    char palavradicionario[MAX_PALAVRA + 1];

    while (fgets(palavradicionario, sizeof(palavradicionario), arquivo) != NULL) {
        palavradicionario[strcspn(palavradicionario, "\n")] = '\0';
        if (strcmp(palavradicionario, palavra) == 0) {
            fclose(arquivo);
            return 1; // Palavra encontrada
        }
    }

    fclose(arquivo);
    return 0; // Palavra não* encontrada
}

// Gera o número aleatório entre min e max
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Função principal
int main() {
    srand(time(NULL));

    printf("Bem-vindo ao quase Wordle!\n\n");

    char palavras[NUM_MAX_PALAVRAS][MAX_PALAVRA + 1];
    int numPalavras = 0;
    char palavracerta[MAX_PALAVRA + 1];

    FILE *dicionariofile = fopen(DICIONARIO, "r");
    if (dicionariofile == NULL) {
        printf("Erro ao abrir o arquivo do dicionário.\n");
        return 1;
    }

    char palavradicionario[MAX_PALAVRA + 1];
    while (fgets(palavradicionario, sizeof(palavradicionario), dicionariofile) != NULL && numPalavras < NUM_MAX_PALAVRAS) {
        palavradicionario[strcspn(palavradicionario, "\n")] = '\0';
        if (strlen(palavradicionario) == MAX_PALAVRA) { // Considerar apenas pavras com 5 letras
            strcpy(palavras[numPalavras], palavradicionario);
            numPalavras++;
        }
    }
    fclose(dicionariofile);

    if (numPalavras == 0) {
        printf("Nenhuma palavra de tamanho %d encontrada no dicionário.\n", MAX_PALAVRA);
        return 1;
    }

    strcpy(palavracerta, palavras[randomInRange(0, numPalavras - 1)]);

    printf("Uma palavra de %d letras foi escolhida aleatoriamente do dicionário.\n", MAX_PALAVRA);
    printf("Tente adivinhar qual é!\n");

    int tentativa = 0;
    char palpite[MAX_PALAVRA + 1];
    char resultado[MAX_PALAVRA + 1];
    char nome[100];

    while (tentativa < MAX_TENTATIVAS) {
        printf("\nTentativa %d de %d: ", tentativa + 1, MAX_TENTATIVAS);
        scanf("%s", palpite);

        if (strlen(palpite) != MAX_PALAVRA) {
            printf("Por favor, insira uma palavra de %d letras.\n", MAX_PALAVRA);
            continue;
        }

        if (!palavranodicionario(palpite)) {
            printf("A palavra não está no dicionário.\n");
            continue;
        }

        // Verificação das letras e posições
        memset(resultado, 'x', MAX_PALAVRA);
        resultado[MAX_PALAVRA] = '\0';

        for (int i = 0; i < MAX_PALAVRA; i++) {
            if (palpite[i] == palavracerta[i]) {
                resultado[i] = '^'; // Posição e letra corretas
            } else {
                for (int j = 0; j < MAX_PALAVRA; j++) {
                    if (palpite[i] == palavracerta[j] && resultado[j] != '^') {
                        resultado[j] = '!'; // Posição errada e letra certa
                        break;
                    }
                }
            }
        }

        printf("Resultado: %s\n", resultado);

        if (strcmp(palavracerta, palpite) == 0) {
            printf("\nParabéns! Você acertou a palavra secreta!\n");

            printf("Digite seu nome: ");
            scanf("%s", nome);

            FILE *scoresFile = fopen(SCORES, "a");
            if (scoresFile == NULL) {
                printf("Erro ao abrir o arquivo de scores.\n");
                return 1;
            }

            // Informações do jogador no arquivo 'scores'
            fprintf(scoresFile, "%s %s %d %d\n", nome, palavracerta, tentativa + 1, (int)time(NULL));

            fclose(scoresFile);
            return 0;
        }

        tentativa++;
    }

    printf("\nVocê não acertou a palavra! A palavra era: %s\n", palavracerta);
    return 0;
}
  

