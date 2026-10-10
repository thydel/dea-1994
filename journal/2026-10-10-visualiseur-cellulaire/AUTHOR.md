# Intention de l'auteur

Le moteur historique `cell` a été recompilé récemment et semble
encore utilisable. En revanche, les anciens visualiseurs X11
(`xdump`, `xdump-1`, `xdump-2`, `xdisp` et variantes) affichent du
blanc ou du noir, sans résultat exploitable.

L'objectif immédiat est de retrouver un programme graphique simple,
recevant sur l'entrée standard les images successives produites par
`cell`, afin de relancer les expériences, notamment Life. Les données
semblent être des bits bruts sans en-tête, avec une taille de trame
connue par option. Un pixel par cellule suffit au départ ; un facteur
d'agrandissement optionnel serait utile. Les options historiques
doivent être relues et documentées, sans en deviner la signification.

Un outil existant convient s'il sait lire le flux ; sinon, produire
un petit programme C compatible Debian 12, avec une aide intégrée.
Ne pas moderniser l'ensemble du système pour cette première étape.
Conserver `old/` intact ; mettre les nouveaux sources sous `new/`.
