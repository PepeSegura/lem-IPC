#include "shared.h"

int	get_or_create_msg_queue(char *filename, int team_name, bool create)
{
	const int	key = ftok(filename, team_name);

	// ft_dprintf(2, "Key: %d Size: %d\n", key, size);
	if (key == -1)
	{
		if (create == false)
			return (-1);
		perror("ftok");
		return (-1);
	}
	if (create == true)
		return (msgget(key, 0644 | IPC_CREAT));
	return (msgget(key, 0644));
}

int	destroy_msg_queue(char *filename, int team_name)
{
	const int	msg_id = get_or_create_msg_queue(filename, team_name, false);

	if (msg_id == -1)
	{
		perror("destroy_msg_queue");
		return (1);
	}
	return (msgctl(msg_id, IPC_RMID, NULL));
}
