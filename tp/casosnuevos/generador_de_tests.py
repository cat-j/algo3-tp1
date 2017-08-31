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


#i creciente, ninguno positivo
generarEntradaICreciente(30, 1.0, 0.5, "icreciente_10_05")
generarEntradaICreciente(30, 1.0, 0.1, "icreciente_10_01")
generarEntradaICreciente(30, 1.0, 0.9, "icreciente_10_09")

#i creciente, 10% positivos
generarEntradaICreciente(30, 0.9, 0.5, "icreciente_09_05")
generarEntradaICreciente(30, 0.9, 0.1, "icreciente_09_01")
generarEntradaICreciente(30, 0.9, 0.9, "icreciente_09_09")

#i creciente, 25% positivos
generarEntradaICreciente(30, 0.75, 0.5, "icreciente_075_05")
generarEntradaICreciente(30, 0.75, 0.1, "icreciente_075_01")
generarEntradaICreciente(30, 0.75, 0.9, "icreciente_075_09")

#i creciente, igual cantidad de positivos y no positivos
generarEntradaICreciente(30, 0.5, 0.5, "icreciente_05_05")
generarEntradaICreciente(30, 0.5, 0.1, "icreciente_05_01")
generarEntradaICreciente(30, 0.5, 0.9, "icreciente_05_09")

#i creciente, 75% positivos
generarEntradaICreciente(30, 0.25, 0.5, "icreciente_025_05")
generarEntradaICreciente(30, 0.25, 0.1, "icreciente_025_01")
generarEntradaICreciente(30, 0.25, 0.9, "icreciente_025_09")

#i creciente, 90% positivos
generarEntradaICreciente(30, 0.1, 0.5, "icreciente_01_05")
generarEntradaICreciente(30, 0.1, 0.1, "icreciente_01_01")
generarEntradaICreciente(30, 0.1, 0.9, "icreciente_01_09")

#i creciente, todos positivos
generarEntradaICreciente(30, 0.0, 0.5, "icreciente_00_05")
generarEntradaICreciente(30, 0.0, 0.1, "icreciente_00_01")
generarEntradaICreciente(30, 0.0, 0.9, "icreciente_00_09")


#a creciente, ninguno positivo
generarEntradaACreciente(15, 1.0, 20, "acreciente_00")

#a creciente, 1% positivos
generarEntradaACreciente(15, 0.99, 20, "acreciente_001")

#a creciente, 10% positivos
generarEntradaACreciente(15, 0.9, 20, "acreciente_01")

#a creciente, 25% positivos
generarEntradaACreciente(15, 0.75, 20, "acreciente_025")

#a creciente, igual cantidad de positivos y no positivos
generarEntradaACreciente(15, 0.5, 20, "acreciente_05")

#a creciente, 75% positivos
generarEntradaACreciente(15, 0.25, 20, "acreciente_075")

#a creciente, 90% positivos
generarEntradaACreciente(15, 0.1, 20, "acreciente_09")

#a creciente, 99% positivos
generarEntradaACreciente(15, 0.01, 20, "acreciente_099")

#a creciente, todos positivos
generarEntradaACreciente(15, 0.0, 20, "acreciente_10")


#positivo creciente, 1% responden
generarEntradaPositivoCreciente(15, 0.99, 20, "positivocreciente_001")

#positivo creciente, 10% responden
generarEntradaPositivoCreciente(15, 0.9, 20, "positivocreciente_01")

#positivo creciente, 25% responden
generarEntradaPositivoCreciente(15, 0.75, 20, "positivocreciente_025")

#positivo creciente, igual cantidad de responden y no responden
generarEntradaPositivoCreciente(15, 0.5, 20, "positivocreciente_05")

#positivo creciente, 75% responden
generarEntradaPositivoCreciente(15, 0.25, 20, "positivocreciente_075")

#positivo creciente, 90% responden
generarEntradaPositivoCreciente(15, 0.1, 20, "positivocreciente_09")

#positivo creciente, 99% responden
generarEntradaPositivoCreciente(15, 0.01, 20, "positivocreciente_099")

#positivo creciente, todos responden
generarEntradaPositivoCreciente(15, 0.0, 20, "positivocreciente_10")
