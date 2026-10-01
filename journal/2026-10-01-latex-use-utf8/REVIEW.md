# Independent review — Literal UTF-8 conversion

## Review — 2026-10-01

Reviewed result: commit
`fca8b2ff944716827636526c6237d4cd7774556e`.

The implementation matches the author's source-readability intent and the
operational directive. It converted 4,895 eligible historical accent or
ligature occurrences in ordinary text to literal Unicode while deliberately
leaving 116 protected occurrences unchanged: 115 in comments and one in a
mathematical context.

The work did more than a blind textual substitution. It inventories forms and
contexts, protects syntax-sensitive material, adapts the preservation
comparison, and adds regression checks intended to reject unrelated changes.

The validation reports the same 129 pages, 254 labels, 146 bibliography keys,
47 contents entries, 89 figures, and 10 tables, with no unresolved references
or citations, LaTeX errors, package warnings, or missing characters. The same
14 pre-existing underfull-box messages remain.

Most convincingly, the extracted layout-text hash is unchanged and all 129
page rasters at 45 dpi match the pre-conversion baseline. This provides strong
evidence that the source representation changed without changing the rendered
document.

The implementation added several scripts and validation artifacts. They are
useful for making this transformation reproducible, although a later cleanup
may decide which are durable project tooling and which are one-time
scaffolding.

Conclusion: the UTF-8 conversion is satisfactory and preserves the Phase 1
baseline according to the supplied structural, textual, and rendered-output
checks.
