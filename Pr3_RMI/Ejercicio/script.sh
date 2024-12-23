#!/bin/sh -e
# ejecutar = Macro para compilacion y ejecucion del programa ejemplo
# en una sola maquina Unix de nombre localhost.
echo
# echo "Lanzando el ligador de RMI ... "
# rmiregistry 1099 &
echo
echo "Compilando con javac ..."
javac *.java
sleep 2
echo
echo "Lanzando el servidor"
java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy Servidor1 &
sleep 2

java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy Servidor2 &
sleep 2

echo
echo "Lanzando el cliente"
echo
java -cp . -Djava.security.policy=server.policy Cliente
sleep 2
#echo
#echo "Lanzando el segundo cliente"
#echo
#java -cp . -Djava.security.policy=server.policy Cliente_Ejemplo localhost 3
