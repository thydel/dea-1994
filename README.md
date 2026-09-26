# What ?

- This is a very old arbo from 1994 containing a DEA (Diplôme d’Études
  Approfondies (DEA): An older French university degree equal to 5
  years of higher education, used before preparing for a doctorate)
  thesis about cellular automata
- The (gitignored) `orig` is the base arbo from the past
- The `old` is a `cp -al` copy of `orig` slightly *cleaned*
  - Mainly remove all `.00` etc files and folder and remove `.o` files
  - The *data* files (raw, PBM, etc) and executable still there
  
# Why ?

- I want to ask some agent to incrementally revamp all this to a
  modern generable again latex version

# How to explore

- `cas-1.1` and `cas-2.0` are older tools associated with older (the
  previous year academic work) tool used with the older `txt-roff`
  (yes, `roff`) kept because later work may reuse some data files via
  relative symlinks. So not to be use as entry point
- `cell` is the associated code use to produce CA data from
  experiments.  The `src-98` and various other newer than 1994 files
  come from various then forgotten tries to somehow revive the tools
- `data-manip`, `gapp` and `slice` are other associated tools
- `tex` is the arbo for latex src and associated non textual data
