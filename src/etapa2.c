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
