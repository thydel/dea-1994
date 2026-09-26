.\"
.\" ANNEXE/RABBIT
.\"
.thy@APP "pre'dateur/proie"
.thy@BIG
.thy@PLOT2V rabbit-gnans-1 rabbit-gnans-2 "\fBfox-rabbit\fP gnans" 12c 3c 12c 3c
La figure \*[plot-rabbit-gnans-1+rabbit-gnans-2]
montre deux solutions pe'riodiques obtenus
avec \fCgnans\fP\*[Rf]
.RS
B. Martensson
.br
gnans - A program for Stochastic and Deterministic Dynamical Systems
.br
Copyright (C) 1989, 1991 Free Software Foundation, Inc.
.RF
pour l'e'quation du mode`le pre'dateur-proie de Lokta-Volterra.
D'apre`s:
.[
Murray
.]
.DS CB
.EQ \*[app*ind].1
dN over dt = N(a - bP),
.EN
.EQ \*[app*ind].2
dP over dt = P(cN - d),
.EN
.DE
avec a, b, c et d constantes positives.
Les e'quations \*[app*ind].1 et \*[app*ind].2 sont spe'cifie'es tels que a` \fCgnans\fP:
.thy@CODE-START
	CONTINUOUS TIME SYSTEM lokta;
	
	AT TIME t:
	d(n) = n * (a - b * p);
	d(p) = p * (c * n - dd);
.thy@CODE-END
Les valeurs des variables et des parame`tres sont,
pour la solution 1\*F:
.FS
Et les conditions ope'rationnelles: timestep = 1, stoptime = 48, algo = RKF45.
.FE
.thy@CODE-START
	STATE n = 2;
	STATE p = 1.99;
	TIME t;
	
	PARAMETER a = 4;
	PARAMETER b = 3;
	PARAMETER c = 2;
	PARAMETER dd = 5;
.thy@CODE-END
et pour la solution 2\*F:
.FS
timestep = 1, stoptime = 200, algo = Ode.
.FE
.thy@CODE-START
	STATE n = 1;
	STATE p = 1;
	TIME t;
	
	PARAMETER a = .8;
	PARAMETER b = .1;
	PARAMETER c = .1;
	PARAMETER dd = .1;
.thy@CODE-END
.P
.thy@BIG
.thy@PLOT2V rabbit-1 rabbit-1-512 "\fBfox-rabbit\fP Version 1" 12c 3c 12c 3c
La figure \*[plot-rabbit-1+rabbit-1-512]
montre l'e'volution des populations proie-pre'dateurs obtenue
avec la re`gle \fBfox-rabbit\fP version 1,
pour 100 ge'ne'rations sur un espace taille $128 times 128$ (haut)
et $512 times 512$ (bas).
Dans les deux cas, l'espace initial est de densite' ale'atoire \(12
sur le plan fox et sur le plan rabbit.
.br
\fBfox-rabbit\fP version 1:
.thy@CODE-START
	fox_sum = W0 + N0 + S0 + E0;
	rabbit_sum = W1 + N1 + S1 + E1;
	ofox = ifox;
	orabbit = irabbit;

	if (ifox && irabbit) {
		orabbit = 0;
	}
	if (ifox) {
		ofox_life = ifox_life - 1;
		ofox = ofox_life > 0;
	} 
	if (irabbit && !ifox) {
		orabbit_life = irabbit_life - 1;
		orabbit = orabbit_life > 0;
	}
	if (!ifox && fox_sum >= 2 && rabbit_sum >= 1) {
		ofox = 1;
		ofox_life = 3;
	}
	if (!irabbit && rabbit_sum >= 2) {
		orabbit = 1;
		orabbit_life = 3;
	}
.thy@CODE-END
.P
.thy@BIG
.thy@PLOT2V rabbit-2 rabbit-3 "\fBfox-rabbit\fP Version 2 et 3" 12c 3c 12c 3c
La figure \*[plot-rabbit-2+rabbit-3]
montre l'e'volution des populations proie-pre'dateurs obtenue
avec la re`gle \fBfox-rabbit\fP version 2 (haut) et 3 (bas).
pour 200 et 400 ge'ne'rations sur un espace taille $128 times 128$,
me^me espace initial que pour la figure \*[plot-rabbit-1+rabbit-1-512].
.br
\fBfox-rabbit\fP version 2\*F:
.FS
La dernie`re condition de cre'ation d'un rabbit est buge'!
.FE
.thy@CODE-START
	if (ifox && irabbit) {
		ofox_life = ifox_life - 1;
		ofox = ofox_life > 0;
		orabbit = 0;
	}
	if (ifox && !irabbit) {
		ofox_life = ifox_life - 3;
		ofox = ofox_life > 0;
	} 
	if (irabbit && !ifox) {
		orabbit_life = irabbit_life - 1;
		orabbit = orabbit_life > 0;
	}
	if (!ifox && fox_sum == 2 && rabbit_sum >= 1) {
		ofox = 1;
		ofox_life = 7;
	}
	if (!irabbit && (rabbit_sum >= 2 || rabbit_sum <= 3)) {
		orabbit = 1;
		orabbit_life = 2;
	}
.thy@CODE-END
\fBfox-rabbit\fP version 3:
.thy@CODE-START
	if (ifox && irabbit) {
		if (fox_sum > rabbit_sum) {
			ofox_life = ifox_life - 1;
			ofox = ofox_life > 0;
			orabbit = 0;
		} else if (fox_sum < rabbit_sum) {
			orabbit_life = irabbit_life - 1;
			orabbit = orabbit_life > 0;
			ofox = 0;
		}
	}
	if (ifox && !irabbit) {

		ofox_life = ifox_life - 2;
		ofox = ofox_life > 0;
	}
	if (irabbit && !ifox) {
		orabbit_life = irabbit_life - 2;
		orabbit = orabbit_life > 0;
	}
	if (!ifox && fox_sum == 2) {
		ofox = 1;
		ofox_life = 7;
	}
	if (!irabbit && rabbit_sum >= 2 && fox_sum >= 1) {
		orabbit = 1;
		orabbit_life = 3;
	}
.thy@CODE-END
.\"
.\" ANNEXE/CAW
.\"
.thy@APP "Exemple de code Tcl top-level"
\fCTcl\fP\*[Rf]
.RS
J. Ousterhout
.br
Tcl - tool command language facilities
.br
Copyright 1987-1991 Regents of the University of California
.RF
est un langage de commande et une librairie
utilisable comme interface de programmes interactif.
.br
Cre'ation des structures de donne'es pour le voisinage:
.EQ
delim off
.EN
.thy@CODE-START
.so src/conex.tcl-src
.thy@CODE-END
De'finitions des fonctions:
.thy@CODE-START
.so src/func.tcl-src
.thy@CODE-END
De'finitions d'objets top-level:
.thy@CODE-START
.so src/data.tcl-src
.thy@CODE-END
De'finitions de proce'dures travaillant sur des objets top-level
destine's a` l'interface humaine
(soit par un tty, soit par une interface \fCTk\fP).
.thy@CODE-START
.so src/cas.tcl-src
.thy@CODE-END
.\"
.\" ANNEXE/XCAW
.\"
.thy@APP "Exemple d'interface X11"
Une interface X11 expe'rimentale re'alise'e avec \fCTk\fP\*[Rf]:
.RS
J. Ousterhout
.br
Tk - an X11 toolkit that provides the Motif look and feel and is implemented using the Tcl command language.
.br
Copyright 1987-1991 Regents of the University of California
.RF
.thy@BIG
.thy@DUMP2 cas-dump cas-cmd-1 "Une interface expe'rimentale et son dumper"
.\"
.\" ANNEXE/PRETTY
.\"
.thy@APP "Encore quelques images"
.thy@BIG
.thy@DUMP loop-1024 "1024 step of Langton \fBloop\fP rule"
.thy@BIG
.thy@DUMP anneal-sum-1k-8k "A big \fBanneal\fP sum"
.thy@BIG
.thy@DUMP anneal-sum-1k-8k-xv "Une autre colormap pour la figure \*[dump-anneal-sum-1k-8k]"
.thy@BIG
.\"thy@DUMP anneal-sum-1k4k8k-he "Color test"
.thy@BIG
.thy@DUMP2 life-3d lifex-3d "Une autre vue de la figure \*[plot-lifex-sum-1+lifex-sum-2]"
.thy@BIG
.thy@DUMP anneal-3d "Une autre vue de la dynamique de la re`gle \fBanneal\fR"
Voir aussi la figure \*[plot-anneal-sum].
.\"
.\" ANNEXE/OTHER-SYSTEMS
.\"
.\"thy@APP "La concurrence"
.\"
.\" ANNEXE/TCL-TK
.\"
.\"thy@APP "Tcl/Tk"
.\"
.\" ANNEXE/MANUEL
.\"
.\"thy@APP "Manuel"
.\"
.\" ANNEXE/LEXIK
.\"
.thy@APP "Lexique"
.so mm/lexik.mm
.EQ
delim $$
.EN
