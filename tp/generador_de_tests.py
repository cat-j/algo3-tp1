import numpy as np

def generarCaso(k, umbral_respuesta_positiva=0.5, umbral_responder=0.5):
    a = 0
    caso = []
    
    for i in range(1,k+1):
        for j in range(1,k+1):
            p = np.random.uniform()

            if p >= umbral_responder:
                a = a + 1
                v = np.random.uniform()
                if v >= umbral_respuesta_positiva:
                    signo = 1
                else:
                    signo = -1
                    j = j * signo
                caso.append(str(i) + " " + str(j))

    caso.insert(0, str(k) + " " + str(a))
    return caso

def generarEntrada(hasta, umbral_respuesta_positiva=0.5, umbral_responder=0.5, archivo="prueba.txt"):
    with open(archivo, 'w') as entrada:
        for i in range(1,hasta+1):
            caso = generarCaso(i, umbral_respuesta_positiva, umbral_responder)
            
            for j in caso:
                entrada.write(j + '\n')

        entrada.write("0 0 \n")

    return


generarEntrada(6, 0.2, 0.5)
