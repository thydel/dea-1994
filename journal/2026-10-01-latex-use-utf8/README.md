# LaTeX source: use literal UTF-8

Date: 2026-10-01

## Context

Phase 1 deliberately preserved the historical TeX accent notation in the
active LaTeX sources. The resulting files are valid UTF-8 at the byte level,
but French prose still contains forms such as `Universit\'e` instead of
literal `Université`.

The purpose of this directive is source readability, not scientific or
typographical modernization.

## Directive

Convert appropriate human-readable text in the reconstructed project under
`new/latex/` from historical TeX accent notation to literal Unicode UTF-8.

Never modify `old/`. Do not alter the intellectual or scientific content.
Do not perform blind substitutions across syntax-sensitive material.

First inventory the accent and special-character forms actually present.
Classify contexts before conversion. Convert ordinary prose, headings,
captions, metadata, and other human-readable LaTeX text where the Unicode
replacement is semantically equivalent and supported by the current build.

Treat macros, control sequences, mathematics, verbatim material, code,
resource names, labels, citation keys, paths, and other machine-sensitive
text conservatively. Leave a historical notation unchanged where conversion
would be ambiguous or could alter LaTeX semantics, and document such cases.

The bibliography was already converted from its historical encoding during
Phase 1; do not gratuitously rewrite it.

## Validation

The existing Phase 1 validation intentionally compares reconstructed sources
with historical sources character-for-character after a few documented
transformations. Literal Unicode conversion will invalidate that particular
byte/character-level invariant.

Do not simply remove the preservation check. Adapt validation so that the
historical TeX accent notation and the new literal Unicode representation are
normalized to a common semantic representation before comparison. Preserve
the strength of the existing checks for all unrelated content.

After conversion, run the complete build and validation suite. Confirm at
least that:

- `old/` remains unchanged;
- the document builds reproducibly;
- labels and their numbering are unchanged;
- citations and bibliography keys are unchanged;
- chapter and appendix order is unchanged;
- equations and machine-sensitive identifiers are unchanged;
- there are no new unresolved references or citations;
- there are no new LaTeX errors or missing-character warnings;
- generated textual content is semantically unchanged apart from the
  intended Unicode representation.

Update the project documentation and validation report to describe the UTF-8
source convention and any deliberately unconverted cases.

## Acceptance criterion

The reconstructed LaTeX source should be naturally readable as modern UTF-8
text while retaining the preservation guarantees established by Phase 1.
