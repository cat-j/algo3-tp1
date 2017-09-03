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

def generarEntradaMismoTamano(k, umbral_respuesta_positiva=0.5, umbral_responder=0.5, archivo="prueba"):
    with open(archivo, 'w') as entrada:
        for i in range(32):
            caso = generarCaso(k, umbral_respuesta_positiva, umbral_responder)
            for j in caso:
                entrada.write(j + '\n')

        entrada.write("0 0 \n")

    return

def generarEntradaICreciente(hasta, umbral_respuesta_positiva=0.5, umbral_responder=0.5, archivo="prueba"):
    # Genera una entrada que cumple el formato pedido por la catedra en la que cada caso tiene un agente
    # mas que el anterior. La probabilidad de que respondan y la de que lo hagan positivamente se mantiene
    # fija para todos los casos.
    with open(archivo, 'w') as entrada:
        for i in range(1,hasta+1):
            caso = generarCaso(i, umbral_respuesta_positiva, umbral_responder)
            
            for j in caso:
                entrada.write(j + '\n')

        entrada.write("0 0 \n")

    return

def generarEntradaACreciente(i, umbral_respuesta_positiva=0.5, cantidad=20, archivo="prueba"):
    # Genera una entrada que cumple el formato pedido por la catedra en la que, en cada caso, la probabilidad
    # de que los agentes respondan aumenta en "cantidad". La cantidad de agentes y la probabilidad de que respondan
    # positivamente se mantiene fija para todos los casos.
    with open(archivo, 'w') as entrada:
        for p in np.linspace(0.0, 1.0, num=cantidad):
            caso = generarCaso(i, umbral_respuesta_positiva, p)

            for j in caso:
                entrada.write(j + '\n')

        entrada.write("0 0 \n")

    return

def generarEntradaPositivoCreciente(i, umbral_responder=0.5, cantidad=20, archivo="prueba"):
    # Genera una entrada que cumple el formato pedido por la catedra en la que, en cada caso, la probabilidad
    # de que los agentes respondan positivamente aumenta en "cantidad". La cantidad de agentes y la probabilidad
    # de que respondan en absoluto se mantiene fija para todos los casos.
    with open(archivo, 'w') as entrada:
        for p in np.linspace(0.0, 1.0, num=cantidad):
            caso = generarCaso(i, p, umbral_responder)

            for j in caso:
                entrada.write(j + '\n')

        entrada.write("0 0 \n")

    return

probas = [0.0, 0.25, 0.5, 0.75, 0.875, 0.99, 1.0]

for p in probas:
    for q in probas[:-1]:
        pstring = str(p).replace(".","")
        qstring = str(q).replace(".","")
        generarEntradaMismoTamano(15,p,q,"tamanofijo/TEST_15agentes_"+pstring+"_"+qstring)

generarEntradaMismoTamano(15,0.0,1.0,"tamanofijo/TEST_15agentes_avacio")

for i in range(1,25):
    for p in probas:
        pstring = str(p).replace(".","")
        generarEntradaMismoTamano(i,0.5,p,"tamanovariable/TEST_" + str(i) + "agentes_" + pstring)


#generarEntradaMismoTamano(20,0.5,0.5,"prueba1")
