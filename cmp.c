/*
Nelly Duke - ND659
cmp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        return 2;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    char *line = NULL;
    size_t lineBuffSize = 0;
    ssize_t lineSize;
    char *line2 = NULL;
    size_t lineBuffSize2 = 0;
    ssize_t lineSize2;
    int lineCount = 1;
    int byte = 1;



    if (fp == NULL | fp2 == NULL) {
        return 2;
    }

    while ((lineSize = getline(&line, &lineBuffSize, fp)) != -1) {
        if ((lineSize2 = getline(&line2, &lineBuffSize2, fp2)) == -1) {
            printf("cmp: EOF on %s after byte %d, line %d\n", argv[2], byte, lineCount);
            return 1;
        }
        int lineLen = strlen(line);
        for (int i = 0; i < lineLen; i++) {
            if (line[i] != line2[i]) {
                printf("%s %s differ: byte %d, line %d\n", argv[1], argv[2], byte, lineCount);
                return 1;
            }
            byte += 1;
        }
        lineCount += 1;
    }

    if ((lineSize2 = getline(&line2, &lineBuffSize2, fp2)) != -1) {
        printf("cmp: EOF on %s after byte %d, line %d\n", argv[1], byte, lineCount);
        return 1;
    }



    fclose(fp);
    fclose(fp2);
    return 0;
}