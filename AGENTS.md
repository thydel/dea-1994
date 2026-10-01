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

Each journal directory contains a `README.md` that is the authoritative
chronological record for that work session or topic. The README may contain
multiple successive sections and directives. Continue adding sections to the
same journal while the work remains part of the same day's topic. Start a new
journal directory when the date changes or when the work moves to a
substantially different topic.

A journal directory may also contain supporting artifacts specific to that
work: scripts, test data, intermediate results, notes, or other files needed
to make the work reproducible and understandable.

Journal history is append-oriented. Preserve earlier directives and their
context rather than rewriting history after they have been acted upon. If a
later directive changes or supersedes an earlier one, record that explicitly
in a new section.

When asked to execute the latest additions to the current work journal, read
the complete journal README for context, identify the latest unexecuted
directive or additions, and execute them in accordance with this file and the
repository's other applicable specifications.

Interactive instructions to Codex should normally serve only to identify the
journal or directive to execute. Material requirements, decisions,
corrections, and acceptance criteria belong in the version-controlled
journal.

## Author intent and independent review

Each journal directory may contain three documents with distinct roles:

- `AUTHOR.md` records the human author's intent as reconstructed from the
  conversation. It should be concise and faithful to the request, without
  expanding it into an implementation specification.
- `README.md` is the operational work journal: it contains the formalized
  directives, implementation decisions, execution notes, and outcomes.
- `REVIEW.md` records independent reviews of completed work against both the
  author's intent and the operational directive.

`AUTHOR.md` and `REVIEW.md` are independent records. Codex may read them for
context but must not create, rewrite, append to, or otherwise modify them.
They are maintained outside the implementation agent's execution role.

Both author-intent and review history are append-oriented. When reconstructed
retrospectively, say so explicitly rather than implying that the record
existed before the work was performed.

A review should identify the commit or result examined, its scope, material
findings, any open issues, and the review conclusion. Multiple review passes
for the same journal are appended as successive sections of `REVIEW.md`.

The intended workflow is:

human intent (`AUTHOR.md`) -> operational directive (`README.md`) -> Codex
implementation -> commit -> independent review (`REVIEW.md`) -> human
decision.
