BEGIN {
  inst["NS_RAM"] = 1;
  inst["NS_N"] = 2;
  inst["NS_S"] = 3;
  inst["NS_EW"] = 4;
  inst["NS_C"] = 5;
  inst["NS_0"] = 6;
  inst["EW_RAM"] = 1 * 8;
  inst["EW_E"] = 2 * 8;
  inst["EW_W"] = 3 * 8;
  inst["EW_NS"] = 4 * 8;
  inst["EW_C"] = 5 * 8;
  inst["EW_0"] = 6 * 8;
  inst["C_RAM"] = 1 * 64;
  inst["C_NS"] = 2 * 64;
  inst["C_EW"] = 3 * 64;
  inst["C_CY"] = 4 * 64;
  inst["C_BW"] = 5 * 64;
  inst["C_0"] = 6 * 64;
  inst["C_1"] = 7 * 64;
  inst["RAM_C"] = 2 * 512;
  inst["RAM_SM"] = 3 * 512;
  FS = ";"
}
/^#*$/ { print 0, 0, 0; }
!/^#*$/ {
  instf = $1;
  address = $2;
  extract = $3;
  n = split(instf, t, ",");
  for (i = 1; i <= n; ++i) {
    code += inst[t[i]];
  }
  print code, address, extract;
  code = 0;
}
