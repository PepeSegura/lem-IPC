#include "shared.h"

bool	number_in_array(int len, const int array[len], int to_find)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (array[i] == to_find)
			return (true);
		i++;
	}
	return (false);
}
