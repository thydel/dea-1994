# Reconstruction LaTeX du mémoire de DEA (phase 1)

Le contenu provient de `../../old/txt/tex/`, sans modification du
répertoire historique. La reconstruction conserve le texte
scientifique, les équations, notes, citations, légendes, labels et
l'ordre du mémoire. Le projet se compile avec des dérivés PDF locaux
des images PostScript, sans le format privé `mytex`.

## Construction

Sur Debian, dépendances :

```sh
sudo apt-get install make python3 texlive-latex-base texlive-latex-recommended texlive-lang-french lmodern poppler-utils ghostscript
cd new/latex
make
make check
```

`make` produit `main.pdf` par pdfLaTeX, BibTeX puis autant de passes
pdfLaTeX que nécessaire pour stabiliser les fichiers auxiliaires
(limite : huit passes). `make check` vérifie la conservation des
sources, l'ordre des inclusions, les labels et numéros historiques,
les clés bibliographiques, les références, les citations, les tables
et l'absence de chargement EPS/PS ou de `mytex.fmt`. Ce contrôle
comparatif nécessite le dépôt historique ; la construction du PDF
elle-même utilise seulement les fichiers de ce projet et TeX Live.

```sh
make clean
make
make check
```

`make clean` supprime le PDF et les fichiers auxiliaires de
compilation, mais conserve les sources, inventaires et rapports. Les
sorties détaillées des passes sont dans `build-pass-*.txt`,
`build-bibtex.txt`, `main.log` et `main.blg`. `validation.json` est
régénéré par `make check`.

## Organisation et inventaire préalable

| Catégorie | Éléments historiques | Traitement |
|---|---|---|
| A : contenu | `title.tex`, `abstract.tex`, `intro-top.tex`, `intro-part-1.tex`, `intro-part-2.tex`, `obj-space.tex`, `obj-time.tex`, `obj-law.tex`, `rule-space.tex`, `about-anneal.tex`, `conclusion.tex` | Conservés sous `chapters/`. |
| A : annexes | `ann-rules.tex`, `ann-rabbit.tex`, `ann-caw.tex`, `soft-tools.tex` | Conservées dans cet ordre, confirmé par `top.tex` et `top.log`. |
| A : citations et données | `nocite.tex`, `biblio.tex`, les sept bases citées par `biblio.tex` | Conservés ; chemins locaux vers `bib/`. `journal.bib` est disponible sous `Bib/` dans le dépôt historique. |
| A : tables | Dix ressources `.tbl` effectivement utilisées | Copies ordinaires sous `tables/`, y compris le contenu des liens symboliques historiques ; aucune neutralisation. |
| B : vocabulaire | `Sty/simple.sty` | Copie dans `compat/simple.tex` : notamment `arule`, `aconcept`, `anewterm`, `asoft`, `avar`, `alambda`, `xor`. |
| B : références | `Sty/ref-and-cite.sty` | API inchangée dans `compat/ref-and-cite.tex`, sans substitutions dans le corps. |
| B : autres macros | `Sty/email.sty`, `Sty/spl.sty`, `Sty/num-in-bib.sty` | Définitions conservées dans `compat/`. `num-in-bib` est entouré de `makeatletter` ; l'affichage effectif dépend du natbib actuel. |
| B/C : figures | `Sty/fig-cap.sty` | Signatures et construction des labels préservées. Chargeur remplacé par `graphicx` et le manifeste local ; légendes simplifiées dans `compat/phase-one.tex`. |
| C : format | `mytex.fmt`, configuration du Makefile historique | Classe `report` A4 12 pt et packages déclarés explicitement dans `main.tex`/`preamble.tex`. |
| C : mathématiques | `amstex`, `latexsym` | `amsmath`, `amssymb`. |
| C : langue | Babel `francais` | Babel `french` et `texlive-lang-french`, avec césure française. |
| C : en-têtes | `fancyheadings` | `fancyhdr` ; titres courts dans les en-têtes, titres longs au sommaire. |
| C : sommaire | `Sty/long-title-in-toc.sty` | Aucun patch des internes de LaTeX repris. Petits wrappers des commandes publiques de titres pour préserver le comportement utile. |
| C : specials | `Sty/greydraft.sty` | Exclu : pas de special PostScript. |
| D : images | `epsfig`, ressources `../dump/`, `../plot/`, `../fig/` | 88 images réintégrées après conversion mécanique. Chaque occurrence réellement exécutée est consignée par la compilation dans `main.resources` et détaillée dans `RESSOURCES.md`. |
| D : listings externes | `lgrind`, `Sty/mygrind.sty`, `../src-txt/*.tex` | Quatorze listings différés ; légendes, labels et noms conservés. Le code `verbatim` directement présent dans les chapitres est conservé intégralement. |
| C : non requis | `afterpage`, `varioref`, `multicol`, package `verbatim` | Pas de dépendance : pas d'usage actif nécessitant ces packages. La macro de listing à deux colonnes délègue au même placeholder que les autres listings. `verbatim` du noyau suffit. |
| C : style non chargé | `Sty/old.sty` | Anciennes macros non utilisées par la compilation de référence ; non repris. |
| D : documents distincts | `Slide.tex`, `Notes.tex`, `thy-notes*.tex`, `pg-notes.tex`, `fichier-these.tex`, `Keep/` | Hors arbre d'inclusion du mémoire attesté par `top.log` ; non inclus. |

Les autres bases présentes dans `Bib/` (`my-others`, `my-references`,
`my-spl`, `dref`) ne sont pas des dépendances directes de
`biblio.tex`. Le fichier `my-hack.bib`, utilisé historiquement comme
concaténation, est conservé tel quel. Les auxiliaires historiques
servent uniquement de preuves comparatives ; ils ne sont ni copiés
comme contenu principal ni chargés par la construction.

## Encodage et fidélité

Les chapitres utilisent désormais des caractères Unicode UTF-8
littéraux pour la prose, les titres, légendes, notes et métadonnées :
`Université`, `règle`, `façon`, `œuvre`. La directive est consignée
dans `journal/2026-10-01-latex-use-utf8/README.md`.

La conversion concerne 4 895 occurrences dans 14 fichiers. Les seules
normalisations admises par `tex_unicode.py` sont les formes d'accent
inventoriées et le groupe exact `{\oe}`, remplacé par `œ`. Aucun
remplacement global aveugle ni changement de ponctuation n'est
effectué. La validation applique cette normalisation contextuelle aux
sources historiques et aux sources actuelles avant comparaison. Tous
les autres caractères doivent encore correspondre exactement.

Les mathématiques, environnements de code, blocs `verbatim`, arguments
d'identifiants et de ressources, définitions de macros et commentaires
restent exacts. Les 116 occurrences non converties sont inventoriées
dans `journal/2026-10-01-latex-use-utf8/accent-inventory.json` : 115
dans les commentaires et une dans `\text{m\'egaoctets}`, au sein d'une
formule de `intro-part-2.tex`, ligne 367. Les espaces insécables `~`,
coupures explicites `\-` et caractères TeX échappés restent inchangés.

Les macros de compatibilité et les tables ne contenaient pas de formes
d'accent à convertir. Les sept bases bibliographiques, déjà converties
de Latin-1 vers UTF-8 en phase 1, restent inchangées et sont comparées
exactement à leur décodage historique.

Les autres différences dans les sources des chapitres restent les
chemins de l'introduction/bibliographie et la date de titre. `today`
est fixé au 27 septembre 1994, date établie dans `old/DEA-1994.pdf`.
Aucune correction orthographique ou scientifique n'a été faite : les
formulations telles que « Lokta-Volterra » restent celles des sources.

Les scripts de régression et de comparaison du PDF sont dans le
journal :

```sh
python3 journal/2026-10-01-latex-use-utf8/test_normalization.py
python3 journal/2026-10-01-latex-use-utf8/verify_output.py
```

Le contrôle `verify_output.py` appartient à l'étape UTF-8 antérieure ;
il n'est plus un critère du PDF avec images. Ces commandes
s'exécutaient depuis la racine du dépôt. La comparaison du PDF vérifie
le texte extrait avec sa disposition et le rendu de chaque page contre
les empreintes de la version précédant la conversion.

## Figures, tables et code

Les 89 figures numérotées (dont les listings), leurs textes
explicatifs, listes courtes et labels sont conservés. Les labels
`*-section`, posés avant les flottants dans les macros historiques,
restent des références au passage du texte concerné. Les labels des
figures suivent la légende et portent leur numéro. Les appels doubles
conservent les deux noms de ressource et le label composé. Le passage
à la ligne vertical entre deux images devient un paragraphe entre
images ; les proportions sont conservées.

Les tableaux restent de vrais tableaux avec leurs données et légendes.
Les noms `neighburhood-size-{cube,croix,sphere}` sont conservés, ainsi
que les données des cibles des liens symboliques. Les quatorze
listings préformatés `lgrind` sont explicitement différés ; aucun
contenu de listing n'est inventé ou reformulé.

## Bibliographie

Le style privé `thy.bst` est absent du dépôt. La solution temporaire
retenue est BibTeX avec `plainnat`, fourni par TeX Live, et natbib en
mode auteur-année. Les sept bases historiques, les commandes de
citation et les 146 clés de la bibliographie historique sont
préservées ; BibTeX ne signale ni erreur ni warning.

Écarts intentionnels : présentation standard de `plainnat`,
ponctuation, capitalisation des titres selon les règles du style,
prénoms, champs affichés (ISBN/URL), termes de liaison anglais et
absence de la présentation numérotée personnalisée de 1994. Les
chaînes et données originales restent dans les `.bib`. Aucune
migration vers biblatex n'a été entreprise. La récupération éventuelle
du style privé et l'harmonisation visuelle sont reportées à une phase
ultérieure.

## Validation et suite

Voir [VALIDATION.md](VALIDATION.md), `validation.json` et
[FIGURES.md](FIGURES.md). La pagination de 1994 n'est pas un critère.
Les listings et le style bibliographique privé restent différés.

## Réintégration des images

Les 88 appels actifs, répartis dans 75 figures illustrées,
correspondent à 39 PS et 49 EPS existants. L'inventaire préalable
couvre les 2 567 chemins de fichiers de `old/`, y compris les liens.
Le journal historique `top.log` désambiguïse les extensions et les
répertoires ; les chaînes de liens remontent notamment aux arbres de
1993 et 1994. Aucune image active n'est manquante, ambiguë ou
inutilisable. Aucun contenu graphique n'a été redessiné ou inventé.

`figure-manifest.json` consigne les candidats, chemins, liens,
formats, empreintes SHA-256, appels, labels, numéros et conversions.
Les sources exactes sont copiées dans `figures/source/` ; leurs
dérivés sont dans `figures/pdf/`. `figures-map.tex` associe l'API
historique à ces seuls PDF locaux. Les tailles relatives demandées
sont conservées et les images gardent leurs proportions, avec une
hauteur maximale pour laisser place aux légendes et aux textes
explicatifs.

Ghostscript convertit mécaniquement les EPS selon leur boîte déclarée.
Pour les anciens PS, la taille et le décalage sont fixés explicitement
à leur `BoundingBox` historique. La rotation automatique est
désactivée. Les dates et identifiants variables sont omis ; une
seconde conversion vérifie l'identité SHA-256 des 88 dérivés.

```sh
python3 prepare_figures.py --verify-reproducible
make clean
make
make check
```

La préparation et la compilation utilisent les copies locales ; elles
ne lisent pas `old/`. `make clean` supprime aussi les dérivés et leur
marqueur de préparation, puis `make` les recrée automatiquement.
L'import initial explicite `python3 prepare_figures.py --stage` relit
les fichiers historiques sélectionnés et vérifie leurs empreintes ; il
n'est pas nécessaire pour reconstruire le projet fourni.
`figure_inventory.py` est l'outil de l'inventaire initial : le
relancer remplacerait les métadonnées de conversion par un nouvel
inventaire.
