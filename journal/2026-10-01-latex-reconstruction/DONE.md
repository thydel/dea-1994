# Codex work report — LaTeX reconstruction

This report was reconstructed retrospectively on 2026-10-01 from the
completed Phase 1 result and its own project documentation.

## Phase 1 outcome

Codex reconstructed the historical LaTeX project under `new/latex/`.
The resulting baseline is commit
`55aaf7b3f814491a538e5668caa465b48718aa1d`.

The reconstructed project contains the modern build and compatibility
machinery together with chapter sources, bibliography, tables, generated PDF,
validation tools, and documentation.

Detailed documentation produced with the result is kept with the artifact:

- `new/latex/README.md` describes the reconstructed project, dependencies,
  build procedure, and compatibility choices.
- `new/latex/RESSOURCES.md` inventories historical and deferred resources.
- `new/latex/VALIDATION.md` records the detailed validation results.
- `new/latex/validation.json` contains machine-readable validation results.

The validated result contains 129 A4 pages, 254 labels, 146 bibliography
keys, 47 table-of-contents entries, 89 numbered figures, 10 tables, 88
deferred image occurrences, and 14 deferred external listings. There are no
unresolved references or citations. The historical `old/` tree is unchanged.

The next identified source-readability issue was the continued use of
historical TeX accent notation in ordinary French prose. That follow-up work
is recorded separately under `journal/2026-10-01-latex-use-utf8/`.
