load 'head.plot'

set title 'distribution prob. de lambda et prob. de flip'

plot 'Data/lambda-prob-sort.data' title 'sorted lambda prob.' with lines, \
	'Data/flip-prob-sort.data' title 'sorted flip prob.' with lines
