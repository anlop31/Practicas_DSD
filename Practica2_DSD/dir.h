/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DIR_H_RPCGEN
#define _DIR_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct numeros *nums;

typedef int num;

struct numeros {
	int num_1;
	int num_2;
};
typedef struct numeros numeros;

struct readdir_res {
	int errno;
	union {
		num result;
	} readdir_res_u;
};
typedef struct readdir_res readdir_res;

#define CALC 0x20000156
#define CALCVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define CALC 1
extern  resultado * calc_1(numeros *, CLIENT *);
extern  resultado * calc_1_svc(numeros *, struct svc_req *);
extern int calc_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define CALC 1
extern  resultado * calc_1();
extern  resultado * calc_1_svc();
extern int calc_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_nums (XDR *, nums*);
extern  bool_t xdr_num (XDR *, num*);
extern  bool_t xdr_numeros (XDR *, numeros*);
extern  bool_t xdr_readdir_res (XDR *, readdir_res*);

#else /* K&R C */
extern bool_t xdr_nums ();
extern bool_t xdr_num ();
extern bool_t xdr_numeros ();
extern bool_t xdr_readdir_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DIR_H_RPCGEN */
