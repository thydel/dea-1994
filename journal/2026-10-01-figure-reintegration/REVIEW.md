---
date: 2026-10-01
model: GPT-5.6 Sol
interface: ChatGPT Voice
role: reviewer
---

# Review — Figure reintegration

## Verdict

Accepted, with one provenance-metadata discrepancy noted below.

The implementation satisfies the operational directive: the historical
figure resources were inventoried before restoration, all 88 active image
occurrences were mapped to documented historical PS/EPS sources, the selected
sources were copied into the reconstructed project, deterministic PDF
derivatives were produced, and the figures were restored without modifying
the scientific chapter sources or the historical tree.

## Evidence reviewed

The review compared the implementation report in [DONE.md](DONE.md) with the
original [PROMPT.md](PROMPT.md), the resulting
[figure inventory](../../new/latex/FIGURES.md), the
[resource audit](../../new/latex/RESSOURCES.md), the
[validation report](../../new/latex/VALIDATION.md), and the committed
implementation changes.

The resulting validation records:

- 88 restored image occurrences in 75 illustrated figures;
- zero image occurrences still deferred, missing, ambiguous, or technically
  unusable;
- 89 numbered figures and ten tables, with the historical numbering order
  preserved;
- 254 labels and 146 bibliography keys;
- zero unresolved references or citations;
- no modification or untracked addition under `old/`;
- SHA-256 verification from historical sources through staged copies to the
  loaded derivatives;
- deterministic regeneration of all 88 PDF derivatives;
- no direct build input from `old/`.

The increase from 129 to 157 pages is consistent with restoring graphical
material that had previously been represented by deferred placeholders and is
therefore not, by itself, a preservation regression.

## Scope and implementation

The implementation respected the important separation established by the
prompt: historical material remains unchanged under `old/`, while active
copies and generated derivatives live under `new/latex/figures/`. The
mapping is explicit and reproducible rather than based only on matching
filenames. Historical link chains and 1993/1994 source locations are retained
in the inventory.

The conversion mechanism is mechanical. Ghostscript conversion is documented
and driven from the manifest; PS resources that require explicit historical
bounding-box handling are treated without redrawing or content
reinterpretation. The compatibility layer preserves the existing figure API
instead of rewriting scientific prose to load the images.

The strengthened validation checks the exact set of loaded PDF derivatives
against the manifest, verifies hashes and dimensions, and preserves the
existing structural checks. This is an appropriate replacement for the
whole-page raster identity criterion, which could not remain valid once the
figures were intentionally restored.

## Independent-review limits

The repository contains the generated PDF, manifests, validation outputs,
conversion code and implementation report needed to audit the result. Claims
in [DONE.md](DONE.md) about commands actually run and the manual inspection of
all 157 rendered pages are execution records produced by the implementer; this
review confirms that the committed artefacts and validation machinery are
consistent with those claims, but does not independently rerun the toolchain.

The 14 external listings remain deferred, as explicitly outside the scope of
this figure-reintegration directive.

## Provenance note

[DONE.md](DONE.md) records its model as `GPT-6`. During the preceding
interactive session, the Codex `/status` output was recorded more
specifically as a GPT-6.1 Sol configuration. The implementation provenance
should therefore be reconciled with the exact `/status` value rather than
silently treating these two labels as equivalent. This metadata issue does not
affect acceptance of the figure-reintegration work itself.

## Conclusion

The figure-reintegration task is accepted. The committed result provides a
traceable inventory, reproducible local conversions, restored figures, and
stronger provenance validation while preserving the historical sources and
the document's scientific semantics.
