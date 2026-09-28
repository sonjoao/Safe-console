#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_BUFFER   256
#define MAX_LOGS     50
#define TAM_ALG      20

char historico[MAX_LOGS][TAM_BUFFER];
char algoritmo_usado[MAX_LOGS][TAM_ALG];
int total_logs = 0;
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


void registrar_log(const char *conteudo, const char *algoritmo) {
    if (total_logs >= MAX_LOGS) {
        printf("Limite de logs atingido. Log nao registrado.\n");
        return;
    }
    strncpy(historico[total_logs], conteudo, TAM_BUFFER - 1);
    historico[total_logs][TAM_BUFFER - 1] = '\0';

    strncpy(algoritmo_usado[total_logs], algoritmo, TAM_ALG - 1);
    algoritmo_usado[total_logs][TAM_ALG - 1] = '\0';

    total_logs++;
}


void buscar_logs(const char *termo) {
    int encontrados = 0;
    int i;

    for (i = 0; i < total_logs; i++) {
        if (strstr(historico[i], termo) != NULL) {
            printf("  [Log %d] (%s) %s\n", i + 1, algoritmo_usado[i], historico[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum log encontrado contendo \"%s\".\n", termo);
    }
}

void relatorio_auditoria(void) {
    int i;

    if (total_logs == 0) {
        printf("Nenhum log registrado ainda.\n");
        return;
    }

    printf("\n===================== RELATORIO DE AUDITORIA =====================\n");
    printf("%-5s %-12s %-10s %s\n", "ID", "ALGORITMO", "TAMANHO", "PAYLOAD");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < total_logs; i++) {
        printf("%-5d %-12s %-10lu %s\n",
               i + 1,
               algoritmo_usado[i],
               (unsigned long) strlen(historico[i]),
               historico[i]);
    }
    printf("====================================================================\n\n");
}


void menu_sanitizacao(void) {
    char entrada[TAM_BUFFER];
    char mascarado[TAM_BUFFER];

    printf("\n--- Sanitizacao de Dados ---\n");
    printf("Digite o dado sensivel (ex: CPF, cartao, token): ");
    ler_entrada(entrada, TAM_BUFFER);

    mascarar_dados(entrada, mascarado);
    printf("Dado mascarado: %s\n", mascarado);

    registrar_log(mascarado, "MASCARA");
}

void menu_validador_senha(void) {
    char senha[TAM_BUFFER];

    printf("\n--- Validador de Senha ---\n");
    printf("Digite a senha: ");
    ler_entrada(senha, TAM_BUFFER);

    if (validar_senha(senha)) {
        printf("Senha VALIDA (forte).\n");
        registrar_log("Senha validada com sucesso", "VALIDACAO");
    } else {
        printf("Senha INVALIDA. Requisitos: minimo 8 caracteres, "
               "1 maiuscula, 1 minuscula e 1 digito.\n");
        registrar_log("Tentativa de senha invalida", "VALIDACAO");
    }
}

void menu_cifra_cesar(void) {
    char texto[TAM_BUFFER];
    char original[TAM_BUFFER];
    int deslocamento;
    int opcao;

    printf("\n--- Cifra de Cesar ---\n");
    printf("Digite o texto: ");
    ler_entrada(texto, TAM_BUFFER);
    strcpy(original, texto);

    printf("Digite o deslocamento (numero inteiro): ");
    scanf("%d", &deslocamento);
    getchar(); 

    printf("1) Cifrar\n2) Descifrar\nEscolha: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 1) {
        cifrar_cesar(texto, deslocamento);
        printf("Texto cifrado: %s\n", texto);
        registrar_log(texto, "CESAR");
    } else if (opcao == 2) {
        descifrar_cesar(texto, deslocamento);
        printf("Texto descifrado: %s\n", texto);
        registrar_log(texto, "CESAR");
    } else {
        printf("Opcao invalida.\n");
    }
}

void menu_cifra_xor(void) {
    char texto[TAM_BUFFER];
    char chave_str[TAM_BUFFER];
    char chave;

    printf("\n--- Cifra XOR ---\n");
    printf("Digite o texto: ");
    ler_entrada(texto, TAM_BUFFER);

    printf("Digite a chave (um unico caractere): ");
    ler_entrada(chave_str, TAM_BUFFER);
    chave = chave_str[0];

    cifrar_xor(texto, chave);

    printf("Payload cifrado (hexadecimal): ");
    exibir_hex(texto, (int) strlen(texto));

    registrar_log(texto, "XOR");

    printf("Dica: aplique a cifra XOR novamente com a mesma chave "
           "sobre este payload para recuperar o texto original.\n");
}

void menu_logs(void) {
    int opcao;
    char termo[TAM_BUFFER];

    do {
        printf("\n--- Modulo de Logs e Auditoria ---\n");
        printf("1) Ver relatorio de auditoria\n");
        printf("2) Buscar termo nos logs\n");
        printf("0) Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                relatorio_auditoria();
                break;
            case 2:
                printf("Digite o termo a buscar: ");
                ler_entrada(termo, TAM_BUFFER);
                buscar_logs(termo);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}


int main(void) {
    int opcao;

    printf("============================================\n");
    printf("           SAFECONSOLE C - v1.0\n");
    printf("============================================\n");

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1) Sanitizacao (mascarar dados)\n");
        printf("2) Validador de senha\n");
        printf("3) Cifra de Cesar\n");
        printf("4) Cifra XOR\n");
        printf("5) Logs e Auditoria\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        getchar();

        switch (opcao) {
            case 1: menu_sanitizacao();      break;
            case 2: menu_validador_senha();  break;
            case 3: menu_cifra_cesar();      break;
            case 4: menu_cifra_xor();        break;
            case 5: menu_logs();             break;
            case 0: printf("Encerrando o SafeConsole C.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
