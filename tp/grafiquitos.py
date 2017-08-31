import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

complejidadTeorica = pd.DataFrame()

ies = []
aes = []
v = []

for i in range(31):
    for a in range(i**2+1):
        ies.append(i)
        aes.append(a)
        v.append(2**i * a * numpy.log(i))

complejidadTeorica['value'] = v
complejidadTeorica['i'] = ies
complejidadTeorica['a'] = aes

plt.clf()

for i in [0, 5, 10, 15, 20, 25, 30]:
