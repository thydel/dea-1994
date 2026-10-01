# Author intent — LaTeX reconstruction

This record was reconstructed retrospectively on 2026-10-01 after the work
had already been performed.

The author's aim was to recover a maintainable and regenerable LaTeX source
for the 1994 DEA from the original LaTeX sources, rather than to convert the
historical PDF or reproduce it page by page.

The first stage should establish a simple modern source tree, preferably with
one file per chapter, a small and understandable preamble, a Makefile, and a
minimal current TeX toolchain. Historical technical machinery should be
simplified where possible without rewriting the scientific content.

Figures did not need to be restored during this first stage. They could be
deferred or represented by placeholders while preserving the information
needed for later restoration. The same conservative principle applied to
other historical external resources.

The result should compile, be editable for later work, preserve the original
content, and provide a reliable basis for subsequent modernization.
