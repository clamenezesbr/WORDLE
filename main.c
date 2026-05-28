//Gabriel Menezes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_PALAVRA 5
#define MAX_TENTATIVAS 6
#define NUM_MAX_PALAVRAS 50000
#define DICIONARIO "dicionario.txt"
#define SCORES "scores.txt"

#define RESET  "\033[0m"
#define BOLD   "\033[1m"
#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN  "\033[1;32m"
#define GRAY   "\033[90m"

static char palavras[NUM_MAX_PALAVRAS][MAX_PALAVRA + 1];

void enableColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

int palavranodicionario(char *palavra) {
    FILE *arquivo = fopen(DICIONARIO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo do dicionario.\n");
        return 0;
    }

    char linha[64];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strcmp(linha, palavra) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void printResultado(char *palpite, char *resultado) {
    printf("  ");
    for (int i = 0; i < MAX_PALAVRA; i++) {
        if (resultado[i] == '^') {
            printf(GREEN "[%c]" RESET, palpite[i]);
        } else if (resultado[i] == '!') {
            printf(YELLOW "[%c]" RESET, palpite[i]);
        } else {
            printf(RED "[%c]" RESET, palpite[i]);
        }
    }
    printf("\n");
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    enableColors();
    srand(time(NULL));

    printf(BOLD "\n=== Bem-vindo ao Wordle! ===\n\n" RESET);

    int numPalavras = 0;
    char palavracerta[MAX_PALAVRA + 1];

    FILE *dicionariofile = fopen(DICIONARIO, "r");
    if (dicionariofile == NULL) {
        printf("Erro ao abrir o arquivo do dicionario.\n");
        return 1;
    }

    char linha[64];
    while (fgets(linha, sizeof(linha), dicionariofile) != NULL && numPalavras < NUM_MAX_PALAVRAS) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (strlen(linha) == MAX_PALAVRA) {
            strcpy(palavras[numPalavras], linha);
            numPalavras++;
        }
    }
    fclose(dicionariofile);

    if (numPalavras == 0) {
        printf("Nenhuma palavra de %d letras encontrada no dicionario.\n", MAX_PALAVRA);
        return 1;
    }

    strcpy(palavracerta, palavras[randomInRange(0, numPalavras - 1)]);

    printf("Uma palavra de %d letras foi escolhida. Tente adivinhar!\n\n", MAX_PALAVRA);
    printf("Legenda: " GREEN "[x]" RESET " certa  " YELLOW "[x]" RESET " posicao errada  " RED "[x]" RESET " nao esta na palavra\n");

    int tentativa = 0;
    char palpite[MAX_PALAVRA + 2];
    char resultado[MAX_PALAVRA + 1];
    char nome[100];

    while (tentativa < MAX_TENTATIVAS) {
        printf("\nTentativa %d de %d: ", tentativa + 1, MAX_TENTATIVAS);
        scanf("%100s", palpite);
        palpite[MAX_PALAVRA + 1] = '\0';

        if (strlen(palpite) != MAX_PALAVRA) {
            printf("Por favor, insira uma palavra de %d letras.\n", MAX_PALAVRA);
            continue;
        }

        if (!palavranodicionario(palpite)) {
            printf("A palavra nao esta no dicionario.\n");
            continue;
        }

        // Primeira passagem: acertos exatos
        char usadoPalavra[MAX_PALAVRA] = {0};
        char usadoPalpite[MAX_PALAVRA] = {0};
        memset(resultado, 'x', MAX_PALAVRA);
        resultado[MAX_PALAVRA] = '\0';

        for (int i = 0; i < MAX_PALAVRA; i++) {
            if (palpite[i] == palavracerta[i]) {
                resultado[i] = '^';
                usadoPalavra[i] = 1;
                usadoPalpite[i] = 1;
            }
        }

        // Segunda passagem: letras certas na posicao errada
        for (int i = 0; i < MAX_PALAVRA; i++) {
            if (usadoPalpite[i]) continue;
            for (int j = 0; j < MAX_PALAVRA; j++) {
                if (!usadoPalavra[j] && palpite[i] == palavracerta[j]) {
                    resultado[i] = '!';
                    usadoPalavra[j] = 1;
                    break;
                }
            }
        }

        printResultado(palpite, resultado);

        if (strcmp(palavracerta, palpite) == 0) {
            printf("\nParabens! Voce acertou em %d tentativa(s)!\n", tentativa + 1);

            printf("Digite seu nome: ");
            scanf("%99s", nome);

            FILE *scoresFile = fopen(SCORES, "a");
            if (scoresFile == NULL) {
                printf("Erro ao abrir o arquivo de scores.\n");
                return 1;
            }

            fprintf(scoresFile, "%s %s %d %d\n", nome, palavracerta, tentativa + 1, (int)time(NULL));
            fclose(scoresFile);
            return 0;
        }

        tentativa++;
    }

    printf("\nVoce nao acertou! A palavra era: " GREEN "%s" RESET "\n", palavracerta);
    return 0;
}
