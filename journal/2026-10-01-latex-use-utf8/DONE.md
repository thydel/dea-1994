---
date: 2026-10-01
model: GPT-6.1 Sol
interface: Codex
role: implementer
---

# Codex work report — Literal UTF-8 LaTeX source

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
