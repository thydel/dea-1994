# Contextes de travail

Ce fichier rassemble des contextes thématiques destinés à amorcer de nouvelles
conversations ou de nouveaux axes de travail autour du dépôt. Il ne constitue
ni une spécification, ni un journal des modifications, ni une liste de tâches.
Chaque section doit pouvoir être lue comme un point de départ relativement
autonome.

## Exploration de l’espace des automates cellulaires

### Positionnement

Le dépôt contient la reconstruction d’un mémoire de DEA réalisé en 1994 autour
des automates cellulaires et d’un environnement expérimental permettant de les
construire, exécuter, observer et transformer. Pour le présent contexte, la
restauration matérielle du document n’est pas le sujet principal : le mémoire,
les anciens programmes, les figures et les données servent de matériau pour
reprendre aujourd’hui une exploration interrompue depuis longtemps.

Cette exploration ne doit pas être présupposée comme une reprise de recherche
mathématique formelle. L’auteur signale lui-même ses limites en mathématiques
et, plus généralement, dans les disciplines scientifiques concernées. Il
dispose en revanche d’une forte culture informatique pratique : programmation,
Unix/Linux, traitement et transformation de données, construction d’outils,
automatisation et expérimentation par le calcul. Une discussion productive doit
donc pouvoir alterner intuition, expérience numérique, programmation,
visualisation et, lorsque cela apporte quelque chose, formalisation
mathématique expliquée sans supposer un niveau académique spécialisé.

Il existe également un intérêt important pour les arts plastiques. La
production d’images n’est pas seulement un moyen d’illustrer les résultats :
les transformations de l’espace et du temps cellulaires peuvent être
considérées comme une matière plastique en elles-mêmes. Les dispositifs de
génération, réduction, projection, filtrage et visualisation peuvent donc être
interrogés à la fois comme instruments d’observation et comme producteurs de
formes, d’images et d’un imaginaire spatio-temporel. Certaines pistes peuvent
ainsi se déplacer vers l’art conceptuel sans qu’il soit nécessaire de tracer
d’avance une frontière nette entre expérience informatique, interrogation
scientifique et démarche plastique.

### Ce que le mémoire fournit déjà

Le mémoire ne considère pas seulement l’état instantané d’un automate. Il
traite l’espace, le temps et l’espace-temps comme des objets manipulables, avec
des opérations d’édition, de réduction, de transformation et de visualisation.

Parmi les idées déjà présentes :

- application itérative d’une fonction de transition à des espaces finis ;
- observation de trajectoires et de cycles limites ;
- réductions intégrales, par exemple la somme d’une séquence d’espaces ;
- réductions différentielles, notamment par XOR entre états successifs ;
- mesure des populations et de leur évolution ;
- élimination ou mise en évidence de cellules engagées dans des cycles courts ;
- projections et coupes de l’espace-temps ;
- statistiques, entropie, dimension fractale, texture et autres réductions ;
- visualisations bitmap, pixmap, surfaces d’élévation, volumes et séquences ;
- variation des dimensions, voisinages, règles, paramètres et conditions
  initiales ;
- utilisation d’outils externes comme partie intégrante de la chaîne
  expérimentale.

Le texte contient déjà des questions qui restent ouvertes. Il évoque notamment
la recherche d’invariants d’échelle, des relations possibles avec
l’auto-organisation critique, la découverte inattendue de cycles limites de
grande taille pour la règle Anneal, et la recherche d’attracteurs de faible
dimension extraits de systèmes possédant un très grand nombre de degrés de
liberté. Il propose aussi explicitement des expériences futures plutôt que de
présenter l’environnement comme un travail clos.

### Orientation pour de nouvelles expériences

Le but d’une nouvelle conversation n’est pas de rester prisonnier des
expériences de 1994. Elles constituent un point de départ à partir duquel on
peut reformuler les questions avec les moyens de calcul, de stockage et de
visualisation actuels.

Une piste importante est l’étude des attracteurs et de leurs bassins. Pour un
automate fini, l’évolution déterministe définit un graphe fonctionnel :
chaque configuration possède un successeur unique, les trajectoires finissent
donc par entrer dans un cycle, et les configurations qui aboutissent au même
cycle constituent son bassin d’attraction. Les expériences peuvent porter sur
des espaces d’états suffisamment petits pour être explorés exhaustivement,
puis chercher des méthodes permettant d’aller beaucoup plus loin.

Les questions intéressantes ne se limitent pas à compter les attracteurs. On
peut notamment examiner :

- la distribution des tailles et profondeurs des bassins ;
- la longueur des transitoires et des cycles ;
- la structure des arbres qui alimentent les cycles ;
- les symétries entre configurations et la possibilité de quotienter l’espace
  d’états ;
- l’effet des translations sur un tore et la distinction entre identité
  stricte d’une configuration et identité à translation près ;
- l’effet de la taille et de la géométrie de l’espace, y compris le choix de
  tailles premières lorsqu’il permet d’éviter ou de révéler certaines
  périodicités spatiales ;
- la comparaison entre règles par des signatures globales plutôt que par
  quelques trajectoires choisies ;
- la recherche de quantités réduites capables de révéler des régularités que
  l’observation directe de l’espace masque ;
- la relation entre comportement global, structure locale de la règle,
  symétries et conditions initiales.

Les bassins d’attraction sont ici une piste de travail, pas une doctrine. Une
discussion peut aussi repartir des questions du mémoire sur les réductions,
les invariants, les cycles, les projections de l’espace-temps ou inventer des
observables entièrement nouveaux.

### Changement d’échelle depuis 1994

Une question transversale consiste à reprendre des expériences qui étaient
alors limitées par la mémoire, le débit de calcul ou les outils de
visualisation, et à demander ce qui devient aujourd’hui explorable.

Il faut éviter deux écueils : refaire simplement plus grand ce qui avait déjà
été fait, ou supposer qu’une augmentation de puissance de calcul produit à
elle seule une question intéressante. L’intérêt est plutôt d’identifier les
expériences dont le changement d’échelle modifie qualitativement ce qu’on peut
observer : exploration exhaustive d’un espace d’états, statistiques sur de
très nombreuses règles ou conditions initiales, calcul de grands graphes de
bassins, recherche automatique d’exceptions, comparaison systématique de
tailles d’espaces, ou production de représentations auparavant impraticables.

### Manière de travailler

Pour explorer une idée, privilégier une boucle courte :

1. formuler la question en langage ordinaire ;
2. préciser juste assez les objets et les hypothèses pour qu’elle soit
   testable ;
3. distinguer ce qui peut être calculé exhaustivement de ce qui devra être
   échantillonné ;
4. construire l’expérience la plus simple susceptible de réfuter ou de
   préciser l’intuition ;
5. conserver les données intermédiaires utiles, pas seulement une image
   finale ;
6. chercher plusieurs réductions ou visualisations du même phénomène ;
7. comparer avec les idées et résultats connus seulement lorsque cela aide à
   interpréter l’expérience ;
8. reformuler ensuite la question.

Les mathématiques peuvent intervenir à n’importe quelle étape, mais elles
doivent servir l’exploration : définition précise d’un quotient, estimation de
complexité, combinatoire de l’espace d’états, théorie des graphes, probabilités,
dynamique discrète, etc. Lorsqu’un formalisme devient nécessaire, l’expliquer
à partir de l’objet informatique concret.

De même, une image surprenante n’a pas à être immédiatement réduite à une
mesure. Elle peut conduire soit à chercher l’observable qui explique sa
structure, soit à devenir elle-même le point de départ d’une transformation ou
d’un dispositif plastique. Les deux démarches peuvent coexister.

### Usage de ce contexte

Dans une nouvelle conversation, utiliser cette section comme arrière-plan,
puis partir directement de la question ou de l’expérience proposée. Ne pas
ramener systématiquement la discussion à la reconstruction du document de
1994. Consulter le mémoire et les ressources historiques lorsqu’ils peuvent
éclairer une idée précise, mais considérer que l’objectif est désormais
d’explorer ce qui peut être pensé, calculé, visualisé ou construit à partir de
ce matériau.
