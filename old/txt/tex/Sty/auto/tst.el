(TeX-add-style-hook "tst"
 (function
  (lambda ()
    (LaTeX-add-environments
     '("Filesave" 1))
    (TeX-add-symbols
     '("newsolution" 1)
     '("Newassociation" 3)
     '("Iffileundefined" 3)
     '("Ifopen" 3)
     '("Writetofile" 2)
     "filename"
     "Copyright"
     "solutionextension"
     "protect"
     "Opensolutionfile"
     "Tmp"
     "Tmp"
     "Closesolutionfile"
     "Tmp"
     "Tmp"
     "Readsolutionfile"
     "Tmp"
     "Tmp"
     "Currentlabel"))))

