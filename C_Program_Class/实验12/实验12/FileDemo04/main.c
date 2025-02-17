#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS 50
#define LONG 100

int main()
{
    FILE *file;
    char *words[WORDS];
    char word[LONG];
    int wordsc = 0;


    file = fopen("words.txt", "r");

    while (fscanf(file, "%s", word) != EOF)
        {
            words[wordsc] = malloc(strlen(word) + 1);
            strcpy(words[wordsc], word);
            wordsc++;
        }

    fclose(file);

    printf("单词个数：%d\n", wordsc);
    printf("所有单词：");

    for (int i = 0; i < wordsc; i++)
        {
            printf("%s  ", words[i]);
        }

    return 0;
}
