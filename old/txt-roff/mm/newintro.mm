.pn 1
.nr thy@head-flag 1
.nr thy@foot-flag 1
.nr H1 0
.EH "'\\\\nP''Chapitre \\\\n(H1.  \\\\*[thy@chapter-name-1]'"
.OH "'\\\\n(H1.\\\\n(H2.  \\\\*[thy@chapter-name-2]''\\\\nP'"
.EF "'\\\\nP'\*[thy@title]''"
.OF "''\*[thy@title]'\\\\nP'"
.thy@H 1 "Introduction"
.\"
.\" INTRO/CA
.\"
.\" thy@H 2 "Les automates cellulaires"
.\"
.\" INTRO/CA/DEFINITION
.\"
.\" thy@H 3 "De'finition"
Les automates cellulaires (AC) sont des syste`mes dynamiques virtuels,
discrets en espace,
en temps et en e'tats,
homoge`nes, synchrones et de'terministes.
.P
L'espace est constitue' de cellules identiques
dote'es d'un re'seau d'interconnexion re'gulier
(une grille de dimension 2 ou 3 par exemple).
.P
Une cellule est une variable discre`te
(une cha\(^ine de bits dont la taille
de'termine le nombre d'e'tats de la cellule).
.P
Le temps est une se'quence d'espaces
ge'ne're'e par l'application synchrone
d'une fonction de transition de'terministe.
.P
La fonction de transition est locale dans le temps et dans l'espace,
son argument est un ensemble fini d'e'tats de cellules
voisines du re'seau d'interconnexion,
pour un nombre fini de points d'espaces ante'rieurs.
.\"
.\" INTRO/AC/APPLICATION
.\"
.\" thy@H 3 "Domaines d'application"
.P
Quelques domaines d'application:
.br
.BL
.LI
Mathe'matiques
.P
Les AC constituent un champ d'e'tudes des mathe'matiques discre`tes
et un mode`le important en the'orie du calcul,
en particulier pour les proble`mes lie's au paralle'lisme\*F.
.FS
Les AC lorsqu'ils sont e'tudie's par les mathe'maticiens
posse`dent a` priori un espace infini.
Notre point de vue est quant a` lui empirique et pratique:
nous visons a` la re'alisation de programmes efficaces.
Dans un contexte de ressource me'moire limite'e,
les AC sont toujours dote's d'un espace fini.
Ne'anmoins l'espace est par de'faut torique.
.FE
.LI
Architectures des machines
.P
La structure des AC est en fait tre`s proche
de l'architecture des machines SIMD\*F,
.[
Greussay ordinateur cellulaire
.]
et nous pensons que le progre`s des connaissances et
des outils dans ces deux domaines sont intimement lie's.
.FS
La puissance de calcul et la taille de la me'moire disponible
sur des machines aujourd'hui largement accessibles
permet d'envisager la re'alisation de multiples expe'riences
dans le domaine du paralle'lisme synchrone massif,
sans attendre l'arrive'e de machines SIMD.
Les AC fournissent un outil conceptuel en mesure de jouer
un ro^le central dans la recherche d'objets naturels
(comportement e'mergent) ou artificiels (comportement construit),
pouvant servir de bases a` la de'finition d'outils pratiques
d'exploitation des ressources du paralle'lisme synchrone massif.
.FE
.LI
Programmation paralle`le
.P
Inde'pendemment de l'architecture des machines de nombreux algorithmes
se pre^tent a` une formulation cellulaire,
.[
parallelism Arrays
.]
.[
parallelism Artificial
.]
en particulier les algorithmes
de traitement d'images.
.[
Preston
.]
.LI
Simulation de syste`mes naturels
.P
Les AC peuvent e^tre vus comme une version discre`te de syste`mes
d'e'quations diffe'rentielles\*F,
et a` ce titre permettent la mode'lisation de nombreux syste`mes naturels.
.FS
La mode'lisation d'un syste`me naturel par un ensemble d'e'quations
diffe'rentielles e'tablit des relations diffe'rentielles entre les
variables macroscopiques du syste`me (des populations par exemple).
La mode'lisation par AC e'tabli des relations entre les composants
discrets e'le'mentaires (les cellules) du syste`me.
Les variables macroscopiques deviennent des proprie'te's e'mergentes du
syste`me dont le choix peut e^tre fait a posteriori,
mais le mode`le doit impe'rativement reposer sur une description en
terme de comportement collectif du phe'nome`ne e'tudie'.
.P
La description d'un syste`me naturel en terme de
comportement collectif n'implique pas l'identification d'une cellule
a` un individu.
Par exemple,
dans une simulation de dynamique des populations,
une cellule peut e^tre identifie'e a` une densite' de
population en un point d'espace.
Ne'anmoins la validite' de la
mode'lisation (conformite' de la dynamique des populations d'un AC a` un
syste`me d'e'quations diffe'rentielles standards de re'fe'rence par
exemple) de'pends toujours de la pre'sence d'un nombre minimum de
cellules dans la simulation.
.FE
.LE
.\"
.\" INTRO/CAW
.\"
.\" thy@H 2 "Le Cellular Automata Workbench"
.\"
.\" COW-PROJECT
.\"
.\"thy@H 1 "Le projet CAW"
.\"
.\" COW-PROJECT/OBJECTIF
.\"
.thy@WARNING
.thy@H 2 "Objectifs et contraintes"
Nous cherchons a` de'finir et a` re'aliser un environnement de
de'veloppement et de d'observation de ces syste`mes.
.P
Une des motivation principale de ce travail re'side dans le de'sir de
voir (et montrer) les se'quences anime'es ge'ne're'es par un AC.  En
effet s'il est aise' de trouver des ouvrages sur les AC, contenant des
photos d'AC, il est plus difficile de voir des ``films'' d'AC, bien
qu'il existe quelques outils de spe'cification d'AC et d'observation
de leur dynamique, aucun de ceux dont nous connaissons l'existence ne
reponds pleinement aux contraintes que nous definissons plus loin.
.P
Nous souhaitons e'galement que cet outil permmettent ulte'rieurement
la recherche et la cre'ation de nouveaux AC, puis la constitution d'un
catalogue d'AC connus.  Enfin nous espe'rons qu'il serve a
l'identification d'AC pouvant servir de primitives dans un futur
language base' sur la combinaison d'AC.
.P
Les qualite's privile'gie's sont la rapidite', l'extensibilite',
la facilite' de spe'cification et d'interaction.
.\"
.\" COW-PROJECT/ENVIRONNEMENT-CONTRAINTES
.\"
.\"thy@H 2 "Environnement et contraintes"
.P
L'environnement de de'velloppemment est unix et X11,
l'architecture cible est une machine standard de 10 a` 100 mips et 8
a` 64 Mega octets de me'moire utile.
Pour un AC 2d compose' de 256x256 cellules de 2 bits avec un
voisinage de Moore, le syste`me doit e^tre capable de calculer une
dizaine d'e'tats par seconde (10 hz).  Le cout lie' a` la
visualisation est plus difficile a` e'valuer, mais la chaine de
traitement comple`te (production, extraction, visualisation) doit
permettre l'observation d'un film a` une fre'quence supe'rieure a` 1 hz.
.P
CAS fournit un noyau d'objets permmettant la construction d'experience,
sous la forme d'une librairie C, interface' a Tcl.
.\"thy@H 3 "Spe'cification"
.P
La spe'cification concerne les re'seux d'interconnexion,
les fonctions de transitions, et le se'quencement des ope'ration
applicable sur l'espace.
.P
Les fonctions de transitions sont ecrites en C, et sont dote' d'une
convention d'interface pre'vue pour permettre une inde'pendance des
parame`tres a leur localisation dans la me'moire d'etats d'une cellule
et la re'utilisation dans des fonctions de plus haut niveau.
.P
Les re'seaux d'interconnexion sont de'finit et cre'e' en Tcl
a` partir des primitive de la librairie.
Les espaces sont cre'e' en Tcl.
Le se'quencement est de'fini par un programme Tcl.
.\"thy@H 3 "Interaction"
.P
L'interaction se fait soit par l'interme'diaire d'un shell Tcl,
soit par une interface X11 base' su Tk.
.\"thy@H 3 "Visualisation"
.P
La visualisation se fait par l'interme'diaire de fene`tres X11
presentant des se'quences d'espaces monochrome (plan de bits de l'espace cellaires) 
out couleurs (tranches de bits de l'espace cellaires).
Les variables macroscopique (e'le'ments statistiques) sont visualise's
par l'interme'diares d'objets X11 spe'cialise' (plotters).
.\"
.\" INTRO/NEW STUFF
.\"
.thy@H 2 "Les outils existant"
Les outils de de'veloppement et de visualisation d'automates cellulaires
sont peu nombreux\*F.
.FS
Bien que le nombre de re'alisation de \fIlife\fP soit sans doute innombrable,
et les packages cellulaires plus ou moins ge'ne'raux tre`s nombreux,
leurs re'alisation minimale posant peu de proble`me,
nous ne prennons en compte que les packages ???.
.FE
Le plus connus d'entre eux est sans doute \fCCellsim\fP\*[Rf].
.RS
cellsim - CA Simulator
.br
Cellsim copyright 1989, 1990 by Chris Langton and Dave Hiebeler
(cgl@lanl.gov, hiebeler@heretic.lanl.gov)
.br
Version 2.5 of Cellsim is a SunView-based cellular automata simulator
allowing interactive specification, editing, running, and analysis of
1- and 2-D CA's.  It will run on Sun-3's, -4's, and Sparc stations,
color or B&W.
.RF
\fCScamper\fP\*[Rf]
.RS
Scamper - a simulator of Cellular automata.
Copyright 1991 by Ian Palmer of Imperial College of Science, Technology
and Medicine, University of London.
.RF
et \fCCA LAB\fP\*[Rf]
.RS
Rudy Rucker.
.RF
sont e'galement des outils disponibles depuis
plusieurs anne'es.
Il existe aussi des outils spe'cialise'
autour d'un mode`le d'automate cellulaire.
\fCxlife\fP\*[Rf]
.RS
Xlife - Conway's Game of Life for X, version 3.0
.br
XLife Copyright 1989 Jon Bennett jb7m+@andrew.cmu.edu, jcrb@cs.cmu.edu
.RF
fournit une re'alisation d'execution tre`s rapide du jeux de la vie de Conway,
.[
Berlekamp Winning Ways
.]
\fCHODGE-C\fP\*[Rf]
.RS
HODGE-C -- A C implementation of Gerhard & Schuster's hodge-podge machine
Copyright (C) 1993 Joerg Heitkoetter
.RF
une re'alisation de la machine hodge-podge de Gerhard & Schuster,
.[
Dewdney Hodgepodge
.]
une classe d'AC inspire' par les reactions chimiques
autocatalytique, telle la re'action de Belousov-Zhabotinskii.
Enfin, \fCCellang\fP\*[Rf],
.RS
Copyright (C) 1992  J Dana Eckart
.br
cellc - Cellang 2.0 (cellular automata) compiler
.br
cellview - cellular automata viewer
.br
pe-scam - Cellang 2.0 (cellular automata) machine driver
.RF
d'inspiration plus architecturale,
propose un langage de description d'AC.
.[
Eckart Cellular Automata Simulation system
.]
.[
Eckart Language Reference manual
.]
.thy@H 2 "Pourquoi un nouvel environnement?"
Tout d'abord, me^me si l'histoire de l'e'tude des AC
est presque aussi ancienne que l'histoire des ordinateurs,
les architectures cellulaires construitent,
bien que souvent de'signe' comme prometteuses,
restent marginale\*F,
.FS
Il est difficile de savoir si ce fait est a mettre au cre'dit
des architectures cellulaires,
nous nous bornerons a proposer l'ide'e
que le potentiel d'usage d'une architecture
est inversement proportionnel a` son succe`s (sa re'alisation).
.FE
et le proble`me des me'thodes
de constructions d'architectures et d'algorithmes cellulaires
restent largement ouvert.
De me^me,
au travers du proble`me de l'auto-reproduction,
.[
Von Neumann
.]
la dualite' opposant analytique a` synthe'tique accompagne la naissance des AC\*F.
.FS
Voir
.[
Reggia
.]
pour une approche permmettant d'accorder plus d'autonomie
aux phe'nome`mes d'auto-reproduction.
Nous consid'erons, dans ce contexte, l'autonomie comme la mesure
d'une position sur l'axe qui va du construit a` l'e'mergeant.
.FE
Cette dualite', ou plutot la capacite' offerte par les AC
de basculer d'un univers episte'mologique a` un autre tout
en restant au sein d'un mode`le unique,
doit e^tre incarne' dans l'environnement.
Nous souhaitons donc un environnement permettant
une approche mixte.
.P
Par ailleur, aucuns des outils que nous avons cite's
ne reponds totalement a un ensembles de contraintes
plus pratique que nous avons fixe's comme cadre de devellopement.
.BL
.LI
la nature publique\*F des outils
.FS
Par \fIpublique\fP nous entendons accessible sous forme source
et utilisable sans license commerciale.
Nous ne justifions pas ici les raisons de ce choix.
.FE
.LI
la rapidite' d'execution
.LI
la richess de visualisation
.LI
la souplesse de spe'cification
.LI
un environnement d'exploitation Unix et X11
.LI
la modularite' des constituants en vue de la construction et du se'quencement
d'expe'riences cellulaires.
.LE
\fCCA LAB\fP n'est pas un outil public et n'est pas disponible dans l'environnement Unix.
\fCCellsim\fP de part sa de'pendence a SunView ne \fItourne\fP
que dans un environnement Sun\*F.
.FS
Georges Faw a re'alise' un portage de \fCCellsim\fP pour l'environnement XView.
.FE
\fCScamper\fP pre'sente une application inte'grant un formalisme de spe'cification
des re`gles base' par pattern, des compteurs de populations et une interface visuel
base' sur X11, mais il ne permet ni execution rapide, ni se'quencement.
\fCCellang\fP propose un langage de description de CA,
mais son compilateur 
.thy@WARNING
.thy@H 2 "Des AC comme outils d'optimisation d'usage de ressources"
Concernant le paralle'lisme massif
Les tendances de la decennies 90 en architectures des machines
ne confirment pas les pre'dictions
avance'es au cours de la decenies pre'cedente\*F
.FS
Machines SIMD massives reposant sur des technique de fabrication
de type wafer scale integration, assossie' a des algorithmes de
reconfiguration de re'seaux d'interconnexion permmettant la resistances
aux defaults;
pyramides de telles architectures pour la vision et plus ge'neralement l'IA,
ou architectures diverse pour la physique, la biologie moleculaire,
le pattern matching haut de'bit, la re'alisation de film holographiqe temps re'el.
.FE
Ne'anmoins, hors conside'ration architecturale,
les ressources accessibles continue a croite a un rythme soutenue\*F.
.FS
Au point que certain semble mettre en doute l'application du principe
des gaz parfaits applique' a la consommation de ressources.
contre cette tendance,
nous proposons de conside'rer qu'il n'est plus temps d'apprendre
comment se contenter de ressources restreintre,
mais comment tirer profit de ressources disponible.
.FE
Hormis le calculs intensif \fIclassique\fP, les gains de ressources semblent
s'orienter vers le paralle'lisme MIMD massif pour la gestion et
le support multime'dia pour le poste de travail.
Nous affirmons que les AC constituent un mode`le efficace et universel
pour l'utilisation de ces ressources, y compris par la prise en compte
du paralle'lisme \fImulti-computer\fP associe' a l'interconexion large.
La re'gularite' structurelle des donne' et des traitement des AC
associe' a l'absence de proble`mes algorithmique de synchronisation inter ele'mentaires,
permet un calcul et une affectation de ressource simple.
Une approche bottom-up de la specification du comportement des e'le'ments cellulaires
permet, de plus, de s'affranchir des proble`mes d'architectures CPU,
une fonction, conside're' sous l'angle de sa table de transition est
inde'pendante des architecture de traitement\*F.
.FS
A une permutation de l'ordre des bit sur le mot pre`t,
et toujours en consid'erant que l'unite' de traitement re'ellement
disponible reste fondamantelement une architecture de Von Neumann
dote' d'une me'moire addressable importante.
.FE
Au niveau du paralle'lisme SIMD 
.thy@WARNING
.thy@H 2 "Des AC comme outils de re'fexion sur la forme"
L'essence de la forme est necessairement multiple,
ne serait ce que par l'existence de la ge'ne'ricite' du moule.
tout e'tat du monde est forme.
Une forme e'tant, par de'finition, un configuration d'espace cellulaire
prise parmi un ensemble finit de configurations,
tout espace cellulaire est forme.
cette de'finition paradoxale\*F,
.FS
de'finissant e'galement l'informe.
.FE
re'clame un crite`re de discrimination/re'duction
de de l'ensemble des e'tats.
une premie`re possibilite' re'side dans l'utilisation d'une fonction arbitraire
sur un e'tat determinant la valeur d'un attribut formel:
esthe'tique, ge'ome'trique, statistique, arithme'tique.
les formes sont figurative, abstraite, belles, rondes, carre, syme'trique,
rares, uniques\*F,
.FS
chaque configuration d'espace est evidemment unique,
on pourrais ne'anmoins mesurer, intuitivement ou formellement,
l'unicite' comme le cardinal de l'intersection des images de l'ensemble
des e'tats par l'ensemble des fonction de qualification formelles disponible.
.FE
re'gulie`re, fractale, dense, colore', leur nume'ro d'orde
enfin, peut e^tre argument d'une fonction totalement arbitraire.
Cette me'thode pose, le probl`eme de l'e'nume'ration
des fonctions de re'duction\*F, ainsi que celui du choix
a prioris des e'tats conside're'.
.FS
Les fonctions de qualifications sont implicitement destine'
a introduire une re'duction du nombres des formes par l'introduction
de classes d'e'quivalence sur l'ensemble des e'tats.
.FE
Une deuxime`me me'thode,
consiste a opposer la ge'ne'ticite' a la ge'ne'ricite',
c'est a dire l'histoire de la forme au moule de la forme.
Dans ce contexte la re'duction du nombre d'espaces appele's
a la forme, est de'termine' par l'existence d'une trajectoire
dans l'espace des e'tats.
Cette trajectoire e'tant elle me^me de'termine' par l'application
ite're' d'une fonction de l'ensemble des e'tats vers l'ensembles des e'tats.
Les trajectoires ne sont pas moins nombreuses que les e'tats,
mais si l'on ajoute une contrainte de localite' aux fonctions ge'neratrices
de trajectoires, une tentative d'enume'ration devient accessible.
Cette contrainte de localite' constitue le fondement d'une approche
cellulaire de la forme.
elle introduit un lien entre la vitesse et la forme.
Plus ge'ne'ralement, la notion de contrainte s'applique aise'ment
au monde des forme dans une perspective esthetique,
le libre choix des contrainte de production de l'objet,
determinant la qualite' artistique de l'oeuvre,
dont la forme peut e^tre concu comme une trace d'execution\*F.
.FS
la perception de l'oeuvre n'est jamais exempte de la perception
de l'histoitre de sa fabrication.
.FE
De me^me la \fIforme\fP d'un espace cellulaire\*F
.FS
un espace conside're' comme une forme.
.FE
devient la trace d'un programme.
.thy@WARNING
