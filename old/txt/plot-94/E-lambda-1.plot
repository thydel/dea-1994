load 'head.plot'

set title 'lambda et enchassement pour les 59049 CA additif 01U'

plot [0:500] 'Data/tot-01u-E-lambda.data' using 1 title 'lambda' with lines, \
	'Data/tot-01u-E-lambda.data' using 2 title 'enchassement voisins' with lines, \
	'Data/tot-01u-E-lambda.data' using 3 title 'enchassement centre' with lines, \
	'Data/tot-01u-E-lambda.data' using 4 title 'enchassement moyen' with lines, \
	'Data/tot-01u-E-lambda-anneal.show' title 'Anneal position' with lines
