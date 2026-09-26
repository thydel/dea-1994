gawk -f diff.awk $1 | sed -e '1s/.*/0/'
