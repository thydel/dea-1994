(TeX-add-style-hook "ltx-tst"
 (function
  (lambda ()
    (TeX-run-style-hooks
     "amstext"
     "art10"
     "article"
     "a4paper"
     "neighburhood-size"
     "neighburhood-size-1"
     "neighburhood-size-2"
     "compute-time-100kcps"
     #("compute-time-10mcps" 0 19 (mouse-face highlight))
     "lifex-sum-1"
     "lifex-sum-2"
     "space-size"))))

