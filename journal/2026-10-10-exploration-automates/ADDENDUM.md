# Complément à la séance du 10 octobre 2026

## Reprise effective des outils

Un nouveau visualiseur a été construit sous `new/` par Codex,
et l'auteur confirme avoir exécuté le pipeline Life avec succès.
Le fonctionnement a été constaté à l'écran ; des mesures
approximatives ont été rapportées : 1024 trames de 256 × 256
en environ 2,3 secondes, et un essai plus long en environ
20 secondes. Il s'agit d'observations de séance, non de benchmarks
reproductibles.

La prochaine étape envisagée, sans commande immédiate, est de
remettre l'ancien code en état de compilation, puis de reconstruire
une chaîne complète en conservant le principe du compilateur.
La précomputation des offsets de voisinage pourrait être faite
à l'initialisation plutôt qu'à la compilation.

## Flux auto-descriptif

Nouvelle piste : préférer à deux canaux séparés un seul flux
contenant un en-tête textuel JSON de taille variable, suivi
de données binaires brutes. Le générateur écrirait l'en-tête
décrivant dimensions, encodage et structure des trames ;
les étapes suivantes liraient cet en-tête, pourraient
l'enrichir, puis traiteraient le flux binaire sans rupture
de synchronisation. Les options propres à chaque composant
resteraient possibles.

Proposition minimale à étudier : une ligne JSON UTF-8
terminée par LF, suivie immédiatement du binaire.
En C, utiliser `getline()` puis `fread()` sur le même
`FILE *` permet de préserver les octets déjà tamponnés.
Prévoir une taille maximale d'en-tête et une définition
explicite de l'ordre des bits et des trames.

Ce format est une hypothèse de conception, pas un protocole
arrêté. Il ne couvre pas à lui seul la communication de
contrôle bidirectionnelle ou les métadonnées produites en
cours de flux.

## Références et outils

L'auteur a installé et examiné `pipexec`, jugé intéressant
mais potentiellement plus élaboré que nécessaire pour le
premier prototype. L'article de P. M. Binder (1993) sur les
automates cellulaires élémentaires a particulièrement retenu
son attention ; lecture détaillée à poursuivre.

## Configuration et ordre des travaux

Précision de l'auteur : l'en-tête n'a pas vocation à transporter
les résultats calculés pendant le flux. Les statistiques ou autres
sorties secondaires peuvent aller dans un fichier distinct, voire
être coordonnées ultérieurement par un outil comme `pipexec`.

Le but premier de l'en-tête JSON est d'éviter la répétition des
arguments communs à chaque étage. Le générateur reçoit les options
de l'expérience, applique ses valeurs par défaut, puis publie
dans l'en-tête les paramètres effectifs : taille, profondeur,
voisinage, format des cellules, etc. Chaque composant les lit
automatiquement ; il peut conserver ou enrichir le descripteur
pour le composant suivant. Les paramètres strictement locaux,
comme le nombre de pixels affichés par bit dans le visualiseur,
restent des options propres à ce programme.

Ordre des travaux envisagé, sans lancement immédiat :

1. Demander à l'agent d'inventorier les sources, bibliothèques et
   outils historiques, puis de remettre en état leur compilation,
   édition de liens et exécution pour constituer une référence
   vérifiable, sans écraser les originaux sous `old/`.
2. Une fois cette base historique fonctionnelle, reconstruire
   progressivement les composants sous `new/`, depuis zéro,
   avec une interface de flux commune `JSON + NUL + binaire`.
3. Étendre les capacités du moteur, notamment la profondeur
   d'état et l'étendue des voisinages, avec une attention
   particulière à la génération de code et aux performances.

Ces points sont des orientations pour un futur journal de travail,
pas une directive à exécuter dès maintenant.

## Positionnement vis-à-vis des bibliothèques existantes

Après un premier survol des bibliothèques et environnements
d'expérimentation cellulaire cités dans les références, l'auteur
les juge intéressants comme points de comparaison, mais
probablement trop généraux et trop riches pour son objectif
immédiat. Le projet privilégie de petits composants spécialisés,
un traitement minimaliste, du code compact et une interface de
pipeline simple. L'optimisation du débit reste une motivation,
sans supposer qu'elle doive être maximale à tout prix.

Ces outils restent dans la bibliographie ; leur adoption n'est
pas prévue à ce stade. Le prochain travail avec l'agent sera
défini ultérieurement, en commençant par récupérer et remettre
en état le reste des sources historiques.
