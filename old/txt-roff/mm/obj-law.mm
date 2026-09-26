.thy@H 2 "Les lois"
La fonction de transition est le gros morceau du proble`me.
Les objets pre'sente's pre'ce'demment ne sont pas particulie`rement
spe'cifiques d'un environnement de de'veloppement d'AC.
Ils pourraient convenir a` un environnement de production et de
traitement d'images anime'es quelconques.
Il constituent des extensions plus ou moins e'videntes d'outils
existant\*F,
.FS
Initialement nous pensions me^me pouvoir utiliser un des outils
existant dans le domaine de l'animation interactive d'images,
auquel des fonctions spe'cifiques d'application de fonctions de
transitions auraient pu e^tre ajoute'es.
.FE
ou sont base's sur des impe'ratifs d'architectures et de gestion de
ressources a` peu pre`s ine'vitables.
.P
La fonction de transition concentre les proble`mes de gestion de
ressources en me'moire et en CPU,
et le proble`me du pouvoir expressif
de la spe'cification du re'seau d'interconnexion cellulaire
et de la table de transition.
.\"
.\" OBJECTS/LOIS/STRUCTURE
.\"
.thy@H 3 "Structure"
La fonction de transition est la structure de contro^le de l'AC.
Une fonction de transition locale rec,oit en argument un fragment
d'espace\*F
.FS
Encore appele' voisinage.
.FE
(un ensemble de cellules ordonne'es).
Il existe un tel fragment pour chaque cellule de l'espace.
La fonction retourne le nouvel e'tat
de la cellule associe'e a` ce fragment (la cellule cible).
En ge'ne'ral,
la cellule cible est un des e'le'ments du fragment.
Si le fragment n'est pas re'duit a` la cellule cible,
les fragments ne sont pas disjoints
et l'information peut circuler de cellule en cellule.
.P
Sur une machine se'quentielle,
un espace temporaire stocke le nouvel e'tat des cellules cibles
et l'espace temporaire devient le nouvel e'tat d'espace
apre`s l'application de la fonction de transition
locale a` chaque cellule de l'espace courant\*F.
.FS
Avec la contribution du se'quenceur.
.FE
Ce me'canisme de simulation
d'une architecture SIMD dote'e d'un re'seau d'interconnexion homoge`ne
ne pre'sente pas de difficulte' algorithmique
mais l'efficacite' et la souplesse du syste`me
de'pendent de l'architecture choisie pour sa re'alisation.
.P
Il faut une me'thode de balayage et de collecte
des fragments d'espace pour chaque cellule cible,
d'association\*F
.FS
Encore appele' binding.
.FE
des parame`tres formels de la fonction de transition
aux cellules du fragment
et d'invocation de la fonction.
La fonction qui rec,oit en argument un ensemble d'espaces,
un re'seau d'interconnexion et une fonction de transition,
est la fonction d'application.
.P
Le choix du me'canisme d'invocation
conditionne la me'thode de binding.
La me'thode la plus rapide d'invocation de fonction
est l'acce`s par table.
On construit une table des valeurs de la fonction
pour l'ensemble des valeurs possibles de ses arguments
et chaque e'le'ment de l'ensemble des valeurs est conside're' comme un
indice d'acce`s a` la table.
Le binding des valeurs d'appel de la fonction se rame`ne a` la
concate'nation des valeurs des cellules du fragment d'espace
et le calcul du nouvel e'tat de la cellule cible,
a` un acce`s me'moire
indirect.
.P
Les avantages sont e'vidents.
Les fonctions de transitions peuvent e^tre re'alise'es dans
n'importe quel langage,
sans souci de performance.
La mise a` jour d'une cellule est re'ductible a` un nombre minimum
d'instructions.
Les inconve'nients sont e'galement e'vidents.
Les fonctions re'alisables sont limite'es par la taille
des tables (en nombre d'entre'es)
qui est une fonction exponentielle de la taille des arguments
(produit du nombre de bits $k = log2(K)$ codant le nombre $K$ d'e'tats
par cellules et du nombre $r$ de cellules du fragment d'espace).
La taille $T$ des tables exprime'e en bytes de'pend de $k$ exprime' en byte
$T = byte(k) pow(2, kr)$.
Le rendement de la contraction de la table au strict nombre de bits ne'cessaires
est proportionnelle au rapport du nombre de voisins et du nombre d'e'tats.
Un espace de dimension $d = 3$ dote' du voisinage complet des $r = 26$
cellules distantes de 1 unite' de la cellule cible
.thy@GET-REF nombre-de-voisin 2
et de $k = 1$ bit d'e'tat requiert une table de 128 me'gabytes
sans contraction et 16 me'gabytes avec contraction.
.P
Nous pensons que les avantages sont plus grands que les inconve'nients.
Le nombre d'AC accessibles,
me^me limite',
reste e'norme,
et l'e'tude des AC concerne pour une bonne part
les plus simples d'entre eux.
De plus il est possible de cre'er des fonctions complexes
en combinant\*F
.FS
.thy@GET-REF combine-func 1
.FE
l'application de tables de fonction simple.
.\"Cette ide'e constitue en fait le coeur de notre recherche,
.\"et la seule ve'ritable source de cre'ation d'objets cellulaires.
.\"
.\" OBJECTS/LOIS/OPERATIONS
.\"
.thy@H 3 "Ope'rations"
Un autre avantage des tables est de permettre tre`s simplement la
ge'ne'ration ou la transformation de fonctions.
Un parame`tre e'le'mentaire de ge'ne'ration de fonctions est par
exemple donne' par la densite' de remplissage de la table\*F.
.FS
Il s'agit du parame`tre \(*l.
.[
Langton Edge
.]
d'une richesse e'tonnante
.\" thy@GET-REF lambda 2
puisqu'il est directement associe' a` la
classe de comportement dynamique de la fonction.
.FE
En fait,
une fonction assimile'e a` un vecteur d'e'tats devient un objet cible
de multiples re'ductions et transformations au me^me titre qu'un
espace de dimension 1.
Des attributs comme la tranquillite'\*F ou l'isotropie
.FS
Un voisinage dont toutes les cellules sont a` ze'ro
(un e'tat conventionnel nul),
donne une cellule cible e'galement a` ze'ro.
.FE
impliquent, cependant, une connaissance du mapping
espace/index du voisinage.
Le simple comptage des acce`s aux entre'es de la table
pour une transition
(ou cumule' sur le temps)
fournit une information statistique relativement complexe\*F
.FS
L'histogramme de l'occurrence de toutes les combinaisons d'espaces
possibles sur un fragment d'espace de la taille du voisinage,
qui peut servir a` calculer l'entropie de l'espace.
.FE
sur le point d'espace pre'ce'dent
pour un cou^t CPU ne'gligeable\*F.
.FS
Au prix ne'anmoins d'une consommation me'moire $M$
pe'nalisante pour les plus grande tables
$M = log2(SN)T$, en pratique $2 T$ ou $4 T$.
.FE
On peut encore citer les ope'rateurs de bruitage (ou mutation)
sur table et de cross-over sur deux tables,
qui permettent la re'alisation d'algorithmes ge'ne'tiques
pour l'exploration de l'espace des fonctions,
ou enfin l'utilisation possible de re'seaux de neurones sur une
table.
.\"
.\" OBJECTS/LOIS/COMPOSITION
.\"
.thy@H 3 "Composition"
.SETR ref-combine-func
La coordination de plusieurs tables ne'cessite la mise au point d'un
syste`me de binding parame`tres/valeurs pour le multiplexage spatial
des tables et d'un se'quenceur pour le multiplexage temporel.
.thy@BIG
.thy@FIG func-1 "deux visions du voisinage"
La figure \*[fig-func-1]
montre la transformation d'un fragment d'espace en
index d'une table de transition.
Le choix du mapping des coordonne'es des cellules de l'espace
(de dimension $d$) vers le vecteur d'index est arbitraire.
Il n'est cependant pas quelconque,
car de'terminant pour l'efficacite' de la fonction de mapping.
.thy@BIG
.thy@FIG apply-1 "le pipeline apply"
La figure \*[fig-apply-1]
montre par exemple comment pipeliner la fonction de mapping
pour un voisinage de Moore,
re'duisant l'obtention d'un nouvel index a` 1 shift et 3 copies,
a` la place des 9 copies ne'cessaires en l'absence de pipeline.
.SETR ref-mem-struct
La ne'cessite' d'adresser rapidement chaque cellule de l'espace
sur des machines adressables au niveau du byte,
conduit au choix d'une organisation
en plan de vecteur de bits
(tableau de bytes)
pluto^t qu'en vecteur de plan de bits.
Le re'seau d'interconnexion est une liste de couples cellule/bit
spe'cifiant les coordonne'es spatiales
de chacun des bits constituant l'index d'acce`s a` la table
associe' a` une liste des bits cibles
de la valeur de l'entre'e dans la table.
.thy@BIG
.thy@FIG apply-2 "quelques re'seaux d\*[thy@quote]interconnexion"
La figure \*[fig-apply-2]
montre quelques re'seaux d'interconnexions.
Les premier et troisie`me,
et deuxie`me et troisie`me d'entre eux,
dont les bits cibles sont disjoints
sont applicables en paralle`le sur le me^me espace.
Les deuxie`me et troisie`me,
de taille d'index
et de taille de valeur cible identique,
peuvent e^tre associe's a` une table de transition identique.
.thy@BIG
.thy@FIG func-2 "mise a` jour par table"
La figure \*[fig-func-2]
montre l'application d'un re'seau d'interconnexion sur une table.
.thy@BIG
.thy@FIG func-3 "deux tables disjointes"
.br
la figure \*[fig-func-3]
montre la mise en oeuvre de deux AC disjoints.
.thy@BIG
.thy@FIG func-4 "deux tables non disjointes"
La figure \*[fig-func-4]
montre la mise en oeuvre de deux AC coordonne's par l'interme'diaire
de deux re'seaux d'interconnexion non disjoints.
.\"
.\" OBJECTS/LOIS/VOISINAGES-SPECIAUX
.\"
.bp
.thy@H 3 "Voisinages spe'ciaux"
On remarque sur la figure \*[fig-func-4]
la pre'sence d'un e'le'ment (E) de voisinage non issu de l'espace.
La fonction d'application peut fournir une valeur fonction
du temps ou de l'espace utilisable comme e'le'ment de l'index.
Ce type d'extension a` la notion de voisinage peut sembler contraire
a` la de'finition que nous avons donne' d'un AC.
Me^me si les AC qui nous inte'ressent sont ba^tis par combinatoire d'AC
simple,
il existe toujours un couple
\fIespace initial, fonction de transition\fR
permettant de calculer et de diffuser une valeur globale
quelconque de l'espace ou du temps\*F.
.FS
Ou si l'on pre'fe`re il est possible de simuler une architecture de
Von Neuman dans un espace cellulaire.
.FE
Les e'le'ments de voisinages spe'ciaux sont des acce'le'rateurs
d'acce`s a` ces valeurs.
Certains d'entre eux sont simplement des e'conomiseurs d'espace.
Par exemple,
au lieu d'utiliser un plan me'moire pour stocker un pattern
re'gulier permettant a` l'AC de conna\(^itre la parite' des coordonne'es
d'une cellule\*F,
.FS
Ce qui revient a` organiser un multiplexage spatial des re`gles,
qui pourrait e'galement e^tre re'alise' en acce'dant a` la table de
transition a` travers une indirection supple'mentaire via un index de
type spatial d'une cellule.
.FE
la fonction d'application maintient un bit de parite' par dimension
d'espace.
D'autres permettent de re'duire la taille d'une table en fournissant
un compteur ou un timer synchrone sur l'espace\*F.
.FS
Dans ce cas la table contient plusieurs fonctions de transition
distinctes qui alternent cycliquement,
et il est sans doute plus avantageux d'utiliser un se'quenceur
externe.
.FE
Enfin certaines re'ductions de l'espace,
dont le calcul ne'cessiterait un protocole cellulaire complexe,
sont e'videmment utile,
tel le OR de l'ensemble des valeurs d'un plan de bit qui permet a`
chaque cellule de savoir que ce plan est a` ze'ro pour toutes les
cellules de l'espace.
.P
La fonction d'application peut e'galement calculer une valeur locale,
permettant ainsi une re'alisation par tables
de fonctions autrement inaccessibles.
Si la fonction de transition ope`re une re'duction simple sur l'index,
celle-ci peut e^tre confie'e a` la fonction d'application.
Si l'ope'rateur de re'duction est commutatif,
associatif,
et posse`de un ope'rateur inverse,
la re'duction peut e^tre pipeline'e.
Par exemple,
un voisinage de $r$ cellules a` $k$ bits d'e'tat
donnerait une table de taille $pow(2, rk)$.
La distribution de l'ope'rateur d'addition sur les $r$ cellules
sources permet de re'duire la taille de la table a`
$pow(2, log2(r pow(2, k)))$.
Dans ce cas pour $k = 8$,
la taille de la table passe de
$pow(2, 72)$ bits a` $pow(2, 12)$ bits,
et le pipeline de binding remplace un shift\*F
.FS
A condition de disposer d'une arithme'tique sur mots de 72 bits.
.FE
par une soustraction,
et trois concate'nations (un shift et un or) par trois additions.
.\" MARK
.thy@BIG
.thy@FIG func-7 "apply sum"
La figure \*[fig-func-7]
montre un voisinage de Moore
ou` l'addition des cellules sources remplace leur concate'nation.
Les connexions barre'es sont active'es au cycle 2,
et les connexions doublement barre'es au cycle 3 du pipe-line.
.P
La distribution de l'ope'rateur d'addition sur les $r - 1$ cellules
sources
(prive'es de la cellule cible dont la pre'servation est en ge'ne'ral
souhaitable pour obtenir une gamme d'AC accessibles plus vaste)
associe'e a` la concate'nation de la cellule cible,
donnerait une taille
.\"2^(log((R - 1) * 2^K) + K)
.\"2^(log(R - 1) + K + K)
.\"2^(log(R - 1) + 2K)
$M = pow(2, log2((r - 1) pow(2, k)) + k) = pow(2, log2(r - 1) + 2k)$.
Cette architecture ope`re l'addition pipeline'e des cellules du
voisinage de Moore moins la cellule cible,
et la concate'nation de cette somme avec la valeur de la cellule cible.
Dans ce cas, pour $k = 8$,
la taille de la table passe a` $pow(2, 19)$ bits.
.P
D'autres fonctions locales,
telles les minimums et maximums des valeurs cellulaires,
pourraient e^tre calcule'es par la fonction d'application.
L'association d'AC dont les cellules posse`dent une varie'te' de
densite's large pour une varie'te' de comportements re'duite,
a` des AC de nature oppose'e est un de nos objectifs.
.P
En plus d'e'le'ments de voisinages spe'ciaux la fonction
d'application peut fournir toutes sortes de voisinages non standards,
destine's a` une utilisation dans le cadre du se'quenceur,
ou a` un usage ge'ne'ralise' du me'canisme des table de transitions.
Nous avons de'ja` e'voque'
.thy@GET-REF time-xor 2
un voisinage a` deux bits associe' a` la
table XOR pour la re'alisation d'une transformation sur le temps.
Le se'quencement d'une se'rie de voisinages a` deux cellules,
balayant un espace re'gulier standard en pivot sur la cellule cible,
permet d'accumuler une ope'ration quelconque sans faire appel a` un
e'le'ment de voisinage spe'cial (non spatial) pour cette
re'duction\*F.
.SETR ref-seq-vs-pipe
.FS
Le nombre d'ope'rations ne'cessaires a` la fabrication d'un index est
re'duit mais le balayage de la me'moire est multiplie' et la pre'sence
possible d'un pipeline pour les voisinages disposant d'un plus grand
nombre de cellules re'duit cet avantage.
.FE
Une table a` deux arguments,
utilisable comme accumulateur,
a deux entre'es de taille diffe'rente et une sortie de taille e'gale a`
l'entre'e accumulatrice.
Cette table peut e^tre utilise'e par une fonction d'application pour
le calcul d'une valeur locale en place de la concate'nation pour la
fabrication de l'index.
.P
Dans le cas d'une ge'ne'ralisation de l'usage de tables a` une
combinatoire (multiplexage spatial et temporel) d'usage de tables non
disjointes sur un me^me espace,
le gain escompte' n'est pas toujours un
gain de me'moire,
mais e'galement du pouvoir d'expression des structures de donne'es
associe'es a` cette combinatoire.
Par exemple,
il n'est pas ne'cessaire de conside'rer le OR de tout les bits d'un
plan cellulaire comme un e'le'ment de voisinage spe'cial dont le
calcul est laisse' au soin de la fonction d'application.
Il est possible d'utiliser une variable spe'ciale,
un accumulateur
(une variable scalaire,
contrairement aux variables cellulaires),
comme un e'le'ment de cellule cible,
et non plus seulement d'index.
Le binding de la table de la fonction binaire OR,
ou de toute autre fonction binaire,
aux arguments CENTRE et ACU et au re'sultat ACU,
et le report au se'quenceur de la ta^che de l'application de cette
fonction sur l'espace 
(ou plus probablement a` la capacite' de la fonction d'application
d'appliquer plusieurs AC sur un me^me pipeline)
permet d'utiliser la machinerie cellulaire a` son propre
service.
Bien su^r, dans ce cas,
seul le re'sultat de la re'duction applique'e sur le plan pre'ce'dent est
accessible (a` moins de faire deux passes),
et ce type d'approche n'est pas possible sur une architecture SIMD
re'elle.
.\"
.\" OBJECTS/LOIS/UTILISATION
.\"
.thy@H 3 "Utilisation"
Si l'on veut conside'rer l'application de tables sur des espaces,
lesquels ne sont pas toujours confondus avec l'espace cellulaire a`
proprement parler,
comme la structure de contro^le e'le'mentaire\*F de l'univers
cellulaire,
.FS
En tout cas dans un environnement SISD.
Nous choisissons de'libe're'ment d'ignorer les proble`mes que poserait
le portage du syste`me sur une architecture SIMD.
Les AC e'tant quant a` eux e'videmment inde'pendants de l'architecture.
Nous pensons que l'usage d'une architecture SIMD simule'e reposant sur
une organisation pipeline'e de la transformation de plans me'moires
par tables permet une utilisation efficace des ressources d'une
architecture Von Neuman,
applicable a` une vaste classe de proble`mes
ge'ne'raux.
.FE
celle-ci doit e^tre munie d'une structure de donne'es supportant la
construction,
le me'lange et la composition.
.BL
.\"
.\" OBJECTS/LOIS/USAGE/CONSTRUCTION
.\"
.LI
.SETR ref-static-param
La construction des tables permet l'association d'une fonction a` ses
parame`tres statiques.
Les parame`tres statiques d'une fonction sont les parame`tres de la
fonction qui ne sont pas associe's a` un des e'le'ments du voisinage
cellulaire,
mais permettent de ge'ne'raliser le
comportement de la fonction.
Il s'agit par exemple de la valeur de timers locaux
(propres a` chaque cellule)
ou de valeurs de seuil de'clenchant des portions de code de la fonction.
.\"
.\" OBJECTS/LOIS/USAGE/COMPOSITION
.\"
.LI
La composition des tables permet la construction d'une liste de
fonctions travaillant en paralle`le sur un me^me espace.
On peut obtenir le me^me effet en utilisant un se'quenceur temporel,
mais au de'triment de l'usage du pipeline\*F.
.FS
.thy@GET-REF seq-vs-pipe 1
.FE
De plus,
la disponibilite' d'un objet spe'cifique de composition de
fonctions permet l'application d'ope'rateurs de me'lange et de
se'paration sur les tables.
On peut enfin imaginer une ge'ne'ralisation de cette liste a` un arbre,
permettant l'utilisation de re'sultats interme'diaires d'application de
table comme e'le'ment de voisinage d'une autre table.
.\"
.\" OBJECTS/LOIS/MELANGE
.\"
.LI
Le me'lange de deux tables consiste en la combinaison de leurs
parame`tres formels en une seule liste de parame`tres,
re'sultant en une table dont la taille est e'gale au plus
(si l'intersection des ensembles de parame`tres est vide)
au produit de la taille de chaque table\*F.
.FS
Il s'agit de la taille de la table en nombre d'entre'es,
qui doit e^tre multiplie'e par le cardinal de l'union des parame`tres,
exprime's en bits,
pour obtenir la taille en bits.
.FE
Cette ope'ration est applicable
soit au niveau des fonctions elles-me^mes,
et ne'cessite une nouvelle invocation de chaque fonction
pour la construction de la nouvelle table\*F,
.FS
Cela peut s'ave'rer relativement cou^teux pour les grandes tables,
si la fonction est fournie par un interpre`te.
.FE
soit directement sur les tables elles me^mes.
Le me'lange de tables permet une optimisation de l'usage des
ressources CPU au de'triment des ressources me'moire.
Cette optimisation peut sembler douteuse puisqu'elle e'change une
augmentation line'aire\*F
.FS
Le facteur de gain de'pend de fac,on difficile a` pre'voir du cou^t
relatif de la construction se'pare'e ou unifie'e de l'index et de la
dispersion des indexs produit par la simulation.
.FE
de la vitesse de calcul contre une
augmentation exponentielle de la taille de la me'moire utilise'e.
De plus la construction de grandes tables redondantes
est en elle me^me un processus cou^teux,
voire tre`s cou^teux si l'on en vient a` faire appel a` la me'moire
pagine'e.
Cependant une me'moire qui se compte en dizaine de me'gabytes sur une
station de travail,
rend inte'ressant ce genre d'optimisation.
D'autant plus qu'une fois acheve'e la construction de la table
son usage peut re've'ler une densite' d'acce`s concentre'e sur des
fractions de la table\*F,
.FS
Cela de'pend des espaces initiaux et des AC, bien su^r.
Tous ceux qui ont observe' un jeu de la vie partant d'un espace
initial ale'atoire de densite' \(12,
comprennent qu'apre`s les premiers points de temps
la densite' d'impact des indexs se concentre en fonction de la
densite' ge'ne'rale de l'espace,
et de la densite' des patterns produits.
.FE
allant jusqu'a` justifier l'usage de tables d'une taille
supe'rieure a` la me'moire re'elle disponible.
Encore que dans ce cas le cache devrait pluto^t e^tre fourni par
l'applicatif,
sous forme d'une construction virtuelle de la table\*F,
.FS
Pour ne pas e^tre trop cou^teuse
celle ci doit reposer sur les services du syste`me d'exploitation
qui permettent une re'cupe'ration (trap) des de'fauts de pages.
.FE
que par le syste`me d'exploitation.
La dualite' opposant l'usage
de nombreuses petites tables applique'es en paralle`les sur un me^me
espace,
a` l'usage d'une seule grande ou tre`s grande table,
permet de choisir entre une mise en oeuvre adapte'e au de'veloppement
incre'mental interactif
(faible de'lai de mise en marche d'une architecture,
associe' a` un de'bit de mise a` jour cellulaire non optimum),
et une mise en oeuvre adapte'e a` l'exploration de la dynamique a`
long terme d'AC sur de grands espaces
(temps de de'marrage important,
associe' a` un de'bit de mise a` jour cellulaire optimum pour une
architecture mate'rielle donne'e).
.\"
.\" OBJECTS/LOIS/SEPARATION
.\"
.LI
La se'paration des tables est l'ope'ration inverse du me'lange.
Cette ope'ration
(pour laquelle nous n'avons pas actuellement cherche' d'algorithme)
devrait permettre de de'terminer la qualite' de primitive d'une
fonction.
.LE
.\"
.\" OBJECTS/LOIS/VIRTUAL
.\"
.thy@H 3 "Des machines virtuelles"
Nous avons de'ja` e'voque' l'e'quivalence entre
une fonction de transition et une machine SIMD.
La cellule d'espace est la me'moire locale a` un PE,
la table de transition le PE,
le re'seau d'interconnexion les liens entre les PE,
et la fonction d'application l'e'mulateur (la machine) qui
de'place les bits de la me'moire aux PE.
Le choix d'une fonction d'application
de'termine la taille de la table de transition,
et donc le nombre de machines virtuelles possibles
associe'es a` cette fonction.
Les contraintes qui pe`sent sur la conception d'une architecture
mate'rielle re'elle ne sont pas les me^mes que celles qui pe`sent
sur une architecture mate'rielle virtuelle.
Les machines virtuelles peuvent e^tre tre`s spe'cifiques,
et pas ne'cessairement universelles.
Les machines SIMD re'elles doivent e^tre universelles.
Ne'anmoins, le but de l'objet loi de transition,
est bien de permettre la spe'cification d'une architecture
SIMD quelconque, et sa mise en oeuvre la plus efficace
possible.
.P
Que doit e^tre une fonction de transition pour simuler un plan de $N$ GAPP ?
.thy@BIG
.thy@FIG gap-pe "GAP layout of a single processor"
La figure \*[fig-gap-pe] pre'sente l'architecture d'un PE GAPP\*F.
.FS
Nous ignorons le registre CM.
.FE
.thy@BIG
.thy@FIG gap "apply gap"
La cellule est compose'e
des 3 registres (C, NS et EW),
des 3 bits de sortie de l'alu (SM, CY et BW),
et de 1 bit de ram (M).
La fonction d'application rec,oit en plus des arguments usuels,
les 11 bits de contro^le,
les 7 bits d'adresse
et un espace supple'mentaire de $N times 128$ bits.
Voir la figure \*[fig-gap].
.P
Le travail de de'codage des bits de contro^le
est minimal et peut donc e^tre sorti de la boucle d'application.
.P
Le bit de ram de la cellule est charge' depuis la me'moire.
.br
Condition $roman {Ctl} sub {8} roman {Ctl} sub {9} == 0$.
.P
.B1
.VERBON
*cellule &= CLEAR_RAM;
*cellule |= !!(ram[adresse_hi] & adresse_pos) << RAM;
.VERBOFF
.B2
.P
Le registre NS est charge' depuis la cellule au nord.
.br
Condition $roman {Ctl} sub {4} roman {Ctl} sub {3} roman {Ctl} sub {2} == 2$.
.P
.B1
.VERBON
*cellule &= CLEAR_NS;
*cellule |= *north & NS;
.VERBOFF
.B2
L'action existe aussi pour les cas $roman {NS} <- roman {S}$,
$roman {EW} <- roman {E}$ et $roman {EW} <- roman {W}$.
.P
L'index est compose' avec les 11 bits de contro^le et
les 7 bits d'e'tats de la cellule\*F.
.FS
La table de transition a donc une taille de 256 kilobyte,
chaque byte contenant 7 bits utiles.
.FE
Le nouvel e'tat de la cellule est calcule'.
.P
.B1
.VERBON
*cellule = transition[*cellule | contro^le];
.VERBOFF
.B2
.P
Le bit de ram est e'crit dans la me'moire.
.br
Condition $roman {Ctl} sub {8} roman {Ctl} sub {9} != 0$.
.P
.B1
.VERBON
ram[adresse_hi] &= clear_ram;
ram[adresse_hi] |= !!(*cellule & GET_RAM) << adresse_pos;
.VERBOFF
.B2
.P
Les 3 conditions possibles pour l'acce`s a` la ram
(pas d'acce`s ou read ou write) et
les 5 conditions possible pour l'acce`s au voisins
(pas d'acce`s ou $roman {NS} <- ( roman {N} ou roman {S})$
ou $roman {EW} <- ( roman {E} ou roman {W})$)
donnent 15 fonctions de boucle d'application,
qui peuvent pre'calculer certaines valeurs
associe'es aux conditions
(offset en byte et en bit de l'adresse par exemple),
et dans le cas d'une instruction sans acce`s me'moire
ni voisins, peut se ramener a` \fC*cellule = transition[*cellule]\fP
(apre`s un pre'calcul \fCtransition += contro^le\fP).
.P
On peut aussi ajouter le traitement du global output,
dont la condition de re'alisation est sous contro^le du se'quenceur.
.P
.B1
.VERBON
global |= *cellule & NS;
.VERBOFF
.B2
.P
Nous avons tout de me^me besoin d'e'crire la fonction
qui remplit la table de transition,
mais le passage par table simplifie conside'rablement la ta^che.
.\"
.\" OBJECTS/LOIS/COMPILE
.\"
.thy@H 3 "Et leur compilateur"
Nous avons montre' comment un AC re'alise' par table,
peut simuler une architecture SIMD.
Comment transformer une fonction de transition
en une se'quence d'instructions pour une machine SIMD?
Soit une table de transition de $N$ bits de voisinage
et $R$ bits de re'sultats.
Construisons $R$ tables de taille $pow(2, N)$ bits.
Nous cherchons un ge'ne'rateur d'instructions pour une machine SIMD
pour chacune des $R$ fonctions boole'ennes associe'es a` la fonction de transition.
Soit $T$ une table de $N$ bits de voisinage,
avec $R = 1$.
La table $T$ de'finit un langage sur les $pow(2, N)$ indexs de la table.
Le nombre de mots du langage e'tant fini il est toujours possible de construire
un DFA pour reconna\(^itre ce langage.
Les expressions re'gulie`res constituent donc un mode d'expression possible
d'une table de transition.
Par exemple pour life, si le premier bit de l'index est le bit cible:
.B1
(00*10*10*10*)|(10*10*10*10*)|(10*10*10*)
.B2
.thy@BIG
.thy@FIG life-dfa "Le DFA de \fBlife\fP"
La construction automatique du DFA de nombre d'e'tats minimum associe'
a` une table ne pose pas de proble`me:
Il suffit de construire l'arbre de de'codage des indexs,
et d'appliquer sur cet arbre conside're' comme un DFA
un algorithme de minimisation.
.thy@BIG
.thy@FIG life-tree "Une partie de \*[thy@quote]arbre de de'codage de \fBlife\fP"
La figure \*[fig-life-tree] montre
les 32 premie`res entre'es de la table de transition.
La racine de l'arbre est l'e'tat initial du DFA,
les feuilles de l'arbre sont les entre'es de la table.
Une entre'e a` 1 est un e'tat acceptant du DFA.
.P
Chaque PE de la machine SIMD est de'die' a` une cellule.
La me'moire locale de chaque PE maintient l'e'tat de la cellule,
plus l'e'tat courant du DFA.
Pour chacun des bit de voisinages de l'automate,
chaque PE rec,oit le sous ensemble du DFA
construit a partir de l'ensemble des e'tats du DFA pre'ce'demment acce'de's.
Le DFA est transmis sous la forme de triple's (e'tat courant, e'tat si 1, e'tat si 0).
En utilisant les noms des e'tats de la figure \*[fig-life-dfa]:
.thy@TBL gapp-dfa "Calcul \*[thy@quote]une ge'ne'ration de \fBlife\fP"
.TS
center allbox;
c	c	c
n	n	n.
index	DFA transition	state set
Center	016	16
North	112, 667	1267
South	112, 223, 667, 778	123678
East	112, 223, 334, 667, 778, 889	1234678
West	112, 223, 334, 445, 667, 778, 884	12345678
NE	112, 223, 334, 445, 555, 667, 778, 884	12345678
NW	112, 223, 334, 445, 555, 667, 778, 884	12345678
SE	112, 223, 334, 445, 555, 667, 778, 884	12345678
SW	112, 223, 334, 445, 555, 667, 778, 884	12345678
.TE
.thy@TBL-END
Pour finir chaque PE rec,oit la liste des e'tats acceptants.
.thy@TBL gapp-dfa "et une optimisation imme'diate"
.TS
center allbox;
c	c	c
n	n	n.
index	DFA transition	state set
Center	016	16
North	1-2, 6-7	1267
South	1-2, 2-3, 6-7, 7-8	123678
East	1-2, 2-3, 3-4, 6-7, 7-8, 8-4	1234678
West	1-2, 2-3, 3-4, 4-5, 6-7, 7-8, 8-4	12345678
NE	1-2, 2-3, 3-4, 4-5, ---, 6-7, 7-8, 8-4	12345678
NW	1-2, 2-3, 3-4, 4-5, ---, 6-7, 7-8, 8-4	12345678
SE	1-2, 2-3, 3-4, 4-5, ---, 6-7, 7-8, 8-4	12345678
SW	1-2, 2-3, 3-4, 4-5, ---, 6-7, 7-8, 8-4	12345678
.TE
.thy@TBL-END
