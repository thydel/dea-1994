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

## Articulation avec le projet actuel

La section `Supplementary info` ajoutée au `README.md` donne le contexte postérieur au DEA. Il faut conserver une séparation explicite entre :

1. **le travail de 1994**, qui fournit notamment des outils de représentation, d'exploration et de filtrage statique de l'espace des règles, avec l'enchâssement comme piste centrale ;
2. **les développements et intuitions postérieurs**, notamment l'étude des bassins d'attraction et la réduction par quotient des translations spatiales ;
3. **le nouveau projet**, qui pourrait articuler un tamis statique, des simulations dynamiques légères, puis une analyse plus coûteuse des bassins sur les règles retenues.

La relecture ne doit donc pas projeter rétrospectivement le projet actuel dans le mémoire. Elle doit au contraire déterminer ce qui était effectivement formulé ou expérimenté en 1994, puis identifier les continuités avec les idées apparues ensuite.

## Un autre objet de la relecture : retrouver les intuitions

Le mémoire est également une trace des intuitions de l'époque et de leurs limites de formalisation. Il est utile de distinguer :

- une idée ou une observation effectivement présente ;
- sa formulation parfois empirique ou insuffisamment mathématisée ;
- les limites imposées par l'outillage informatique et la puissance de calcul de l'époque ;
- les questions qui auraient demandé des outils mathématiques supplémentaires.

L'objectif n'est donc pas d'évaluer rétrospectivement le texte selon le niveau de formalisation disponible aujourd'hui, mais de reconstruire les questions qui étaient réellement posées. Dans une étape ultérieure, certaines intuitions pourront être reformulées avec des outils mathématiques contemporains, confrontées à la littérature et transformées en expériences calculables, sans présumer qu'elles sont correctes.

## À examiner pendant la lecture

- définition formelle de l'enchâssement ;
- invariances ou dépendances vis-à-vis du codage des états et du voisinage ;
- lien entre enchâssement, activité/dynamique et transitions observées ;
- statut des résultats sur Anneal et l'idée d'une relative invariance spatio-temporelle des trajectoires associées à une transition de phase ;
- séparation entre les choix d'architecture logicielle dictés par les machines de 1994 et les abstractions qui restent pertinentes indépendamment du matériel.

## Point d'étape — 26 septembre 2026

Le mode de travail retenu est incrémental : lecture du matériau ancien, ajout de blocs cohérents dans ce fichier, puis discussion avant d'approfondir les axes les plus prometteurs. Ce document doit rester utilisable comme état intermédiaire si la session est interrompue.

À ce point, le principal axe scientifique identifié reste l'enchâssement : il faut maintenant passer du résumé et des intentions à la définition précise et aux expériences du chapitre correspondant. Le contexte ajouté au README indique en parallèle pourquoi cette relecture est utile au projet actuel, mais ces éléments postérieurs seront traités comme contexte et non comme résultats du DEA.
