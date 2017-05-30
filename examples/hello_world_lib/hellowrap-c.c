#include <string.h>
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include "stdio.h"
#include "hello.h"

static int is_initialized = 0;

void hello_world() {
	/* Startup OCaml */
	if (is_initialized == 0)
	{
		is_initialized = 1;
		char* dummyargv[2];
		dummyargv[0]="";
		dummyargv[1]=NULL;
		caml_startup(dummyargv);
	}
	CAMLparam0();
	CAMLlocal1(res);

	static value* hello_world_fun = NULL;
	if (hello_world_fun == NULL)
	{
		hello_world_fun = caml_named_value("hello_world");
	}
//	fprintf(stderr, "ciao\n");

	res =  caml_callbackN_exn( *hello_world_fun, 0, NULL );
	if (Is_exception_result(res))
	{
		fprintf(stderr, "%s\n", "There was an error.");
		CAMLreturn0;
	}

	CAMLreturn0;
}
