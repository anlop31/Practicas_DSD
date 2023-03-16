typedef struct numeros *nums;
typedef int num;

struct numeros {
    int num_1;
    int num_2;
};

/* la siguiente union se utiliza para discriminar entre llamadas con exito y llamadas con errores */
union readdir_res switch (int errno) {
	case 0:
		num result; /* sin error: listado del directorio */
	default:
		void; /* con error: nada */
};

program CALC {
    version CALCVER {
        resultado CALC(numeros) = 1;
    } =1;
} = 0x20000156;