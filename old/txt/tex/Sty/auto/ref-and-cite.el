(TeX-add-style-hook "ref-and-cite"
 (function
  (lambda ()
    (LaTeX-add-labels
     "ref-#1")
    (TeX-add-symbols
     '("mygetplot" ["argument"] 1)
     '("mygetcode" ["argument"] 1)
     '("mygetdump" ["argument"] 1)
     '("mygetfig" ["argument"] 1)
     '("mygettbl" ["argument"] 1)
     '("mygetrule" ["argument"] 1)
     '("mygetref" ["argument"] 1)
     '("mysoftcite" ["argument"] 1)
     '("myget" 3)
     '("mycaptionname" 2)
     '("mysoftref" 1)
     '("myrulecite" 1)
     '("mysetref" 1)))))

