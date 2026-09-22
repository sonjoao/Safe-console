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