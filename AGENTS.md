# Repository instructions

The historical source tree under `old/` is immutable. Never modify files
under `old/`.

New implementation work belongs under `new/`. Work directives and their
supporting journal artifacts belong under `journal/`.

Inspect the repository before changing it, make incremental changes, compile
and test when applicable, diagnose failures, and iterate until the applicable
acceptance criteria are met.

Do not alter the intellectual or scientific content merely to modernize it.
If a substantive ambiguity is encountered, do not guess: preserve it or
report it for human review.

## Text formatting

Markdown prose must be hard-wrapped at 70 columns, in the style of Emacs
`fill-column: 70` and `fill-paragraph`, rather than stored as one physical
line per paragraph.

Do not hard-wrap constructs for which physical line breaks are significant or
where wrapping would damage syntax, including code blocks, tables, URLs, and
other machine-sensitive text.

## Work journal and communication protocol

Substantive work instructions must be recorded in the repository before they
are executed. Do not rely on ad hoc interactive prompts as the authoritative
source of a work directive.

Work journals are organized as dated, topic-specific directories. A journal
directory is named with an ISO date followed by a short topic identifier, for
example:

`journal/2026-10-01-latex-reconstruction/`

Continue using the same journal while the work remains part of the same
day's topic. Start a new journal directory when the date changes or when the
work moves to a substantially different topic.

Each journal directory uses these records:

- `README.md` is a concise index explaining the journal and its contents.
- `AUTHOR.md` records the human author's intent as reconstructed from the
  conversation. It stays close to the request and does not expand it into an
  implementation specification.
- `PROMPT.md` is the append-oriented chronological record of operational
  directives given to Codex. Successive directives, corrections, and
  additions are appended rather than silently rewriting executed history.
- `DONE.md` is Codex's append-oriented chronological report of work
  performed. After each work pass, Codex must add a concise account of what
  it changed, the important files affected or created, validation performed,
  remaining issues, and links or paths to more detailed documentation.
- `REVIEW.md` records independent reviews of completed work against both
  `AUTHOR.md` and `PROMPT.md`.

A journal may also contain supporting inputs or artifacts such as
specifications, manuals, grammar files, test data, examples, scripts, or
other material referenced by `PROMPT.md`.

Do not turn `DONE.md` into a command transcript. Detailed execution traces
belong to a separate logging mechanism if one is adopted later. When the
implemented artifact has its own README, validation report, resource audit,
or other detailed documentation, keep that documentation with the artifact
and point to it from `DONE.md` rather than duplicating it.

`AUTHOR.md` and `REVIEW.md` are independent records. Codex may read them
for context but must not create, rewrite, append to, or otherwise modify
them. They are maintained outside the implementation agent's execution role.
Codex owns its additions to `DONE.md`; operational directives in
`PROMPT.md` are supplied outside Codex's execution role.

Retrospective records must say so explicitly rather than implying that they
existed before the work was performed.

When asked to execute the latest additions to a journal, read its
`README.md`, the complete `PROMPT.md`, and any referenced supporting
material needed for context. Identify the latest unexecuted directive and
execute it in accordance with this file and the repository's other
applicable specifications.

Interactive instructions to Codex should normally serve only to identify the
journal or directive to execute. Material requirements, decisions,
corrections, and acceptance criteria belong in the version-controlled
`PROMPT.md`.

The intended workflow is:

human intent (`AUTHOR.md`) -> operational directives (`PROMPT.md`) ->
Codex implementation -> work report (`DONE.md`) -> independent review
(`REVIEW.md`) -> human decision.

`README.md` is the navigation entry point for that chain.
