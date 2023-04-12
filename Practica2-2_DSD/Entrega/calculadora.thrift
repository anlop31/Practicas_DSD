
service Calculadora{
   void ping(),
   i32 suma(1:i32 num1, 2:i32 num2),
   i32 resta(1:i32 num1, 2:i32 num2),
   i32 multiplicacion(1:i32 num1, 2:i32 num2),
   i32 division(1:i32 num1, 2:i32 num2),
   list<double> sumaVectores(1:list<double> n1, 2:list<double> n2),
   list<double> restaVectores(1:list<double> n1, 2:list<double> n2),
   list<double> multiplicaVectores(1:list<double> n1, 2:list<double> n2),
   list<double> divideVectores(1:list<double> n1, 2:list<double> n2)
}
