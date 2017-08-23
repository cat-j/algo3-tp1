import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def datos(nombre_archivo):
    valores = open(nombre_archivo, "r") 
    valores = valores.read()
    valores = [float(x) for x in valores.split()]
    return valores

def bloques(valores,intervalo):
    res = []
    valor = 0
    for elem in range(0,len(valores)):
        if elem % intervalo == 0 and elem != 0:
            res.append(valor/intervalo)
            valor = 0
        valor += valores[elem]
    res.append(valor/intervalo)
    return res

def transformacion(lista,intervalo):
    aux = 0
    res = []
    for elem in lista:
        for rep in range(elem):
            res.append(aux/intervalo)
        aux += intervalo
    return res

def promedio(muestras):
    res = []
    while len(res) < len(muestras[0]):
        res.append(0)
    for muestra in muestras:
        for elem in range(len(muestra)):
            res[elem] += muestra[elem]
    for elem in range(len(res)):
        res[elem] = int(res[elem]/len(muestras))
    return res


if __name__ == "__main__":
    sns.set(style="white", palette="muted", color_codes=True)
   

    # Set up the matplotlib figure
    #f, axes = plt.subplots(1, 1, sharex=True)
    sns.set(style="darkgrid")

    # Generate a random univariate dataset
    intervalo = 10
   
    python = bloques(datos("res.txt"),intervalo)
    plt.plot([None] + python)

    plt.xlabel("Cantidad de nodos.")   
    plt.ylabel("Tiempo en segundos.")
    plt.title("Comparacion tiempos.")

    #plt.xticks([x for x in range(0,151) if x % 50 == 0])   
    #plt.xticks([x for x in range(0,5001) if x % intervalo == 0])
    #plt.setp(axes,yticks=[])
    plt.tight_layout()
    plt.legend(["Python"])
    #plt.legend(["50%","0%","Arbol","Bosque"])
    #plt.savefig('FreeForAllTiempo.png')
    plt.show()
    