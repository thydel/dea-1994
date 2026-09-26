load 'head.plot'

set title 'distribution de lambda et de flip'

plot 'Data/lambda-ratio-sort.data' title 'sorted lambda ratio.' with lines, \
	'Data/flip-ratio-sort.data' title 'sorted flip ratio.' with lines
