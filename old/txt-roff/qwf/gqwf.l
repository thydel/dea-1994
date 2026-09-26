%s QWE
%%
			BEGIN QWE;
^\.qwe.*\n		BEGIN QWE;
^\.cpy.*\n		BEGIN 0;
<QWE>^e'		printf("\\&\\('e");
<QWE>^[aeu]`		printf("\\&\\(`%c", yytext[0]);
<QWE>^[aeiou]^		printf("\\&\\(^%c", yytext[0]);
<QWE>^c\,[aeiou]	printf("\\&\\(,c%c", yytext[2]);
<QWE>e'			printf("\\('e");
<QWE>[aeu]`		printf("\\(`%c", yytext[0]);
<QWE>[aeiou]^		printf("\\(^%c", yytext[0]);
<QWE>c\,[aeiou]		printf("\\(,c%c", yytext[2]);
<QWE>e\\'		printf("e'");
<QWE>[aeu]\\`		printf("%c`", yytext[0]);
<QWE>[aeiou]\\^		printf("%c^", yytext[0]);
<QWE>c\\\,[aeiou]	printf("c,%c", yytext[3]);
