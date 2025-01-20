#include "shared.h"

static int get_or_create_shared_block(char *filename, int size, bool create)
{
    const int key = ftok(filename, 0);
    ft_dprintf(2, "Key: %d Size: %d\n", key, size);
    if (key == -1)
    {
        perror("ftok");
        return (-1);
    }
    if (create == true)
        return (shmget(key, size, 0644 | IPC_CREAT));
    return (shmget(key, size, 0644));
    
}

void *attach_memory_block(char *filename, int size, bool create)
{
    const int shm_id = get_or_create_shared_block(filename, size, create);

    ft_dprintf(2, "SHM_ID: %d\n", shm_id);
    if (shm_id == -1)
    {
        ft_dprintf(2, "invalid block id\n");
        perror("shm_get");
        return (NULL);
    }

    void *memory_block = shmat(shm_id, NULL, 0);
    if (memory_block == (char *)-1)
    {
        ft_dprintf(2, "coudnt attach to the block\n");
        perror("shm_attach");
        return (NULL);
    }
    return (memory_block);
}

int dettach_memory_block(char *memory_block)
{
    return (shmdt(memory_block));
}

int destroy_memory_block(char *filename)
{
    const int shm_id = get_or_create_shared_block(filename, 0, false);

    if (shm_id == -1)
    {
        perror("destroy");
        return (1);
    }
    return (shmctl(shm_id, IPC_RMID, NULL));
}