struct vectorDouble {
   1: list<double> data
}

service Calculadora{
   void ping(),
   i32 suma(1:i32 num1, 2:i32 num2),
   i32 resta(1:i32 num1, 2:i32 num2),
   i32 multiplicacion(1:i32 num1, 2:i32 num2),
   i32 division(1:i32 num1, 2:i32 num2),
   vectorDouble sumaVectores(1:vectorDouble n1, 2:vectorDouble n2)
}
