import glob
import sys

from calculadora import Calculadora


from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

from thrift.Thrift import TApplicationException


import logging

logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print("me han hecho ping()")

    def suma(self, n1, n2):
        print("sumando " + str(n1) + " con " + str(n2))
        return n1 + n2

    def resta(self, n1, n2):
        print("restando " + str(n1) + " con " + str(n2))
        return n1 - n2
    
    def multiplicacion(self, n1, n2):
        print("multiplicando " + str(n1) + " con " + str(n2))
        return n1 * n2
    
    def division(self, n1, n2):
        print("dividiendo " + str(n1) + " con " + str(n2))
        if(n2 == 0):
            resultado = -1
        else:
            resultado = n1 / n2
        return resultado

    def sumaVectores(self, n1, n2):
        print("sumando vectores...")
        v = []
        for i in range(len(n1)):
            v.append(n1[i] + n2[i])
        return v
    
    def restaVectores(self, n1, n2):
        print("restando vectores...")
        v = []
        for i in range(len(n1)):
            v.append(n1[i] - n2[i])
        return v
    
    def multiplicaVectores(self, n1, n2):
        print("multiplicando vectores...")
        v = []
        for i in range(len(n1)):
            v.append(n1[i] * n2[i])
        return v
    
    def divideVectores(self, n1, n2):
        print("sumando vectores...")
        v = []
        try:
            for i in range(len(n1)):
                if(n2[i] == 0):
                    raise ValueError("NO SE PUEDE DIVIDIR ENTRE 0")
                else:
                    v.append(n1[i] / n2[i])
        except ValueError as e:
            raise TApplicationException(TApplicationException.INTERNAL_ERROR, str(e))
        return v
    

if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("iniciando servidor...")
    server.serve()
    print("fin")
