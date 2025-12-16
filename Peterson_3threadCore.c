#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int milk = 0;

int flag01[2] = {0, 0};
int turn01 = 0;

int flag_final[2] = {0, 0};
int turn_final = 0;

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
        flag_final[1] = 1;
        turn_final = 0;
        while (flag_final[0] && turn_final == 0)
        {
        }
    }
    else
    {
        flag_final[0] = 1;
        turn_final = 1;
        while (flag_final[1] && turn_final == 1)
        {
        }
    }

    if (milk == 0)
    {
        milk++;
        printf("Thread %d bought milk. Total milk: %d\n", id, milk);
    }

    if (id == 0 || id == 1)
    {
        flag01[id] = 0;
        flag_final[0] = 0;
    }
    else
    {
        flag_final[1] = 0;
    }

    return NULL;
}

int main()
{
    pthread_t t0, t1, t2;
    int id0 = 0;
    int id1 = 1;
    int id2 = 2;

    pthread_create(&t0, NULL, buy_milk, &id0);
    pthread_create(&t1, NULL, buy_milk, &id1);
    pthread_create(&t2, NULL, buy_milk, &id2);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final milk count: %d\n", milk);
    return 0;
}
