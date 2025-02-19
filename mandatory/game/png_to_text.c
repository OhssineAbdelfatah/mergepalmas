#include "../includes/ps.h"

mlx_texture_t	*safe_load(char *path)
{
	mlx_texture_t	*img;

	img = mlx_load_png(path);
	if (!img)
	{
		ft_putstr_fd(path, 2);
		panic("load png failed !\n");
	}
	return (img);
}

int	**gat_pixles(mlx_texture_t *img, int w, int h)
{
	int	**pixs;
	int	i;
	int	j;

	i = 0;
	pixs = malloc(sizeof(int *) * h);
	if (!pixs)
		return ((printf("malooc in pix int** failed")), NULL);
	while (i < h)
	{
		j = 0;
		pixs[i] = (int *)malloc(sizeof(int) * w);
		if (!pixs)
			return ((printf("malooc in pix int* failed")), NULL);
		while (j < w)
		{
			pixs[i][j] = gettt_rgba(&img->pixels[((i * w) + j) * 4]);
			j++;
		}
		i++;
	}
	return (pixs);
}
<<<<<<< HEAD
=======

t_text	*get_image(char *path)
{
	t_text			*img;
	mlx_texture_t	*text;

	text = safe_load(path);
	img = malloc(sizeof(t_text));
	if (!img)
		return (NULL);
	img->pixels = gat_pixles(text, text->width, text->height);
	img->hieght = text->height;
	img->width = text->width;
	mlx_delete_texture(text);
	return (img);
}
>>>>>>> faa013583df783da84bd3c6a85091958a6d56b24
