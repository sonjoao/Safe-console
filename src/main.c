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
