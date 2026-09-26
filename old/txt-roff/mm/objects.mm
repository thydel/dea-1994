.thy@H 1 "Vers des objets cellulaires: espace, temps, lois"
Nous pensons qu'un environnement de de'veloppement d'AC doit reposer
sur un ensemble d'objets permettant la construction d'expe'riences.
Ces objets doivent correspondre aux ressources utilisables par une
simulation et fournir les ope'rations
et les fonctions de re'duction d'information
utilise'es lors de la description de l'expe'rience projete'e.
.P
Les objets de base d'une simulation sont l'\fIespace\fR,
le \fItemps\fR et la \fIfonction de transition\fR.
La fonction de transition se compose
d'une structure d'interconnexion cellulaire associable a` un espace,
d'une fonction de transition locale\*F
.FS
L'expression \fIfonction de transition\fR de'signe, suivant le contexte,
soit l'objet regroupant le re'seau d'interconnexion et la fonction de
transition locale, soit la fonction de transition locale elle me^me.
La fonction de transition locale sera par ailleurs e'galement nomme'e
\fIre`gle\fR ou \fItable de transition\fR,
et l'objet fonction de
transition sera a` l'occasion nomme' loi, ou AC.
.FE
applicable de manie`re synchrone sur l'ensemble des cellules
d'un espace dote' d'un re'seau d'interconnexion,
et d'une fonction d'application utilisant
les composants de la fonction de transition
pour ge'ne'rer le nouvel e'tat d'un l'espace.
La fonction de transition re'alise
les lois de la dynamique de l'univers cellulaire simule'.
Elle est ge'ne'ratrice du temps par application sur l'espace.
.P
Des instances d'objets de base sont regroupe'es pour la re'alisation
d'une simulation au sein d'un objet de type se'quenceur.
Des manipulateurs et des observateurs
peuvent e^tre associe's aux objets de la simulation.
.\"
.\" OBJECTS/SPACE
.\"
.so mm/obj-space.mm
.\"
.\" OBJECTS/TIME
.\"
.so mm/obj-time.mm
.\"
.\" OBJECTS/LOIS
.\"
.bp
.so mm/obj-law.mm
\"
.\" OBJECTS/SEQUENCER
.\"
.thy@H 2 "Les se'quenceurs"
Exemple de fonctions de se'quencement
.BL
.LI
Certain AC pre'sentent une e'volution croissante tendant vers un point
fixe ou un cycle limite court, passant par une phase de croissance
tre`s rapide, suivi d'une phase de croissance tre`s lente d'une
variable macroscopique e'le'mentaire comme la population d'un plan de
bit.
.P
Le couplage de la variation de cette variable a` la commande
d'enregistrement du point de temps courant permet de re'aliser des
films a` e'chantillonnage variable et a` variation de densite' spatiale
constante.
.LE
