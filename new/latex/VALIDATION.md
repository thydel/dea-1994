# Rapport de validation — phase 1 et sources UTF-8

Validation effectuée le 1er octobre 2026 avec pdfTeX 1.40.24 / TeX
Live 2022 Debian, BibTeX 0.99d et Python 3.11. Les dépendances sont
des paquets standards Debian ; `texlive-lang-french`, absent
initialement, a été installé pour la césure et la typographie
françaises. Aucun format privé n'est utilisé.

## Commandes et résultat

Depuis `new/latex/` :

```sh
make clean
make
make check
```

La construction complète après nettoyage se stabilise en quatre passes
pdfLaTeX et une exécution de BibTeX. Les constructions incrémentales
déjà stabilisées demandent deux passes. `make` est sans effet si les
sources n'ont pas changé.

| Critère | Résultat |
|---|---|
| Sources historiques | `git diff --exit-code HEAD -- old` vide ; aucun ajout sous `old/`. |
| Localisation des livrables | Tout le nouveau projet et ses rapports sous `new/latex/`. |
| PDF principal | `main.pdf`, 129 pages A4. |
| Texte complet | Comparaison des 17 sources actives après les transformations techniques documentées et normalisation contextuelle des accents en prose ; tout autre contenu reste exact. |
| Ordre | Titre, résumé, sommaire, introduction, espace, temps, lois, espace des règles, Anneal, conclusion, annexes A/B/C/D, listes des figures/tables, bibliographie. |
| Macros sémantiques | Définitions conservées, comparaison exacte de cinq fichiers de compatibilité. |
| Équations, notes, citations | Équations et identifiants conservés exactement ; prose comparée après normalisation des accents. |
| Labels | 254 labels, identiques aux auxiliaires de 1994, avec exactement les mêmes numéros. |
| Sommaire | 47 entrées, même nombre que le sommaire historique ; titres longs conservés. |
| Figures | 89 figures numérotées, même nombre que la liste historique ; légendes, textes explicatifs et références conservés. |
| Images différées | 88 occurrences, dont les composants des figures doubles ; toutes inventoriées avec ressource, label, numéro et ligne d'appel. |
| Code externe différé | 14 listings `lgrind`, tous inventoriés ; noms, légendes et labels conservés. |
| Code intégré | Tous les blocs `verbatim` du corps sont conservés. |
| Tables | 10 tableaux avec données, labels et légendes ; tous réellement chargés par TeX et comparés aux sources. |
| Bibliographie | BibTeX exécuté sur les sept bases historiques ; 146 clés, exactement le même ensemble que `top.bbl`. |
| Références/citations non résolues | Aucune. |
| Erreurs ou warnings de packages | Aucun dans le journal final ; aucun warning BibTeX. |
| Débordements/glyphes absents | Aucun `Overfull`, aucun `Missing character`. |
| Indépendance des ressources historiques | Le fichier recorder `main.fls` ne contient ni lecture de `old/`, ni EPS/PS, ni `mytex.fmt`. |

Les vérifications automatisées sont dans `validate.py`. Les résultats
chiffrés sont dans `validation.json`. `inventory.py` régénère
`RESSOURCES.md` à partir des appels exécutés ; aucune image n'est
chargée pour produire cet inventaire.

## Contrôle visuel

Le PDF final a été rendu avec Poppler
(`pdftoppm -r 45 -png main.pdf ...`) : inspection d'ensemble de chaque
page sur planches de contact, puis inspection plus détaillée de pages
représentatives (titre, tables et annexes). Aucun texte coupé,
chevauchement, table débordante ou glyphe manquant observé. Les sauts
de page, en-têtes, numérotation romaine/arabe et transitions d'annexes
sont cohérents. Le texte extrait par `pdftotext` contient les accents,
la date historique et la bibliographie, sans marqueur de référence
`??` ni caractère de remplacement.

## Messages résiduels

Le journal final contient 14 messages `Underfull hbox`, concernant
l'espacement horizontal de quelques paragraphes du texte et de la
bibliographie. Ils ne signalent ni contenu manquant ni débordement ;
la lecture reste correcte. Ils n'ont pas été masqués par modification
des seuils du journal. Leur détail reste disponible dans `main.log`
après construction.

Aucune référence, citation ou ressource nécessaire à la compilation ne
reste non résolue. Les ressources différées sont explicitement
présentées comme telles, avec tous leurs labels et légendes ; elles
sont la limitation prévue de phase 1.

## Écarts intentionnels et travaux reportés

- La pagination passe de 156 pages dans la compilation historique à
  129 pages. La reproduction page par page n'est pas recherchée ;
  images et listings externes sont remplacés par des mentions de
  ressource, et les légendes utilisent une mise en page simple sans
  les boîtes historiques.
- Le format privé `mytex`, les specials PostScript, `epsfig`, `lgrind`
  et les anciennes modifications des internes de LaTeX sortent de la
  chaîne de construction.
- La police Latin Modern assure une sortie vectorielle lisible ; Babel
  et les packages AMS actuels remplacent les mécanismes anciens.
- La date du titre est fixée au 27 septembre 1994, établie dans le PDF
  historique, au lieu d'afficher la date de la machine.
- Le style bibliographique `thy` est absent ; `plainnat` est un
  remplacement temporaire documenté dans le README. Les données et
  clés sont conservées ; la présentation, les champs affichés et la
  capitalisation dépendent du style.
- La restauration EPS/PS, la réintégration des listings et la
  récupération du style bibliographique privé sont reportées. Aucune
  modernisation du logiciel historique extérieur au mémoire ni
  reformulation scientifique n'a été entreprise.

Les critères d'acceptation de la phase 1 sont satisfaits avec ces
neutralisations expressément prévues par la spécification.

## Validation supplémentaire — Unicode littéral

La directive UTF-8 du 1er octobre 2026 a été exécutée après inventaire
des contextes. Elle remplace 4 895 formes d'accent ou de ligature dans
14 fichiers de chapitres. Les 116 formes volontairement conservées
sont 115 occurrences de commentaire et `\text{m\'egaoctets}` dans une
expression mathématique. Bibliographie, tables, macros, code,
identifiants et ressources restent inchangés.

La vérification de conservation n'a pas été retirée. `tex_unicode.py`
normalise seulement les formes de prose équivalentes. Les tests de
régression vérifient aussi que des modifications d'équation, de label,
de clé de citation ou de texte scientifique sont toujours rejetées.

Commandes supplémentaires depuis la racine du dépôt :

```sh
python3 journal/2026-10-01-latex-use-utf8/test_normalization.py
python3 journal/2026-10-01-latex-use-utf8/verify_output.py
```

Les cinq tests passent. Après `make clean`, `make` et `make check`, le
PDF reste à 129 pages, avec 254 labels, 146 clés bibliographiques et
les mêmes 14 messages d'espacement `Underfull hbox`. Aucune erreur,
référence ou citation non résolue, ni caractère manquant n'est apparu.

Le texte extrait par `pdftotext -layout` est strictement identique à
celui de la version précédant la conversion. Les empreintes PNG des
129 pages rendues par Poppler à 45 dpi sont également identiques. Ces
résultats sont consignés dans le journal, avec `baseline.json` et
`output-validation.json`. Le PDF produit conserve donc le contenu et
la mise en page ; seule la représentation des accents dans les sources
change.
