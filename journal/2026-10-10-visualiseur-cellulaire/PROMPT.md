---
date: 2026-10-10
model: GPT-6
interface: ChatGPT Voice
role: prompt-author
---

# Directive 1 — Restaurer un visualiseur minimal

## Périmètre

Lire `AGENTS.md`, `old/cell/life/life.sh`, le code effectif de
`cell` et les variantes historiques des afficheurs, en suivant les
liens symboliques éventuels. Relever les options, le format exact de
sortie, l'ordre des bits, le découpage en trames, le comportement en
fin de flux et les dimensions. Ne pas déduire le format du seul script.

Le cas de référence est :

```sh
cd old/cell/life
sh life.sh
```

Le script lance `../src/cell -s 9 -l 1024 -k 0 -e 8` avec
`../rule/life.t` et `../frame/random-9-0`, puis envoie le flux à
`../src/xdump-1 -s 9`. Vérifier la signification de chaque option
dans les sources avant de la documenter.

## Implémentation

Créer sous `new/` un sous-répertoire de sources dédié au visualiseur.
Choisir la solution la plus simple et maintenable : réutilisation
d'un outil existant si compatible, sinon petit visualiseur C avec
une bibliothèque graphique disponible sur Debian 12. Lire le flux
binaire sur stdin sans le modifier. Accepter la dimension et le
facteur d'échelle en options ; prévoir `-h` / `--help`. Afficher les
trames successives, gérer proprement EOF et erreurs de lecture.
Préserver le comportement pixel par cellule par défaut. Ne pas
introduire de protocole de flux nouveau sans nécessité démontrée.

Ne modifier aucun fichier sous `old/`. Fournir une commande de
compilation reproductible et un exemple de pipeline explicite
utilisant le nouveau binaire. Ne pas supposer que l'ancien programme
`cell` est correct : vérifier séparément le flux brut si l'affichage
reste vide ou uniforme. Ne pas confondre l'absence de données avec
un défaut d'affichage.

## Validation et documentation

Compiler sur Debian 12 ou signaler explicitement si cet environnement
n'est pas disponible. Tester d'abord des trames synthétiques de
motifs connus, puis le pipeline Life si le moteur fonctionne. Vérifier
l'alignement des bits, les tailles, l'agrandissement et EOF ; relever
les éventuelles limitations de performances. Documenter les options,
les dépendances, la compilation, l'exécution et les différences
pertinentes avec les anciens afficheurs. Aucun remaniement du moteur,
des règles ou des autres pipelines n'est demandé.

Compléter `DONE.md` selon `AGENTS.md`, avec les tests réellement
exécutés et les problèmes restants. Ne pas modifier `AUTHOR.md` ni
`REVIEW.md`. Ne pas présenter comme vérifié ce qui ne l'a pas été.
