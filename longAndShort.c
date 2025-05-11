#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

void convert_case(char *str, int to_upper) {
    while (*str) {
        *str = to_upper ? toupper((unsigned char)*str) : tolower((unsigned char)*str);
        str++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s source.txt short.txt long.txt\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    FILE *out1 = fopen(argv[2], "w");
    FILE *out2 = fopen(argv[3], "w");

    if (!src || !out1 || !out2) {
        perror("File error");
        return 1;
    }

    char line[MAX_LINE];
    int count1 = 0, count2 = 0;

    while (fgets(line, sizeof(line), src)) {
        size_t len = strlen(line);
        if (len && line[len - 1] == '\n') line[len - 1] = '\0';

        if (strlen(line) < 20) {
            convert_case(line, 1);
            fprintf(out1, "%s\n", line);
            count1++;
        } else {
            convert_case(line, 0);
            fprintf(out2, "%s\n", line);
            count2++;
        }
    }

    fclose(src);
    fclose(out1);
    fclose(out2);

    printf("%d lines written to %s\n", count1, argv[2]);
    printf("%d lines written to %s\n", count2, argv[3]);

    return 0;
}
