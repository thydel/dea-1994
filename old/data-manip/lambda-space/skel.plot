# WARNING in data file col 1 is line number
set data style lines

#'data' using 1 title 'one', \
#'data' using 2 title 'flip', \
#'data' using 3 title 'one_diff', \
#'data' using 4 title 'flip_diff', \
#'data' using 5 title 'one_ratio', \
#'data' using 6 title 'flip_ratio', \
#'data' using 7 title 'one_ratio_diff', \
#'data' using 8 title 'flip_ratio_diff', \
#'data' using 9 title 'one_prob', \
#'data' using 10 title 'flip_prob', \
#'data' using 11 title 'one_prob_diff', \
#'data' using 12 title 'flip_prob_diff', \
#'data' using 13 title 'one_hist', \
#'data' using 14 title 'flip_hist', \
#'data' using 15 title 'one_hist_ratio', \
#'data' using 16 title 'flip_hist_ratio', \
#'data' using 17 title 'sum_ratio', \

plot \
[0:8] \
'data' using 13 title 'one_hist', \
0 with dots
