import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# complejidadTeorica = pd.DataFrame()

# ies = []
# aes = []
# v = []

# for i in range(31):
#     for a in range(i**2+1):
#         ies.append(i)
#         aes.append(a)
#         v.append(2**i * a * numpy.log(i))

# complejidadTeorica['value'] = v
# complejidadTeorica['i'] = ies
# complejidadTeorica['a'] = aes

# plt.clf()

# for i in [0, 5, 10, 15, 20, 25, 30]:

def generar_dataframe(archivo, parametro):
    dataset = pd.read_csv(archivo)
    xs = dataset[parametro]
    dataset = dataset.T
    mediciones = dataset[2:]
    media = np.mean(mediciones)
    if xs[0] > xs[len(xs)-1]:
        xs = list(reversed(xs))
        media = list(reversed(media))
    nombre = archivo.replace("mediciones/" + parametro + "creciente_","").replace("_sinpoda.csv","")
    df = pd.DataFrame({nombre: media,parametro: xs})
    df = df.sort_values(by=parametro)
    print df
    return df

def graficar_muchos_datasets(archivos, parametro, label):
    ax = generar_dataframe(archivos[0], parametro).plot(x=parametro, logy=True)
    for f in archivos[1:]:
        generar_dataframe(f, parametro).plot(x=parametro, ax=ax)
    plt.ylabel(label)
    plt.show()
    return


def graficar_dataset(archivo, parametro):
    # Grafica un unico dataset que consiste en valores i, a y mediciones de tiempo.
    # El grafico consiste en la media de las mediciones de tiempo para un parametro dado,
    # especificado en "parametro".
    df = generar_dataframe(archivo,parametro)
    df.plot(x=parametro, y='Tiempo medio (milisegundos)', logy=True)
    return

graficar_muchos_datasets(["mediciones/acreciente_00_sinpoda.csv",
    "mediciones/acreciente_025_sinpoda.csv", "mediciones/acreciente_05_sinpoda.csv",
    "mediciones/acreciente_075_sinpoda.csv", "mediciones/acreciente_10_sinpoda.csv"], 'a',
    "Tiempo de ejecucion (en milisegundos)")

icreciente_00_sinpoda = []

for p in ["00", "025", "05", "075", "0875", "10"]:
    icreciente_00_sinpoda.append("mediciones/icreciente_00_" + p + "_sinpoda.csv")

icreciente_025_sinpoda = []

for p in ["00", "025", "05", "075", "0875", "10"]:
    icreciente_025_sinpoda.append("mediciones/icreciente_025_" + p + "_sinpoda.csv")

graficar_muchos_datasets(icreciente_00_sinpoda, 'i', "Tiempo de ejecucion (en milisegundos)")
graficar_muchos_datasets(icreciente_025_sinpoda, 'i', "Tiempo de ejecucion (en milisegundos)")

# for d in ["mediciones/acreciente_00_sinpoda.csv", "mediciones/acreciente_001_sinpoda.csv", "mediciones/acreciente_01_sinpoda.csv", "mediciones/acreciente_05_sinpoda.csv", "mediciones/acreciente_05_sinpoda.csv", "mediciones/acreciente_075_sinpoda.csv", "mediciones/acreciente_09_sinpoda.csv", "mediciones/acreciente_099_sinpoda.csv", "mediciones/acreciente_10_sinpoda.csv"]:
#     graficar_dataset(d, 'a')
#     plt.show()

# p001 = p001.T
# medicionesp001 = p001[2:]
# medicionesp001.T
# mediap001 = np.mean(medicionesp001)
# dfp001 = pd.DataFrame({'mean': mediap001, 'p': np.linspace(1.0,0.0,num=20)})

# plt.clf()
# dfp001.plot(x='p')
# plt.show()