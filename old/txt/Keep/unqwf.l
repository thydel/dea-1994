%s QWE
%%
			BEGIN QWE;
\\qwe			BEGIN QWE;
\\\{qwe\}		BEGIN QWE;
\\cpy			BEGIN 0;
\\\{cpy\}		BEGIN 0;
<QWE>\\\'e		printf("e'");
<QWE>\\\`[aeu]		printf("%c`", yytext[2]);
<QWE>\\\^[aeou]		printf("%c^", yytext[2]);
<QWE>\\^\\i[ ] 		printf("i^");
<QWE>\\c\ c		printf("c,");
