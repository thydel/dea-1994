;

function ret = ncol (mat, n)
	[l c] = size(mat);
	ret = reshape(mat, n, (l / n))';
endfunction

function ret = extract (mat, first, last)
	ret = mat([first : last]);
endfunction

function ret = normalize (mat)
	min = min(mat);
	max = max(mat);
	range = abs(max - min);
	ret = (mat - min) / range;
endfunction

function ret = translate (mat)
	min = min(mat);
	max = max(mat);
	ret = mat - min;
endfunction

function ret = diff (mat)
	[l c] = size(mat);
	for i = 2:l
		nmat(i) = mat(i) - mat(i - 1);
	endfor
	ret = nmat;
endfunction

function ret = undiff (mat)
	[l c] = size(mat);
	for i = 2:l
		mat(i) = mat(i) + mat(i - 1);
	endfor
	ret = mat;
endfunction

function anim (mat, from, to, width, slip)
	cnt = 0;
	for i = from:to
		if ((i + slip * cnt) > to)
			return
		endif
		cmd = sprintf ("gplot [%d:%d] mat", i + slip * cnt, i + slip * cnt + width);
		eval(cmd);
		++cnt;
	endfor
	purge_tmp_files
endfunction

function ret = mtv (mat)
	ret = flipud(rot90(mat));
endfunction

function manim (mat, vect, from, to, width, slip)
	tmp = sprintf ("mat(:,%d)", vect(1));
	[l c] = size(vect);
	for i = vect(2:c);
		tmp = sprintf ("%s, mat(:,%d)", tmp, i);
	endfor
	cnt = 0;
	for i = from:to
		if ((i + slip * cnt) > to)
			return
		endif
		cmd = sprintf ("gplot [%d:%d] %s", i + slip * cnt, i + slip * cnt + width, tmp);
		++cnt;
		eval(cmd);
#		printf("%s\n", cmd);
	endfor
	purge_tmp_files
endfunction
