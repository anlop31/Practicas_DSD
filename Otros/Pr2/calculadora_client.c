/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"

#define suma_tipo 0
#define multiplica_tipo 1
#define divide_tipo 2
#define resta_tipo 3
#define vector_tipo 4

double
calculadora_1(char *host, double n1, double n2, int tipo)
{
	CLIENT *clnt;
	result  *result_1;
	// vect  *result_5;
	// vect  suma_vectores_1_n1;
	// vect  suma_vectores_1_n2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	if(tipo == suma_tipo)
		result_1 = suma_1(n1, n2, clnt);
		if (result_1 == (result *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	else if(tipo == multiplica_tipo){
		result_1 = multiplica_1(n1, n2, clnt);
		if (result_1 == (result *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	}
	else if(tipo == divide_tipo){
		result_1 = divide_1(n1, n2, clnt);
		if (result_1 == (result *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	}
	else if(tipo == resta_tipo){
		result_1 = resta_1(n1, n2, clnt);
		if (result_1 == (result *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	int error = result_1->code;

	if (error > 0){
		printf("Operación no válida: código de error %d\n", error);

		if (error == 1){
			printf("División por cero\n");
		}

		exit (1);
	}

	return result_1->valor_resultado;
}


vect*
calculadora_2(char *host, vect n1, vect n2)
{
	CLIENT *clnt;
	// result  *result_1;
	vect  *result;
	// vect  suma_vectores_1_n1;
	// vect  suma_vectores_1_n2;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	// if(tipo == vector_tipo){
		result = suma_vectores_1(n1, n2, clnt);
		if (result == (vect *) NULL) {
			clnt_perror (clnt, "call failed");
		}
	// }

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	return result;
}

int
main (int argc, char *argv[])
{
	char *host;
	char operador;
	double n1 = 0.0, n2 = 0.0;
	double resultado = 0.0;
	vect *resultado_vec;

	vect vect1;
	vect vect2;

	// Reservamos memoria para los vectores
	vect1.vect_len = 5;
	vect1.vect_val = (double *)malloc(vect1.vect_len * sizeof(double));
	vect2.vect_len = 5;
	vect2.vect_val = (double *)malloc(vect2.vect_len * sizeof(double));


	if (argc < 2) {
		printf ("usage: %s <maquina>\n", argv[0]);
		exit (1);
	}

	host = argv[1];
	// operador = argv[3][0];
	// n1 = atof(argv[2]);
	// n2 = atof(argv[4]);

	int tipo;
	int opcion;

	int salir = 0;


	while( salir == 0){
		printf("Menu:\n");
		printf("1. Sumar\n");
		printf("2. Restar\n");
		printf("3. Multiplicar\n");
		printf("4. Dividir\n");
		printf("5. Suma de vectores\n");
		printf("6. Salir\n");

		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				tipo = suma_tipo;
				operador = '+';
				break;
			case 2:
				tipo = resta_tipo;
				operador = '-';
				break;
			case 3:
				tipo = multiplica_tipo;
				operador = '*';
				break;
			case 4:
				tipo = divide_tipo;
				operador = '/';
				break;
			case 5:
				tipo = vector_tipo;
				operador = '/';
				break;
			case 6:
				salir = 1;
				break;
			default:
				printf("Operador no valido\n"); // y se sigue preguntando que quiere?
				break;
		}



		// double a,b,c,d,e;


		if(salir == 0){
			
			if(tipo != vector_tipo){
				printf("\nInserte operandos: ");
				scanf("%lf %lf", &n1, &n2);

				resultado = calculadora_1 (host, n1, n2, tipo);

				printf("\nEl resultado de %f %c %f es %f\n\n",
					n1, operador, n2, resultado);
			}
			else{
				printf("\nInserte 5 elementos del primer vector: ");
				scanf("%lf %lf %lf %lf %lf", &vect1.vect_val[0], &vect1.vect_val[1],
									&vect1.vect_val[2], &vect1.vect_val[3], &vect1.vect_val[4]);

				printf("Vector 1: %lf %lf %lf %lf %lf", vect1.vect_val[0], vect1.vect_val[1],
									vect1.vect_val[2], vect1.vect_val[3], vect1.vect_val[4]);

				printf("\nInserte 5 elementos del segundo vector: ");
				scanf("%lf %lf %lf %lf %lf", &vect2.vect_val[0], &vect2.vect_val[1],
									&vect2.vect_val[2], &vect2.vect_val[3], &vect2.vect_val[4]);

				printf("Vector 2: %lf %lf %lf %lf %lf\n", vect2.vect_val[0], vect2.vect_val[1],
									vect2.vect_val[2], vect2.vect_val[3], vect2.vect_val[4]);


				resultado_vec = calculadora_2 (host, vect1, vect2);

				printf("\nEl vector resultado es %f %f %f %f %f\n\n",
					resultado_vec->vect_val[0], resultado_vec->vect_val[1], resultado_vec->vect_val[2],
					resultado_vec->vect_val[3], resultado_vec->vect_val[4]);
			}
		}

	} // bucle mientras salir es false



	exit (0);

}
