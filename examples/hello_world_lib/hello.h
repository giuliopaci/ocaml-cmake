#ifndef _HELLO_H_
#define _HELLO_H_

#undef  HELLO_BEGIN_C_DECLS
#undef  HELLO_END_C_DECLS
#ifdef __cplusplus
#  define HELLO_BEGIN_C_DECLS extern "C" {
#  define HELLO_END_C_DECLS }
#else /* !__cplusplus */
#  define HELLO_BEGIN_C_DECLS
#  define HELLO_END_C_DECLS
#endif  /* __cplusplus */

HELLO_BEGIN_C_DECLS

void hello_world();

HELLO_END_C_DECLS

#endif
