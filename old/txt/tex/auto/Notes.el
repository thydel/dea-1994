(TeX-add-style-hook "Notes"
 (function
  (lambda ()
    (TeX-add-symbols
     '("mytitle" 1))
    (TeX-run-style-hooks
     "babel"
     "slides10"
     "slides"
     "a4paper"))))

