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

## Inventory and execution approach — 2026-10-01

The initial inventory is recorded in `accent-inventory.json`. There
are 5,011 historical accent or ligature occurrences in the chapter
sources. Of these, 4,895 occur in ordinary text and will be converted.
The eligible forms are acute, grave and circumflex accents, diaeresis,
cedilla, and the exact grouped ligature `{\oe}`.

The lexical reader protects comments, inline/display mathematics,
mathematical environments, verbatim/code, identifier and resource
arguments, and macro definitions. It leaves 116 occurrences intact:
115 in comments and one in the mathematical text `\text{m\'egaoctets}`
in `intro-part-2.tex`, line 367. The mathematical expression is
preserved exactly, including this text fragment.

No accent forms were found in compatibility macros or table sources.
The seven bibliography files remain unchanged. Labels, citation keys,
resource arguments and macro definitions remain exact source text.

`new/latex/tex_unicode.py` implements this scoped normalization. The
preservation comparison will normalize only eligible prose on both
sides; protected contexts and unrelated characters will still have to
match exactly. Regression checks in `test_normalization.py` exercise
both equivalent accents and rejected changes to prose, equations,
labels and citation keys.

Before conversion, the complete Phase 1 checks passed. `baseline.json`
records the baseline Git revision, PDF hash, extracted layout-text
hash and the rendered hashes of all 129 pages at 45 dpi. After
conversion, those text and rendering hashes will be compared with the
new PDF, in addition to the source and structural checks.

## Outcome and validation — 2026-10-01

The directive is completed. Fourteen chapter files now use literal
Unicode for ordinary text, with 4,895 converted occurrences. The
remaining three active chapter files had no eligible accent forms. The
116 deliberately retained occurrences are listed individually in
`accent-inventory.json`. That inventory also records the preserved TeX
special-character forms, nonbreaking spaces and explicit hyphens.

The implementation is `new/latex/tex_unicode.py`. The one-time
`convert.py` checks every inventoried file before writing any change;
it is not a general-purpose converter. `test_normalization.py` checks
prose equivalence and exact protection of code, mathematics, macro
bodies, comments, keys and resource names. It also proves that
unrelated content changes are still rejected by semantic comparison.

Commands executed from the repository root:

```sh
python3 journal/2026-10-01-latex-use-utf8/test_normalization.py
python3 journal/2026-10-01-latex-use-utf8/convert.py
make -C new/latex clean
make -C new/latex
make -C new/latex check
python3 journal/2026-10-01-latex-use-utf8/verify_output.py
```

All five regression tests pass. A clean build stabilizes after four
LaTeX passes and one BibTeX invocation. The result retains 129 A4
pages, 254 labels with their historical numbers, 146 bibliography
keys, 47 contents entries, 89 figures and 10 tables. The equation and
identifier checks pass. There are no unresolved references or
citations, no LaTeX errors, no package warnings, and no missing
characters. The same 14 underfull-box messages remain.

`verify_output.py` compares the built PDF with `baseline.json`. The
entire extracted layout-text hash is identical. All 129 page rasters
at 45 dpi are also identical. `output-validation.json` records this
comparison against the pre-conversion Git revision. Thus the generated
textual content and page rendering are unchanged.

The project README and validation report describe the literal UTF-8
convention and its exceptions. Their prose, and the resource audit
produced by `inventory.py`, is wrapped at 70 columns. Tables and code
blocks retain their syntax-sensitive physical lines.
`wrap_markdown.py` records the formatting operation for the two edited
project documents. Earlier journal directives remain intact.

`old/` and all seven bibliography sources are unchanged. No
scientific, terminological or punctuation changes were made. The only
intentionally unconverted active accent is the mathematical text
fragment documented above; no content ambiguity was resolved by
guessing.

Final whitespace review: `git diff --check` reports six trailing-space
lines in converted chapters. Those spaces were already present in the
baseline, at the same line numbers, and were preserved rather than
introducing an unrelated source cleanup. No new trailing spaces were
introduced. The edited Markdown prose passes the 70-column check,
excluding tables and fenced code.
