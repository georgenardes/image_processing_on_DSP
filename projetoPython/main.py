import numpy as np
import cv2



def salvaImagem(imagem):
    cv2.imwrite("dog.jpg", imagem)

def inicio():
    imagem = cv2.imread("data/dog.jpg", 0)
    cv2.imshow("original", imagem)

    imagem2 = imagem

    laplace = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]], dtype=np.int)

    sobel_v = np.array([[1, 0, -1], [2, 0, -2], [1, 0, -1]], dtype=np.int)

    sobel_h = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]], dtype=np.int)

    resultado = cv2.filter2D(imagem, ddepth=cv2.CV_16S, kernel=sobel_h)

    resultado_final = cv2.convertScaleAbs(resultado)

    cv2.imshow("modificado", resultado_final)
    cv2.waitKey(0)

    salvaImagem(resultado_final)

inicio()