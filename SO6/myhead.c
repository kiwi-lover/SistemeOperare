#include <stdio.h>
#include <stdlib.h>

void print_lines(FILE *f, int num_lines) {
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
        count++;
        if (count >= num_lines) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Eroare! Trebuie să specifici un fișier și opțiunea (de exemplu -n 2 pentru primele 2 linii).\n");
        return 1;
    }

    FILE *f = fopen(argv[2], "r");
    if (f == NULL) {
        printf("Fișierul nu a fost găsit!\n");
        return 1;
    }

    int num_lines = 10;  // default
    if (argv[1][1] == 'n') {
        num_lines = atoi(argv[2]);
    }

    print_lines(f, num_lines);
    fclose(f);
    return 0;
}

