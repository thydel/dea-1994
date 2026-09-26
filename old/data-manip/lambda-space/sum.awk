{ sum += $1; ++cnt; }
END { print cnt, sum, sum/cnt; }
