#include "shared_functions.h"

void	ft_perror(char *msg)
{
	dprintf(2, "Error:\n\t");
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	dprintf(2, "Error:\n\t%s\n", str);
	exit(EXIT_FAILURE);
}

static int get_shared_block(char *filename, int size)
{
    const int key = ftok(filename, 0);
    printf("Key: %d Size: %d\n", key, size);
    if (key == -1)
    {
        perror("ftok");
        return (-1);
    }
    return (shmget(key, size, 0644 | IPC_CREAT));
}

void *attach_memory_block(char *filename, int size)
{
    const int shm_id = get_shared_block(filename, size);

    printf("SHM_ID: %d\n", shm_id);
    if (shm_id == -1)
    {
        dprintf(2, "invalid block id\n");
        perror("shm_get");
        return (NULL);
    }

    void *memory_block = shmat(shm_id, NULL, 0);
    if (memory_block == (char *)-1)
    {
        dprintf(2, "coudnt attach to the block\n");
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
    const int shm_id = get_shared_block(filename, 0);

    if (shm_id == -1)
    {
        perror("destroy");
        return (1);
    }
    return (shmctl(shm_id, IPC_RMID, NULL));
}