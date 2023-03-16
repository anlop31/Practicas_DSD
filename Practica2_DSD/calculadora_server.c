/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"

result *
suma_1_svc(double n1, double n2,  struct svc_req *rqstp)
{
	static result  result;

	/*
	 * insert server code here
	 */
	result.valor_resultado = n1+n2;
	result.code = 0;

	return &result;
}

result *
multiplica_1_svc(double n1, double n2,  struct svc_req *rqstp)
{
	static result  result;

	/*
	 * insert server code here
	 */
	result.valor_resultado = n1*n2;
	result.code = 0;

	return &result;
}

result *
divide_1_svc(double n1, double n2,  struct svc_req *rqstp)
{
	static result  result;

	/*
	 * insert server code here
	 */
	if(n2 == 0){
		result.code = 1;
		printf("División por cero\n\n");
	}
	else{
		result.valor_resultado = n1/n2;
		result.code = 0;
	}
	
	return &result;
}

result *
resta_1_svc(double n1, double n2,  struct svc_req *rqstp)
{
	static result  result;

	/*
	 * insert server code here
	 */
	result.valor_resultado = n1-n2;
	result.code = 0;

	return &result;
}