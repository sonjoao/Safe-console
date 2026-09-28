

#include <stdio.h>
#include <string.h>

#define TAM_BUFFER 256
#define MAX_LOGS   50
#define TAM_ALG    20

char historico[MAX_LOGS][TAM_BUFFER];
char algoritmo_usado[MAX_LOGS][TAM_ALG];
int total_logs = 0;


void registrar_log(const char *conteudo, const char *algoritmo) {
    if (total_logs >= MAX_LOGS) {
        printf("Topo de logs atingido. Log nao registrado.\n");
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
        printf("Não há logs contendo \"%s\".\n", termo);
    }
}


void relatorio_auditoria(void) {
    int i;

    if (total_logs == 0) {
        printf("Nenhum log registrado ainda.\n");
        return;
    }

    printf("\n##################### RELATORIO DE AUDITORIA #####################\n");
    printf("%-5s %-12s %-10s %s\n", "ID", "ALGORITMO", "TAMANHO", "PAYLOAD");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < total_logs; i++) {
        printf("%-5d %-12s %-10lu %s\n",
               i + 1,
               algoritmo_usado[i],
               (unsigned long) strlen(historico[i]),
               historico[i]);
    }
    printf("#######################################################################\n\n");
}

int main(void) {
    char termo[TAM_BUFFER];

    printf("### Teste: registrando alguns logs de exemplo ###\n");
    registrar_log("*******8901", "MASCARA");
    registrar_log("Khoor Pxqgr", "CESAR");
    registrar_log("38 0E 0C 19", "XOR");
    printf("3 logs de exemplo (registro log).\n");

    relatorio_auditoria();

    printf("### Teste: buscar_logs() ###\n");
    printf("Digite um termo para buscar (ex: Khoor): ");
    fgets(termo, TAM_BUFFER, stdin);
    termo[strcspn(termo, "\n")] = '\0';
    buscar_logs(termo);

    return 0;
}
