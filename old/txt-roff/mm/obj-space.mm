.thy@H 2 "L'espace, la me'moire"
L'espace est un ensemble de cellules
ordonne'es conforme'ment a` la structure d'interconnexion de la fonction.
La structure de l'espace peut the'oriquement e^tre quelconque
pourvu qu'elle soit homoge`ne.
En pratique nous limitons initialement les structures disponibles
aux espaces de dimension $d$ 1, 2 ou 3.
.SETR ref-nombre-de-voisin
Le nombre $r$ de cellules
distantes de $n$ unite's au plus
d'une cellule quelconque de l'espace est $pow((2n + 1), d)$.
La structure d'interconnexion sera un sous-ensemble
de l'ensemble des cellules distantes de $n$ unite's au plus,
avec $n$ typiquement limite' a` 1 ou 2 unite's.
Nous appelerons \fIcube d'interconnexion\fR de dimension $d$
une structure d'interconnexion comple`te pour la dimension $d$
et \fIcroix d'interconnexion\fR de dimension $d$
l'ensemble des cellules distantes de $n$ unite's au plus
sur une dimension de l'espace au plus.
Le cube d'interconnexion de dimension 2 et distance 1 correspond au voisinage de Moore,
et la croix d'interconnexion de dimension 2 et distance 1 au voisinage de von Neumann.
Le nombre d'e'le'ments d'une croix d'interconnexion est
$2 n d + 1$.
.thy@TBL neighburhood-size "Nombres d\*[thy@quote]e'tats (en bytes) de quelques cubes d\*[thy@quote]interconnexions"
.so tbl/neighburhood-size.tbl
.thy@TBL-END
La table \*[tbl-neighburhood-size]
donne la taille en bytes
des tables de transitions des cubes d'interconnexions de cellules binaires
pour les 4 premie`res dimensions d'espace
et les 4 premie`res distances.
Les entre'es en caracte`res gras sont re'alisables par lookup table.
.thy@TBL neighburhood-size-1 "Nombres d\*[thy@quote]e'tats (en bytes) de quelques croix d\*[thy@quote]interconnexions"
.so tbl/neighburhood-size-1.tbl
.thy@TBL-END
La table \*[tbl-neighburhood-size-1]
sugge`re l'inte're^t de voisinages mixtes $croix(d, n) union cube(d, n - 1)$.
Mais la structure d'interconnexion re'gulie`re offrant le meilleurs compromis
distance/volume/isotropie est une \fIsphe`re de manhattan\fR,
une hyper-sphe`re de dimension $d$ dont le rayon est une distance de
manhattan\*F.
.FS
Le volume d'une sphe`re de manhattan est
$S(d, r) = S(d - 1, r) + 2 sum from i=R-1 to i=0 S(d - 1, i)$
avec
$S(1, r) = 2r + 1$.
Les de'finition que nous proposons pour les cubes, croix et sphe`re de connexions
conside`rent le centre comme exclu du rayon.
l'inclusion du centre dans le rayon permet la de'finition de cubes et de sphe`res
prive' d'un centre ponctuel.
Le voisinage de Margolus
.[
Toffoli Cellular Automata Machines
.]
par exemple utilise un carre' de 2 cellules de cote'.
.FE
Une sphe`re de manhattan de rayon 1 de'fini la me^me structure d'interconnexion
qu'une croix de rayon 1.
Le voisinage de von Neumann est donc une sphe`re de manhattan,
mais pas voisinage de Moore.
Avec des cellules binaires,
en dimension 2 les sphe`res de rayons 2 et 3 sont accessibles (1K et 4M),
en dimension 3 la sphe`re de rayons 2 est accessible (4M).
.thy@TBL neighburhood-size-2 "Nombres d\*[thy@quote]e'tats (en bytes) de quelques sphe`res d\*[thy@quote]interconnexions"
.so tbl/neighburhood-size-2.tbl
.thy@TBL-END
.P
L'espace supporte des fonctions
d'entre'e/sortie,
d'e'dition,
de re'duction et de transformation.
.\"
.\" OBJECTS/SPACE/STRUCT
.\"
.thy@H 3 "Structure d'espace"
L'espace appara\(^it comme une ligne,
un plan,
ou un volume de cellules
adressables globalement par leurs coordonne'es euclidiennes.
Nous utiliserons un espace de dimension 2 par de'faut
pour exposer les ope'rations applicables sur les espaces.
Cet espace peut e^tre vu et manipule'
soit comme un plan de cellules,
soit comme un vecteur de plans de bits
correspondant a` une tranche cellulaire.
Les ope'rations sur un espace
sont toutes les ope'rations possibles
sur une \fIme'moire\fR organise'e selon une dualite'
vecteur de plans de bits,
plan de vecteurs de bits.
.P
Ide'alement,
en association avec une structure d'interconnexion,
le vecteur de bits de la me'moire cellulaire
est associe' a` une structure de nommage.
Les noms des zones de me'moire
sont utilisables en parame`tres des ope'rations
portant sur les tranches d'espaces cellulaires
(e'dition, visualisation, re'duction)
et sur les variables cellulaires
(de'finition de la fonction de transition).
.\"
.\" OBJECTS/SPACE/EDIT
.\"
.thy@H 3 "Edition d'espace"
Une premie`re famille d'ope'rations
est fournie par un e'diteur de \fIpixmaps\fP
permettant la construction des configurations d'espaces
au temps ze'ro d'une simulation.
L'e'diteur permet e'galement
la modification du point d'espace courant dans le temps
entre chaque application de la fonction de transition.
.P
Il est souhaitable de pouvoir utiliser
aussi d'autres outils que les no^tres
(que nous nommons outils externes)
pour manipuler les espaces.
Le format de stockage externe
doit permettre l'application \fIoff-line\fP
de nombreux outils sur les espaces.
Le terme off-line
de'signe le passage des objets de la simulation
a` d'autres processus.
Ceci permet une inte'gration e'troite de ces outils
a` l'environnement de de'veloppement et/ou d'interaction,
mais implique l'existence de plusieurs classes de de'bit
pour les ope'rations applicables sur les objets.
Cette contrainte est quasiment sans effet pour l'utilisation
d'e'diteurs interactifs de type \fIpainter\fP ou \fIdrawer\fP sur un espace.
.thy@BIG
.thy@DUMP neighburhood-size-tbl-16xor9 "Ge'ne'ration 16 de la re`gle \fBxor9\fP sur la table \*[tbl-neighburhood-size]\*F"
.\"thy@PCS
.FS
Les nume'ros de notes en indice supe'rieur entre crochets
renvoient au repertoire des outils, donne' en appendice.
.br
Nous avons choisi \fCPBM\fP\*[Rf]
.RS
J. Poskanzer
.br
pbmplus - Extended Portable Bitmap Toolkit
.br
Copyright (C) 1989, 1991 by Jef Poskanzer.
.RF
comme format pivot de bitmap/pixmap.
La figure \*[dump-neighburhood-size-tbl-16xor9]
montre l'application de la re`gle \fBxor9\fP
.thy@GET-REF rule-xor9 2
sur un espace obtenu a` partir de la table \*[tbl-neighburhood-size].
Pour ce faire \fCgroff\fP\*[Rf]
.RS
J. Clark
.br
groff - document formatting system
.br
Copyright (C) 1989, 1990, 1991, 1992 Free Software Foundation, Inc.
.br
From the README:
.br
Included in this release are implementations of troff, pic, eqn, tbl,
refer, the -man macros and the -ms macros, and drivers for PostScript,
TeX dvi format, and typewriter-like devices.  Also included is a
modified version of the Berkeley -me macros, an enhanced version of
the X11 xditview previewer, and an implementation of the -mm macros
contributed by Joergen Haegg.
.RF
est utilise' pour produire une repre'sentation PostScript de la page,
puis \fCghostscript\fP\*[Rf]
.RS
Aladdin Enterprises
.br
ghostscript - PostScript previewer
.br
Copyright (C) 1989, 1992 Aladdin Enterprises. Distributed by Free Software Foundation, Inc.
.RF
est utilise' pour produire une repre'sentation PBM de la page,
divers outils comprenant le format PBM
tel \fCxv\fP\*[Rf],
.RS
J. Bradley
.br
xv - interactive image display for the X Window System
.br
Copyright 1989, 1990, 1991, 1992 by John Bradley and the University of Pennsylvania
.RF
peuvent e^tre utilise' a` ce stade
pour retravailler le bitmap,
enfin le bitmap est utilise' par CAW qui fournit le bitmap
transforme' par l'application ite'rative d'une re`gle,
lequel est retransforme' en PostScript pour insertion dans le document final.
.\"thy@PCE
.FE
L'e'diteur devrait e'galement fournir
une famille de fonctions de remplissage ale'atoire de l'espace
aussi riche que possible.
.\"
.\" OBJECTS/SPACE/REDUCT
.\"
.thy@H 3 "Re'duction d'espace"
La deuxie`me famille d'ope'rations fournit
des fonctions de re'duction de l'information contenu dans un espace.
Il s'agit de re'ductions arithme'tiques e'le'mentaires
(somme, histogramme, parite'),
de re'ductions statistiques standards
(minimum, maximum, moyenne, entropie, dimension fractale)
ou spe'cialise'es comme le comptage de patterns propres a` une simulation.
On peut ajouter les outils standards de compressions de donne'es qui,
outre l'archivage des espaces, fournissent des quantite's informationnelles.
.br
Ici encore l'utilisation d'un format pivot standard
et dote' de nombreux outils de conversion de format
permet l'utilisation d'outils statistiques off-line\*F.
.FS
.thy@GET-TBL tbl-lifex-sum-1 1
.FE
De plus les outils externes se pre'sentant sous la forme de librairie
sont e'galement inte'grables a` l'environnement de de'veloppement
et permettent une utilisation directe
qui ne ne'cessite pas l'emploi de fichiers temporaires.
.\"
.\" OBJECTS/SPACE/TRANSFORM
.\"
.thy@H 3 "Transformation d'espace"
Enfin, des transformations globales arbitraires
sont applicables sur les espaces.
Il s'agit par exemple
des fonctions de traitement du signal en ge'ne'ral,
et de traitement d'images
tel que la reconnaissance des formes et l'extraction de contour.
.thy@BIG
.thy@DUMP tsum-128-edge "Un dithering et deux de'tections de contours"
La figure \*[dump-tsum-128-edge] montre une de'tection de contours
utilisant des outils fournit par PBM.
.thy@GET-FIG dump-tsum-grey 3
.P
Certaines de ces fonctions
sont elle me^mes base'es sur des algorithmes cellulaires,
elle doivent alors pouvoir e^tre re'alise'es
a` l'aide de l'environnement de de'veloppement,
les fonctions de se'quencement
permettant leur application non destructive
a` la vole'e sur le point d'espace courant d'une se'quence.
.\"
.\" OBJECTS/SPACE/VISUAL
.\"
.thy@H 3 "Visualisation d'espace"
L'espace constitue un objet de visualisation e'le'mentaire a priori.
Il peut e^tre vu par l'interme'diaire de fene^tres X11
associe'es a` un bitmap,
ou a` une se'quence de plans de bits (pixmap)
associe's a` une \fIcolormap\fP.
.thy@BIG
.thy@DUMP anneal-g128-s11 "Un bitmap point-bit $2048 times 2048$"
La figure \*[dump-anneal-g128-s11]
montre la visualisation par bitmap
de l'espace de la ge'ne'ration 128
de la re`gle \fBanneal\fP\*F.
.FS
.thy@GET-REF rule-anneal 1
.FE
L'espace est de taille $2048 times 2048$.
L'espace initial a une densite' ale'atoire \(12.
La taille de la cellule e'tant de 1 bit,
le bitmap permet de visualiser l'inte'gralite' des e'tats cellulaires.
Chaque point de l'image correspond a` un bit.
.thy@BIG
.thy@DUMP tube-worm-mix "64 bitmaps ($256 times 256$)"
La figure \*[dump-tube-worm-mix]
montre 8 se'quences (de haut en bas),
de 8 espaces chacune(de gauche a` droite).
.\"thy@PCS
Il s'agit de se'quences de la re`gle \fBtube-worm\fP\*F
.FS
.thy@GET-REF rule-tube-worm 1
.FE
applique' sur le me^me espace initial,
les variations portant sur les parame`tres statiques\*F
.FS
.thy@GET-REF static-param 1
.FE
de la re`gle.
Le nombre de ge'ne'rations entre deux espaces
de'pend d'un des parame`tres statiques de la re`gle.
Il est de 32 intervalles du temps propre a` cette re`gle.
.\"thy@PCE
.P
.thy@BIG
.thy@DUMP tsum-grey "Visualisation pixmap de 2 ge'ne'rations de la re`gle \fBqmean\fP"
La figure \*[dump-tsum-grey]
montre la visualisation par pixmap
des espaces de ge'ne'ration 128 et 256 (de gauche a droite)
de la re`gle \fBqmean\fP
.thy@GET-REF rule-qmean 2
utilisant deux type de colormaps\*F (de haut en bas).
.FS
Les colormaps sont ici des greymaps.
Les deux pixmaps supe'rieurs utilisent une greymap
dont l'e'chelle des valeurs est progressive.
Les deux pixmaps infe'rieurs utilisent une greymap
dont l'e'chelle des valeurs est ale'atoire,
masquant la re'partition ge'ne'rale des intensite's,
mais re've'lant les de'tails de l'alternance de valeurs.
.FE
L'espace est de taille $256 times 256$.
L'espace initial a une densite' ale'atoire \(12.
La taille de la cellule e'tant de 8 bit,
256 couleurs sont ne'cessaires pour visualiser tous les e'tats possible\*F.
.FS
Bien entendu, en terme purement informationnel
l'espace est comme pour la figure \*[dump-anneal-g128-s11] $2048 times 2048$.
.FE
.thy@BIG
.thy@DUMP tsum "Visualisation bitmap des 8 plans de 8 ge'ne'rations de la re`gle \fBqmean\fP"
La figure \*[dump-tsum]
montre la visualisation des ge'ne'rations $pow(2,3)$ a` $pow(2,10)$
(de haut en bas)
de la re`gle \fBqmean\fP\.
L'espace est de taille $128 times 128$.
L'espace initial a une densite' ale'atoire \(12.
Les 256 e'tats possibles de chaque cellule
sont visualise's par 8 bitmaps au lieu d'un pixmap.
Les bitmaps sont pre'sente's de gauche a` droite pour les bit 0 a` 7.
.P
Les variables de re'ductions d'espace
sont pre'sente'es sous forme ASCII,
associe'es aux fene^tres pixmap,
ou e'ventuellement par des \fIviewers\fP
de groupe de variables scalaires (bargraph par exemple).
Ce type de visualisation (bitmaps + scalaires)
est assez rapide pour permettre la re'alisation
de films de se'quences d'espaces
a` une fre'quence supe'rieure a` 1 Hz.
.P
D'autres types de visualisations
de'die'es a` une simulation particulie`re
ou plus consommatrices en ressources sont possibles:
.BL
.LI
Une version iconique de l'e'tat d'une cellule.
.LI
Une vision tridimensionnelle,
re'alise'e par \fIplotter\fP\*F
.FS
Ce type de visualisation repose e'videmment
sur le transfert d'un espace a` un outil externe spe'cialise'.
Nous avons utilise' \fCgnuplot\fP\*[Rf]
.RS
T. Williams, Pixar Corporation
.br
gnuplot - an interactive plotting program
.br
Copyright(C) 1986, 1987, 1990, 1991, 1992  Thomas Williams, Colin Kelley
.RF
et \fCKhoros\fP\*[Rf].
.RS
Khoros Consortium
.br
Khoros - an integrated software development environment
for information processing and visualization.
.br
Khoros is a Registered Trademark of The University of New Mexico
.br
From the README:
.br
Khoros components include a visual programming
language, code generators for extending the visual language
and adding new application packages to the system, an
interactive user interface editor, interactive image display 
programs, surface visualization, an extensive library of image 
processing, numerical analysis and signal processing routines, 
and 2D/3D plotting packages.  X applications built using the Khoros
User Interface Libraries have built in journal/playback and groupware
capabilities.
.RF
.FE
.thy@GET-FIG plot-anneal-sum 2
ou \fIrenderer\fP\*F
.FS
Nous avons utilise' \fCqrt\fP\*[Rf]
.RS
S. Koren
.br
qrt - Ray Tracer
.br
Copyright 1988 and 1989 Steve Koren
.RF
et la toolbox \fCVart\fP\*[Rf] sous \fCKhoros\fP.
.RS soft-ref-vart
P. Averkamp
.br
vart - 3D object toolbox for Khoros 1
.br
Copyright 1992, Peter Averkamp.  All rights reserved.
.RF
.FE
.thy@GET-FIG dump-tsum-ray-one 2
d'un espace conside're' comme surface d'e'le'vation,
ou dont une des variables d'e'tat de la cellule
est conside're' comme donne'e d'e'le'vation,
et une autre comme donne'e de projection.
.LI
Pour les espaces de dimension 3,
une vision tridimensionnelle
par seuillage,
e'pluchage
ou transparence.
.LE
Les visualisations cou^teuses en ressources,
ne permettant pas la re'alisation de films temps re'el,
servent a` la re'alisation d'instantane's,
la re'alisation de films de se'quences d'instantane's
restant possible en temps diffe're'.
.thy@BIG
.thy@DUMP tsum-ray-one "Visualisation par ray-tracer d\*[thy@quote]espaces de la re`gle \fBqmean\fP"
.thy@BIG
.thy@DUMP tsum-ray-all "Visualisation par films de vues ray-trace'es"
.\"thy@PCS
La fonction d'extraction d'isosurface fournie par
\fCvart\fP\v'-.4m'\s-3[\*[soft-ref-vart]]\s0\v'.4m'
a e'te' utilise'e sur le volume constitue' par l'empilement
de 128 espaces (128 ge'ne'rations) de $128 times 128$ cellules.
La valeur de seuil varie de 0.3 a 0.8.
L'espace initial est issu de la ge'ne'ration 8192 de la re`gle
\fBanneal\fP elle me^me applique'e sur un espace de taille $1024 times 1024$
et de densite' ale'atoire \(12, re'duit a` $128 times 128$.
.\"thy@PCE
.\"
.\" OBJECTS/SPACE/RESSOURCE
.\"
.thy@H 3 "Ressources"
La consommation me'moire d'un espace
d'arre^te $a$
et de dimension $d$ est $pow(a, d)$.
Pour des raisons de'taille'es
lors de la pre'sentation de la fonction de transition\*F,
.FS
.thy@GET-REF mem-struct 1
.FE
l'organisation me'moire de l'espace
privile'gie le plan de vecteurs de bits,
d'une taille multiple de l'unite' adressable,
c'est a` dire que les cellules seront constitue'es au minimum d'un byte.
.thy@TBL space-size "Taille d\*[thy@quote]espaces"
.so tbl/space-size.tbl
.thy@TBL-END
La table \*[tbl-space-size]
donne un aperc,u des tailles d'espaces maximum accessibles
pour les 4 premie`res dimensions d'espace.
On peut voir que si les espaces de dimension 2
ne posent pas de proble`mes,
les espaces de dimension 3
seront avantageusement ramene's a` des parties de cube.
Par exemple les 256K d'un espace $128 times 64 times 32$,
sont probablement plus avantageux
que les 256K d'un espace $64 times 64 times 64$.
La consommation CPU de la fonction de transition,
croissant line'airement en fonction de la taille de l'espace,
on peut e'galement avoir une ide'e
des temps de calculs associe's a` la taille des espaces.
Celui-ci est ${roman {G} a sup {d}} over roman {D}$,
avec $roman G$ pour le nombre de ge'ne'rations,
$d$ pour la dimension de l'espace
et $roman D$ pour le de'bit de la fonction d'application.
.thy@TBL compute-time-100kcps "Temps de calcul de 1000 ge'ne'rations a` 100 KCPS"
.so tbl/compute-time-100kcps.tbl
.thy@TBL-END
La table \*[tbl-compute-time-100kcps] montre les temps
associe's au calcul de 1K \*F ge'ne'rations
.FS
Les de'bits sont en puissance de 10,
1 kilo cell = 1024 cell,
1 kilo ge'ne'ration = 1000 ge'ne'rations.
.FE
d'espaces de la table \*[tbl-space-size]
avec une fonction d'application a`
100 KCPS \*F,
.FS
Kilo Cell update per Second.
.FE
(consommant 100 instructions par cellule
sur une machine 10 MIPS, par exemple).
Seule l'unite' de temps la plus significative est indique'e.
On pourrait obtenir un de'bit de 10 MCPS
avec une fonction d'application consommant 20 instructions par cellule,
et quatre processeurs a` 50 MIPS,
lesquels ne partagent qu'une faible partie de la me'moire totale.
.thy@TBL compute-time-10mcps "Temps de calcul de 1000 ge'ne'rations a` 10 MCPS"
.so tbl/compute-time-10mcps.tbl
.thy@TBL-END
La table \*[tbl-compute-time-10mcps]
reprend les calculs de la table \*[tbl-compute-time-10mcps]
pour $roman {G} = 10 ~ roman {MCPS}$.
