import numpy as np
''' Effectue le pivotage de Gauss-Jordan sur la matrice A par rapport à l'élément A[pivot_row][pivot_column].
    ARGS
        - A : la matrice a pivoter
        - pivot_row : le numero de la ligne du pivot
        - pivot_column : le numero de la collonne du pivot
    Reurn
        None , la matrice entree sera la matrice pivoter au final
'''
def pivotage_gauss_jordan(A, pivot_row, pivot_column):
    facteur = A[pivot_row, pivot_column]
    A[pivot_row, :] /= facteur
    
    for i in range(len(A)):
        if i == pivot_row:
            continue
        facteur = -A[i, pivot_column] / A[pivot_row, pivot_column]
        A[i, :] += A[pivot_row, :] * facteur