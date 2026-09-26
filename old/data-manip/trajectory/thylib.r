film = function(v) {
	local(i, k, K, cnt);

	k = 2;
	K = 1;
	cnt = 1;
	for (i in 1:v.nr) {
		v[i] = cnt;
		k = k + K;
		cnt = cnt + k;
	}
	return v;
};

film1 = function(v) {
	local(i, k, K, cnt);

	k = 2;
	K = 2;
	cnt = 1;
	for (i in 1:v.nr) {
		v[i] = cnt;
		k = k + K;
		cnt = cnt + k;
	}
	return v;
};

filmindex = function(film, idx) {
	local(i);

	for (i in 1:film.nr) {
		if (film[i] > idx) {
			if ((film[i] - idx) < (idx - film[i - 1])) {
				return <<index = i; error = film[i] - idx>>;
			else
				return <<index = i - 1; error = idx - film[i - 1]>>;
			}
		}
	}
	return -1;
};

smooth = function(t, w) {
	local(r, i, j, s);
	
	r[t.nr] = 0;
	for (i in w + 1 : t.nr - w) {
		s = 0;
		for (j in -w : w) {
			s = s + t[i - j];
		}
		r[i] = s / (w * 2 + 1);
	}
	return r';
};

part = function(T, f, t) {
	local(from);

	if (f == 0) {
		from = 1;
	else
		from = f * T.nr;
	}
	return T[from : t * T.nr];
};

plim = function(T, f, t) {
	local(from);

	if (f == 0) {
		from = 1;
	else
		from = f * T.nr;
	}
	plimits(f, t * T.nr);
};

nolog = function() {
	plgrid("bcgnst", "bcgnstv");
};

ylog = function() {
	plgrid("bcgnst", "bcgnstvl");
};
