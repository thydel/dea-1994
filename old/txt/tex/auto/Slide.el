(TeX-add-style-hook "Slide"
 (function
  (lambda ()
    (TeX-add-symbols
     '("mystitle" 1)
     '("mytitle" 1)
     '("aplane" 1)
     '("agencnt" 1)
     '("agen" 1))
    (TeX-run-style-hooks
     "Sty/simple"
     "Sty/fig-cap"
     "xspace"
     "epsfig"
     "ifthen"
     "babel"
     "slides10"
     "slides"
     "a4paper"
     "dvips"))))

