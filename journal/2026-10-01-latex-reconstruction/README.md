# LaTeX reconstruction — Phase 1

Date: 2026-10-01

## Status

This journal entry was reconstructed retrospectively after Phase 1 had
already been executed. It records the directive that governed that work; it
does not pretend that the journal existed before execution.

The original detailed specification remains preserved at:

`new/2026-10-01-work-latex-phase-1.md`

Phase 1 produced the modern compilable project under `new/latex/`. The
resulting baseline commit is `55aaf7b3f814491a538e5668caa465b48718aa1d`.

## Directive — Phase 1 reconstruction

Reconstruct the 1994 DEA document from the historical LaTeX sources under
`old/txt/tex/` as a modern, simple, maintainable, reproducibly compilable
LaTeX project under `new/latex/`.

The historical tree under `old/` is immutable. Preserve the scientific
content, document structure, equations, notes, citations, labels, references,
chapters, appendices, and ordering. Modernize technical mechanisms only where
needed for a current TeX Live environment.

Do not attempt page-for-page facsimile reproduction in this phase. Do not
restore EPS/PS figures. Preserve figure numbering, captions, labels,
references, and historical resource names through a compatibility or
placeholder layer. Preserve tables where possible and similarly inventory
deferred external listings.

Remove dependencies on the private historical `mytex` format and obsolete
PostScript machinery. Keep useful semantic macros or reimplement them
compatibly. Preserve the existing cross-reference API where doing so reduces
risk.

Use the historical LaTeX sources as the primary source of truth,
`old/txt/tex/top.log` as evidence of the successful 1994 build and its
inclusions, the historical PDF to resolve ambiguities, and historical
auxiliary files only as secondary evidence.

Provide a simple build, preferably `make`, document current Debian/TeX Live
dependencies, iterate compilation to convergence, and validate more than the
mere existence of a PDF: references, citations, labels, resource inventory,
warnings, and preservation invariants must be checked.

The complete requirements and acceptance criteria are the detailed
specification referenced above. That specification is authoritative for the
already-completed Phase 1 work.
