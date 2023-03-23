/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULADORA_H_RPCGEN
#define _CALCULADORA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	u_int vect_len;
	double *vect_val;
} vect;

struct result {
	double valor_resultado;
	int code;
};
typedef struct result result;

struct result2 {
	double valor_resultado[5];
	int code;
};
typedef struct result2 result2;

struct readdir_res {
	int errno;
	union {
		double result;
	} readdir_res_u;
};
typedef struct readdir_res readdir_res;

struct suma_1_argument {
	double n1;
	double n2;
};
typedef struct suma_1_argument suma_1_argument;

struct multiplica_1_argument {
	double n1;
	double n2;
};
typedef struct multiplica_1_argument multiplica_1_argument;

struct divide_1_argument {
	double n1;
	double n2;
};
typedef struct divide_1_argument divide_1_argument;

struct resta_1_argument {
	double n1;
	double n2;
};
typedef struct resta_1_argument resta_1_argument;

struct suma_vectores_1_argument {
	vect n1;
	vect n2;
};
typedef struct suma_vectores_1_argument suma_vectores_1_argument;

#define CALCULADORA 0x20000156
#define CALCULADORA_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define suma 1
extern  result * suma_1(double , double , CLIENT *);
extern  result * suma_1_svc(double , double , struct svc_req *);
#define multiplica 2
extern  result * multiplica_1(double , double , CLIENT *);
extern  result * multiplica_1_svc(double , double , struct svc_req *);
#define divide 3
extern  result * divide_1(double , double , CLIENT *);
extern  result * divide_1_svc(double , double , struct svc_req *);
#define resta 4
extern  result * resta_1(double , double , CLIENT *);
extern  result * resta_1_svc(double , double , struct svc_req *);
#define suma_vectores 5
extern  vect * suma_vectores_1(vect , vect , CLIENT *);
extern  vect * suma_vectores_1_svc(vect , vect , struct svc_req *);
extern int calculadora_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define suma 1
extern  result * suma_1();
extern  result * suma_1_svc();
#define multiplica 2
extern  result * multiplica_1();
extern  result * multiplica_1_svc();
#define divide 3
extern  result * divide_1();
extern  result * divide_1_svc();
#define resta 4
extern  result * resta_1();
extern  result * resta_1_svc();
#define suma_vectores 5
extern  vect * suma_vectores_1();
extern  vect * suma_vectores_1_svc();
extern int calculadora_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vect (XDR *, vect*);
extern  bool_t xdr_result (XDR *, result*);
extern  bool_t xdr_result2 (XDR *, result2*);
extern  bool_t xdr_readdir_res (XDR *, readdir_res*);
extern  bool_t xdr_suma_1_argument (XDR *, suma_1_argument*);
extern  bool_t xdr_multiplica_1_argument (XDR *, multiplica_1_argument*);
extern  bool_t xdr_divide_1_argument (XDR *, divide_1_argument*);
extern  bool_t xdr_resta_1_argument (XDR *, resta_1_argument*);
extern  bool_t xdr_suma_vectores_1_argument (XDR *, suma_vectores_1_argument*);

#else /* K&R C */
extern bool_t xdr_vect ();
extern bool_t xdr_result ();
extern bool_t xdr_result2 ();
extern bool_t xdr_readdir_res ();
extern bool_t xdr_suma_1_argument ();
extern bool_t xdr_multiplica_1_argument ();
extern bool_t xdr_divide_1_argument ();
extern bool_t xdr_resta_1_argument ();
extern bool_t xdr_suma_vectores_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULADORA_H_RPCGEN */
