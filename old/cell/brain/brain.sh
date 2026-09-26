#cell -l 32 -h hist.out -u sum.out -n cnt.out -s 8 -c moore-2 -t cellsim/Rules/brain.m4 -f frame/random-0-1 -e 8 | xdump-1 -s 8
../src/cell -l 256 -h brain-hist.out -s 8 -c moore-2 -t cellsim/Rules/brain.m4 -f frame/random-0-1 -e 8 | ../src/xdump-1 -s 8
