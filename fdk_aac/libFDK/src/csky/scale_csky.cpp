#if ((defined(__ck804ef__) || defined(__ck805ef__)) && defined(FDK_CSKY_ASM))

#ifndef __INCLUDE_SCALE_CSKY__
#define __INCLUDE_SCALE_CSKY__

#if !defined(FUNCTION_scaleValuesWithFactor_DBL)
#define FUNCTION_scaleValuesWithFactor_DBL
SCALE_INLINE
void scaleValuesWithFactor(FIXP_DBL *vector, FIXP_DBL factor, INT len,
                           INT scalefactor) {
  /* This code combines the fMult with the scaling             */
  /* It performs a fMultDiv2 and increments shift by 1         */
  int shift = scalefactor + 1;
  FIXP_DBL *mySpec = vector;

  shift = fixmin_I(shift, (INT)DFRACT_BITS - 1);

  if (shift >= 0) {
    for (int i = 0; i < (len >> 2); i++) {
      FIXP_DBL tmp0 = mySpec[0];
      FIXP_DBL tmp1 = mySpec[1];
      FIXP_DBL tmp2 = mySpec[2];
      FIXP_DBL tmp3 = mySpec[3];
      tmp0 = fMultDiv2(tmp0, factor);
      tmp1 = fMultDiv2(tmp1, factor);
      tmp2 = fMultDiv2(tmp2, factor);
      tmp3 = fMultDiv2(tmp3, factor);
      tmp0 <<= shift;
      tmp1 <<= shift;
      tmp2 <<= shift;
      tmp3 <<= shift;
      *mySpec++ = tmp0;
      *mySpec++ = tmp1;
      *mySpec++ = tmp2;
      *mySpec++ = tmp3;
    }
    for (int i = len & 3; i--;) {
      FIXP_DBL tmp0 = mySpec[0];
      tmp0 = fMultDiv2(tmp0, factor);
      tmp0 <<= shift;
      *mySpec++ = tmp0;
    }
  } else {
    shift = -shift;
    for (int i = 0; i < (len >> 2); i++) {
      FIXP_DBL tmp0 = mySpec[0];
      FIXP_DBL tmp1 = mySpec[1];
      FIXP_DBL tmp2 = mySpec[2];
      FIXP_DBL tmp3 = mySpec[3];
      tmp0 = fMultDiv2(tmp0, factor);
      tmp1 = fMultDiv2(tmp1, factor);
      tmp2 = fMultDiv2(tmp2, factor);
      tmp3 = fMultDiv2(tmp3, factor);
      tmp0 >>= shift;
      tmp1 >>= shift;
      tmp2 >>= shift;
      tmp3 >>= shift;
      *mySpec++ = tmp0;
      *mySpec++ = tmp1;
      *mySpec++ = tmp2;
      *mySpec++ = tmp3;
    }
    for (int i = len & 3; i--;) {
      FIXP_DBL tmp0 = mySpec[0];
      tmp0 = fMultDiv2(tmp0, factor);
      tmp0 >>= shift;
      *mySpec++ = tmp0;
    }
  }
}
#endif /* #if !defined(FUNCTION_scaleValuesWithFactor_DBL) */

#endif /* #ifndef __INCLUDE_SCALE_CSKY__ */

#endif
