#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dotcom.h"
int main()
{
    bool isAlive = true;

    int guess;
    bool guessed[7] = {false};

    Status result = MISS;
    DotCom dotcom;

    init_dotom(&dotcom);
    int gue = 0;


    while (isAlive)
    {
        printf("请输入一个整数（0-6之间）：");
        scanf("%d", &guess);
        if (guessed[guess])
        {
            printf("无效猜测！这个数字已经猜过了\n");
            continue;
        }
        if (guess < 0 || guess > 6)
        {
            continue;
        }
        result = check_user_guess(&dotcom, guess);
        switch (result)
        {
        case MISS:
            printf("MISS\n");
            break;
        case HIT:
            printf("HIT\n");
            break;
        case DUNK:
            printf("DUNK\n");
            isAlive = false;
            break;
        default:
            break;
        }
        gue++;
        printf("用户猜测总次数：%d\n", gue);
        guessed[guess] = true;

    }
    return 0;
}
