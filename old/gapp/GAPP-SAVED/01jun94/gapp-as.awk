BEGIN {
  funk["gapp"] = ++tmp;
  funk["extract"] = ++tmp;
  funk["pause"] = ++tmp;
  funk["clear"] = ++tmp;
  funk["single"] = ++tmp;
  funk["random"] = ++tmp;
  funk["bloc"] = ++tmp;
  funk["label"] = ++tmp;
  funk["goto"] = ++tmp;
  funk["state2ascii"] = ++tmp;
  funk["frame2ascii"] = ++tmp;
  funk["print"] = ++tmp;

  gapp["ns:=ram"] = 1;
  gapp["ns:=n"] = 2;
  gapp["ns:=s"] = 3;
  gapp["ns:=ew"] = 4;
  gapp["ns:=c"] = 5;
  gapp["ns:=0"] = 6;
  gapp["ew:=ram"] = 1 * 8;
  gapp["ew:=e"] = 2 * 8;
  gapp["ew:=w"] = 3 * 8;
  gapp["ew:=ns"] = 4 * 8;
  gapp["ew:=c"] = 5 * 8;
  gapp["ew:=0"] = 6 * 8;
  gapp["c:=ram"] = 1 * 64;
  gapp["c:=ns"] = 2 * 64;
  gapp["c:=ew"] = 3 * 64;
  gapp["c:=cy"] = 4 * 64;
  gapp["c:=bw"] = 5 * 64;
  gapp["c:=0"] = 6 * 64;
  gapp["c:=1"] = 7 * 64;
  gapp["ram:=c"] = 2 * 512;
  gapp["ram:=sm"] = 3 * 512;
}

/^#.*$/ || /^ *$/ {;}

/^gapp/ {
  sub(/gapp/, "");
  gsub(/ +/, "");
  sub(/;$/, "");
  n = split($0,t,";");
  for (i = 1; i <= n; ++i) {
    match(t[i], /ram[0-9]+/);
    if (RSTART) {
      ram = substr(t[i], RSTART + 3, RLENGTH - 3);
      sub(/ram[0-9]+/, "ram", t[i]);
    } else {
      ram = 0;
    }
    if (gapp[t[i]] == 0) {
      print "illegal micro-instruction", t[i], "at line", FNR > "/dev/stderr";
      exit(1);
    }
    code += gapp[t[i]];
  }
  print funk["gapp"], code, ram;
  code = 0;
}

/^single/ || /^random/ || /^bloc/ || /^clear/ {
  print funk[$1]
}

/^extract/ || /^pause/ || /^label/ || /^goto/ || /^state2ascii/ {
  print funk[$1], $2;
}

/^frame2ascii/ {
  print funk[$1], $2, $3;
}

/^print/ {
  print funk[$1], $2, $3, $4, $5, $6
}
