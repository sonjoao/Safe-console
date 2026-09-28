
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER 256


void ler_entrada(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}


void mascarar_dados(const char *entrada, char *saida) {
    int tamanho = (int) strlen(entrada);
    int i;

    for (i = 0; i < tamanho; i++) {
        if (i < tamanho - 4) {
            saida[i] = '*';
        } else {
            saida[i] = entrada[i];
        }
    }
    saida[tamanho] = '\0';
}


int validar_senha(const char *senha) {
    int tamanho = (int) strlen(senha);
    int tem_maiuscula = 0;
    int tem_minuscula = 0;
    int tem_digito = 0;
    int i;

    if (tamanho < 8) {
        return 0;
    }

    for (i = 0; i < tamanho; i++) {
        unsigned char c = (unsigned char) senha[i];
        if (isupper(c)) tem_maiuscula = 1;
        else if (islower(c)) tem_minuscula = 1;
        else if (isdigit(c)) tem_digito = 1;
    }

    return (tem_maiuscula && tem_minuscula && tem_digito);
}


int main(void) {
    char entrada[TAM_BUFFER];
    char mascarado[TAM_BUFFER];
    char senha[TAM_BUFFER];

    printf("### Teste: mascarar_dados() ###\n");
    printf("Digite um dado sensivel (ex: CPF, cartao): ");
    ler_entrada(entrada, TAM_BUFFER);
    mascarar_dados(entrada, mascarado);
    printf("Resultado: %s\n\n", mascarado);

    printf("### Teste: validar_senha() ###\n");
    printf("Digite uma senha: ");
    ler_entrada(senha, TAM_BUFFER);
    if (validar_senha(senha)) {
        printf("Resultado: senha VALIDA\n");
    } else {
        printf("Resultado: senha INVALIDA (min 8 caracteres, 1 maiuscula, "
               "1 minuscula, 1 digito)\n");
    }

    return 0;
}
