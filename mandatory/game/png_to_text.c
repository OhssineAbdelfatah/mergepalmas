#include "../includes/ps.h"

mlx_texture_t *safe_load(char *path)
{
    mlx_texture_t *img;

    img = mlx_load_png(path);
    if(!img)
    {
        ft_putstr_fd(path, 2);
        panic ("load png failed !\n");
    }
    return img ;
}

int **gat_pixles(mlx_texture_t* img, int w, int h)
{
    (void)img;
    int **pixs;
    int i;
    int j;

    i = 0 ;
    pixs = malloc(sizeof(int *) * h );
    if(!pixs)
        return (printf("malooc in pix int** failed")), NULL ;
    while(i < h )
    {
        j = 0 ;
        pixs[i] = (int *)malloc(sizeof(int) * w);
        if(!pixs)
            return (printf("malooc in pix int* failed")), NULL ;
        while(j < w )
        {
            pixs[i][j] = gettt_rgba( &img->pixels[((i * w) + j) * 4] ); // y * width + x
            j++;
        }
        i++;
    }
    return pixs;
}
