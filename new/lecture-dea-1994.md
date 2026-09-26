# Notes de lecture — DEA 1994

Document de travail évolutif pendant la relecture de `old/DEA-1994.txt`.

## Axe de lecture

- reconstruire le modèle conceptuel tel qu'il était formulé en 1994 ;
- distinguer le noyau scientifique des éléments surtout liés au mémoire et à son contexte ;
- examiner particulièrement le paramètre d'enchâssement et son rôle dans l'exploration de l'espace des règles ;
- relever ce que les expériences établissent, suggèrent ou laissent ouvert ;
- ignorer autant que possible les scories de `pdftotext`, notamment les données issues des figures PostScript.

## Premières observations

Le résumé présente le travail comme une tentative assez unifiée d'exploration et de visualisation d'espaces de règles de grande dimension pour les automates cellulaires. Plusieurs niveaux y sont volontairement liés : représentation des lois par tables, moteurs cellulaires, méthodes de réduction et de visualisation, exploration expérimentale de familles de règles, puis recherche de paramètres permettant de structurer l'espace des règles.

Le **paramètre d'enchâssement** est annoncé comme un nouveau paramètre de contrôle de l'échantillonnage des espaces de règles. Il est défini, pour chaque élément du voisinage du réseau d'interconnexion associé à une règle, en termes d'**influence de ce voisin sur la règle**. Le chapitre 3 est explicitement consacré aux outils de quantification de l'espace des règles et à ce paramètre.

À ce stade, cette notion est un axe prioritaire de la relecture, sans encore conclure sur sa portée : il faut retrouver sa définition formelle, la manière dont elle est calculée, sa relation aux paramètres déjà connus à l'époque, et surtout ce qu'elle permet effectivement de discriminer ou d'organiser dans l'espace des règles.

## À examiner pendant la lecture

- définition formelle de l'enchâssement ;
- invariances ou dépendances vis-à-vis du codage des états et du voisinage ;
- lien entre enchâssement, activité/dynamique et transitions observées ;
- statut des résultats sur Anneal et l'idée d'une relative invariance spatio-temporelle des trajectoires associées à une transition de phase ;
- séparation entre les choix d'architecture logicielle dictés par les machines de 1994 et les abstractions qui restent pertinentes indépendamment du matériel.
