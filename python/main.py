import numpy as np
import optimisation.pivotage as opv

def save_matrix_to_file(matrix, filename):
    """
    Sauvegarde la matrice dans un fichier.
    """
    try:
        with open(filename, "w") as f:
            n, p = matrix.shape
            f.write(f"{n}\n{p}\n")
            for row in matrix:
                row_str = " ".join(str(Fraction(elem).limit_denominator()) for elem in row)
                f.write(row_str + "\n")
        print(f"Matrice sauvegardée avec succès dans '{filename}'.")
    except Exception as e:
        print(f"Une erreur s'est produite lors de la sauvegarde de la matrice dans '{filename}': {e}")

def get_data(path:str):
    """
    Récupère les données de la matrice à partir d'un fichier.
    """
    try:
        with open(path, "r") as f:
            n = int(f.readline())
            p = int(f.readline())
            n_element = int(f.readline())
            p_element = int(f.readline())
            A = np.zeros((n, p))
            for i in range(n):
                row = list(map(float, f.readline().split()))
                A[i, :] = row
        return n, p, n_element, p_element, A
    except FileNotFoundError:
        print("Impossible de trouver le fichier.")
        return None

def display_matrix(matrix, name):
    """
    Affiche la matrice avec un nom donné.
    """
    print(f">> [{name}] ({matrix.shape[0]},{matrix.shape[1]})")
    for row in matrix:
        print("\t|", end="")
        for elem in row:
            print(f"\t{elem:.2f}", end="")
        print("\t|")
from fractions import Fraction

def display_matrix_fraction(matrix, name):
    """
    Affiche la matrice avec un nom donné, en utilisant des fractions.
    """
    print(f">> [{name}] ({matrix.shape[0]},{matrix.shape[1]})")
    for row in matrix:
        print("\t|", end="")
        for elem in row:
            frac = Fraction(elem).limit_denominator()
            print(f"\t{frac}", end="")
        print("\t|")


def show_results(matrix, n_element, p_element):
    """
    Affiche les résultats du pivotage de la matrice par rapport à l'élément (n_element, p_element).
    """
    print(f"Pour le pivotage de la matrice par rapport au ({n_element},{p_element})")
    display_matrix_fraction(matrix, 'A')

if __name__ == "__main__":
    print("Ce programme permet de faire le pivotage d'une matrice A donnée par rapport à un élément de la matrice en n^ème ligne et p^ème colonne\n")
    # Récupération des données
    path = "pivotage.txt"
    var = input("Entrer le chemin vers le fichier contenant la matrice : ")
    if var != "":
        path = var
    data = get_data(path)
    if data:
        n, p, n_element, p_element, matrice = data
        # Pivotage de Gauss-Jordan
        opv.pivotage_gauss_jordan(matrice, n_element, p_element)
        # Affichage des résultats
        show_results(matrice, n_element, p_element)
        save_matrix_to_file(matrice,"result.txt")
        del(matrice)
    del(data)