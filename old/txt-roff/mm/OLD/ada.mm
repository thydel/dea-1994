.nr Hu 1
.HU "Assistant de la mise en scene"
Synthetiseur des sequences de parametres pour les outils de visualisation,
applique au ray-tracing.
.HU Introduction
Certains  logiciels, surtout ceux trouvable parmis les free software, ne
disposent pas de modules d'animation.  On peut faire des sequences animes
en sauvgardant au fur et a mesure  les images et en variant pour chaque
cadre la position de la camera ou des objets qui le compose. On peut apre`s
construire l'animation avec un autre programme plus spe'cialise'. Me`me si 
c'est le stade primitif de l'animation on peut e'largir un peux la perspective
d'utilisation en de'finissant des primitives filmiques pour cre'er les cadres 
et les effects voulus, en be'ne'ficiant comme c,a de la qualite' des outils 
accessibles.
.P
C'est incomparable plus facile pour l'utilisateur de pouvoir demander a` un
logiciel une pleine vue sur un objet genre: "gros plan sur la tour Eiffel, d'en
bas de la tour, dans une journe'e ensoleille" , que d'approfondir plusieurs semaines
un logiciel pour obtenir ses propres images ou  animations. Il ne faut pas spe'cialement
e^tre un infographiste ou un initie' en informatique pour vouloir se re'jouir dans
la cre'ation  et la pe'rfection de ses propres objects virtuels. Les outilisateurs 
pourront be'ne'ficier des primitives de mouvements de la camera que j'inte'ntionne
a` fabriquer.
.HU Me'thodologie
Une premie`re e'tape dans la re'alisation sera de produire les se'quences de parame'tres
ge'ome'triques capables de concre'tiser les e'le'ments de base d'une grammaire du
language filme'. Plus concret: cre'er un language qui e'xplicitera les mouvements 
de la camera pour des prises du vue pre'cises. Pour tester (dans une premie`re 
approximation) les primitives du langage cre'e je vais m'en servir d'un outil comme x3d
qui assure une re'pre'sentation interne en fil de fer, rapide et e'conomique en moyens
et en temps de calcul. En utilisant ce genre de maquette nomme' "Previews" je peut me
faire une ide'e des mouvements et d'e'chelle pour une future animation.
Dans une se'conde e'tape je vais adapter les primitives pour qu'elles constituent 
l'interface de commande pour un ou plusieurs ray-tracings, dans le but de faciliter
la cre'ation de l'animation des images abstractes ou plus pre`cise, comme les fractals.
.SP 2
.BL
.LI Utilisation
.LI Photore'alisme
.LI Animation
.LE
.HU Bibliographie
.BL
.LI D.Arijon
Grammaire du langage filme'
.LI F.Louguet
Synthe`se d'image sur micro-ordinateur
.LE