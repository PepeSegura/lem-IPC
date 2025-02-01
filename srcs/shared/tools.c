#include "shared.h"

mlx_image_t	*mlx_load_img(mlx_t *mlx, char *name)
{
	mlx_texture_t	*new_texture;
	mlx_image_t		*new_image;

	new_texture = mlx_load_png(name);
	if (new_texture == NULL)
		ft_mlx_error();
	new_image = mlx_texture_to_image(mlx, new_texture);
	if (new_image == NULL)
		ft_mlx_error();
	mlx_delete_texture(new_texture);
	return (new_image);
}

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
