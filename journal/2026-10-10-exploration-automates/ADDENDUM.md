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
