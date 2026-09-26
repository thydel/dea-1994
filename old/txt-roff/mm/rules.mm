.thy@H 1 "Quelques fonction de transitions"
.\"
.\" RULES/XOR9
.\"
.thy@H 2 "Xor9"
.SETR ref-rule-xor9
$C = N \*[thy@xor] S \*[thy@xor] E \*[thy@xor] W \*[thy@xor] C \*[thy@xor] NE \*[thy@xor] NW \*[thy@xor] SE \*[thy@xor] SW$
.\"
.\" RULES/ANNEAL
.\"
.EQ
delim off
.EN
.thy@H 2 "Anneal"
.SETR ref-rule-anneal
.thy@CODE-START
.so src/anneal.c-src
.thy@CODE-END
.thy@CODE-START
.so src/anneal.tcl-src
.thy@CODE-END
.\"
.\" RULES/QMEAN
.\"
.thy@H 2 "qmean"
.SETR ref-rule-qmean
.thy@CODE-START
tmp = (SUM + C) / 9;
tmp = tmp & mask == match ? tmp : tmp + delta;
.thy@CODE-END
Les parame`tres utilise's dans les illustrations\*F
.FS
.thy@GET-FIG dump-tsum-grey 1
.FE
sont:
.thy@CODE-START
mask = 3; match = 0; delta = -1;
.thy@CODE-END
.\"
.\" RULES/TUBE-WORM
.\"
.thy@H 2 "tube-worm"
.SETR ref-rule-tube-worm
.thy@CODE-START
.so src/tube-worm.c-src
.thy@CODE-END
.EQ
delim $$
.EN
