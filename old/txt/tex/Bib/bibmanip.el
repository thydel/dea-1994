(query-replace-regexp "  note =  \\(.*Reprinted.*\\)" "  Znote = \\1" nil)

(query-replace-regexp "@Book{\\(.*\\),
  author =       \"\\(.*\\)\"," "@Book{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@Book{\\(.*\\),
  title =        \\(.*\\),
  editor =       \"\\(.*\\)\"," "@Book{\\1,
  title =        \\2,
  editor =       \"\\3#marginpar{\\1}\"," nil)

(query-replace-regexp "@Article{\\(.*\\),
  author =       \"\\(.*\\)\"," "@Article{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@TechReport{\\(.*\\),
  author =       \"\\(.*\\)\"," "@TechReport{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@PhdThesis{\\(.*\\),
  author =       \"\\(.*\\)\"," "@PhdThesis{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@MastersThesis{\\(.*\\),
  author =       \"\\(.*\\)\"," "@MastersThesis{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@Manual{\\(.*\\),
  author =       \"\\(.*\\)\"," "@Manual{\\1,
  author =       \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@Misc{\\(.*\\),
  title =        \"\\(.*\\)\"," "@Misc{\\1,
  title =        \"\\2#marginpar{\\1}\"," nil)

(query-replace-regexp "@In\\(.*\\){\\(.*\\),
  author =       \"\\(.*\\)\"," "@In\\1{\\2,
  author =       \"\\3#marginpar{\\2}\"," nil)

