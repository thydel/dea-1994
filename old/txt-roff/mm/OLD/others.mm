.\"
.\" COW-PROJECT
.\"
.thy@H 1 "Le projet CAW"
.\"
.\" COW-PROJECT/OBJECTIF
.\"
.thy@H 2 "Les objectifs"
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
.thy@H 2 "Environnement et contraintes"
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
.thy@H 3 "Spe'cification"
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
.thy@H 3 "Interaction"
L'interaction se fait soit par l'interme'diaire d'un shell Tcl,
soit par une interface X11 base' su Tk.
.thy@H 3 "Visualisation"
La visualisation se fait par l'interme'diaire de fene`tres X11
presentant des se'quences d'espaces monochrome (plan de bits de l'espace cellaires) 
out couleurs (tranches de bits de l'espace cellaires).
Les variables macroscopique (e'le'ments statistiques) sont visualise's
par l'interme'diares d'objets X11 spe'cialise' (plotters).
.\"
.\" COW-PROJECT/VALIDATION
.\"
.thy@H 2 "Validation"
.\"
.\" WORKBENCH
.\"
.thy@H 1 "Le workbench"
.\"
.\" ARCHITECTURE
.\"
.thy@H 1 "Architecture du syste`me"
.thy@H 2 "les objets et fonctions de bas niveau"
.thy@H 3 "les vecteurs, les frames et les planes"
.thy@H 3 "les applicateurs de fonctions"
.thy@H 2 "les objets de haut niveau"
.thy@H 3 "les sequenceurs"
.thy@H 4 "le sequenceur Simple"
.thy@H 3 "la structure Space"
.thy@H 4 "la me'moire de calcul"
.thy@H 5 "la grille de cellules"
.thy@H 5 "la cellule"
.thy@H 4 "la me'moire de visualisation"
.thy@H 4 "les statistiques"
.thy@H 5 "l'histograme"
.thy@H 5 "l'empilage"
.thy@H 3 "la structure Time"
.thy@H 4 "le vecteur de Space"
.thy@H 4 "les Space spe'ciaux"
.thy@H 5 "acus"
.thy@H 5 "past"
.thy@H 4 "les statistiques"
.thy@H 3 "la structure Func"
.thy@H 4 "la structure d'interconnexion (ConexSpec)"
est une liste de connexion en entre'e (les arguments de la fonction de
transition), et une liste de connexion en sortie (les valeurs
retourne' par la fonction de transition) associe' a une fonction
d'application d'une fonction de transition sur un espace de cellules.
elle a pour but de permettre la transformation et la combinaison de
plusieurs structure Func.
.thy@H 5 "la liste de connexion"
est une liste de variable de connexion associe' a une liste de valeur
de connexion.
.thy@H 6 "une variable de connexion"
indique le type de la connexion et sa taille
- un type de connexion
associe un identificateur et un multiplicateur a une variable de connexion
.thy@H 6 "une valeur de connexion"
indique la position et la valeur effective de chacun des arguments de la
fonction de transition
.thy@H 6 "examples (en Tcl)"
le voisinage de Moore:
.br
.EQ
delim off
.EN
.B1
.VERBON
set moore [ConexType moore [set a 9]]
set local [ConexType local [set b 1]]
set moore_1 [ConexSpec [ConexList [ConexVar $moore [set c 1]]]
[ConexList [ConexVar $local [set d 1]]]
.VERBOFF
.B2
.br
.EQ
delim $$
.EN
necessite une table de taille
$2 sup {roman {c} times roman {a}}$ e'tats de $2 sup {roman {d} times roman {b}}$ bits.
le voisinage de Moore a quatres e'tats pas cellule
.EQ
delim off
.EN
.B1
.VERBON
set moore_2 [ConexSpec [ConexList [ConexVar $moore [set c 2]]]
[ConexList [ConexVar $local [set d 2]]]
.VERBOFF
.br
.B2
.EQ
delim $$
.EN
necessite une table de taille $2 sup 18$ e'tats de 2 bits.
deux plans Moore + centre:
.br
.EQ
delim off
.EN
.B1
.VERBON
ConexSpec [ConexList [ConexVar $moore 1 0] [ConexVar $local 1 1]
[ConexVar $moore 1 1] [ConexVar $local 1 0]]
[ConexList [ConexVar $local 1] [ConexVar $local 1]]
.B2
.VERBOFF
.br
.EQ
delim $$
.EN
necessite une table de taile $2 sup 10$ e'tats de 2 bits.
.thy@H 4 "la fonction locale et ses parame`tres"
.thy@H 4 "la table de transition"
.thy@H 4 "les statistiques"
.thy@H 3 "les dumpers"
.thy@H 4 "dumper monochrome"
.thy@H 4 "dumper couleur"
.thy@H 3 "les plotters"
.thy@H 2 "les outils"
.\"
.\" EXAMPLES
.\"
.thy@H 1 "Exemples"
.thy@H 2 "Objets simple"
.thy@H 2 "Objets construit"
.thy@H 2 "Objets utile"
.\"
.\" PROSPECTIVE
.\"
.thy@H 1 "Prospective"
.\"
.\" CONCLUSION
.\"
.thy@H 1 "Conclusion"
