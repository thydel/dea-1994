# Validation du 10 octobre 2026

Environnement : Debian GNU/Linux 12 (bookworm), Xlib 1.8.4.
Compilation C11 avec `-Wall -Wextra -Wpedantic`, sans avertissement.

`make check` a réussi avec Xvfb en profondeur 24 bits. Le sandbox
empêchait initialement la création des sockets X ; les tests ont
ensuite été exécutés hors sandbox avec autorisation.

Tests réalisés dans `test_viewer.py` :

- Images noires, blanches, motif asymétrique aux limites d'octets
  et de lignes, damier ; comparaison des pixels par capture `xwd`.
- Échelles 1 et 3 ; dimensions et chaque pixel agrandi vérifiés.
- Plusieurs trames, lectures fragmentées, conservation à EOF.
- EOF vide et après deux trames, troncature après une trame complète.
- Arguments invalides, aide, affichage inaccessible et vraie erreur
  de lecture via un descripteur de répertoire.
- Audit brut du moteur, indépendamment du visualiseur : statut 0,
  stderr vide, 33554432 octets, exactement 1024 trames.
- Première trame identique au bit 0 compacté du fichier initial.
  Deuxième trame identique à un calcul indépendant Conway Life avec
  bords périodiques, sans utiliser la table historique.
- Pipeline complet du moteur vers le visualiseur ; EOF annoncé après
  1024 trames et pixels de la dernière trame comparés au flux brut.

Les 1024 trames du flux brut sont distinctes. Nombre de cellules
actives des huit premières trames : 130960, 71877, 66393, 65600,
62635, 60771, 58522, 56676. La dernière en contient 10982 ;
le minimum est 10982 et le maximum 130960. Le flux n'est donc ni
absent ni uniforme.

SHA-256 du flux de référence :

```text
505026dcb8451db1134adff024cebc8ab4fa610959c4cbd35a7225cd3006d2f3
```

Le passage complet des tests a pris environ 7 secondes, dont le
calcul Python indépendant. Ce n'est pas un benchmark d'affichage.
Le rendu parcourt tous les pixels agrandis : son coût et la mémoire
croissent avec le carré de l'échelle. XSync à chaque trame peut
limiter le débit sur une connexion X distante. Aucune cadence
interactive ni performance distante n'a été mesurée. La visibilité
humaine de chaque état très bref n'est pas garantie.

La vérification porte sur Xvfb, pas sur une session graphique humaine,
un gestionnaire de fenêtres ou XWayland. Les événements Expose,
fermeture et clavier sont implémentés, mais leur manipulation par
un utilisateur n'a pas été testée. Le moteur n'a pas été recompilé
ni modifié ; le binaire déjà présent a été utilisé. Un seul pas
scientifique a été comparé indépendamment ; cela ne valide pas
l'ensemble des règles ou du moteur historique.
