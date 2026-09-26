.EH "'\\\\nP''Conclusion '"
.OH "'Conclusion ''\\\\nP'"
.thy@H 1 "Conclusion"
Nous avons expose' les raisons pour lesquels
nous de'fendons une approche bottom-up ge'ne'rale
en vue de la re'alisation d'un environnement
de de'veloppement cellulaire a` vocation universelle.
L'ampleur de la ta^che,
qui reste largement inacheve',
mais aussi l'expe'rience acquise,
nous conduit a` pre'ciser
quelques directions privile'gie's
de de'veloppement ulte'rieur.
.P
Les principaux re'sultats
portent sur l'obtention d'un moteur cellulaire rapide
et sur la validation de plusieurs outils
bien adapte's a` l'analyse et la pre'sentation visuelle
des dynamiques ge'ne're'es par le Workbench.
.P
La re'alisation des me'canismes de spe'cification
des architectures cellulaires pose
un proble`me de bootstrap.
Ce proble`me se pose e'galement
pour la re'alisation d'une bibliothe`que
d'objets cellulaires e'le'mentaires.
.P
Autrement dit,
nous pensons qu'il convient de consolider
le noyau de fonctionnalite' acquises,
par une inte'gration plus e'troite
de quelques moteurs cellulaires simples et rapides aux
environnements externes,
tout en poursuivant la recherche des me'thodes utilisables
pour la de'finition d'architectures plus ge'ne'rales.
.P
Ne'anmoins,
la re'alisation d'outils puissants (rapides et flexibles)
de manipulation de tables de transitions,
n'e'loignerais pas la tentation d'expe'rimenter
des AC mois radicalement bottom-up.
.P
Nous pre'sentons donc en guise de conclusion
un AC dont la re'alisation effective exclu
l'usage d'une combinatoire de tables de transitions.
.P
Cet AC utilise un voisinage de Von Neumann,
l'horloge interne est a` deux pas,
et la structure cellulaire est a` six champs.
Chaque champs est un entier,
dont la taille est,
dans notre re'alisation,
de 32 bits.
La fonction de transition est exprime'e
de manie`re un peu inhabituelle,
en terme de modification simultane'e
des cinq cellules du voisinage,
avec consultation de l'e'tat local uniquement.
La re`gle de transition re'alise
une physique e'nerge'tique naive.
Les quatre premiers champs de la variable
d'e'tat cellulaire associent des quantite's (les poids)
aux quatres directions de l'espace (nord, sud, est et ouest).
Les deux derniers champs associent des quantite's (les potentiel)
aux axes nord/sud et est/ouest.
Les poids sont des donne'es initiales.
La somme des poids sur l'ensemble des cellules de l'espaces
reste constante dans le temps (conservation de l'e'nergie).
Les potentiels associe's aux axes NS et EO
sont fonction du cumul des poids des deux directions de chaque axes.
Le rapport de cette quantite' a` la somme des poids des quatres directions
de'termine le de'placement additif,
champs par champs,
de la cellule vers une de ses quatre voisines (fusion).
Ce mouvement-fusion a lieu au temps 2 de chaque cycle.
L'ope'ration de fusion porte e'galement sur les potentiels,
dont les reliquats sont conserve's.
par exemple pour l'axes EO:
.thy@CODE-START
	dx = icell->poids[EST] - icell->poids[OUEST];
	icell->potentiel[EO] += dx;

	if (abs(icell->potentiel[EO]) >= sum) {
		if (dx > 0) {
			icell->potentiel[EO] -= sum;
			x = modx(x + 1);
		} else {
			icell->potentiel[EO] += sum;
			x = modx(x - 1);
		}
	}
.thy@CODE-END
Au temps temps 1 de chaque cycle,
la somme est compare' a` la constante universelle (ou K).
si la somme est supe'rieure a` K la cellule explose.
Cette explosion distribue la cellule dans
les quatre voisins par l'ope'ration de fusion.
La division de la cellule en quatre partie est une division entie`re.
Le reliquat cette division permet d'ajouter la rupture de syme'trie
a` la conservation de la quantite' alloue'e au temps ze'ro.
Le choix de la distribution du reliquat de cette division
constitue avec le choix de l'espace initial et de la valeur de K
les seuls parame`tres contro^lable.
Un reliquat subit une rotation et une translation
relative a` sa position cellulaire.
Les exemples de dynamique expose's le sont
pour K = 4, rotation = clockwise next, translation = clockwise next.
.thy@BIG
.thy@DUMP xu-photo-1 "La dynamique de l\*[thy@quote]AC xu"
la figure  \*[dump-xu-photo-1]
est une photo de l'e'volution (de bas en haut) de l'espace initial suivant:
.thy@CODE-START
X	Y	N	S	E	O
-60	0	0	100	100000	0
60	8	0	100	100	100000
0	-60	0	100000	0	0
0	48	100000	0	200	400
.thy@CODE-END
de taille 128 par 128,
sur 128 ge'ne'ration.
L'origine du repe`re est au centre.
.thy@BIG
.thy@DUMP xu-photo-1-top "Un rendu d\*[thy@quote]une tranche des valeurs du dernier plan de la figure \*[dump-xu-photo-1]"
.\" thy@BIG
.\" thy@DUMP xu-film-1-1 "D\*[thy@quote]autre points de vues"
.\" thy@BIG
.\" thy@DUMP xu-film-1-2 "Et un e'pluchage"
.thy@BIG
.thy@DUMP xu-Cfilm-1-1 "D\*[thy@quote]autre points de vues"
.thy@BIG
.thy@DUMP xu-Cfilm-1-2 "Et un e'pluchage"
.thy@BIG
.thy@DUMP xu-Cfilm-2-1 "Une autre configuration initiale"
.thy@BIG
.thy@DUMP xu-Cfilm-2-2 "Et un e'pluchage exponentiel"
