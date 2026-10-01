---
date: 2026-10-01
model: GPT-5.6 Sol
interface: ChatGPT Voice
role: prompt-author
---

# Operational directive — Figure reintegration

## Context

Phase 1 deliberately neutralized historical image loading while preserving
figure numbering, captions, labels, explanatory text, and references. Its
resource inventory is
[`new/latex/RESSOURCES.md`](../../new/latex/RESSOURCES.md). The current
validation reports 89 numbered figures and 88 deferred image occurrences.

This task begins the restoration of those figures from historical resources
already present in the repository.

## 1. Inventory before modification

Do not begin by converting or inserting images.

Starting from the image occurrences recorded by the reconstructed project,
build a complete mapping between:

- each image resource expected by the active LaTeX source;
- the figure label and number using it;
- the historical resource name/path expected by the original source;
- every plausible matching file actually present under `old/`;
- any indirection represented by historical symbolic links or recovered link
  information;
- the actual format of the available resource, such as PS or EPS;
- whether the resource can be reused directly, needs a mechanical format
  conversion for the current toolchain, is ambiguous, or is missing.

Search the complete relevant historical tree rather than assuming that the
resource is located beside the old TeX source. In particular, account for
material originating in earlier 1993 work and reused in the 1994 DEA, and for
historical directory/link structures such as the dump trees described by the
author.

Distinguish carefully between image resources and other historical inputs.
For example, `.tbl` resources are LaTeX table material and were already
restored during Phase 1; do not classify them as images.

Record the resulting inventory in a durable, human-readable document under
`new/latex/`, extending or replacing the figure-related portion of
`RESSOURCES.md` as appropriate. Preserve machine-readable inventory data
when useful.

## 2. Establish provenance

For each resource considered reusable, establish why it corresponds to the
LaTeX call. Prefer evidence from original source paths, names, historical
logs, macro arguments, link targets, and repository structure.

Do not select a resource merely because its filename looks similar. When more
than one candidate is plausible, mark the mapping ambiguous and leave the
figure deferred.

Do not modify `old/`.

## 3. Restore available figures

After the inventory is complete, modify only the reconstructed project under
`new/latex/` so that figures with unambiguous, available historical
resources are rendered again.

Use the simplest maintainable mechanism supported by the current TeX Live
toolchain. If an old PS/EPS resource cannot be consumed directly by the
chosen PDF build, a deterministic mechanical conversion is permitted, but:

- retain the historical source resource unchanged under `old/`;
- place any generated derivative under `new/latex/` in a clearly identified
  location;
- make the conversion reproducible from the project build or a documented
  preparation command;
- record the source-to-derivative relationship in the inventory;
- do not redraw, reinterpret, retouch, or otherwise alter image content.

Preserve the current figure API where practical rather than rewriting chapter
prose merely to accommodate image loading.

## 4. Preserve document semantics

The restoration must not change:

- scientific text;
- captions or explanatory figure text;
- labels;
- cross-references;
- figure numbering or ordering;
- equations;
- citations and bibliography keys;
- chapter or appendix ordering.

Figures whose resources are missing or ambiguous must retain the existing
deferred/placeholder behavior and remain explicitly inventoried.

## 5. Validation

Run the full build and validation suite after the restoration.

In addition to the existing preservation checks, verify and report:

- the number of deferred image occurrences before and after the work;
- the exact set of figures restored;
- the exact set still deferred, classified at least as missing, ambiguous, or
  technically unusable;
- that every rendered image comes from a documented historical resource;
- that no build input is read directly from `old/` if the project's
  reproducibility rules require active inputs to live under `new/latex/`;
- that labels, numbering, references, citations, equations, and document
  structure remain unchanged;
- that there are no new unresolved references, LaTeX errors, missing
  characters, or unexplained warnings.

Visual output is expected to change where figures are restored, so do not use
the Phase 1 whole-page raster identity check as an acceptance criterion for
those pages. Adapt validation so that unchanged invariants remain strong and
the intended visual changes are explicitly accounted for.

## 6. Documentation and report

Update the project documentation to explain:

- where restored image resources live;
- any conversion mechanism and required tools;
- how figure restoration is reproduced by a clean build;
- what remains missing or deferred and why.

In this journal's `DONE.md`, give a concise synthesis with links to the
detailed inventory and validation documents under `new/latex/`. Do not turn
`DONE.md` into a command transcript.

## Acceptance criteria

The task is complete when the historical image resources have been
systematically inventoried, every safely reusable figure has been restored to
the reconstructed document, unresolved resources remain explicitly deferred,
and the complete project builds and validates without altering unrelated
content.
