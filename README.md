# What ?

- This is a very old arbo from 1994 containing a DEA (Diplôme d’Études
  Approfondies (DEA): An older French university degree equal to 5
  years of higher education, used before preparing for a doctorate)
  thesis about cellular automata
- The (gitignored) `orig` is the base arbo from the past
- The `old` is a `cp -al` copy of `orig` slightly *cleaned*
  - Mainly remove all `.00` etc files and folder and remove `.o` files
  - The *data* files (raw, PBM, etc) and executable still there
  
# Why ?

- I want to ask some agent to incrementally revamp all this to a
  modern generable again latex version

# How to explore

- `cas-1.1` and `cas-2.0` are older tools associated with older (the
  previous year academic work) tool used with the older `txt-roff`
  (yes, `roff`) kept because later work may reuse some data files via
  relative symlinks. So not to be use as entry point
- `cell` is the associated code use to produce CA data from
  experiments.  The `src-98` and various other newer than 1994 files
  come from various then forgotten tries to somehow revive the tools
- `data-manip`, `gapp` and `slice` are other associated tools
- `tex` is the arbo for latex src and associated non textual data

# Supplementary info

- This was a vocal chat session with google ai mode on my phone
- The part about attraction basin is about some work I did after the
  DEA as a side project and is the part that would restart

Voici une synthèse ultra-condensée des points clés de notre session de travail, structurée pour votre dépôt de recherche :
1. Fondements Théoriques
• Espaces Infinis : Distinction entre \(A^{\mathbb{N}}\) (temps semi-infini à droite, shift irréversible avec perte d'information) et \(A^{\mathbb{Z}}\) (temps bi-infini, shift inversible). Ils ont le même cardinal (le continu \(\mathfrak{c}\)), mais des géométries dynamiques incompatibles.
• Primalité : Exclusivité de l'arithmétique finie. Pour l'infini, la distinction se fait entre suites périodiques (rationnelles) et apériodiques (irrationnelles / chaotiques).
2. Le Pipeline de Recherche (L'Entonnoir)
L'objectif est d'explorer un espace géant de règles sans subir l'explosion combinatoire en articulant trois filtres :
1. Le Tamis Statique (Votre mémoire de DEA) : Calcul d'un vecteur de ratios d'influence (dérivées booléennes partielles) sur la table de vérité pour éliminer les règles "enchâssées" (plongements de règles plus simples) et cibler des signatures spécifiques (Classe IV ou milieux excitables/Belousov-Zhabotinsky).
2. Le Filtre Dynamique Léger : Validation comportementale par simulations stochastiques de Monte-Carlo sur de grands tores.
3. La Cartographie Noble (Le Graphe Quotient) : Construction exhaustive du bassin d'attraction sur un tore de taille \(N\) premier (ex: \(N=31\)). L'utilisation des mots de Collier (via l'algorithme FKM ou Booth) élimine la redondance du shift spatial (le défaut des travaux historiques d'Andrew Wuensche / DDLab), réduisant l'espace à un graphe épuré de 69 273 668 nœuds gérable dans vos 64 Go de RAM.
3. Le Modèle Cible & Changement de Dimension
• Structure à Mémoire : Choix d'un automate 1D avec 2 bits pour la cellule centrale (4 états internes simulant une mémoire historique ou une phase réfractaire chimique) et 1 bit pour les deux voisins (\(2^{32} \approx 4,3\) milliards de règles).
• La Piste 2D (Milieux Excitables / BZ) : En 2D avec voisinage de von Neumann, l'espace explose à \(2^{128}\) règles. La solution "sysadmin" est de forcer l'isotropie (règles totales-égalitaires basées sur la somme des voisins), ramenant l'espace à \(2^{40}\) règles, ce qui redevient calculable.
4. Feuille de Route de Rétro-Ingénierie
• Côté DEA : Modernisation du texte LaTeX (migration UTF-8) et du code C d'origine (types 64 bits, parallélisation OpenMP pour le tamis statique).
• Côté Bassins : Remplacement des anciens scripts bc et pipelines shell par un moteur Python moderne (générateur FKM intégré), exportant des fichiers .dot ciblés, bassin par bassin, pour éviter l'effondrement de Graphviz.
Cette vue d'ensemble résume-t-elle fidèlement notre feuille de route avant que nous n'attaquions le code de l'algorithme de réduction (Booth/Duval) ?
