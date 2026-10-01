# Operational directives — LaTeX reconstruction

This prompt record was reconstructed retrospectively on 2026-10-01 after
Phase 1 had already been executed. The detailed directive below is the
specification that governed that work.

# Spécification Work — modernisation LaTeX, phase 1

Date : 2026-10-01

## But

Reconstruire, à partir des sources LaTeX historiques présentes sous `old/txt/tex/`, une version moderne, simple, maintenable et compilable du mémoire de DEA 1994.

Cette phase ne cherche **pas** à reproduire page par page le PDF historique. Elle ne cherche pas non plus à restaurer les figures. Son objectif est d'obtenir un socle textuel LaTeX fiable sur lequel les phases suivantes pourront travailler.

## Sources de vérité

Ne jamais modifier `old/`.

Utiliser comme sources, par ordre de rôle :

1. les fichiers LaTeX historiques sous `old/txt/tex/` pour le contenu et la structure ;
2. `old/txt/tex/top.log` comme trace d'une compilation historique réussie (27 septembre 1994, 156 pages) et comme inventaire des inclusions réellement utilisées ;
3. `old/DEA-1994.pdf` / `old/txt/tex/top.pdf` comme référence visuelle et documentaire, uniquement lorsqu'une ambiguïté des sources doit être levée ;
4. les fichiers auxiliaires historiques (`.toc`, `.lof`, `.lot`, `.aux`, `.bbl`) comme indices supplémentaires, jamais comme contenu primaire.

## Contraintes de conservation

- Ne pas réécrire, corriger, moderniser ni reformuler le texte scientifique.
- Préserver les équations, notes, citations, labels, références croisées, chapitres, sections, annexes et ordre documentaire.
- Les changements d'encodage ou de syntaxe LaTeX doivent être sémantiquement neutres.
- Conserver les macros qui portent un vocabulaire sémantique utile, ou les réimplémenter avec le même sens. Exemples repérés : `\\arule`, `\\aconcept`, `\\anewterm`, `\\asoft`, `\\avar`, `\\alambda`, `\\xor`.
- Éviter de propager les mécanismes purement techniques de 1994 lorsqu'un mécanisme LaTeX actuel, simple et standard suffit.

## Architecture cible

Créer le nouveau projet sous `new/latex/`.

Architecture souhaitée, à ajuster seulement si une raison technique claire l'impose :

- `new/latex/main.tex`
- `new/latex/preamble.tex` ou un petit fichier de macros clairement identifié
- un fichier source par chapitre/annexe, avec noms explicites
- `new/latex/Makefile`
- `new/latex/README.md`
- sous-répertoire(s) éventuel(s) pour bibliographie et compatibilité temporaire

Le projet doit pouvoir être construit depuis `new/latex/` avec une commande simple, idéalement :

```sh
make
```

et nettoyé avec :

```sh
make clean
```

Préférer une chaîne TeX Live standard disponible sur Debian actuel. Minimiser les dépendances et les documenter précisément.

## Travail demandé

### 1. Inventaire avant modification

Examiner `top.tex`, tous les fichiers qu'il inclut, les styles locaux `Sty/*.sty`, les bibliographies et les inclusions externes.

Classer les éléments historiques en quatre catégories :

A. contenu à préserver ;
B. macro sémantique à conserver/réimplémenter ;
C. mécanisme technique ancien à remplacer ;
D. ressource externe à différer ou à neutraliser en phase 1.

Produire cet inventaire dans `new/latex/README.md` ou dans un fichier d'audit dédié.

### 2. Supprimer la dépendance au format historique

Le projet historique utilisait un format précompilé `mytex` contenant notamment la classe et des packages.

Le nouveau `main.tex` doit déclarer explicitement sa classe et ses packages. Ne pas dépendre de `mytex.fmt`, de formats TeX précompilés privés ni d'une installation TeX historique.

### 3. Moderniser le préambule avec parcimonie

Remplacer les dépendances obsolètes uniquement lorsqu'elles sont nécessaires.

Points déjà identifiés :

- `epsfig` : ne pas en dépendre en phase 1 ;
- `fancyheadings` : remplacer si nécessaire par un mécanisme actuel ;
- `amstex` : utiliser les packages AMS actuels nécessaires ;
- ancien Babel `francais` : utiliser la configuration française actuelle appropriée ;
- `lgrind` / `mygrind.sty` : ne pas en faire une dépendance obligatoire de phase 1 ;
- `greydraft.sty` et ses specials PostScript : supprimer de la chaîne ;
- `long-title-in-toc.sty` modifie directement des internes LaTeX : ne pas reprendre ce patch tel quel ; reproduire son comportement uniquement si nécessaire, avec un mécanisme actuel ou une compatibilité locale clairement commentée.

Ne pas ajouter de packages sans nécessité observée.

### 4. Encodage

Identifier l'encodage réel des sources historiques avant conversion.

Convertir les nouveaux fichiers vers UTF-8 si cela peut être fait sans altérer le contenu. Vérifier les accents, caractères spéciaux, mathématiques et bibliographie.

Ne pas effectuer de substitutions textuelles aveugles susceptibles de modifier la sémantique LaTeX.

### 5. Figures : neutralisation contrôlée

Ne pas restaurer ni convertir les images en phase 1.

Les macros historiques de `fig-cap.sty` encapsulent les figures, légendes, labels et parfois plusieurs images. Réimplémenter une couche de compatibilité minimale qui :

- n'essaie pas de charger les EPS/PS ;
- conserve le numéro de figure lorsqu'il existe ;
- conserve le label ;
- conserve la légende et son texte explicatif ;
- affiche éventuellement un placeholder discret indiquant le ou les fichiers historiques attendus ;
- permet aux `\\ref` / mécanismes équivalents de fonctionner.

Ne pas supprimer simplement les appels aux figures.

### 6. Tables et inclusions de code

Les macros historiques gèrent également des `\\input` de tables sous `../tbl/` et du code sous `../src-txt/`.

Essayer de préserver directement les tables qui compilent sans dépendance problématique.

Pour les inclusions de code incompatibles (notamment dépendance à `lgrind`), créer un mécanisme de compatibilité ou un placeholder conservant au minimum label, légende et nom de la ressource.

Documenter chaque inclusion neutralisée.

### 7. Références croisées

Les macros de `ref-and-cite.sty` constituent une API utilisée dans le texte (`\\mygetref`, `\\mygetfig`, `\\mygettbl`, etc.).

Ne pas remplacer massivement leurs usages dans le corps du mémoire lors de cette phase sauf si cela simplifie clairement le projet sans risque.

Préférer une petite couche de compatibilité moderne reproduisant leur comportement observable.

Après compilation stabilisée, vérifier l'absence de références non définies, sauf éléments explicitement documentés comme différés.

### 8. Bibliographie

Préserver les citations et clés bibliographiques.

Le projet historique utilise plusieurs bases `.bib` et le style `thy`. Déterminer ce qui est disponible et ce qui compile aujourd'hui.

Pour la phase 1, privilégier la solution la moins invasive permettant une bibliographie complète. Ne pas convertir vers une nouvelle technologie bibliographique uniquement par préférence esthétique.

Si le style `thy` est incompatible ou absent, choisir un remplacement temporaire standard et documenter la différence ; ne pas modifier les clés de citation.

### 9. Page de titre et métadonnées

Préserver les informations historiques du document. Ne pas remplacer automatiquement les dates historiques par la date courante.

Si `\\today` dans la source historique produit aujourd'hui une date erronée pour le document de 1994, signaler le problème et choisir une valeur historique seulement si elle peut être établie à partir du dépôt/PDF ; sinon laisser un TODO explicite.

### 10. Boucle de compilation

Itérer jusqu'à obtenir une compilation reproductible.

À chaque erreur :

1. identifier la cause réelle ;
2. préférer la correction locale la plus simple ;
3. éviter les hacks globaux ;
4. recompiler ;
5. continuer jusqu'à stabilisation.

Ne pas considérer le travail terminé dès qu'un PDF est produit : examiner également warnings, références, citations et ressources manquantes.

## Critères d'acceptation de phase 1

La phase est réussie lorsque :

- `old/` est inchangé ;
- tout le nouveau travail est sous `new/latex/` ;
- `make` depuis `new/latex/` produit le PDF principal avec une TeX Live actuelle ;
- aucune figure EPS/PS n'est nécessaire à cette compilation ;
- le texte complet prévu par le document historique est présent ;
- chapitres et annexes sont dans le bon ordre ;
- équations, notes et citations sont conservées ;
- les figures neutralisées gardent légendes, labels et références exploitables ;
- les tables et codes sont soit inclus correctement, soit neutralisés et inventoriés ;
- la bibliographie est générée ou toute limitation résiduelle est précisément documentée ;
- il n'y a pas d'erreur LaTeX ;
- les références/citations non résolues restantes, s'il en existe, sont peu nombreuses, expliquées individuellement et consignées ;
- `README.md` indique les paquets Debian/TeX Live nécessaires et la procédure exacte de construction ;
- un rapport final résume les changements, les écarts intentionnels avec 1994 et les travaux reportés à la phase suivante.

## Hors périmètre

Ne pas, pendant cette phase :

- chercher une identité visuelle page par page avec le PDF de 1994 ;
- convertir/restaurer les EPS/PS ;
- redessiner les figures ;
- réécrire ou corriger le contenu scientifique ;
- « améliorer » la terminologie ;
- refactoriser agressivement les macros utilisées dans le texte ;
- remplacer la bibliographie par une nouvelle architecture sans nécessité ;
- entreprendre la modernisation du code logiciel historique extérieur au document.

## Principe de décision

En cas de choix entre fidélité au mécanisme LaTeX de 1994 et fidélité au contenu du mémoire, préserver le contenu et simplifier le mécanisme.

En cas d'ambiguïté substantielle sur le contenu, ne pas deviner : documenter le point et le comparer au PDF ou demander une décision humaine.

## Livrables

À la fin de la phase 1, fournir au minimum :

- le projet compilable `new/latex/` ;
- le PDF généré ;
- le `Makefile` ;
- le `README.md` avec dépendances, commandes et audit des compatibilités ;
- un inventaire des figures/codes/ressources neutralisés ;
- un bref rapport de validation indiquant les commandes exécutées et les problèmes résiduels.

