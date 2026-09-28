
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER 256


void cifrar_cesar(char *texto, int deslocamento) {
    int tamanho = (int) strlen(texto);
    int desloc = ((deslocamento % 26) + 26) % 26; 
    int i;

    for (i = 0; i < tamanho; i++) {
        unsigned char c = (unsigned char) texto[i];
        if (isupper(c)) {
            texto[i] = (char) ('A' + (c - 'A' + desloc) % 26);
        } else if (islower(c)) {
            texto[i] = (char) ('a' + (c - 'a' + desloc) % 26);
        }
    }
}

void descifrar_cesar(char *texto, int deslocamento) {
    cifrar_cesar(texto, 26 - ((deslocamento % 26) + 26) % 26);
}


void cifrar_xor(char *texto, char chave) {
    int tamanho = (int) strlen(texto);
    int i;
    for (i = 0; i < tamanho; i++) {
        texto[i] = (char) (texto[i] ^ chave);
    }
}


void exibir_hex(const char *texto, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%02X ", (unsigned char) texto[i]);
    }
    printf("\n");
}

int main(void) {
    char texto[TAM_BUFFER];
    char copia[TAM_BUFFER];
    int deslocamento;
    char chave;

    printf("### Teste: Cifra de Cesar ###\n");
    printf("Digite um texto: ");
    fgets(texto, TAM_BUFFER, stdin);
    texto[strcspn(texto, "\n")] = '\0';
    strcpy(copia, texto);

    printf("Digite o deslocamento (ex: 3): ");
    scanf("%d", &deslocamento);
    getchar();

    cifrar_cesar(texto, deslocamento);
    printf("Cifrado:    %s\n", texto);

    descifrar_cesar(texto, deslocamento);
    printf("Descifrado: %s  (deve voltar a ser igual ao original: %s)\n\n",
           texto, copia);

    printf("### Teste: Cifra XOR ###\n");
    printf("Digite um texto: ");
    fgets(texto, TAM_BUFFER, stdin);
    texto[strcspn(texto, "\n")] = '\0';

    printf("Digite uma chave (1 caracter): ");
    scanf(" %c", &chave);

    cifrar_xor(texto, chave);
    printf("Cifrado (hex): ");
    exibir_hex(texto, (int) strlen(texto));

    cifrar_xor(texto, chave); 
    printf("Descifrado: %s\n", texto);

    return 0;
}
