#ifndef DOTCOM_H
#define DOTCOM_H

#define N 6
#define M 3

typedef struct DotCom
{
    int pos[M];  // 存放连续的三个坐标
    int numOfHits;  // 用户猜中的次数
} DotCom;

typedef enum Status
{
    MISS,
    HIT,
    DUNK
} Status;

void init_dotom(DotCom* dotcom);
Status check_user_guess(DotCom* dotcom, int guess);

#endif // DOTCOM_H
