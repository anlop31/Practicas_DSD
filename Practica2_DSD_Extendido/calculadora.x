struct result {
    double valor_resultado;
    int code;
};

/* la siguiente union se utiliza para discriminar entre llamadas con exito y llamadas con errores */
union readdir_res switch (int errno) {
	case 0:
		double result; /* sin error: listado del directorio */
	default:
		void; /* con error: nada */
};

program CALCULADORA {
    version CALCULADORA_1 {
        result suma(double n1, double n2) = 1;
        result multiplica(double n1, double n2) = 2;
        result divide(double n1, double n2) = 3;
        result resta(double n1, double n2) = 4;
    } =1;
} = 0x20000156;