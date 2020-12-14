#include <stdio.h>
#include <string.h>


#define STB_IMAGE_IMPLEMENTATION
#include "uwimg/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "uwimg/stb_image_write.h"

typedef struct{
    int w,h,c;           // largura x altura x canais
    unsigned char *data; // vetor de pixels
} Imagem;