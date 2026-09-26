.cpy
.\" point size = 12
.\" .S 12
.S 12 20
.\" page length
.\" .pl 11i
.\"
.\" CONFIGURATION
.\"
.\" HEADERS * FOOTERS
.\" eject before .H 1
.\" .nr Ej 1
.\" break after each heading
.nr Hb 4
.\" blank line after each heading
.nr Hs 4
.\" indent next line of text
.nr Hi 1 
.\" center .H 1
.\" .nr Hc 1
.\" heading font H 1 = bold, other = italic
.ds HF 3 3 2 2 2 2 2
.\" heading point size
.\" .ds HP +4 +2 +2 +2 +2 +2 +2
.ds HP 18 12 11 11 11 11 11
.\" heading to put in table of content
.nr Cl 4
.\" DIVERS
.\" indent begining of paragraph
.\"  .nr Pt 1
.\" default indent for paragraph
.\"  .nr Pi 8
.\" indent dans un DS
.nr Si 8
.\" point of foot note index
.ds F \u\\n+(:p\d
.\" FRENCH STRINGS
.ds Lf Liste des figures
.ds Lt Liste des tableaux
.\" MACROS
.de Cs
.DS I
\f(GR
.lg 0
\\!.lg 0
..
.de Ce
.lg
\\!.lg
\fP
.DE 1
..
.qwe
.ds Pj Maitrise d'informatique
.ds Do Pre'sentation du sujet
.ds Sd Thierry Delamare
.TL
\s+4\*(Pj\s-4
.br
.sp
\*(Do
.br
.sp
\n(dy/\n(mo/19\n(yr
.AF ""
.AU "\\*(Sd"
.MT 4 1
.AS
.in +5
.sp
.in -5
.AE
.PH "|\*(Pj||\*(Do|"
.PF "||Page - \\\\nP -||"
.H 1 "Quoi?"
Un outil d'observation d'automates cellulaires.
.H 1 "Pourquoi?"
.BL
.LI
voir (et montrer) les se'quences anime'es ge'ne're'es par un AC.
En effet s'il est aise' de trouver des ouvrages sur les AC,
contenant des photos d'AC, il est plus difficile de voir des ``films'' d'AC,
bien qu'il existe quelques outils de spe'cification d'AC
et d'observation de leur dynamique.
.LI
cre'er un catalogue d'AC bien connus
.LI
chercher de nouveau AC
.LI
chercher des primitives et une combinatoire d'AC
.LE
.H 1 "Dans Quel environnement?"
unix et X11
.H 1 "Quelles caracte'ristiques aura cet outil?"
.H 2 "rapide"
L'architecture cible est une machine standard de 10 a` 100 mips et 8
a` 64 Mega octets de me'moire utile, associe'e a` un serveur X.  Par
exemple pour un AC 2d compose' de 256x256 cellules de 2 bits avec un
voisinage de Moore le syste`me doit e^tre capable de calculer une
dizaine d'e'tats par seconde (10 hz).  Le cout lie' a` la
visualisation est plus difficile a` e'valuer, mais la chaine de
traitement comple`te (production, extraction, visualisation) doit
permettre l'observation d'un film a` une fre'quence supe'rieure a` 1
hz.  Le travail comprend une e'tude pragmatique des performances et
des limites des architectures utilisables pour des AC 1, 2 et 3
dimensions.
.H 2 "adaptable"
L'environnement est unix et X11, mais le but n'est pas de faire un
programme X ou une interface humaine.  les composants du syste`me
doivent pouvoir s'inte'grer a` divers environnements d'interaction
humaine.  La ``glue'' utilise'e pour re'unir les composants, pourrait
faire intervenir par exemple tcl, xgen, interviews, emacs, elk ou
khoros.
.P
La configuration minimum comprend:
.BL
.LI
les primitives de manipulations d'AC.
.LI
un interpre`te de se'quencement des primitives.
.LI
un viewer passif de se'quences d'images.
.LE
.H 2 "extensible"
L'architecture du syste`me doit permettre l'expe'rimentation de plusieurs:
.BL
.LI
re'seaux d'interconnection:
.DL
.LI
1, 2 et 3 dimensions.
.LI
pyramides.
.LI
flux I/O.
.LE
.LI
re`gles de voisinnage.
.LI
mode`les d'organisation de PE.
.LI
mode`les d'organisation de machines de se'quencement.
.LI
outils de mesure de la dynamique des AC.
.LE
.P
En fait, le syste`me devrait pouvoir e^tre e'tendu a` la simulation
de syste`mes dynamiques discrets a` re'seaux d'interconnections maille'es
utilisant un formalisme de spe'cifications plus ge'ne'ral qu'un AC ``classique''.
.P
Cela ne signifie pas que l'on disposera de tous les caracte`res souhaite's,
mais l'architecture du syste`me sera prioritairement oriente'e vers ceux-ci.
.H 1 "Pourquoi un nouvel outil?"
Il existe en effet plusieurs logiciels disponibles pour l'observation
des AC.
.BL
.LI
cellsim, sous unix et sunview pour l'environnement de visualisation.
.LI
scamper, sous unix et X11.  utilise un syste`me de pattern matching
pour spe'cifier les fonctions de transitions, ce qui permet d'avoir
des automates avec de nombreux e'tats mais au de'triment de la
rapidite' obtenu avec une table.
.LI
xlife, tre`s rapide et permettant l'usage d'un espace virtuel tre`s
important, mais limite' aux fonctions de transitions totalistiques.
.LI
x3dca, limite' aux fonctions de transitions totalistiques, mais en 3 dimemsions.
.LI
CA Lab, pour IBM PC-compatible
.LI
il en existe sans doute d'autre...
.LI
et enfin une CAM-n et son environnement logiciel.
.LE
.P
La recherche et l'e'valuation des outils existants est ne'cessaire,
cependant aucun ne semble actuellement totalement satisfaisant,
ne serait-ce que pour leur indisponbilite' en version source libre
dans l'environnement souhaite'.
.H 1 "Motivations"
La re'alisation des outils n'est pas ne'cessairement une fin en soi.
Il est pre'vut l'utilisation de cet environnement pour:
.BL
.LI
l'imple'mentation d'un e'chantillon de'monstratif d'AC.
.LI
l'exploration de la puissance symbolique des AC comme outil de mode'lisation
de phe'nome`nes collectifs.
.LI
la recherche de se'quence d'images d'inte`re^t purement plastique.
.LE
.H 1 "Conside'rations e'pistemologiques et morphologiques"
.P
La typologie ontologique des AC utilise une approche mathe'matique.
Je souhaitons structurer notre catalogue plus librement, en
cherchant des classes d'e'quivalences bas'es sur des conside'rations
e'piste'mologiques (les me'taphores utilise'es pour de'crire la
mode'lisation) ou morphologiques et esthe'tiques (les me'taphores
utilise'es pour de'crire la dynamique visuelle).
.P
Les AC semblent pouvoir mode'liser (ou e'voquer) des phe'nome`nes naturels
a` de nombreuses e'chelles:
subatomique,
atomique,
mole'culaire,
macromole'culaire,
organite cellulaire,
cellulaire,
tissulaire ou colonie cellulaire,
organique,
e'cologique,
tellurique,
stellaire,
galactique.
.P
Le passage d'une e'chelle a` l'autre e'tant semble-t-il au coeur de
l'e'mergence de comportements collectifs d'un ensemble de re`gles de
comportement individuel. Autrement dit le choix du couple
individu/population est souvent a` la frontie`re de deux univers
e'piste'mologiques.
.P
les AC mode'lisent, ou semblent pouvoir mode'liser des phe'nome`nes en:
.BL
.LI
physique, physique atomique, mole'culaire
.LI
chimie atomique, mole'culaire, macromole'culaire, biologique
.LI
biologie des organite cellulaire, cellulaire, physiologie, embryologie
vie artificiel
.LI
e'volution, reproduction
.LI
sociologie, communication, coope'ration, culture
.LE 1
.P
Ou pour citer des concepts moins synthe'tiques:
association, compe'tition, mutation, se'lection, activation, croissance, inhibition...
.H 1 "Bibliographie"
.H 2 "Cellular Automata"
.BL
.LI
\fICellular Automata Machines - A new environnement for modeling\fP.
Tommaso Toffoli, Norman Margolus.
MIT Press, 1987.
.LI
\fITheory and Applications of Cellular Automata\fP.
Stephen Wolfram.
World Scientific, 1986.
.LI
\fIL'ordinateur cellulaire\fP.
Patrick Greussay.
La Recherche, Novembre 1988.
.LI
\FiDynamical Systems and Cellular Automata\fP.
Edited by J. Demongeot, E. Goles, M. Tchuente.
ACADEMIC PRESS, 1985.
.LI
\FiModern Cellular Automata,
Theory and Applications\fP.
Kendall Preston, Jr. and Michale J. B. Duff.
Plenum Press, 1984.
.LI
\fICellular Automata Theory and Experiment\fP.
edited by Howard Gutowitz.
MIT Press, 1991.
.LI
\fIEssays on Cellular Automata\fP.
Edited by arthur W. Burks.
University of Illinois Press, 1970.
.LI
\fIAutomates cellulaires\fP.
Girard Hantcherlian, Dominique Hervio.
Universite' de Grenoble, 1972
.LI
\fIParallel Processing by Cellular Automata and Arrays -
Proceeding of the Third International Workshop on
Parallel Processing by Cellular Automata and Arrays
Berlin, GDR, 9-11 September, 1986\fP
Edited by Tamas Legendi, Dennis Parkinson, Roland Vollmar, Gottfried Wolf.
NORTH-HOLLAND, 1987.
.LI
\fIPretty Pictures Generated by Two-state Five-neighbor Cellular Automata\fP.
Wentian li.
Center for Complex System Research, University of Illinois at Urbana-Champaign, 1988.
.LI
\fILifeLine - A quarterly newletter for enthusiast og John Conway's game of life\fP.
Robert T. Wainwright, March 1971 to September 1973.
.LE
.H 2 "Architecture et Programation"
.BL
.LI
\fIEtude pratique des ressources de la programmation plane\fP.
Marie-Noelle Rozin.
Me'moire de maitrise, Universite' de Paris-8-Vincennes, 1987.
.LI
\fIProgrammation des me'ga-processeurs - Du Gapp a` la Connection Machine\fP.
Patrick Greussay.
De'partement  Informatique, Universite' Paris VIII Vincennes a` Saint-Denis.
.LI
\fIControle et programmation paralle`les des architectures pyramidales\fP.
Jean Me'hat.
The`se de l'universite' de Paris-8, Vincennes a` Saint-Denis, 1989.
.LI
\fIGAPP Routeur\fP.
Jacqueline Signorini.
Universite' de Paris-VIII.
.LI
\fIParallel, Hierarchical Software/Hardware Pyramid Architectures\fP.
Leonard Uhr.
Computer Sciences Department, University of Wisconsin, 1986.
.LI
\fIStructured SIMD Programming in Parallaxis\fP.
Thomas Braunl.
Sprinder-Verlag, 1989.
.LI
\fIAlgorithm-Structured Computer Arrays and Networks\fP.
Leonard Uhr.
Academic Press, inc., 1984.
.LI
\fIVLSI Array Processors\fP.
S. Y. Kung.
Prentice Hall, 1998.
.LI
\fIParallel Computers - Architecturem programing and algorithms\fP.
R. W. Hockney, C. R. Jesshope.
Adam Hilger Ltd, 1986.
.LI
\fIThe Connection Machine\fP.
W. Daniel Hillis.
MIT Press, 1986.
.LI
\fIProcesseur GAPP - Geometric Arithmetic Parralel Processor\fP.
NCR, Futur IDS.
.LI
\fIApplication notes to the GAPP\fP.
NCR, Futur IDS.
.LI
\fIDigital Signal Processing - GAPP\fP.
NCR, Futur IDS.
.LE
.H 2 "Artificial Life"
.BL
.LI
\fIArtificial Life -
The proceding of an
interdisciplinary workshop on
the synthesis and simulation of
living systems
held september, 1987.\fP
Christofer G.Langton, Editor.
Addison-Wesley, 1989.
.LI
\fIArtificial Life II -
Procedings of the workshop
on artificial life
help february, 1990
in Santa Fe, New Mexico\fP.
Editors Christofer Langton, Charles Taylor, J. Doyne Farmer, Steen Rasmunssen.
Addison-Wesley, 1992.
.LE
.H 2 "Origin of Life"
.BL
.LI
\fISeven clues to the origin of life - A scientific detective story\fP.
A. G. Cairns-Smith.
Cambridge University Press, 1985.
.LI
\fIThe creation of life - From chemical to animal\fP.
Andrew Scott.
Basil Blackwell, 1986.
.LI
\fIAux origines de la vie\fP.
Ouvrage coordonne' par Marcel V. Locquin.
Fayard, 1987.
.LE
.H 2 "Misc"
.BL
.LI
\fIComputational Aspect of VLSI\fP.
Jeffrey D. Ullman.
Computer Science Press, 1984.
.LI
\fIDynamique des syste`mes complexes,
Une introduction aux re'seaux d'automates\fP.
Ge'rard Weisbush.
InterEditions/Editions du CNRS, 1989.
.LI
\fIProblems in Complex Systems\fP.
Wentian Li.
Center for Complex System Research, University of Illinois at Urbana-Champaign, 1989.
.LI
\fIThe Recursive Universe - Cosmic Complexity and the Limits of Scientific Knowledge\fP.
William Poundstone.
Oxford University Press, 1987.
.LI
\fIOn Growth and Form - Fractal and Non-Fractal Patternsin Physics\fP.
Edited by H. Euge`ne Stanley, Nicole Ostrowsky.
Martinus Nijhoff Publisher, 1986.
.LI
\fIAlternate realities - Mathematical models of nature and man\fP.
John L. Casti.
John Wiley & Sons, 1989.
.LI
\fIThe Cosmic Blueprint\fP.
Paul Davis.
Unwin, 1989.
.LI
\fIColloque de Cerisy - L'Auto Organisation, de la physique au politique\fP.
Sous la direction de Paul Dumouchel et Jean-Pierre Dupuy.
Editions du SEUIL, 1983.
.LI
\fIEntre le cristal et la fune'e - Essai sur l'organisation du vivant\fP.
Henri Atlan.
Seuil, 1979.
.LI
\fIAutonomie et Connaissance\fP.
Francisco J. Varela.
Edition du SEUIL, 1982.
.LI
\fILa machine univers - Cre'ation, cognition et culture informatique\fP.
Pierre Le'vy.
Edition de la de'couverte, 1987.
.LI
\fIEloge de la simulation - De la vie des langages a` la synthe`se des images\fP.
Philippe Que'au.
Champ Vallon, 1986
.LI
\fIEngines of Creation\fP.
K. Eric Drexler.
Anchor Press, 1986.
.LE
.\".CS
.\".TC

