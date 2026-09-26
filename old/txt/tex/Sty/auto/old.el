(TeX-add-style-hook "old"
 (function
  (lambda ()
    (LaTeX-add-labels
     "#2-#3-section"
     "#2-#3"
     "#2-#3"
     "#3-#4+#5-section"
     "#3-#4+#5"
     "#3-#4+#5")
    (TeX-add-symbols
     '("mytwocaption" ["argument"] 7)
     '("mycaption" ["argument"] 5)
     '("myplottwovert" 3)
     '("myplottwo" 3)
     '("myplotnew" 4)
     '("myplot" 2)
     '("mydumpnew" 4)
     '("mydump" 2)
     '("myfignew" 4)
     '("myfig" 2)
     '("mytblnew" 4)
     '("mytbl" 2)))))

