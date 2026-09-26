load -force anneal-cycle.mdata;

a0 = a0 / 65536;

a1 = diff(a0);
a2 = diff(a1);
a3 = diff(a2);
a4 = diff(a3);
a5 = diff(a4);
a6 = diff(a5);
a7 = diff(a6);
a8 = diff(a7);
a10 = imag(fft(a0));
a11 = imag(fft(a1));
a12 = imag(fft(a2));
a13 = imag(fft(a3));
a14 = imag(fft(a4));
a15 = imag(fft(a5));
a16 = imag(fft(a6));
a17 = imag(fft(a7));
a18 = imag(fft(a8));

a_0 = undiff(a0);

a_1 = undiff(a_0);
a_2 = undiff(a_1);
a_3 = undiff(a_2);
a_4 = undiff(a_3);
a_10 = imag(fft(a_0));
a_11 = imag(fft(a_1));
a_12 = imag(fft(a_2));
a_13 = imag(fft(a_3));
a_14 = imag(fft(a_4));

a = flipud(rot90([
	mtv(a0); mtv(a1); mtv(a2); mtv(a3); mtv(a4);
	mtv(a10); mtv(a11); mtv(a12); mtv(a13); mtv(a14);
	mtv(a_0); mtv(a_1); mtv(a_2); mtv(a_3); mtv(a_4);
	mtv(a_10); mtv(a_11); mtv(a_12); mtv(a_13); mtv(a_14);
	mtv(a5); mtv(a6); mtv(a7); mtv(a8);
	mtv(a15); mtv(a16); mtv(a17); mtv(a18);
]));

o = 1;
d1 = 2;
d2 = 3;
d3 = 4;
d4 = 5;
fo = 6;
fd1 =7;
fd2 = 8;
fd3 = 9;
fd4 = 10;
i0 = 11;
i1 = 12;
i2 = 13;
i3 = 14;
i4 = 15;
di0 = 16;
di1 = 17;
di2 = 18;
di3 = 19;
di4 = 20;

d5 = 21;
d6 = 22;
d7 = 23;
d8 = 24;
fd5 = 25;
fd6 = 26;
fd7 = 27;
fd8 = 28;

save data.mdata a a0 a1 a2 a3 a4 a10 a11 a12 a13 a14 a_0 a_1 a_2 a_3 a_4 a_10 a_11 a_12 a_13 a_14
