# Reconstruction LaTeX du mémoire de DEA (phase 1)

Le contenu provient de `../../old/txt/tex/`, sans modification du répertoire
historique. La reconstruction conserve le texte scientifique, les équations,
notes, citations, légendes, labels et l'ordre du mémoire. Le projet se compile
sans accès aux images PostScript ni au format privé `mytex`.

## Construction

Sur Debian, dépendances :

```sh
sudo apt-get install make python3 texlive-latex-base texlive-latex-recommended texlive-lang-french lmodern poppler-utils
cd new/latex
make
make check
```

`make` produit `main.pdf` par pdfLaTeX, BibTeX puis autant de passes pdfLaTeX que
nécessaire pour stabiliser les fichiers auxiliaires (limite : huit passes).
`make check` vérifie la conservation des sources, l'ordre des inclusions,
les labels et numéros historiques, les clés bibliographiques, les références,
les citations, les tables et l'absence de chargement EPS/PS ou de `mytex.fmt`.
Ce contrôle comparatif nécessite le dépôt historique ; la construction du PDF
elle-même utilise seulement les fichiers de ce projet et TeX Live.

```sh
make clean
make
make check
```

`make clean` supprime le PDF et les fichiers auxiliaires de compilation, mais
conserve les sources, inventaires et rapports. Les sorties détaillées des passes
sont dans `build-pass-*.txt`, `build-bibtex.txt`, `main.log` et `main.blg`.
`validation.json` est régénéré par `make check`.

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
| B/C : figures | `Sty/fig-cap.sty` | Signatures et construction des labels préservées. Chargeur d'images remplacé par une mention de ressource ; légendes simplifiées dans `compat/phase-one.tex`. |
| C : format | `mytex.fmt`, configuration du Makefile historique | Classe `report` A4 12 pt et packages déclarés explicitement dans `main.tex`/`preamble.tex`. |
| C : mathématiques | `amstex`, `latexsym` | `amsmath`, `amssymb`. |
| C : langue | Babel `francais` | Babel `french` et `texlive-lang-french`, avec césure française. |
| C : en-têtes | `fancyheadings` | `fancyhdr` ; titres courts dans les en-têtes, titres longs au sommaire. |
| C : sommaire | `Sty/long-title-in-toc.sty` | Aucun patch des internes de LaTeX repris. Petits wrappers des commandes publiques de titres pour préserver le comportement utile. |
| C : specials | `Sty/greydraft.sty` | Exclu : pas de special PostScript. |
| D : images | `epsfig`, ressources `../dump/`, `../plot/`, `../fig/` | Différées. Chaque occurrence réellement exécutée est consignée par la compilation dans `main.resources` et détaillée dans `RESSOURCES.md`. |
| D : listings externes | `lgrind`, `Sty/mygrind.sty`, `../src-txt/*.tex` | Quatorze listings différés ; légendes, labels et noms conservés. Le code `verbatim` directement présent dans les chapitres est conservé intégralement. |
| C : non requis | `afterpage`, `varioref`, `multicol`, package `verbatim` | Pas de dépendance : pas d'usage actif nécessitant ces packages. La macro de listing à deux colonnes délègue au même placeholder que les autres listings. `verbatim` du noyau suffit. |
| C : style non chargé | `Sty/old.sty` | Anciennes macros non utilisées par la compilation de référence ; non repris. |
| D : documents distincts | `Slide.tex`, `Notes.tex`, `thy-notes*.tex`, `pg-notes.tex`, `fichier-these.tex`, `Keep/` | Hors arbre d'inclusion du mémoire attesté par `top.log` ; non inclus. |

Les autres bases présentes dans `Bib/` (`my-others`, `my-references`, `my-spl`,
`dref`) ne sont pas des dépendances directes de `biblio.tex`. Le fichier
`my-hack.bib`, utilisé historiquement comme concaténation, est conservé tel quel.
Les auxiliaires historiques servent uniquement de preuves comparatives ; ils
ne sont ni copiés comme contenu principal ni chargés par la construction.

## Encodage et fidélité

Tous les fichiers `.tex` de l'arbre actif et les styles locaux sont ASCII : leurs
accents sont déjà des commandes TeX. Les copies sont donc également des fichiers
UTF-8 valides, sans conversion des accents ni normalisation du texte. Les bases
bibliographiques contiennent des octets Latin-1 (accents occidentaux) : conversion
ISO-8859-1 vers UTF-8, vérifiée par comparaison caractère par caractère et retour
possible vers les octets d'origine. Les tables sont préservées de la même façon.

Les seules différences dans les sources des chapitres sont les chemins de
l'introduction/bibliographie et la date de titre. `today` devient explicitement
« 27 septembre 1994 », date établie par la première page de `old/DEA-1994.pdf`.
Aucune correction orthographique ou scientifique n'a été faite. Les noms tels
que « Lokta-Volterra » restent ceux des sources.

## Figures, tables et code

Les 89 figures numérotées (dont les listings), leurs textes explicatifs, listes
courtes et labels sont conservés. Les labels `*-section`, posés avant les
flottants dans les macros historiques, restent des références au passage du texte
concerné. Les labels des figures suivent la légende et portent leur numéro.
Les appels doubles conservent les deux noms de ressource et le label composé.
Le passage à la ligne vertical entre deux images devient un paragraphe entre
placeholders : l'ancien `\\` après un placeholder terminé serait invalide.

Les tableaux restent de vrais tableaux avec leurs données et légendes. Les noms
`neighburhood-size-{cube,croix,sphere}` sont conservés, ainsi que les données des
cibles des liens symboliques. Les quatorze listings préformatés `lgrind` sont
explicitement différés ; aucun contenu de listing n'est inventé ou reformulé.

## Bibliographie

Le style privé `thy.bst` est absent du dépôt. La solution temporaire retenue est
BibTeX avec `plainnat`, fourni par TeX Live, et natbib en mode auteur-année.
Les sept bases historiques, les commandes de citation et les 146 clés de la
bibliographie historique sont préservées ; BibTeX ne signale ni erreur ni warning.

Écarts intentionnels : présentation standard de `plainnat`, ponctuation,
capitalisation des titres selon les règles du style, prénoms, champs affichés
(ISBN/URL), termes de liaison anglais et absence de la présentation numérotée
personnalisée de 1994. Les chaînes et données originales restent dans les `.bib`.
Aucune migration vers biblatex n'a été entreprise. La récupération éventuelle du
style privé et l'harmonisation visuelle sont reportées à une phase ultérieure.

## Validation et suite

Voir `VALIDATION.md`, `validation.json` et `RESSOURCES.md`. La comparaison ne vise
pas la pagination de 1994 : les images absentes, listings différés, polices et
mécanismes de flottants modernes modifient volontairement les sauts de page.
La restauration des images EPS/PS, des listings et de la mise en page historique
reste hors périmètre de la phase 1.
