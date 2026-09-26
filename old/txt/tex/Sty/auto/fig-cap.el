(TeX-add-style-hook "fig-cap"
 (function
  (lambda ()
    (LaTeX-add-labels
     "#1"
     "#1"
     "#3-#4-section"
     "#3-#5+#6-section"
     "#4-#5-section"
     "tbl-#2-section"
     "code-#3-section"
     "code-#2-section")
    (TeX-add-symbols
     '("mycodetwothirds" ["argument"] 4)
     '("mycodefull" ["argument"] 4)
     '("mytwofigfull" ["argument"] 5)
     '("mytwoplotVfull" ["argument"] 5)
     '("mytwodumpfull" ["argument"] 5)
     '("mytwoplotfull" ["argument"] 5)
     '("myfighalf" ["argument"] 4)
     '("myfigtwothirdsR" ["argument"] 5)
     '("myfigtwothirds" ["argument"] 4)
     '("myfigfullR" ["argument"] 5)
     '("myfigfull" ["argument"] 4)
     '("myplothalf" ["argument"] 4)
     '("myplottwothirds" ["argument"] 4)
     '("myplotfullR" ["argument"] 5)
     '("myplotfull" ["argument"] 4)
     '("mydumphalf" ["argument"] 4)
     '("mydumptwothirdsR" ["argument"] 5)
     '("mydumptwothirds" ["argument"] 4)
     '("mydumpfullR" ["argument"] 5)
     '("mydumpfull" ["argument"] 4)
     '("mycodetwocol" ["argument"] 4)
     '("mytable" ["argument"] 4)
     '("mycode" 6)
     '("mySfigureR" 5)
     '("myfigureR" 8)
     '("mySthreefigure" 7)
     '("myStwofigureB" 7)
     '("myStwofigureA" 6)
     '("myStwofigure" 6)
     '("mytwofigure" 9)
     '("mySfigure" 4)
     '("myfigure" 7)
     '("myScapted" 2)
     '("mycapted" 5)
     '("mySboxed" 2)
     '("myboxed" 2)))))

