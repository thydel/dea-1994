.warn
.\"
.\" point size and vertical spacing
.\"
.\"S 18 20
.\"S 16 18
.\"S 14 18
.S 12 14
.\"
.\" MM Tuning
.\"
.\" heading point size
.ds HP +6 +4 +2 +2 +2 +2 +2
.\" heading font H 1,2,3 = bold, other = italic
.ds HF 3 3 3 2 2 2 2
.\" eject before .H 1
.nr Ej 1
.\" break after each heading
.nr Hb 4
.\" blank line after each heading
.nr Hs 4
.\" indent next line of text
.nr Hi 1 
.\" center .H 1
.\"nr Hc 1
.\" heading to put in table of content
.nr Cl 4
.\" indent dans un DS
.nr Si 8
.\" control of output for floating display
.nr Df 5
.\"
.\" QWF
.\"
.qwe
.\"
.\" French Strings
.\"
.if n \{\
.ds 'e \z\(aae
.ds `e \z\(gae
.ds ^e \z^e
.ds `a \z\(gaa
.ds ^a \z^a
.ds ^i \z^i
.ds ^o \z^o
.ds `u \z\(gau
.ds ^u \z^u
.ds 'c \z,c\}
.ds ,c \z,c\}
.if t \{\
.ds 'e \o#\(aae#
.ds `e \o#\(gae#
.ds ^e \o#^e#
.ds `a \o#\(gaa#
.ds ^a \o#^a#
.ds ^i \o#^i#
.ds ^o \o#^o#
.ds `u \o#\(gau#
.ds ^u \o#^u#
.ds 'c \o#,c#\}
.ds ,c \o#,c#\}
.ds Lf Liste des Figures
.ds Lt Liste des Tables
.ds Lx Liste des Pie`ces
.ds Le Liste des Equations
.ds Lifg Figure
.ds Litb Table
.ds Liex Pie`ce
.ds Liec Equation
.ds Licon Table des Matie`res
.ds Rp Re'fe'rences des outils
.ds App Annexe
.ds Qrf Voir chapitre \\*[Qrfh], page \\*[Qrfp].
.\"
.ds MO1 janvier
.ds MO2 fevrier
.ds MO3 mars
.ds MO4 avril
.ds MO5 mai
.ds MO6 juin
.ds MO7 juillet
.ds MO8 aout
.ds MO9 septembre
.ds MO10 octobre
.ds MO11 novembre
.ds MO12 de'cembre
.\"
.\" Strings
.\"
.ds thy@title Cellular Automata Workbench
.ds thy@fac Universite' de Paris-8
.\" Universite' de Paris-8
.\" De'partement d'Informatique,
.\" 2, rue de la Liberte' 93526 SAINT-DENIS CEDEX 02
.\" Te'l: (1) 49 49 64 04
.\"
.ds thy@name Thierry Delamare
.\" thy@tao.univ-paris.fr
.\" DIRECTION: Patrick Greussay et Marc Destienne
.ds thy@date \n(dy \*[MO\n(mo] 19\n(yr
.ds thy@quote \N'39'
.ds thy@xor \z\(ci\(pl
.ds thy@line \\l'\\n(.lu'
.\"
.\" Cover Page
.\"
.TL
\s20
.vs 22
CAW
.br
un environnement de de'veloppement
.br
et de visualisation d'automates cellulaires
\s0
.vs
.br
.sp
Me'moire de ma\(^itrise
.br
\*[thy@date]
.AF "\*[thy@fac]"
.AU "\*[thy@name]"
.AT ""
.\"AS
.\"AE
.MT 4
.\"
.\" PAGE PARAMS
.\"
.PGFORM 17c 27c 2c
.\"
.\" Pagers and Footers
.\"
.PH "'\*[thy@line]'''"
.EH "'\\\\nP''Chapitre \\\\n(H1.  \\\\*[thy@chapter-name-1]'"
.OH "'\\\\n(H1.\\\\n(H2.  \\\\*[thy@chapter-name-2]''\\\\nP'"
.PF "'\*[thy@line]'''"
.EF "'\\\\nP'\*[thy@title]''"
.OF "''\*[thy@title]'\\\\nP'"
.so mac/mymm.mac
.mso mac/psmpic.mac
.\"
.\" EQN Macros
.\"
.EQ
delim $$
define log2 'log sub {2} ($1)'
define pow '$1 sup {$2}'
define byte 'roman {"byte"}($1)'
define abs 'roman {"abs"}($1)'
.EN
.\"
.\" References Init
.\"
.INITR mm/references
.\"
.\" Refer Cmds
.\"
.R1
database ref/bib.ref
label "A.n' 'D.y"
bracket-label " [" "]" ", "
move-punctuation
sort A+
.R2
.nr thy@bib-loop 0
.\"
.\" Misc Macs and Params
.\"
.so mac/thy.mac
.nr thy@warning 1
.nr thy@debug 0
.nr thy*big 0
.nr thy@head-flag 0
.\"
.\" Start of Text
.\"
