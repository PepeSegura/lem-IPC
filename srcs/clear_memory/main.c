#include "shared.h"

int main(void)
{
    sem_t *sem = sem_open(SEM_NAME, O_WRONLY);
    if (sem != SEM_FAILED)
    {
        printf("Closing %s\n", SEM_NAME);
        sem_close(sem);
        perror("sem_close");
        sem_unlink(SEM_NAME);
        perror("sem_unlink");
    }
    printf("destroy: %d\n", destroy_memory_block(FILENAME));
}
