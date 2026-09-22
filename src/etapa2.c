void cifrar_cesar(char *texto, int deslocamento) {
    int tamanho = (int) strlen(texto);
    int desloc = ((deslocamento % 26) + 26) % 26; /* normaliza negativos */
    int i;

    for (i = 0; i < tamanho; i++) {
        unsigned char c = (unsigned char) texto[i];
        if (isupper(c)) {
            texto[i] = (char) ('A' + (c - 'A' + desloc) % 26);
        } else if (islower(c)) {
            texto[i] = (char) ('a' + (c - 'a' + desloc) % 26);
        }
        /* demais caracteres nao sao alterados */
    }
}

/* Descifra Cesar: aplica o deslocamento inverso */
void descifrar_cesar(char *texto, int deslocamento) {
    cifrar_cesar(texto, 26 - ((deslocamento % 26) + 26) % 26);
}

/* Cifra XOR: cada byte do texto faz XOR com a chave.
   A mesma funcao cifra e descifra (XOR e reversivel). */
void cifrar_xor(char *texto, char chave) {
    int tamanho = (int) strlen(texto);
    int i;
    for (i = 0; i < tamanho; i++) {
        texto[i] = (char) (texto[i] ^ chave);
    }
}

/* Imprime o conteudo de um buffer em formato hexadecimal (%02X) */
void exibir_hex(const char *texto, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%02X ", (unsigned char) texto[i]);
    }
    printf("\n");
}