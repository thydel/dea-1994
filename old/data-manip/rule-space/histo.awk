#!/usr/bin/awk -f

{ ++t[$col]; }

END {
    for (i in t) {
      print i, t[i];
  }
}
