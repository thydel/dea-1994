;; misc
(query-replace "\\*[thy@quote]" "'" nil)
(query-replace "~\\*[thy@xor]~" "\\xor" nil)
(query-replace "\\\(12" "$1/2$" nil)
(query-replace ".\\\"" "%%" nil)
(query-replace ".thy@BIG" "%% BIG" nil)
(query-replace ".thy@CODE-START" "\\begin{verbatim}")
(query-replace ".thy@CODE-END" "\\end{verbatim}")

;; sections
(query-replace-regexp "^\\.thy@H 1 \"\\(.*\\)\"" "\\\\section{\\1}" nil)
(query-replace-regexp "^\\.thy@H 2 \"\\(.*\\)\"" "\\\\subsection{\\1}" nil)
(query-replace-regexp "^\\.thy@H 3 \"\\(.*\\)\"" "\\\\subsubsection{\\1}" nil)
(query-replace-regexp "^\\.thy@APP \"\\(.*\\)\"" "\\\\chapter*{\\1}" nil)
(query-replace-regexp "^\\.P" "" nil)

;; fonts
(query-replace-regexp "\\\\fB\\([a-zA-Z0-9]*\\)\\\\fP" "\\\\textbf{\\1}" nil)
(query-replace-regexp "\\\\fB\\([^\\]*\\)\\\\fP" "\\\\textbf{\\1}" nil)
(query-replace-regexp "\\\\fI\\([^\\]*\\)\\\\fR" "\\\\emph{\\1}" nil)
(query-replace-regexp "\\\\fI\\([^\\]*\\)\\\\fP" "\\\\emph{\\1}" nil)
(query-replace-regexp "\\\\fC\\([^\\]*\\)\\\\fP" "\\\\texttt{\\1}" nil)

;; footnote
(query-replace-regexp "\\\\\\*F\\([.,]\\)" "\\1\\\\footnote{" nil)
(query-replace-regexp "\\\\\\*F$" "\\\\footnote{" nil)
(query-replace ".FS
" "" nil)
(query-replace ".FE" "}" nil)

;; ref
(query-replace-regexp "\\\\\\*\\[\\(.*\\)\\]" "\\\\myref{\\1}" nil)
(query-replace-regexp "\\.SETR \\(.*\\)" "\\\\label{\\1}" nil)
(query-replace-regexp "^\\.thy@GET-REF \\(.*\\) \\(.*\\)" "\\\\mygetref(\\2){\\1}" nil)
(query-replace-regexp "\\.thy@GET-REF \\(.*\\) \\(.*\\)" "\\\\mygetref(\\2){\\1}" nil)

;; fig
(query-replace-regexp "^\\.thy@FIG \\(.*\\) \"\\(.*\\)\"" "\\\\myfig{\\1}{\\2}" nil)
(query-replace-regexp "^\\.thy@GET-FIG \\(.*\\) \\(.*\\)" "\\\\mygetfig(\\2){\\1}" nil)

;; dump
(query-replace-regexp "^\\.thy@DUMP \\(.*\\) \"\\(.*\\)\"" "\\\\mydump{\\1}{\\2}" nil)

;; plot
(query-replace-regexp "^\\.thy@PLOT \\(.*\\) \"\\(.*\\)\"" "\\\\myplot{\\1}{\\2}" nil)

;; tbl
(query-replace-regexp "\\.thy@TBL \\(.*\\) \"\\(.*\\)\"
.*
.*" "\\\\mytbl{\\1}{\\2}" nil)
(query-replace-regexp "\\\\\\*\\[\\(.*\\)\\]" "\\\\ref{\\1}" nil)
(query-replace-regexp "\\.thy@GET-TBL \\(.*\\) \\(.*\\)" "\\\\mygettbl(\\2){\\1}" nil)

;; cite
(query-replace-regexp "^\\.\\[
\\(.*\\)
\\.\\]" "\\\\cite{\\1}" nil)

;; break line
(query-replace "
.br" "\\hfil\\break" nil)

;; list
(query-replace ".BL" "\\begin{itemize}" nil)
(query-replace ".LE" "\\end{itemize}" nil)
(query-replace ".LI" "\\item" nil)

;; soft ref
(query-replace ".RS" "\\mysoftent{" nil)
(query-replace ".RF" "}" nil)
(query-replace "\*[Rf]" "\mysoftref" nil)

;; math
(query-replace-regexp " \\([^ ]*\\) sub " " \\1_" nil)

;; spl
(query-replace-regexp "\\\\\\*\\[\\([^-]+\\)-\\(.*\\)\\]" "\\\\myget\\1{\\1:\\2}" nil)
