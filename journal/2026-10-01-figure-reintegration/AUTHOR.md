# Author intent — Figure reintegration

The reconstructed LaTeX document currently preserves figure numbering,
captions, labels, and references, but the image resources themselves were
deliberately deferred during Phase 1.

The next task is to determine which historical images already exist in the
repository and can therefore be restored without regenerating them. The
historical tree contains several kinds of material, including PostScript and
EPS resources and older 1993 material reused in the 1994 DEA. Some historical
directories may contain symbolic links or equivalent indirections to material
stored elsewhere.

The work should first establish a reliable inventory: what the reconstructed
document expects, what historical resource corresponds to each expectation,
what is actually present, and what is genuinely missing.

Once that inventory is understood, restore the figures for which usable
historical resources are available. Modify the reconstructed LaTeX project so
that it uses those resources while preserving the document's existing
captions, labels, numbering, references, and scientific content.

Do not regenerate missing images merely to make the document look complete.
Missing or ambiguous resources should remain explicitly identified for later
work.
