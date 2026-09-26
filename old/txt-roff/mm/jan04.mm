.\" point size and vertical spacing
.S 14 18
.\"
.\" MM Tuning
.\"
.\" heading point size
.ds HP +6 +4 +2 +2 +2 +2 +2
.\" heading font H 1,2,3 = bold, other = italic
.ds HF 3 3 3 2 2 2 2
.\" eject before .H 1
.nr Ej 1
.\" break after each heading
.nr Hb 4
.\" blank line after each heading
.nr Hs 4
.\" indent next line of text
.nr Hi 1 
.\" center .H 1
.\"nr Hc 1
.\" heading to put in table of content
.nr Cl 4
.\" indent dans un DS
.nr Si 8
.\" control of output for floating display
.nr Df 5
.\"
.\" QWF
.\"
.qwe
.\"
.\" Cover Page
.\"
.TL
Universite\*' de Paris-8
.br
De\*'partement d'Informatique
.br
2, rue de la Liberte' 93526 SAINT-DENIS CEDEX 02
.br
Te'l: (1) 49 49 64 04
.sp 2
\s20
.vs 22
Structure de l'espace des automates cellulaires
\s0
.vs
.sp 2
Thierry Delamare
.br
Janvier 1994
.AF ""
.AU ""
.AT ""
.\"AS
.\"AE
.MT 4
.bp
.\"
.\" PAGE PARAMS
.\"
.PGFORM 17c 27c 2c
.\"
.\" Strings
.\"
.ds thy@line \\l'\\n(.lu'
.\"
.\" Pagers and Footers
.\"
.PH "'Thierry Delamare\''janvier 1994'"
.EH "'\*[thy@line]'''"
.OH "'\*[thy@line]'''"
.PF "''- \\\\nP -''"
.\"
.\" EQN Macros
.\"
.EQ
delim $$
define log2 'log sub {2} ($1)'
define pow '$1 sup {$2}'
define byte 'roman {"byte"}($1)'
define abs 'roman {"abs"}($1)'
.EN
.\"
.\" References Init
.\"
.INITR mm/references
.\"
.\" Refer Cmds
.\"
.R1
database ref/bib.ref
label "A.n' 'D.y"
bracket-label " (" ")" ", "
move-punctuation
sort A+
.R2
.pn 1
.\"
.\" INTRO
.\"
.H 1 "Introduction"
Intuitivement, la classification des AC est une classification qualitative
de leurs comportements dynamiques.
.P
Cette classification repose sur des mesures statistiques des comportements\*F.
.FS
par exemple l'entropie $S = - sum from i p sub i log(p sub {i})$
ou l'information mutuelle (la corre'lation de deux distributions)
$M = sum from i sum from j p sub {i j} log p sub {i j} over {p sub i p sub j}$
.FE
.P
La premie`re question est celle de l'existence d'un certain comportement,
une re'ponse ge'ne'rale est donne' par l'existence d'AC universel.
Un cadre ge'ne'ral est donne' par l'utilisation des me'thodes de
la me'chanique statistique pour qualifier les comportements.
.P
La deuxie`me question est celle du nombre d'AC d'un type donne'
et de leurs localisations dans l'espace des re`gles.
Cette question introduit le proble`me de l'existence de parame`tres
permettant de parcourir l'espaces des re`gles.
.P
Le proble`me de la classification des AC
se situe a` l'intersection du proble`me \fIforward\fP
(de'terminer les proprie'te's a` partir de la re`gle)
et inverse (de'terminer la re`gle a` partir des proprie'te's).
Il implique l'existence d'un ensemble de mesures re'alisables
sur les re`gles et sur leurs dynamiques.
.P
L'existence de parame`tres de contro^le de la dynamique
des AC permet de de'terminer une structure pour l'espace des AC.
.\"
.\" MINIMAL VERSION
.\"
.H 1 "Une version minimale du proble`me"
les AC e'le'mentaires, tel que de'fini par Wolfram,
.[
Wolfram Theory and Applications
.]
sont les AC de dimension $d = 1$, de rayon\*F $r = 1$ et de nombre d'e'tat $k = 2$.
.FS
le nombre de cellules voisines est $d r + 1$.
.FE
Une simplification ultime conside`re l'espace des AC
de parame`tres $d = 0$, $r = 0$, $k = 2$,
Ce qui donne $pow(k, pow(k, d r + 1)) = 4$ re`gles
(Zero, Flip, Same, One),
lesquelles donnent 8 dynamiques:
.br
Z(0) = 0*, Z(1) = 10*, O(0) = 01*, O(1) = 1*
.br
S(0) = 0*, S(1) = 1*, F(0) = (01)*, F(1) = (10)*
.br
soit 4 points fixes sans transitoire\*F (en 2 varie'te's),
.FS
\fItransient\fP
.FE
2 points fixes avec transitoire de taille 1,
2 cycles de tailles 2 sans transitoire.
.P
Les AC e'le'mentaires, dont le nombre est 256 peuvent e^tre e'nume're's\*F,
.FS
des donne'es statistiques peuvent e^tre obtenues pour
chaque re`gles applique'e sur un espace de configuration
.FE
mais l'e'tude des dynamiques associe's a` une re`gle de'pend du nombre $N$ de cellules
de l'espace de configuration (qui tend vers l'infini)
et fait ne'cessairement appel a` des me'thodes statistiques.
Pour $d = 1$, $k = 2$, $r = 2$,
le nombre de re`gle est $pow(2, 32)$ et ne permet de'ja` plus une e'nume'ration.
.\"
.\" WOLFRAM CLASS
.\"
.H 1 "La classification de Wolfram"
La classification de Wolfram est une classification de re'fe'rence
pour de nombreux auteurs
.[
Vichniac
.]
.[
Li Transition Phenomena
.]
.[
Wootters
.]
.[
McIntosh
.]
.[
Chate'
.]
.[
Gutowitz Hierarchical Classification
.]
.P
les quatre classes de Wolfram (selon Wolfram).
les classes I, II et III sont vue comme des attracteurs de syste`mes dynamiques
.BVL 4
.LI "classe I"
.BL
.LI
point limite
.LI
ou tendance a` un e'tat spatialement homoge`ne
.LI
ou les formes disparaissent avec le temps
.LI
ou de petits changement sur la configuration initiale
sont sans effet sur l'e'tat final
.LE
.LI "classe II"
.BL
.LI
cycle limite
.LI
ou montrant une se'quence de structure simple stable ou pe'riodique
.LI
ou les formes e'voluent vers une taille fixe finie
.LI
ou de petits changements sur la configuration initiale
induisent des changements sur des re'gions de tailles finies
.LE
.LI "classe III"
.BL
.LI
attracteur chaotique
.LI
ou montrant un comportement chaotique ape'riodique
.LI
ou les formes croissent inde'finiment a` une vitesse fixe
.LI
ou de petits changements sur la configuration initiale
induisent des changements sur des re'gions de taille toujours croissante
.LE
.LI "classe IV"
.BL
.LI
comportement plus complexe que les pre'ce'dents,
conjecture de calcul universel.
.LI
ou montrant des structures localise'es complexes, e'ventuellement propageantes
.LI
ou les formes croissent et se contractent avec le temps
.LI
ou de petits changements sur la configuration initiale
induisent des changements irre'guliers
.LE
.LE
.P
La description des classes varie selon les auteurs.
On peut introduire la notion de de'calage spatial homoge`ne,
.[
Li Transition Phenomena
.]
souligner la difficulte' que pre'sente certains comportements interme'diaires,
.[
McIntosh
.]
ou proposer des interpre'tations structurelles faisant, par exemple,
des AC de la classe IV un \fIme'lange\fP d'AC de la classe II et III.
.[
Kayama
.]
Les 4 classes (fixe, pe'riodique, chaotique, complexe)
apparaissent actuellement comme un point de de'part ine'vitable de toute
tentative de classification.
La question de la structure de l'espace, et donc des parame`tres de contro^les
devient alors la question premie`re.
.\"
.\" LAMBDA
.\"
.H 1 "Le parame`tre \(*l de Langton"
Le parame`tre \(*l est de'fini comme le pourcentage d'entre'es de la table
de transition dont la valeur est diffe'rente de l'e'tat ze'ro.
$\(*l = {pow(k, d r + 1) - # sub 0} over pow(k, d r + 1)$
.P
A une petite variation de \(*l entre deux re`gles correspond une petite distance
de Hamming entre deux re`gles.
La variation du parame`tre \(*l permet d'e'chantillonner
un espace de re`gles pour $d$, $k$ et $r$ fixe's.
Chaque re`gle est applique'e sur un ensemble de configurations initiales,
et des mesures statistiques sont faite a` la vole'e.
Les se'ries temporelles de mesures sont utilise'es pour de'terminer
l'appartenance de la re`gle a` une classe ou une autre.
On peut alors essayer d'e'tablir une corre'lation entre \(*l
et la classe d'appartenance de l'AC.
.P
Cette proce'dure est a` priori applicable pour d'autres parame`tres,
et vise a` travers l'e'chantillonnage a` re've'ler la structure ge'ne'rale
que la variation du parame`tre de contro^le imprime a` l'espace des re`gles.
.P
Une question associe'e a` la structure de l'espace de'fini par un parame`tre
est la pre'sence et le type d'une e'ventuelle transition de phase,
qui associe a` une valeur critique du parame`tre de contro^le une transition
plus ou moins brusque de la classe de comportement des re`gles.
.P
Une autre question est la pre'sence d'une tendance au continu associe'e a`
l'augmentation de la taille de l'espace des re`gles.
.\"
.\" EXPERIMENTS
.\"
.H 1 "Expe'rimentations sur le parame'trage des classes de comportements"
Li, Packard et Langton
.[
Li Transition Phenomena
.]
proposent l'existence de transitions de phase controle'es par le parame`tre \(*l.
il s'agit d'une transition du premier ordre (transition brutale)
entre les re`gles de type II et III,
ou d'une transition de deuxie`me ordre (transition graduelle) associant
les re`gles de type IV a` une zone d'intersection des types II et III.
Les mesures statistiques utilise'es sont l'entropie, l'information mutuelle
et la vitesse de propagation des diffe'rences sur l'espace cellulaire\*F.
.FS
conside're'e comme une mesure de l'impre'dictabilite' de l'e'volution
des \fIformes\fP de l'espace cellulaire, elle devient une mesure
de la qualite' chaotique du comportement de l'AC.
.FE
Les espaces de re`gles sont typiquement borne's par $d <= 2$, $k < 10$, $r < 12$
Ce type d'expe'riences a d'abord e'te' mene' sur les AC e'le'mentaires,
.[
Li Structure of the elementary
.]
Wootters et Langton
.[
Wootters
.]
e'tendent la recherche a` des espaces de re`gles plus vaste,
dans le but de re'duire la dispersion de la valeur critique.
L'augmentation de $r$ supprime la transition (la valeur critique tend vers ze'ro),
l'augmentation de $k$ tend a` re'duire la dispersion de la valeur critique.
.P
Toutefois la critique d'une expe'rience de Packard
.[
Packard Adaptation toward the edge of chaos
.]
formule'e par Mitchell
.[
Mitchell Revisiting the Edge of Chaos
.]
fait apparai^tre les limites de l'hypothe`se de Langton
sur l'e'mergence du \fIcalcul\fP\*F
.FS
Il s'agit en fait de la transition vers des re`gles dont les mesures statistiques
indiquent une appartenance a la classe IV,
lesquelles sont suppose's universelles.
.FE
au frontie`re du chaos.
.[
Langton Computation at the edge of chaos
.]
.[
Langton Life at the Edge of Chaos
.]
Packard utilise un algorithme ge'ne'tique pour faire e'voluer des re`gles
effectuant un calcul particulier, et interpre`te les re'sultats comme
une indication de l'existence d'une pression se'lective
sur l'e'volution des re`gles vers les valeurs critiques de \(*l
associe'es a` une transition de phase et a` la re'alisation d'un calcul complexe.
.P
Mitchell trouve des re'sultats diffe'rents,
et souligne la ne'cessite' d'une meilleure compre'hension (de'finition)
des concepts utilise's.
Mitchell montre par exemple que l'e'volution par algorithme ge'ne'tique
d'une re`gle calculant l'e'tat majoritaire
de la configuration initiale en tendant vers un points fixe homoge`ne
de l'e'tat majoritaire, se trouve ne'cessairement loin du point critique
(0.27 d'apre`s Wooter et Langton) avec \(*l = 0.5.
.P
Li a par ailleurs sugge're',
.[
Li Problems in Complex Systems
.]
en apparente contradiction avec l'ide'e d'une association entre calcul, complexite'
et phe'nome`nes critiques
.[
Li Transition Phenomena in Cellular Automata Rule Space
.]
une structure fractale pour la distribution des re`gles complexes
dans l'espace des re`gles.
.\"
.\" PROPOSITIONS
.\"
.H 1 "Proposition pour une recherche d'un parame'trage de l'enchassement"
Face aux proble`mes souleve's par l'utilisation du parame`tre \(*l,
nous proposons quelques remarques pouvant servir de point de de'part
a` de nouvelles expe'riences sur la structure de l'espace de AC.
.P
La premie`re remarque concerne l'existence d'autres parame`tres
de contro^le que \(*l.
Li, Packard et Langton
.[
Li Transition Phenomena in Cellular Automata Rule Space
.]
souligne l'importance de la recherche d'autres parame`tres de contro^les
et sugge`re que la dispersion de la valeur critique
pourrais e^tre re'duite par un parame`tre supple'mentaire
(le \fIparame`tre myste'rieux\fP permettant de localiser
des frontie`res plus pre'cises entre les diffe'rents comportement).
Il semble ne'anmoins peu probable qu'un seul parame`tre supple'mentaire suffise.
.P
La deuxie`me remarque concerne la structure enchasse' des espaces de re`gles.
Nous sugge'rons que l'e'tude du degre' d'enchassement d'une re`gle dans un espace
permet la de'finition d'un nouveau parame`tre de contro^le.
.P
La troisie`me remarque concerne les techniques de re'ductions du nombre de re`gles
le'gales a` conside'rer pour un espace donne',
c'est a` dire l'ablation des re`gles anisotropiques ou enchasse'es,
et la possibilite' d'utiliser un mapping interme'diaire.
.P
Nous proposons l'utilisation du parame`tre \fIflip\fP de'fini
comme le nombre de changements d'e'tats rencontre' en balayant successivement
chaque entre'e de la table de transition.
$roman flip = 1 over N sum from {i = 0} to {N - 1} roman {diff} (f sub {i} - f sub {i + 1~roman {mod}~N})$
.br
avec
$ N = pow(k, d r + 1)$, et
$
roman diff (x) ~=~
left {
  lpile {1 above 0}
  ~~ lpile
  {if~x != 0 above if~x = 0}
$
.P
Si l'on plonge une re`gle $R sub N$ parame'tre'e par $r = N$ dans une re`gle
$R sub {N + 1}$ l'insensibilite' de la re`gle aux deux voisins supple'mentaires,
se traduit par une duplication des entre'es de la re`gle $R sub N$.
Par exemple pour $k = 2$,
si pour la colonne $i$ l'e'galite' de chacune des $N/2$ paires $x sub j = x sub {j + pow(2, i)}$
est ve'rifie'e, la colonne $i$ est inutilise'e,
et soit la re`gle est anisotropique, soit la re`gle est isomorphe a` une re`gle
d'espace de taille infe'rieure et peut e^tre isotropique.
.P
La somme des degre's d'e'galite' de chaque colonne est un candidat possible
au ro^le de parame`tre de contro^le.
.P
Parce que l'on peut construire une re`gle pour un espace de taille donne'e
en plongeant une re`gle d'un espace de taille infe'rieure
(par duplication des entre'es),
a` \(*l et flip constant,
puis de'placer peu a` peu la re`gle vers l'espace de taille supe'rieure
en flippant des entre'es (e'ventuellement en conservant \(*l constant),
la mesure de flip pourrais e^tre associe'e au degre' d'enchassement d'une re`gle.
.P
L'utilisation d'un mapping interme'diaire permet de re'duire la taille de l'espace des re`gles,
tout en maintenant une cohe'rence forte sur le sous ensemble choisie.
Par exemple le re'duction du voisinage a` une somme excluant la cellule centrale,
conserve un sous ensemble isotropique de re`gle.
Pour $d = 2$, $k = 2$, $r = 1$ les $pow(2, 512)$ re`gles
deviennent $pow(4, 9)$, en utilisant les 4 ope'rations des re`gles minimales
(Zero, Same, Flip, One) comme valeur de la table interme'diaire.
.\"
.\" CONCLUSION
.\"
.H 1 "Conclusion"
Le proble`me de la structure de l'espace des AC, semble e^tre un proble`me
encore largement ouvert.
La question des formes possibles de la dynamique
des AC pour des espaces de re`gles de grande taille,
et la question d'une combinatoire de re`gles permettant de contro^ler
l'e'mergence de ces formes ne posse`dent pas actuellement de re'ponses.
.\"
.\" Refer Macros
.\"
.mso mac/bib.mac
.\"
.\" Referenced Bibliographie
.\"
.warn (\n[.warn]-512)
.[
$LIST$
.]
.warn (\n[.warn]+512)
