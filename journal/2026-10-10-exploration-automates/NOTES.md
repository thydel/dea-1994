# Journal de séance — Exploration des automates cellulaires

**Date :** samedi 10 octobre 2026  
**Statut :** notes de travail ; questions ouvertes, pas de choix d'implémentation arrêté.

## Objet de la reprise

Reprendre les outils associés au travail de DEA de 1994 sur les automates cellulaires bidimensionnels, **sans porter littéralement les anciens programmes**. L'objectif est de conserver et améliorer leur approche par génération de code spécialisé, tout en exploitant les possibilités actuelles des processeurs et en élargissant sensiblement l'espace des règles explorables.

Dépôt du travail historique : <https://github.com/thydel/dea-1994>.

## 1. Reconstituer et rénover le pipeline expérimental

Le schéma envisagé demeure un **pipeline linéaire d'outils indépendants**, chacun rénové et susceptible d'être remplacé :

1. **Génération de trajectoires** : spécification de l'automate et de ses paramètres, génération ou exécution du code de simulation.
2. **Extraction / traitements intermédiaires** : notamment extraction ciblée, filtrage différentiel entre générations et autres transformations ; distinguer extraction et filtrage.
3. **Analyse** : calculs statistiques et indicateurs sur les trajectoires ou leurs transformations.
4. **Sortie** : visualisation interactive ou en différé, ou **sauvegarde structurée** des résultats avec collecte des paramètres et métadonnées nécessaires à leur reproduction.

Le pipeline doit rester simple à lancer, idéalement en une commande, sans dépendre d'un environnement shell volatile ni de wrappers fragiles. Discussion d'une **configuration déclarative JSON**, avec paramètres communs et paramètres propres à chaque composant. Un lanceur de type `piperun -c config.json` pourrait construire directement arguments, processus et tubes ; `pipexec` est une référence partielle pour l'orchestration.

**Point d'architecture encore ouvert :** les processus reliés par le flux de données principal doivent aussi pouvoir partager une configuration et éventuellement échanger de l'information **hors de ce flux**. Examiner une architecture à **deux canaux** (données d'une part, contrôle/métadonnées d'autre part), sans figer pour l'instant le protocole ni le sens des échanges. La supervision POSIX (signaux, arrêt cohérent, propagation des erreurs et sémantique analogue à `pipefail`) fait partie de la conception.

## 2. Étendre l'exploration et accélérer le calcul

Repartir de la génération de code spécialisé déjà présente dans le travail de 1994 : spécialisation sur le voisinage, accès indexés et déroulage de boucles. Explorer notamment des **automates 2D**, avec **un à trois bits d'état par cellule** et plusieurs rayons ou niveaux de voisinage (Moore, von Neumann, etc.).

Piste centrale : remplacer la représentation naïve **un octet ou entier par cellule** par une représentation **compactée en plans de bits**, en travaillant avec les mots machines comme des champs de bits contigus. Traduire automatiquement les décalages du voisinage en accès mémoire, décalages et masques ; rechercher une réutilisation incrémentale des indices de transition, en n'ajoutant que les bits manquants lorsqu'on se déplace d'une cellule. Tirer parti des caches, du pipeline d'exécution et, selon les cas, de SIMD et du parallélisme.

**Exemple discuté :** voisinage de Moore de rayon 2, soit 25 cellules. Pour un état binaire, l'index de voisinage occupe 25 bits ; en glissant d'une colonne, 20 bits du motif sont communs aux fenêtres successives, et 5 nouveaux bits entrent. Une table complète aurait `2^25` entrées, soit **32 Mio** à un octet par entrée : il faut comparer table directe, décomposition de tables et logique compilée, ainsi que les contraintes de cache.

## 3. Outils et références à examiner

- **pystencils** : génération de noyaux de calcul spécialisés ; piste pour l'optimisation CPU/SIMD.
- **OpenCAL**, **ACML** : infrastructures de simulation ou d'exploration d'automates cellulaires.
- **Golly**, **CAX** : outils de simulation/exploration servant de points de comparaison.
- **pipexec** : orchestrateur de processus, pertinent pour la partie pipeline plutôt que pour le moteur cellulaire.

Ces références sont des **pistes de lecture ou de comparaison** : aucune n'a été retenue comme solution complète répondant à l'ensemble des exigences.

## 4. Prochaines questions techniques

- Définir un format de spécification des automates, de leurs paramètres et des trajectoires, compatible avec l'archivage reproductible.
- Préciser les interfaces du pipeline et ce qui appartient au canal de données, à la configuration partagée ou à un éventuel canal de contrôle.
- Évaluer plusieurs noyaux de génération : représentation compacte, index glissant, tables décomposées, calcul logique spécialisé, SIMD.
- Comparer coûts de génération du code, consommation mémoire, efficacité des caches et débit de générations calculées.
- Inventorier les anciens composants du DEA puis décider, composant par composant, ce qui mérite d'être adapté, remplacé ou entièrement reconçu.

**Fil conducteur :** conserver la composabilité des expériences tout en permettant une exploration systématique et reproductible d'espaces de règles sensiblement plus grands qu'à l'époque du DEA.

## 5. Caractériser les règles par un vecteur d'influence locale

Nouvelle idée : compléter les paramètres de caractérisation de l'espace des règles (dont le **paramètre d'enchâssement** évoqué dans les travaux antérieurs) par un descripteur calculé **sur la table de transition elle-même**, sans recourir à des trajectoires. Il s'agirait, pour chaque position du voisinage, de distinguer la simple influence sur la sortie de la **nature** de cette influence : copie, inversion ou absence de dépendance conditionnelle.

Pour une transition binaire `f`, et pour chaque entrée `x_i`, fixer les autres entrées et comparer les deux cofacteurs :

- `(f|x_i=0, f|x_i=1) = (0,0)` : sortie constante 0 ;
- `(0,1)` : sortie égale à l'entrée (copie) ;
- `(1,0)` : sortie inverse de l'entrée ;
- `(1,1)` : sortie constante 1.

Définir le vecteur des fréquences `V_i = (p00, p01, p10, p11)` sur les configurations restantes, avec `Σp = 1`. Il contient en particulier l'**influence booléenne** `p01+p10` et l'**influence signée** `p01-p10`. Son calcul structurel repose sur une distribution conventionnelle (par exemple uniforme), **à distinguer** des fréquences rencontrées sur les trajectoires.

**Exemple : Life (B3/S23)**, qui est *outer-totalistique* (dépend du nombre de voisins vivants et séparément de la cellule centrale) et donc isotrope, mais **non additive** au sens de linéaire. Sous distribution uniforme des configurations, la cellule centrale a `V_c=(172,28,0,56)/256` ; un des huit voisins a `V_n=(137,28,70,21)/256`. Les huit voisins ont le même vecteur par symétrie. Les nombres sont des résultats de dénombrement théorique, non des fréquences empiriques de trajectoires.

**Question bibliographique précise :** l'influence ou la sensibilité des positions du voisinage ont été utilisées pour caractériser des espaces de règles, notamment chez **P.-M. Binder (1993)** et dans les travaux sur la caractérisation paramétrique de règles 1D et 2D, mais **l'emploi systématique de ce vecteur signé à quatre composantes comme outil de cartographie des espaces de règles n'a pas été établi pendant la séance**. Éviter donc de le présenter comme inédit ; examiner les littératures de l'analyse booléenne (cofacteurs de Shannon, dérivées booléennes, fonctions unates, canalisation) et de l'analyse des règles cellulaires.

## 6. Bassins d'attraction vus à travers une réduction spatiale

Autre idée exploratoire : simuler des trajectoires d'un automate bidimensionnel sur un **tore de taille modeste**, assez grand pour que des motifs locaux se déploient ; placer ensuite, **dans le pipeline**, un opérateur de réduction spatiale comparable au redimensionnement d'une image. Par exemple, partir de `32×32` et produire `16×16`, `8×8`, etc., en conservant éventuellement une information d'occupation ou un nombre de cellules vivantes par bloc avant une éventuelle binarisation.

Notons `F` la règle de transition microscopique et `P` la projection spatiale : `y_t=P(x_t)` et l'on observe `y_t → y_{t+1}`. Plusieurs configurations détaillées `x` et `x'` peuvent donner le même `P(x)=P(x')`, mais leurs successeurs projetés peuvent diverger : `P(F(x)) ≠ P(F(x'))`. Le graphe des transitions réduites n'est donc **pas nécessairement fonctionnel** ; un même sommet peut avoir plusieurs successeurs. Les arêtes peuvent être pondérées par leur nombre d'occurrences dans un ensemble de trajectoires.

L'objectif **n'est pas** de prétendre reconstruire exactement les bassins d'attraction microscopiques, mais de chercher si l'organisation du graphe agrégé révèle des **signatures robustes** de la dynamique sous-jacente : composantes fortement connexes, distributions des degrés, transitions dominantes, entropie conditionnelle du successeur sachant l'état projeté, structures persistant à plusieurs résolutions. Comparer plusieurs fonctions de réduction et plusieurs trajectoires/conditions initiales ; contrôler les artefacts, notamment les cycles apparents et la fusion de bassins distincts.

La réduction qui rendrait la dynamique macroscopique encore déterministe obéirait à `P(x)=P(x') ⇒ P(F(x))=P(F(x'))`. **L'idée ici est précisément de ne pas imposer cette condition**. Une représentation réduite très simple peut être peu informative ; rechercher plutôt un intervalle d'échelles où subsistent des structures reproductibles.

**Points d'appui bibliographiques évoqués pendant la séance, à relire précisément :**

- Israeli & Goldenfeld (2006), *Coarse-graining of cellular automata, emergence, and the predictability of complex systems*, <https://doi.org/10.1103/PhysRevE.73.026203> : réduction et dynamique macroscopique.
- Costa & de Melo (2020), *Coarse Graining of Partitioned Cellular Automata*, <https://arxiv.org/abs/1905.10391> : cas où une dynamique stochastique apparaît après réduction.
- Domain & Gutowitz (1997), *The Topological Skeleton of Cellular Automaton Dynamics* : graphes et organisation des espaces de transitions.
- Autres notions à explorer : systèmes de transitions abstraits, graphes quotients, dynamique symbolique, *lumpability*, réseaux de transitions d'états et topologie persistante.

La séance n'a **ni démontré ni validé expérimentalement** que ces graphes reconstituent des bassins d'attraction pour Life : c'est une hypothèse de recherche et un programme de visualisation.

## 7. Finalité visuelle, plastique et éventuellement littéraire

L'exploration mathématique n'est pas la seule finalité. Même en l'absence de résultat théorique fort, les graphes réduits pourraient constituer des **artefacts visuels** intéressants. Chercher des productions qui puissent relever de l'art graphique — ou d'une écriture et d'une présentation proches de la littérature scientifique, y compris des **« simili-papiers sérieux »** — tout en restant ancrées dans **un espace de règles et des calculs réels, non imaginaires**.

Le traitement graphique ne doit pas être un simple habillage : faire varier le rendu (disposition du graphe, échelles, codage des poids, regroupement des motifs, sérialisation, animation ou planches imprimables) tout en conservant le lien vérifiable entre **règle, conditions initiales, opérateur de réduction, trajectoire observée, graphe calculé et image produite**. Toute mise en forme spéculative ou littéraire doit être identifiable comme telle, distincte d'une publication scientifique attestant des résultats démontrés.

Ce volet esthétique participe pleinement au cahier des charges : il justifie de soigner les sorties du pipeline et les métadonnées autant que le calcul brut.

## 8. Suites retenues, sans calendrier arrêté

1. Relire les références de caractérisation d'espaces de règles, en particulier Binder (1993), et déterminer si une décomposition voisine du vecteur `(p00,p01,p10,p11)` a déjà été employée systématiquement.
2. Reconstituer/rénover le pipeline pour permettre le branchement de traitements indépendants, dont le calcul des descripteurs de règles et la réduction spatiale.
3. Sur de petits tores, produire **des graphes de transitions réduits** pour plusieurs résolutions et plusieurs opérateurs ; comparer leur stabilité et leurs artefacts.
4. Conserver la dimension **exploratoire et plastique** : produire des images, planches ou documents visuels traçables et reproductibles sans revendiquer prématurément un résultat mathématique.

**Clôture de séance :** plusieurs pistes de travail ont été consignées, sans décision d'implémentation ni engagement sur leur portée scientifique. **Destination du journal : bibliothèque ChatGPT, dossier `Journaux` ; aucune écriture dans le dépôt GitHub.**