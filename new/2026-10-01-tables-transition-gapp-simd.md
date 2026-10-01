# Complément — tables de transition, GAPP et machine SIMD virtuelle

## Objet

Ce document complète l’analyse du mémoire en isolant une direction qui avait été insuffisamment prise en compte : l’usage des tables de transition non seulement comme représentation efficace d’une loi d’automate cellulaire, mais comme matériau de construction d’une architecture de calcul. Le mémoire va jusqu’à établir une correspondance explicite entre fonction de transition et machine SIMD, puis à montrer sur le processeur cellulaire GAPP comment une architecture de PE peut être compilée en tables et exécutée par le moteur cellulaire.

## 1. Le point de départ : la table comme représentation de fonction

Le mémoire choisit l’accès par table comme mécanisme d’invocation de la fonction de transition. Le voisinage est converti en index ; le nouvel état est obtenu par un accès indirect à la table. Ce choix dissocie la spécification de la fonction de son coût d’exécution : la fonction qui produit la table peut être écrite sans contrainte forte de performance, puisque son résultat est ensuite matérialisé.

La conséquence importante est conceptuelle : une loi devient un vecteur manipulable. Elle peut être transformée, mesurée, mutée, croisée, importée ou réordonnée. L’exemple de la table provenant de `cellsim`, convertie par permutation des entrées après identification de l’ordre de l’index, montre déjà que le code source original de la loi n’est pas indispensable : la table est elle-même une représentation complète du comportement local.

## 2. Équivalences de représentation : code, table et automate

Cette partie du mémoire met en pratique plusieurs changements de représentation d’un même calcul :

- une fonction écrite sous forme de code peut être évaluée exhaustivement pour construire sa table ;
- une table peut être réindexée lorsque deux systèmes utilisent des conventions différentes pour le codage du voisinage ;
- une table peut être vue comme un arbre de décision puis comme un automate fini déterministe (DFA), avec possibilité de minimisation ;
- une architecture de processeur élémentaire peut être décrite déclarativement, interprétée par une fonction relativement directe, puis cette fonction peut à son tour être tabulée.

Il ne s’agit donc pas seulement d’optimisation. Le travail établit une circulation entre représentations : spécification déclarative → code d’interprétation → table exhaustive → éventuellement automate de décision. La table sert de forme intermédiaire exécutable.

## 3. Composition des tables : chemins de données

La section « Composition : les chemins de données » est centrale. Plusieurs tables peuvent partager un même espace et être combinées spatialement ou temporellement. Le réseau d’interconnexion indique quels bits des cellules alimentent l’index et quels bits reçoivent le résultat.

Le mémoire distingue notamment :

- des tables disjointes, applicables en parallèle lorsque leurs bits cibles sont disjoints ;
- des tables non disjointes, qui permettent la transmission d’information entre sous-systèmes ;
- le séquencement temporel de plusieurs tables ;
- la composition de fonctions en parallèle sur le même espace ;
- le mélange de tables, qui échange davantage de mémoire contre moins de calcul ;
- l’opération inverse envisagée, la séparation, destinée à rechercher si une fonction complexe possède des primitives plus petites.

L’idée d’un arbre de composition est explicitement évoquée : les résultats intermédiaires d’une table pourraient devenir des entrées d’une autre. On quitte alors le simple modèle « une règle = une table » pour aller vers un graphe de chemins de données constitué de lookup-tables.

## 4. Réductions et accumulateurs : élargissement du modèle

Le mémoire explore aussi des fonctions d’application qui ne se limitent plus à concaténer les bits du voisinage. Une réduction associative peut être pipelinée : l’exemple développé est la somme des cellules voisines, qui remplace une table exponentielle en la taille du voisinage par un calcul local de somme suivi d’une table beaucoup plus petite.

Une table binaire peut également être utilisée comme accumulateur. Le texte propose même d’utiliser la machinerie cellulaire « à son propre service » : une variable scalaire spéciale devient cible d’une table, et le séquenceur applique cette table sur l’espace pour réaliser une réduction.

Cette généralisation est importante pour la lecture actuelle du travail : le moteur n’est déjà plus seulement un simulateur d’automates cellulaires. Il devient un moteur de chemins de données discrets, composé de petites fonctions tabulées, de connexions, d’accumulateurs et d’un séquenceur.

## 5. Le cas GAPP : compiler une architecture SIMD en table

Le cas GAPP rend cette idée concrète.

Le mémoire décrit d’abord le PE GAPP par des champs de bits : entrées, sorties, instruction, registres et éléments externes. Une fonction `gapp_pe` implémente ensuite presque directement le mapping de la spécification architecturale. Cette fonction est évaluée pour toutes les combinaisons d’entrées afin de fabriquer `pe_tab`.

Autrement dit, une description d’architecture devient une fonction, puis la fonction devient une table de transition.

Le texte formule alors explicitement l’équivalence :

- la cellule d’espace correspond à la mémoire locale d’un PE ;
- la table de transition correspond au PE ;
- le réseau d’interconnexion correspond aux liens entre PE ;
- la fonction d’application est la machine qui transporte les bits entre mémoire et PE.

La section 2.3.6 en tire directement la notion de « machine virtuelle » et pose le problème de la compilation d’architectures SIMD vers une architecture cellulaire presque pure.

## 6. Le « gap NCR » et ce que fait réellement le mémoire

Le schéma matériel du PE GAPP est repris de la documentation NCR de 1985. Le travail ne se contente cependant pas de reproduire cette architecture. Il reconstruit les chemins de données utiles à l’exécution, isole la partie déclarative de l’architecture, écrit un modèle fonctionnel du PE, puis transforme exhaustivement ce modèle en table.

C’est précisément là que se situe le passage intéressant entre la documentation NCR et le moteur développé dans le mémoire : ce qui est câblé dans le composant réel devient une description de champs et de chemins de données, puis une fonction, puis une lookup-table exploitable par une machine cellulaire générale.

La différence entre l’architecture physique et sa réalisation tabulaire est donc volontaire. Les contraintes matérielles du GAPP réel ne sont plus les contraintes de la machine virtuelle. Le mémoire insiste sur le fait qu’une architecture virtuelle peut être très spécialisée et ne pas être universelle, contrairement à un processeur SIMD matériel destiné à des usages généraux.

## 7. Lecture rétrospective : vers un pseudo-processeur SIMD à tables

Relu aujourd’hui, ce passage suggère une direction distincte mais cohérente avec le reste du mémoire : construire un processeur virtuel SIMD spécialisé dont les unités fonctionnelles sont des tables de transition.

Le modèle minimal serait constitué de :

1. plans de données représentant les registres distribués des PE ;
2. petites lookup-tables représentant ALU, multiplexeurs ou opérations élémentaires ;
3. descriptions déclaratives des connexions entre bits ;
4. un séquenceur sélectionnant les chemins de données et les tables à appliquer ;
5. éventuellement des accumulateurs et réductions ;
6. un mécanisme de fusion de plusieurs tables lorsque le compromis mémoire/calcul le justifie.

La « programmation » d’une telle machine ne consisterait donc pas principalement à exécuter des instructions scalaires sur chaque cellule. Elle consisterait à configurer et séquencer des transformations tabulées appliquées uniformément à des plans de données — d’où la parenté avec un SIMD, même si l’exécution physique reste SISD sur la machine hôte.

## 8. Intérêt pour la simulation d’automates

Pour les automates cellulaires, cette architecture présente une propriété intéressante : le même mécanisme sert à décrire l’automate simulé et la machine qui l’exécute.

Une règle simple peut être une table unique. Une règle complexe peut devenir un réseau de petites tables. Un PE programmable peut lui-même être compilé en table. Enfin, le séquenceur permet de faire circuler les résultats entre ces tables.

Cela ouvre deux axes d’expérimentation :

- **axe automate** : rechercher des décompositions efficaces d’une fonction de transition complexe en primitives tabulées ;
- **axe architecture** : rechercher une petite machine SIMD virtuelle dont le jeu de chemins de données est particulièrement adapté à une famille d’automates.

Le mémoire contient donc déjà les briques conceptuelles d’un « processeur pour automates » construit non autour d’un jeu d’instructions classique, mais autour de compositions de tables.

## 9. Ce qui relève du mémoire et ce qui constitue une extension

Il faut néanmoins séparer les deux niveaux.

Le mémoire démontre concrètement la tabulation du PE GAPP, décrit la composition et le mélange de tables, introduit les chemins de données, les accumulateurs et le séquencement, et affirme l’équivalence entre fonction de transition et machine SIMD.

En revanche, l’idée d’en faire aujourd’hui un projet autonome de pseudo-processeur SIMD générique à lookup-tables, avec un modèle explicite de compilation et un langage de description de chemins de données, est une extrapolation. Elle est fortement préparée par le mémoire, mais elle n’y est pas développée comme architecture indépendante complète.

## Conclusion

Cette partie du travail est moins périphérique qu’elle ne paraît. Elle révèle un second projet contenu dans le mémoire : derrière l’environnement de simulation d’automates cellulaires se trouve l’esquisse d’une architecture virtuelle où calcul, interconnexion et contrôle peuvent être représentés et recombinés sous forme de tables.

Le cas GAPP joue le rôle de preuve de concept : une architecture SIMD matérielle documentée par NCR est reformulée comme spécification déclarative, exécutée par un modèle fonctionnel, puis compilée en lookup-table. La composition de telles tables fournit ensuite naturellement les briques d’un moteur de calcul spécialisé.

C’est une direction différente de la remise en état historique du Workbench, mais elle pourrait aujourd’hui être isolée beaucoup plus proprement : petit moteur de tables, description déclarative des chemins de données, séquenceur, puis compilation de quelques architectures ou règles d’automates comme cas d’essai.
