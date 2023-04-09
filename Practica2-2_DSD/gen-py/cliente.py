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

# my_vector = vectorDouble()
# my_vector.data = [1.0, 2.0, 3.0]

salir = False

while(salir == False):
	# Menu para elegir operacion
	print("Menu:")
	print("1. Suma.")
	print("2. Resta.")
	print("3. Multiplicacion")
	print("4. Division")
	print("5. Suma de vectores")
	print("6. Salir")

	opcion = input("Que quiere realizar?: ")

	resultado = 0

	v1 = []
	v2 = []
	v_resultado = []

	# Introducir los operandos
	if(opcion == 5):
		print("vectores")
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
		

	elif(opcion == 6):
		print("Salir")
	else:
		n1 = input("Ingrese el primer operando: ")
		n2 = input("Ingrese el segundo operando: ")


	# Realizar operacion con los operandos
	if(opcion == 1):
		resultado = client.suma(n1, n2)
		print("Opcion 1")
	if(opcion == 2):
		resultado = client.resta(n1, n2)
	if(opcion == 3):
		resultado = client.multiplicacion(n1, n2)
	if(opcion == 4):
		resultado = client.division(n1, n2)
	if(opcion == 5):
		v_resultado = client.sumaVectores(v1, v2)
	if(opcion == 6):
		salir = True


	if(salir == False):
		if(opcion != 5):
			# Imprimir operandos y resultado
			print("Los dos operandos son: " + str(n1) + ", " + str(n2))
			print("El resultado es: " + str(resultado))
			print("")
		if(opcion == 5):
			print("Primer vector: " + str(v1))
			print("Segundo vector: " + str(v2))
			print("Vector resultado: " + str(v_resultado))
			print("")

#resultado = client.suma(1, 1)
#print("1 + 1 = " + str(resultado))
#resultado = client.resta(1, 1)
#print("1 - 1 = " + str(resultado))
#resultado = client.multiplicacion(3, 5)
#print("3 * 5 = " + str(resultado))
#resultado = client.division(12, 4)
#print("12 / 4 = " + str(resultado))
	
transport.close()
