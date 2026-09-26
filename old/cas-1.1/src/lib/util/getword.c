#include <ctype.h>

#define YES 1
#define NO 0
#define NULL 0

/* copy in buf the nieme word (arg mot) found in line, and return buf
 * or NULL if there is less than <mot> words. line is a string ended by '\0',
 * a word is a group of any char betwen to space char as define in
 * isspace (3) and obviouly the start and the end of the line.
 */

char *getword (buf, line ,mot)
register char *buf, *line;
register int mot;
{
	typedef int bool;
	register bool inword=NO;
	register char c, *sbuf=buf;

	while (c= *line++)
	{
		if (isspace (c) && inword)
		{
			inword=NO;
			continue;
		}
		if (!isspace (c) && !inword) 
		{
			inword=YES;
			if(! --mot)
			{
				--line;
				while (*line && !isspace (*line))
					*buf++ = *line++;
				*buf='\0';
				return sbuf;
			}
		}
	}
	return NULL;
}
