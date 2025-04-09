#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Eroare! Trebuie să specifici 3 argumente: fișierul de intrare, fișierul de ieșire și caracterele de înlocuit.\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Fișierul de intrare nu a fost găsit!\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "r+");
    if (output != NULL) {
        char confirm;
        printf("Fișierul există deja. Vrei să îl suprascrii? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm != 'y' && confirm != 'Y') {
            printf("anulată.\n");
            fclose(input);
            return 0;
        }
    } else {
        output = fopen(argv[2], "w");
    }

    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c == argv[3][0]) { 
            c = argv[4][0];
        }
        fputc(c, output);
    }

    printf("succes!\n");
    fclose(input);
    fclose(output);
    return 0;
}

