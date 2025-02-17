#include <stdio.h>
#include <stdlib.h>

#define N 7

int main()
{
    const char *weekdays[7] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    FILE *fp;
    fp= fopen("weekdays.txt","w");
    for(int i = 0; i < N; i++)
    {
        fprintf(fp, "%s\n", weekdays[i]);
    }
    fp = fclose(fp);
    return 0;
}
