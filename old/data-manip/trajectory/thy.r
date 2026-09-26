format(10);

load("src/thylib.r");

"hist-7"
read("hist/anneal-size=7");
r7norm=r7/(128^2);
r7d0=r7norm[2:size(r7)[1]-1;1];
r7lin=linspace(0,1,r7d0.nr);
r7d0lin=[r7lin;r7d0']';
r7d1=r7norm[2:size(r7)[1]-1;2];
r7d2=r7norm[2:size(r7)[1]-1;3];
r7d2lin=[r7lin;r7d2']';
r7d2log=log(r7d2);
r7d2loglin=[r7lin;r7d2log']';
r7d2d0=r7d2./r7d0;

"hist-8"
read("hist/anneal-size=8");
r8norm=r8/(256^2);
r8d0=r8norm[2:size(r8)[1]-1;1];
r8lin=linspace(0,1,r8d0.nr);
r8d0lin=[r8lin;r8d0']';
r8d1=r8norm[2:size(r8)[1]-1;2];
r8d2=r8norm[2:size(r8)[1]-1;3];
r8d2lin=[r8lin;r8d2']';
r8d2log=log(r8d2);
r8d2loglin=[r8lin;r8d2log']';
r8d2d0=r8d2./r8d0;

"hist-9"
read("hist/anneal-size=9");
r9norm=r9/(512^2);
r9d0=r9norm[2:size(r9)[1]-1;1];
r9lin=linspace(0,1,r9d0.nr);
r9d0lin=[r9lin;r9d0']';
r9d1=r9norm[2:size(r9)[1]-1;2];
r9d2=r9norm[2:size(r9)[1]-1;3];
r9d2lin=[r9lin;r9d2']';
r9d2log=log(r9d2);
r9d2loglin=[r9lin;r9d2log']';
r9d2d0=r9d2./r9d0;

"hist-10"
read("hist/anneal-size=10");
r10norm=r10/(1024^2);
r10d0=r10norm[2:size(r10)[1]-1;1];
r10lin=linspace(0,1,r10d0.nr);
r10d0lin=[r10lin;r10d0']';
r10d1=r10norm[2:size(r10)[1]-1;2];
r10d2=r10norm[2:size(r10)[1]-1;3];
r10d2lin=[r10lin;r10d2']';
r10d2log=log(r10d2);
r10d2loglin=[r10lin;r10d2log']';
r10d2d0=r10d2./r10d0;

"done"

if (0) {
pstart(1,3,"xwin");
plot(<<r7d0lin; r8d0lin; r9d0lin; r10d0lin>>);
plot(<<r7d2lin; r8d2lin; r9d2lin; r10d2lin>>);
plot(<<r7d2loglin; r8d2loglin; r9d2loglin; r10d2loglin>>);
}

if(0) {
	close("manip/r7d0lin"); write("manip/r7d0lin", r7d0lin);
	close("manip/r7d2lin"); write("manip/r7d2lin", r7d2lin);
	close("manip/r7d2loglin"); write("manip/r7d2loglin", r7d2loglin);

	close("manip/r8d0lin"); write("manip/r8d0lin", r8d0lin);
	close("manip/r8d2lin"); write("manip/r8d2lin", r8d2lin);
	close("manip/r8d2loglin"); write("manip/r8d2loglin", r8d2loglin);

	close("manip/r9d0lin"); write("manip/r9d0lin", r9d0lin);
	close("manip/r9d2lin"); write("manip/r9d2lin", r9d2lin);
	close("manip/r9d2loglin"); write("manip/r9d2loglin", r9d2loglin);

	close("manip/r10d0lin"); write("manip/r10d0lin", r10d0lin);
	close("manip/r10d2lin"); write("manip/r10d2lin", r10d2lin);
	close("manip/r10d2loglin"); write("manip/r10d2loglin", r10d2loglin);
}
