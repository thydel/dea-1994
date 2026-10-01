# Validation — reconstruction, UTF-8 et images historiques

Validation du 1er octobre 2026 avec pdfTeX 1.40.24 / TeX Live 2022
Debian, BibTeX 0.99d, Python 3.11 et Ghostscript 10.00.0.

## Construction et conservation

```sh
make clean
make
make check
python3 prepare_figures.py --verify-reproducible
```

Une reconstruction après nettoyage convertit les 88 sources locales,
exécute BibTeX et stabilise les auxiliaires en quatre passes pdfLaTeX.
Une construction sans changement est sans effet. Les traces restent
consultables dans `build-pass-*.txt`, `main.log` et `main.blg`.

| Critère | Résultat |
|---|---|
| PDF | 157 pages A4 ; 129 pages avant réintégration. |
| Arbre historique | Aucun changement ni ajout sous `old/`. |
| Texte scientifique | 17 sources actives comparées aux originaux après les seuls ajustements techniques documentés et la normalisation contextuelle UTF-8. |
| Équations, code, identifiants, citations | Conservation exacte ; aucune reformulation. |
| Tables et bibliographie | Comparaison exacte des copies décodées ; dix tables incluses et 146 clés bibliographiques historiques. |
| Labels et numéros | 254 labels avec les numéros historiques identiques. |
| Ordre des listes | 47 entrées au sommaire, 89 figures et 10 tables ; séquences de numéros historiques identiques. |
| Images restaurées | 88 occurrences dans 75 figures illustrées, contre zéro avant cette passe. |
| Images restantes | Zéro manquante, zéro ambiguë, zéro techniquement inutilisable. |
| Listings externes | 14 encore différés ; légendes, labels et code intégré conservés. |
| Dépendances TeX | Les 88 PDF chargés correspondent exactement au manifeste ; aucune lecture de `old/`, EPS/PS ou `mytex.fmt` dans `main.fls`. |
| Empreintes | Sources historiques, copies locales et dérivés vérifiés individuellement par SHA-256. |
| Reproductibilité | Une seconde conversion donne exactement les mêmes 88 empreintes de dérivés. |
| Dimensions | Les dimensions de chaque dérivé correspondent à sa boîte historique ; tolérance de 1,1 point pour l'arrondi des boîtes EPS. |
| Références et citations | Aucune non résolue. |
| Erreurs, warnings, débordements | Aucun dans le journal final, aucun avertissement BibTeX ni conversion Ghostscript. |

`validate.py` maintient les contrôles de conservation et ajoute les
contrôles de provenance, d'empreintes, de dimensions et de chargement
exhaustif des images. Les résultats sont dans `validation.json`.
`RESSOURCES.md` liste les appels exécutés. `FIGURES.md` et
`figure-manifest.json` détaillent l'inventaire préalable et tous les
candidats, liens et sources sélectionnées.

## Contrôle visuel et écarts conservés

Le PDF final est rendu avec Poppler pour inspecter les 157 pages sur
planches de contact et examiner des figures représentatives à plus
haute résolution. Les images raster, tracés et schémas apparaissent
avec leurs proportions et leurs légendes ; aucun chevauchement ou
contenu coupé n'est constaté.

L'inspection initiale a révélé que `EPSCrop` seul ne suffisait pas
pour les PS sans en-tête EPS. La conversion définit désormais
explicitement la taille de page et le décalage selon leur
`BoundingBox`, avec média fixe et rotation automatique désactivée. Il
s'agit de la boîte historique, sans recadrage artistique ni retouche
du contenu.

Les 13 messages `Underfull hbox` concernent l'espacement du texte ou
de la bibliographie. Ils ne sont pas masqués ; leur détail demeure
dans `main.log`. Ils ne signalent aucun débordement ou manque.

La pagination et les empreintes des pages diffèrent nécessairement de
la version avec placeholders. L'ancienne comparaison raster du journal
UTF-8 reste une preuve de cette intervention antérieure ; elle ne
constitue pas un critère de cette réintégration.

La mise en page historique exacte, les 14 listings externes et le
style privé `thy.bst` restent différés. `plainnat` conserve les bases
et clés bibliographiques, avec les écarts de présentation documentés
dans le README. Aucun graphique manquant n'a été inventé.
