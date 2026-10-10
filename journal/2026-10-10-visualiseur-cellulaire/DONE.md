---
date: 2026-10-10
model: GPT-6
interface: Codex
role: implementer
---

# Exécution de la directive 1

Lecture de `AGENTS.md`, du journal complet, du script Life et des
sources effectives derrière `old/cell/src -> src-98`, y compris les
extractions et les variantes des afficheurs historiques.

Création de `new/cell-viewer/` : programme C/Xlib, Makefile, aide,
options de dimension et d'agrandissement, boucle d'événements,
assemblage des lectures, gestion des erreurs et EOF. La dernière
trame reste visible par défaut ; `--exit-on-eof` permet de quitter.
Le format compact LSB du pipeline est préservé, sans en-tête ajouté.
Aucun fichier historique n'a été modifié.

Compilation sur Debian 12 sans avertissement. Tests synthétiques
réussis avec comparaison des pixels X11 sous Xvfb, puis audit brut
et pipeline Life complet réussis. Le moteur a produit 1024 trames
complètes et distinctes ; son premier pas correspond à un calcul
Conway indépendant. Les tests Xvfb ont nécessité une exécution hors
sandbox, autorisée après l'échec de création des sockets locales.

Documentation et commande de pipeline dans
`new/cell-viewer/README.md`. Résultats détaillés et limites dans
`new/cell-viewer/VALIDATION.md`. Tests reproductibles dans
`new/cell-viewer/test_viewer.py` via `make check`.

Limites restantes : pas de test humain dans une session graphique,
pas de benchmark distant, pas de validation scientifique exhaustive
ni de recompilation du moteur. Les formats multibit et MSB sont hors
périmètre. `AUTHOR.md`, `PROMPT.md` et `REVIEW.md` sont inchangés.
