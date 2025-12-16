#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 1000000

int milk = 0;

int flag01[2] = {0, 0};
int turn01 = 0;

int flagF[2] = {0, 0};
int turnF = 0;

void* buy_milk(void* arg)
{
    int id = *(int*)arg;

    if (id == 0 || id == 1)
    {
        int i = id;
        int j = 1 - i;

        flag01[i] = 1;
        turn01 = j;
        while (flag01[j] && turn01 == j)
        {
        }
    }

    if (id == 2)
    {
        flagF[1] = 1;
        turnF = 0;
        while (flagF[0] && turnF == 0)
        {
        }
    }
    else
    {
        flagF[0] = 1;
        turnF = 1;
        while (flagF[1] && turnF == 1)
        {
        }
    }

    if (milk == 0)
    {
        milk++;
    }

    if (id == 0 || id == 1)
    {
        flag01[id] = 0;
        flagF[0] = 0;
    }
    else
    {
        flagF[1] = 0;
    }

    return NULL;
}

int main()
{
    pthread_t t0, t1, t2;
    int id0 = 0;
    int id1 = 1;
    int id2 = 2;

    for (int iter = 0; iter < ITERATIONS; iter++)
    {
        milk = 0;
        flag01[0] = 0;
        flag01[1] = 0;
        flagF[0] = 0;
        flagF[1] = 0;

        pthread_create(&t0, NULL, buy_milk, &id0);
        pthread_create(&t1, NULL, buy_milk, &id1);
        pthread_create(&t2, NULL, buy_milk, &id2);

        pthread_join(t0, NULL);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        if (milk != 1)
        {
            printf("ERROR at iteration %d, milk = %d\n", iter, milk);
            return 0;
        }
    }

    printf("All tests passed!\n");
    return 0;
}
