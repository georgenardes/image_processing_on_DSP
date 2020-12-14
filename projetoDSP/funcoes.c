#include "funcoes.h"

Imagem carrega_imagem (const char *caminho, int num_canais)
{
    Imagem im;

    // carrega imagem com num_canais
    im.data = stbi_load(caminho, &im.w, &im.h, &im.c, num_canais);

    if(im.data == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", im.w, im.h, im.c);
    im.c = num_canais;

    return im;
}


Imagem cria_imagem (int w,int h,int c)
{
    Imagem out;

    // metadata
    if (c <= 0) c = 1;
    out.c = c;
    out.w = w;
    out.h = h;

    // aloca memoria para a imagem
    out.data = calloc(h*w*c, sizeof(char));

    return out;
}

void libera_image(Imagem im)
{
    free(im.data);
}

void salva_imagem (const char *caminho, Imagem im, int png)
{
    char buff[256];
    int success = 0;

    sprintf(buff, "%s.jpg", caminho);
    success = stbi_write_jpg(buff, im.w, im.h, im.c, im.data, 100);
    
    if(!success) fprintf(stderr, "Failed to write image %s\n", buff);
}

void set_pixel(Imagem im, int x, int y, int c, unsigned char v)
{
    /**
        Como a imagem é carregada na memória em forma de vetor,
        é necessário calcular o offset dos canais, das linhas e
        por último da coluna.
    */
    im.data[c*im.h*im.w + y*im.w + x] = v;
}

unsigned char get_pixel(Imagem im, int x, int y, int c)
{
    /**
        Quando é solicitado uma posição fora dos limites da imagem,
        existem diversas técnicas para retornar o valor do pixel.
        A técnica usada aqui é a Clamp.
    */

    // garante que as posições estejam no limite
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (c < 0)
        c = 0;
    if(x >= im.w)
        x = im.w - 1;
    if(y >= im.h)
        y = im.h - 1;
    if (c >= im.c)
        c = im.c - 1;

    unsigned char pixel = im.data[c*im.h*im.w + y*im.w + x];

    return pixel;
}


Imagem convolve (Imagem im, char *kernel, int kernel_size)
{
    Imagem resultado = cria_imagem(im.w, im.h, 1);
	
    // ==============
    short new_pix = 0;
    
    unsigned short i, j, x,  y;

    // caminha pelas colunas
    for(i = 0; i < im.w; i++)
    {
    	
        // caminha pela linhas
        for(j = 0; j < im.h; j++)
        {
        	
            // convolui cada pixel
            for(x = i-1; x <= i+1; x++)
            {
                for(y = j-1; y <= j+1; y++)
                {
                    new_pix += (short) get_pixel(im, x, y, 0) * kernel[(y+1-j)*kernel_size + x+1-i];
                }
            }
            

            // abs
            new_pix = abs(new_pix);
            
            // clip values 
            if (new_pix > 255){
           		new_pix = 255;
            }
                        
            set_pixel(resultado, i, j, 0, new_pix);
			            
            // zera resultado convolução
            new_pix = 0;
        }
       
    }
    // ==============
	
    return resultado;
}

void faz(){
	Imagem im = carrega_imagem("..\\data\\helens4.jpg", 1);
    
    // cria kernel do filtro de LAPLACE
    char laplace[3*3] = {0,1,0,1,-4,1,0,1,0};

    // cria kernel do filtro de Sobel vertical
    char sobel_v[3*3] = {1,0,-1,2,0,-2,1,0,-1};

    // cria kernel do filtro de Sobel horizontal
    char sobel_h[3*3] = {1,2,1,0,0,0,-1,-2,-1};

	
    // cria imagem para armazenar o resultado
    Imagem im2;
    
    // convolve com o filtro especificado
    im2 = convolve(im, sobel_h, 3);
    
    // salva imagem criada
    salva_imagem("..\\resultado", im2, 1);
    
    libera_image(im);
    libera_image(im2);
}