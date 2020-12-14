
typedef struct{
    int w,h,c;           // largura x altura x canais
    unsigned char *data; // vetor de pixels
} Imagem;


extern Imagem convolve (Imagem, char *, int);
extern void salva_imagem (const char *, Imagem, int);
extern void libera_image(Imagem);
extern Imagem carrega_imagem (const char *, int);



int main()
{
	
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
	
	
    return 0;
}
