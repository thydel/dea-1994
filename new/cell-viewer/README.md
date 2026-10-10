# Visualiseur cellulaire minimal

Visualiseur C/Xlib pour les trames binaires du pipeline Life
historique. Les sources sous `old/` ne sont pas modifiées. Le choix
est un petit programme X11 : Xlib est disponible sur Debian 12,
et les afficheurs historiques présentent des problèmes de gestion
X11 et de fin de flux qui empêchent leur réutilisation directe.

## Compilation et dépendances

Debian 12 : `build-essential` et `libx11-dev`. À l'exécution, il faut
un serveur X accessible par `DISPLAY` et son autorisation habituelle
(X11 ou XWayland). Aucun serveur Wayland natif n'est implémenté.

Depuis la racine du dépôt :

```sh
make -C new/cell-viewer
# Commande équivalente :
cc -O2 -g -std=c11 -Wall -Wextra -Wpedantic \
  new/cell-viewer/cell-viewer.c -o new/cell-viewer/cell-viewer -lX11
```

## Exécution

Depuis la racine du dépôt, remplacer explicitement l'ancien
afficheur :

```sh
old/cell/src/cell -s 9 -l 1024 -k 0 -e 8 \
  -t old/cell/rule/life.t -f old/cell/frame/random-9-0 \
  | new/cell-viewer/cell-viewer -s 9
```

Ajouter `-z 2` pour agrandir chaque cellule en carré de 2 × 2 pixels.
Le programme affiche chaque trame complète, sans cadence imposée ni
suppression de trames. Le producteur peut être ralenti par le tube.

- `-s N` : côté de `2^N` cellules ; défaut 8 (256), plage 3 à 13.
- `-S N` : côté explicite, multiple positif de 8.
- `-z N` : agrandissement entier positif ; défaut 1.
- `-h`, `--help` : aide.
- `--exit-on-eof` : quitter à EOF plutôt que conserver la dernière
  trame dans une fenêtre réactive.

Le côté agrandi est limité à 8192 pixels. Les options de dimension
successives sont appliquées dans leur ordre. Bit 1 = blanc, bit 0 =
noir. Fermer la fenêtre, `q` ou Échap termine le visualiseur ; fermer
pendant le flux peut provoquer SIGPIPE chez le producteur.

EOF sans données termine avec succès et annonce zéro trame sur
stderr. Une trame finale incomplète n'est jamais affichée : message
sur stderr et code 1. Une erreur de lecture ou d'ouverture X donne
également le code 1 ; des arguments invalides donnent le code 2.
stdout n'est pas utilisé. Les lectures fragmentées sont assemblées ;
les événements X restent traités pendant l'attente des données.

## Format et options historiques vérifiés

`old/cell/src` est un lien vers `src-98`. Le code effectif étudié
est `src-98/cell.c`, avec `extract_lib.c` et les macros de voisinage.
Le moteur lit un octet par cellule dans le fichier initial ; cela
n'est pas le format du flux extrait sur stdout.

Dans `life.sh`, `-s 9` définit le côté à `1 << 9` (512),
`-l 1024` exécute 1024 passages de boucle, `-k 0` émet à chaque
passage, et `-e 8` sélectionne `te[8]`, donc `rextract0` : extraction
du bit 0 de chaque cellule, première cellule au bit de poids faible.
`-t` désigne la table de transition et `-f` l'état initial.
Sans `-c`, le voisinage est `moore-1`. Sans `-o`, la sortie est
stdout.
`-S` du moteur fixe un côté explicite, mais son `-s` non nul prime.
Le saut `-k K` émet une trame puis omet K passages ; `-K` augmente
ce saut après chaque émission. Le moteur n'ajoute pas d'en-tête et
n'émet pas l'état obtenu après la dernière transition.

La première trame est donc l'état initial ; les suivantes sont les
états avant les transitions successives. Chaque trame Life contient
512 × 512 / 8 = 32768 octets. Les cellules sont parcourues par
lignes, de gauche à droite et de haut en bas, sans bourrage de ligne.
Le voisinage boucle aux bords. Le flux se termine après 1024 trames,
soit 33554432 octets. Ce visualiseur n'accepte que ce format compact
LSB ; les extractions 0 à 7 du moteur sont MSB et les sorties sans
extraction ou multibit nécessitent un autre afficheur.

Le moteur historique ne vérifie pas toutes ses lectures, allocations
et écritures. Son fonctionnement ne doit pas être présumé pour un
nouveau jeu de données : contrôler séparément taille et contenu du
flux brut en cas d'image vide ou uniforme.

## Différences avec les afficheurs anciens

Les variantes de `src-98` et leurs homologues de `src.colombie` ont
été consultées. `xdump-1` et `xdump-2` lisent des trames compactes,
avec `-s` comme exposant, `-x` fixant les deux dimensions et `-y`
la hauteur. Ils construisent un `XYBitmap` dont l'ordre des bits
reste celui choisi par Xlib. Ils dessinent avant de lire, sans boucle
d'événements ni vidage explicite après chaque trame. Une fin partielle
passe par une assertion d'affectation (`assert(n = tabsize)`), qui
ne valide pas la taille. `xdump-1 -P` attend via `pause()` après EOF.

`xdump` et `xdump-new` ajoutent plans, extraction, pixmap et mode
synchronisé par Expose ; le réglage explicite MSB est désactivé dans
le code. `xdump-Z8` et `xdump-Z8-new` utilisent des images ZPixmap
8 bits et des visuels/couleurs dédiés, donc un autre format.
`xdisp` et `xdisp+` consomment un octet par cellule ; leur `-s`
est un facteur d'échelle, avec choix de plans et cadence. Ils ne
conviennent pas directement au flux compact de `life.sh`.
Ces observations ne constituent pas un diagnostic expérimental de
chaque ancien binaire sur tous les serveurs X.

Le nouveau programme impose LSB explicitement, règle noir/blanc,
redessine sur Expose, traite fermeture et clavier, valide EOF et
conserve par défaut la dernière trame. Il ne reprend pas les modes
couleur, plans ou historiques de cumul.

## Validation

```sh
# Dépendances de test : python3, xvfb, xauth, x11-apps (xwd)
make -C new/cell-viewer check
```

Les tests lancent un serveur Xvfb isolé et comparent les pixels X11
réels aux motifs attendus. Voir `VALIDATION.md` pour les résultats
et les limites effectivement constatées.
