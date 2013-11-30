/* param_scaler.c
   bees

   parameter-scaling module.

*/


#include "print_funcs.h"

#include "param_scaler.h"
#include "types.h"

// type-specific includes
#include "scalers/scaler_amp.h"
#include "scalers/scaler_fix.h"
#include "scalers/scaler_fract.h"
#include "scalers/scaler_uint.h"

// array of pointers to initialization functions.
// order must be in sync with types enum in param_common.h
scaler_init_fn scaler_init_pr[eParamNumTypes] = {
   &scaler_fix_init,
  &scaler_fract_init,
  &scaler_uint_init,
  &scaler_amp_init,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

/// FIXME: 
/// doing this rather improperly as a workaround,
/// was having super weird problems in class init? not getting it.
// so for now, a static array of fn pointers.
// their orders must all be in sync with types enum in param_common.h

// array of pointers to get_value functions.
scaler_get_value_fn scaler_get_val_pr[eParamNumTypes] = {
  &scaler_fix_val,
  &scaler_fract_val,
  &scaler_uint_val,
  &scaler_amp_val,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

// array of pointers to get_str functions.
scaler_get_str_fn scaler_get_str_pr[eParamNumTypes] = {
  &scaler_fix_str,
  &scaler_fract_str,
  &scaler_uint_str,
  &scaler_amp_str,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};


// array of pointers to get_in functions.
scaler_get_in_fn scaler_get_in_pr[eParamNumTypes] = {
  &scaler_fix_in,
  &scaler_fract_in,
  &scaler_uint_in,
  &scaler_amp_in,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};


//-------------------------------,
//---- extern function
void scaler_init(ParamScaler* sc, const ParamDesc* desc) {
  print_dbg("\r\n initializing scaler, type: ");
  print_dbg_ulong(desc->type);
  if(scaler_init_pr[desc->type] != NULL) {
    (*(scaler_init_pr[desc->type]))(sc, desc);
  }
}

s32 scaler_get_value(ParamScaler* sc, io_t in) {
  /* print_dbg("\r\n requesting scaler value for input: 0x"); */
  /* print_dbg_hex((u32)in); */

  /* print_dbg("\r\n scaler address: 0x"); */
  /* print_dbg_hex((u32)sc); */
  
  /* print_dbg("\r\n scaler type: "); */
  /* print_dbg_ulong(sc->type); */

  /* print_dbg("\r\n input value: "); */
  /* print_dbg_hex((u32)in); */

  //// FIXME: inefficient
  if(scaler_get_val_pr[sc->type] != NULL) {
    return (*(scaler_get_val_pr[sc->type]))(in);
  } else {
    print_dbg("\r\n null function pointer");
    return 0;
  }
}

// get UI string representation for input
void scaler_get_str(char* dst, ParamScaler* sc, io_t in) {

  //// FIXME: inefficient
  if(scaler_get_str_pr[sc->type] != NULL) {
    (*(scaler_get_str_pr[sc->type]))(dst, in);
  }

}

// get input given DSP value (use sparingly)
io_t scaler_get_in(ParamScaler* sc, s32 value) {

  if(scaler_get_in_pr[sc->type] != NULL) {
    return (*(scaler_get_in_pr[sc->type]))(value);
  } else {
    return 0;
  }
}