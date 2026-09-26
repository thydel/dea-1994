# The Stock Market BBS  (613)225-9557    24hrs
# 
# This file contains the daily closing prices for the following:
# The dates are 880720-901231
# 
# 
# Golf   - London PM Gold Fix
# Crbz   - Commodity Bureau Index
# Djci   - DJ Commodity Futures Index
# Ffrt   - Federal Funds US Rate
# Dxy-z  - US Dollar Index
# Xrgm   - Exchange Rate - German Mark
# Xrsf   -               - Swiss Frank
# Xrjy   -               - Japanese Yen
# Xrbp   -               - British Pound


#golf
#crbz
#djci
#ffrt
#dxyz
#xrgm
#xrsf
#xrjy
#xrbp

# split the rates file

golf = rates(:,1);
crbz = rates(:,2);
djci = rates(:,3);
ffrt = rates(:,4);
dxyz = rates(:,5);
xrgm = rates(:,6);
xrsf = rates(:,7);
xrjy = rates(:,8);
xrbp = rates(:,9);

# take of the time part of lorentz data

lrtz = [lorentz(:,2)'; lorentz(:,3)'; lorentz(:,4)']';

# skip the firsrt part of time serie and
# make the new serie divisible by 3, because gnuplot
# doesn't like uncomplete line

tmp = tunnel(2048:8191,1);

# make a 3 dimensional set set from the populatuion serie
# obtained from time-tunnel rule, ran on the configuration space
# that, by only filling a random center square for the plane 0,
# was not initialized like suggested by the book \cite{TofMar87}.

tunnel3fold = ncol(tmp, 3);

spitfile = 0;

gsplot set parametric;
gsplot set data style points;
gsplot set xlabel ''
gsplot set ylabel ''
gsplot set zlabel ''
gsplot set title ''
if (spitfile)
	gsplot set output 'tunnel-1.ps'
	gsplot set terminal postcript portrait
endif
gsplot tunnel3fold title 'time tunnel'

# now make a 4 dimensional set and use
# 3/4 of its points to make a new plot

tunnel4fold = ncol(tunnel, 4);
gsplot tunnel3fold title 'time tunnel X 3', tunnel4fold using 1:2:3 title 'time tunnel X 4'
