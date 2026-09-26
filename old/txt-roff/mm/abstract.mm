.nr thy@do-head 0
.EH "'''"
.OH "'''"
.EF "'''"
.OF "'''"
.\"thy@HU "Re'sume'"
.bp
.sp 4
.DS CB
\s12\fBRe\*'sume\*'\fP\s0
.DE
\s-2
.vs -2
.P
Nous avons re'alise' CAW (Cellular Automata Workbench),
un nouvel environnement de de'veloppement et de visualisation d'automates cellulaires.
.P
Nous destinons cet environnement tant a` l'exploration
de la dynamique des automates cellulaires (AC),
qu'a` la construction et a` l'e'valuation d'architectures
et d'algorithmes SIMD.
De plus nous proposons de conside'rer la re'alisation
d'algorithmes SIMD sur machines SISD non pas comme
un palliatif a` l'absence de machines SIMD,
mais comme un mode d'utilisation particulier
des ressources disponibles sur les machines SISD modernes
(50 Mips, 32 Me'gas).
.P
La programmation des calculateurs massivement paralle`les
re'els et virtuels
pose le double proble`me
du pouvoir d'expression et de l'efficacite' d'un langage
au regard d'une architecture.
Ce proble`me se pose e'galement pour les architecture SISD,
mais l'on peut conside'rer qu'il concerne de'sormais
l'ade'quation des langages aux applications pluto^t qu'aux architectures.
Optant pour une approche re'solument bottom-up
de la recherche des primitives,
nous proposons d'utiliser les AC comme composants e'le'mentaires
d'une combinatoire visant a` la construction d'objets cellulaires/SIMD
arbitrairement complexes.
Ces objets se divisent en deux classes e'piste'mologiques.
Nous les nommerons objets analytiques et objets synthe'tiques.
Les objets analytiques sont typiquement issus de l'application ite'rative
d'une fonction simple sur un espace cellulaire initial ale'atoire.
Ils recoupent intuitivement le champs d'e'tude traditionnel des AC.
Les objets synthe'tiques sont issus de la se'lection d'une fonction
localement universelle,
et de son application contro^le'e (globalement parame'tre'e)
sur un espace initial soigneusement configure'.
Ils correspondent aux architectures des machines SIMD.
De l'e'tude des objets analytiques
nous espe'rons tirer des enseignements permettant a` terme
de conside'rer les morphoge'ne`ses comme des e'le'ments de programmations.
De la construction d'un outillage SIMD
nous attendons les moyens de contro^le ne'cessaire a` l'e'tude des objets analytiques.
Cet objectif, certes ambitieux,
repose pre'cise'ment sur la re'alisation par \fIlookup tables\fR
des fonctions de bas niveau manipulables et combinables au sein de CAW.
.P
No^tre e'tude est organise' autour de la pre'sentation
des structures de donne'es choisi pour CAW;
ces structures de donne'es repre'sentent
l'espace le temps et les lois:
objets e'le'mentaire du Workbench.
Nous proposons des exemples d'ope'rations applicables sur ces objets.
Nous proposons e'galement de conside'rer la re'alisation
de fonctions par lookup tables
comme une structure de donne'e fondamentale,
tant pour des raisons d'efficacite' que de ge'ne'ralite'.
.P
Nous conside'rons la visualisation comme un service primordial,
qui propose l'usage du Workbench comme un laboratoire
de manipulation d'espace cellulaire
(l'espace, mais aussi les fonctions et les dynamiques).
Nous pre'sentons plusieurs exemples de visualisations
principalement associe'es a` des objets analytiques.
Nous montrons comment peut s'effectuer le passage d'une
me'thode naturaliste a` une me'thode artefactuelle
en proposant une re'alisation par lookup table d'une architecture
SIMD spe'cifique,
et une me'thode de transformation d'une lookup table quelconque
en se'quence de contro^le pour cette machine.
.P
L'e'tat actuel du de'veloppement de CAW
n'as pas encore permis l'expe'rimentation
de construction complexes d'objets mixtes.
La mesures de variables d'e'tats macroscopiques,
par exemples,
utilise actuellement des outils externes,
au lieu d'algorithmes SIMD adapte's a` la nature discre`te et fini
des espaces cellulaires.
.vs +2
\s+2
