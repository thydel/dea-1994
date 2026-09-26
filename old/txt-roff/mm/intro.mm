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
en particulier pour les proble`mes lie's au paralle'lisme.
.LI
Architectures des machines
.P
La structure des AC est en fait tre`s proche
de l'architecture des machines SIMD,
.[
Greussay ordinateur cellulaire
.]
et nous pensons que le progre`s des connaissances et
des outils dans ces deux domaines sont intimement lie's.
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
d'e'quations diffe'rentielles,
et a` ce titre permettent la mode'lisation de nombreux syste`mes naturels.
.LE
.P
Les AC lorsqu'ils sont e'tudie's par les mathe'maticiens
posse`dent a` priori un espace infini.
Notre point de vue est quant a` lui empirique et pratique\*F.
.FS
Nous visons a` la re'alisation de programmes efficaces.
.FE
Dans un contexte de ressource me'moire limite'e,
les AC sont toujours dote's d'un espace fini.
Ne'anmoins l'espace est par de'faut torique.
.P
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
.P
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
.\"
.\" INTRO/CAW
.\"
.\" thy@H 2 "Le Cellular Automata Workbench"
