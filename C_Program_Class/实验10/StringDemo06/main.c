#include <stdio.h>
#include <stdlib.h>

int replace(char *s, char c1, char c2);
int main()
{
    char s[] = "The school is withim easy walking distamce of the traim statiom.";
    int countf = replace(s,'m','n');
    printf("Ìæ»» %d´Î\n",countf);
    return 0;
}

int replace(char *s, char c1, char c2)
{
    int countf = 0;
    for(int i = 0; s[i] !='\0';++i)
    {
        if(s[i] == c1)
        {
            s[i] = c2;
            countf++;
        }
    }
    printf("Ìæ»»Îª£º%s\n",s);
    return countf;
}
