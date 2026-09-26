inline void gapp_pe(int* a, int* i, int* o) {
  int nst[] = { i[GAPP_NS], i[GAPP_RAM], i[GAPP_NOS],
		i[GAPP_NOS], i[GAPP_EW], i[GAPP_C], 0 };
  int ewt[] = { i[GAPP_EW], i[GAPP_RAM], i[GAPP_EOW],
		i[GAPP_EOW], i[GAPP_NS], i[GAPP_C], 0 };
  int ct[] = { i[GAPP_C], i[GAPP_RAM], i[GAPP_NS], i[GAPP_EW],
	       i[GAPP_CY], i[GAPP_BW], 0, 1 };
  int ramt[] = { i[GAPP_RAM], 0, i[GAPP_C], i[GAPP_SM] };
  int tmp;

  o[GAPP_NNS] = nst[i[GAPP_NSI]];
  o[GAPP_NEW] = ewt[i[GAPP_EWI]];
  o[GAPP_NC] = ct[i[GAPP_CI]];
  o[GAPP_NRAM] = ramt[i[GAPP_RAMI]];

  tmp = a[(o[GAPP_NNS] << 2) | (o[GAPP_NEW] << 1) | o[GAPP_NC]];

  o[GAPP_NSM] = !!(tmp & 4);
  o[GAPP_NCY] = !!(tmp & 2);
  o[GAPP_NBW] = tmp & 1;
}
