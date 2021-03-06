#include <sys/mman.h>
#include <unistd.h>

#define CAML_NAME_SPACE

#include <caml/alloc.h>
#include <caml/bigarray.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/unixsupport.h>

CAMLprim value ixy_pagesize(value v_unit) {
    CAMLparam1(v_unit);
    CAMLreturn(Val_int(getpagesize()));
}

CAMLprim value ixy_mlock(value v_buf, value v_off, value v_size) {
    CAMLparam3(v_buf, v_off, v_size);

    void *ptr = Caml_ba_data_val(v_buf);
    size_t offset = Long_val(v_off), size = Long_val(v_size);

    if (mlock(ptr, offset + size))
        uerror("mlock", Nothing);

    CAMLreturn(Val_unit);
}
