/*
 * Copyright (c) 2012 Anil Madhavapeddy <anil@recoil.org>
 * Copyright (c) 2012 Pierre Chambart
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <string.h>

#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/bigarray.h>

CAMLprim value
caml_blit_bigstring_to_string(value val_buf1, value val_ofs1, value val_buf2, value val_ofs2, value val_len)
{
  memcpy(Bytes_val(val_buf2) + Long_val(val_ofs2),
         (char*)Caml_ba_data_val(val_buf1) + Long_val(val_ofs1),
         Long_val(val_len));
  return Val_unit;
}

CAMLprim value
caml_blit_string_to_bigstring(value val_buf1, value val_ofs1, value val_buf2, value val_ofs2, value val_len)
{
  memcpy((char*)Caml_ba_data_val(val_buf2) + Long_val(val_ofs2),
         String_val(val_buf1) + Long_val(val_ofs1),
         Long_val(val_len));
  return Val_unit;
}

CAMLprim value
caml_blit_bigstring_to_bigstring(value val_buf1, value val_ofs1, value val_buf2, value val_ofs2, value val_len)
{
  memmove((char*)Caml_ba_data_val(val_buf2) + Long_val(val_ofs2),
         (char*)Caml_ba_data_val(val_buf1) + Long_val(val_ofs1),
         Long_val(val_len));
  return Val_unit;
}

CAMLprim value
caml_compare_bigstring(value val_buf1, value val_ofs1, value val_buf2, value val_ofs2, value val_len)
{
  int res = memcmp((char*)Caml_ba_data_val(val_buf1) + Long_val(val_ofs1),
                   (char*)Caml_ba_data_val(val_buf2) + Long_val(val_ofs2),
                   Long_val(val_len));
  return Val_int(res);
}

CAMLprim value
caml_fill_bigstring(value val_buf, value val_ofs, value val_len, value val_byte)
{
  memset((char*)Caml_ba_data_val(val_buf) + Long_val(val_ofs),
         Int_val(val_byte),
         Long_val(val_len));
  return Val_unit;
}

CAMLprim value
caml_check_alignment_bigstring(value val_buf, value val_ofs, value val_alignment)
{
  uint64_t address = (uint64_t) (Caml_ba_data_val(val_buf) + Long_val(val_ofs));
  int alignment = Int_val(val_alignment);
  return Val_bool(address % alignment == 0);
}
