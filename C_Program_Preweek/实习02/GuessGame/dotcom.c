#include "dotcom.h"
#include <stdlib.h>
#include <time.h>

void init_dotom(DotCom* dotcom)
{
    srand(time(NULL));
    int start = rand() % (N-1);
    dotcom->pos[0] = start;
    dotcom->pos[1] = start+1;
    dotcom->pos[2] = start+2;
    dotcom->numOfHits = 0;
}

Status check_user_guess(DotCom* dotcom, int guess)
{
    Status status = MISS;

    for(int i = 0; i < 3; i++)
        {
        if (dotcom->pos[i] == guess)
        {
            dotcom->numOfHits++;
            if (dotcom->numOfHits == 3)
            {
                return DUNK;
            }
        else
            {
                return HIT;
            }
        }
    }

    return status;
}

