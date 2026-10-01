# Repository instructions

The historical source tree under `old/` is immutable. Never modify files under `old/`.

New work belongs under `new/`.

For the current LaTeX reconstruction task, read and follow the complete specification in:

`new/2026-10-01-work-latex-phase-1.md`

Follow its constraints and acceptance criteria. Inspect the repository before changing it, make incremental changes, compile and test the result, diagnose failures, and iterate until the acceptance criteria are met.

Do not alter the intellectual or scientific content merely to modernize it. If a substantive ambiguity is encountered, do not guess: preserve it or report it for human review.

## Work journal and communication protocol

Substantive work instructions must be recorded in the repository
before they are executed. Do not rely on ad hoc interactive prompts as
the authoritative source of a work directive.

Work journals are organized as dated, topic-specific directories. A
journal directory is named with an ISO date followed by a short topic
identifier, for example:

`journal/2026-10-01-latex-reconstruction/`

Each journal directory contains a `README.md` that is the
authoritative chronological record for that work session or topic. The
README may contain multiple successive sections and
directives. Continue adding sections to the same journal while the
work remains part of the same day's topic. Start a new journal
directory when the date changes or when the work moves to a
substantially different topic.

A journal directory may also contain supporting artifacts specific to
that work: scripts, test data, intermediate results, notes, or other
files needed to make the work reproducible and understandable.

Journal history is append-oriented. Preserve earlier directives and
their context rather than rewriting history after they have been acted
upon. If a later directive changes or supersedes an earlier one,
record that explicitly in a new section.

When asked to execute the latest additions to the current work
journal, read the complete journal README for context, identify the
latest unexecuted directive or additions, and execute them in
accordance with this file and the repository's other applicable
specifications.

Interactive instructions to Codex should normally serve only to
identify the journal or directive to execute. Material requirements,
decisions, corrections, and acceptance criteria belong in the
version-controlled journal.
