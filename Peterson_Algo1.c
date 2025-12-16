#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int milk = 0;

int flag[2] = {0, 0};
int turn = 0;

void* buy_milk(void* arg)
{
    int i = *(int*)arg;
    int j = 1 - i;

    flag[i] = 1;
    turn = j;
    while (flag[j] && turn == j)
    {
    }

    if (milk == 0)
    {
        milk++;
        printf("Thread %d bought milk, total milk: %d\n", i, milk);
    }

    flag[i] = 0;

    return NULL;
}

int main()
{
    pthread_t t0, t1;
    int id0 = 0;
    int id1 = 1;

    milk = 0;

    pthread_create(&t0, NULL, buy_milk, &id0);
    pthread_create(&t1, NULL, buy_milk, &id1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Final milk count: %d\n", milk);

    return 0;
}
