%s QWE
%%
			BEGIN QWE;
\\qwe			BEGIN QWE;
\\\{qwe\}		BEGIN QWE;
\\cpy			BEGIN 0;
\\\{cpy\}		BEGIN 0;
<QWE>\\$                printf(yytext);
<QWE>$[^$]+\$		printf(yytext);
<QWE>$$[^$]+$\$		printf(yytext);
<QWE>e'			printf("\\'e");
<QWE>[aeu]`		printf("\\`%c", yytext[0]);
<QWE>[aeou]^		printf("\\^%c", yytext[0]);
<QWE>i^			printf("\\^\\i ");
<QWE>c\,[aeiou]		printf("\\c c%c", yytext[2]);
