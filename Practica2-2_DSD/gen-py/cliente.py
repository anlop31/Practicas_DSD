from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

print("hacemos ping al server")
client.ping()


salir = False

while(salir == False):
	print("\nMenu:")
	print("1. Operaciones con numeros reales")
	print("2. Operaciones con vectores")
	print("3. Salir del programa\n")
	seleccion = input("Seleccion: ")

	v1 = []
	v2 = []
	v_resultado = []
	resultado = 0
	
	# Si no se ha elegido salir, se entra en el bucle
	if(seleccion != 3):
		menu = False
	else: # Si se elige salir, se sale del programa entero
		menu = True
		salir = True

	while(menu == False):
		if(seleccion == 1): 
			# Menu para elegir operacion
			print("\nOperaciones con reales:")
			print("1. Suma.")
			print("2. Resta.")
			print("3. Multiplicacion")
			print("4. Division")
			print("5. Volver al menu principal\n")
			opcion = input("Que quiere realizar?: ")

			# Introducir valores
			if(opcion != 5):
				n1 = input("Ingrese el primer operando: ")
				n2 = input("Ingrese el segundo operando: ") 

			if(opcion == 1):
				resultado = client.suma(n1, n2)
			if(opcion == 2):
				resultado = client.resta(n1, n2)
			if(opcion == 3):
				resultado = client.multiplicacion(n1, n2)
			if(opcion == 4):
				resultado = client.division(n1, n2)
			if(opcion == 5):
				menu = True

		elif(seleccion == 2):
			# Menu para elegir operacion
			print("\nOperaciones con vectores:")
			print("1. Suma.")
			print("2. Resta.")
			print("3. Multiplicacion")
			print("4. Division")
			print("5. Volver al menu principal\n")
			opcion = input("Que desea realizar?: ")

			# Introducir valores
			if(opcion != 5):
				print("Introduzca el primer vector.")
				for i in range(5):
					valor = input("Introduce el valor {} del vector: ".format(i+1))
					valor_float = float(valor)
					v1.append(valor_float)

				print("Introduzca el segundo vector.")
				for i in range(5):
					valor = input("Introduce el valor {} del vector: ".format(i+1))
					valor_float = float(valor)
					v2.append(valor_float)
			

			# Realizar operacion con los operandos
			if(opcion == 1):
				v_resultado = client.sumaVectores(v1, v2)
			if(opcion == 2):
				v_resultado = client.restaVectores(v1, v2)
			if(opcion == 3):
				v_resultado = client.multiplicaVectores(v1, v2)
			if(opcion == 4):
				try:
					v_resultado = client.divideVectores(v1, v2)
				except ValueError as error:
					print("Se produjo un error: ", error)
					resultado = None
			if(opcion == 5):
				menu = True

		# else: # seleccion = 3
		# 	salir == True
		# 	menu == True
		
		if(menu == False and salir == False):
			if(seleccion == 1): # si la seleccion eran numeros reales
				# Imprimir operandos y resultado
				print("\nLos dos operandos son: " + str(n1) + ", " + str(n2))
				print("El resultado es: " + str(resultado))
			elif(seleccion == 2): # si la seleccion eran vectores
				print("\nPrimer vector: " + str(v1))
				print("Segundo vector: " + str(v2))
				if (resultado == None):
					print("No se pudo calcular, no se puede dividir entre cero")
				else:
					print("Vector resultado: " + str(v_resultado))





transport.close()
