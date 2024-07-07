#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT_FILE_SIZE 512

char *readWord(FILE *inputFile) {
    char *word = calloc(100, 1);
    int i = 0;
    int spaceIsDelimiter = 1;

    while (1) {
        char c = fgetc(inputFile);
        if (c == ' ') {
            if (spaceIsDelimiter) {
                if (i > 0)
                    break;
                continue;
            }
        }
        else if (c == '\n') {
            if (i > 0)
                break;           
            continue;
        }
        else if (c == ',' || c == EOF) {
            break;
        }
        else if (c == '\'') {
            spaceIsDelimiter = 0;
        } 
        word[i++] = c;
    }
    return word;
}

void parse(char *inputFileName, char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "wb");
    int totalBytesWriten = 0;
    char *word;
    word = readWord(inputFile);  /* .bits */
    free(word);
    word = readWord(inputFile);  /* 16 */ 
    free(word);
    word = readWord(inputFile);
    while (strcmp(word, "halt:") != 0) {
        if (strcmp(word, "movb") == 0) {
            char *valor = readWord(inputFile);
            char *registrador = readWord(inputFile);
            if (strcmp(registrador, "%ah") == 0) {
                short primeiroParBytes = 0x0EB4;
                fwrite(&primeiroParBytes, 2, 1, outputFile);
                totalBytesWriten += 2;
            } else if (strcmp(registrador, "%al") == 0) {
                int i = 0;
                for (i = 0; i < strlen(valor); i++) {
                    if (valor[i] == '\'')
                        break;
                }
                char valorCaractere = valor[i+1];
                char valorRegistrador = 0xB0;
                fwrite(&valorRegistrador, 1, 1, outputFile);
                fwrite(&valorCaractere, 1, 1, outputFile);
                totalBytesWriten += 2;
            }
            free(valor);
            free(registrador);
        } else if (strcmp(word, "int") == 0) {
            char *ten = readWord(inputFile);
            short parBytesVideo = 0x10CD;
            fwrite(&parBytesVideo, 2, 1, outputFile);
            free(ten);
            totalBytesWriten += 2;
        }
        else {
            printf("Arquivo de entrada diferente do esperado!");
            exit(-1);
        }
        free(word);
        word = readWord(inputFile);        
    }
    char byteHalt = 0XF4;
    fwrite(&byteHalt, 1, 1, outputFile);
    short parBytesJumpHalt = 0XFDEB;
    fwrite(&parBytesJumpHalt, 2, 1, outputFile);
    totalBytesWriten += 3;
    int i;
    for (i = 0; i < OUTPUT_FILE_SIZE - totalBytesWriten - 2; i++) {
        char zero = 0;
        fwrite(&zero, 1, 1, outputFile);
    }
    short parBytesFimArquivo = 0XAA55;
    fwrite(&parBytesFimArquivo, 2, 1, outputFile);
    free(word);
    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Quantidade de parâmetros inválida!");
        return -1;
    }

    char inputFileName[10];
    strcpy(inputFileName, argv[1]);

    if (strcmp(inputFileName, "hw.S") != 0) {
        printf("Arquivo de entrada diferente do esperado!");
        return -1;
    }

    char outputFileName[10];
    strcpy(outputFileName, argv[2]);

    if (strcmp(outputFileName, "hw.bin") != 0) {
        printf("Arquivo de saída diferente do esperado!");
        return -1;
    }

    parse(inputFileName, outputFileName);

    return 0;
}
