#if ((defined(__ck804ef__) || defined(__ck805ef__)) && defined(FDK_CSKY_ASM))

#define FUNCTION_LPPTRANSPOSER_func1

#ifdef FUNCTION_LPPTRANSPOSER_func1

static void lppTransposer_func1(FIXP_DBL *lowBandReal, FIXP_DBL *lowBandImag,
                                FIXP_DBL **qmfBufferReal,
                                FIXP_DBL **qmfBufferImag, int loops, int hiBand,
                                int dynamicScale, int descale, FIXP_SGL a0r,
                                FIXP_SGL a0i, FIXP_SGL a1r, FIXP_SGL a1i,
                                const int fPreWhitening,
                                FIXP_DBL preWhiteningGain,
                                int preWhiteningGains_sf) {
  FIXP_DBL real1, real2, imag1, imag2, accu1, accu2;

  real2 = lowBandReal[-2];
  real1 = lowBandReal[-1];
  imag2 = lowBandImag[-2];
  imag1 = lowBandImag[-1];
  for (int i = 0; i < loops; i++) {
    accu1 = fMultDiv2(a0r, real1);
    accu2 = fMultDiv2(a0i, imag1);
    accu1 = fMultAddDiv2(accu1, a1r, real2);
    accu2 = fMultAddDiv2(accu2, a1i, imag2);
    real2 = fMultDiv2(a1i, real2);
    accu1 = accu1 - accu2;
    accu1 = accu1 >> dynamicScale;

    accu2 = fMultAddDiv2(real2, a1r, imag2);
    real2 = real1;
    imag2 = imag1;
    accu2 = fMultAddDiv2(accu2, a0i, real1);
    real1 = lowBandReal[i];
    accu2 = fMultAddDiv2(accu2, a0r, imag1);
    imag1 = lowBandImag[i];
    accu2 = accu2 >> dynamicScale;

    accu1 <<= 1;
    accu2 <<= 1;
    accu1 += (real1 >> descale);
    accu2 += (imag1 >> descale);
    if (fPreWhitening) {
      accu1 = scaleValueSaturate(fMultDiv2(accu1, preWhiteningGain),
                                 preWhiteningGains_sf);
      accu2 = scaleValueSaturate(fMultDiv2(accu2, preWhiteningGain),
                                 preWhiteningGains_sf);
    }
    qmfBufferReal[i][hiBand] = accu1;
    qmfBufferImag[i][hiBand] = accu2;
  }
}
#endif /* #ifdef FUNCTION_LPPTRANSPOSER_func1 */

#endif /* __csky__ */
