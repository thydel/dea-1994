# Historical figure inventory

Inventory completed before image conversion or loading. Every expected
image is traced through the exact source argument, the successful 1994
log and surviving link chains.

The scan covers 2567 file paths under the complete historical tree,
including 1993 resources, 1994 resources, older roff material and XV
thumbnails. Tables and data/source files are classified separately and
never selected as images.

The dump Makefile documents the union of `dump-93/*.ps`,
`dump-94/*.eps` and `dump-94/*.ps`. The links select the backing
files; identical stems elsewhere do not override the exact path
recorded in `top.log`. Dump/plot versions of `anneal-01`, `anneal-02`,
`anneal-03`, `anneal-sum` and `lifex-sum-*` are distinct and remain
distinct.

The full machine-readable record is `figure-manifest.json`. It
includes every matching basename, actual format, hash, symbolic-link
chain, selected source and derivative path.

## Mapping of all image occurrences

| Expected resource | Figure label / number | Exact logged file | Link chain / canonical source | Actual format | Disposition | Local derivative |
|---|---|---|---|---|---|---|
| `../dump/casNew` | `dump-casNew` (1.1) | `../dump/casNew.ps` | `old/txt/dump/casNew.ps` → `../dump-93/casNew.ps`; `old/txt/dump-93/casNew.ps` | PS | restored | `figures/pdf/dump/casNew.pdf` |
| `../dump/superglider` | `dump-superglider` (1.2) | `../dump/superglider.eps` | `old/txt/dump/superglider.eps` → `../dump-94/superglider.eps`; `old/txt/dump-94/superglider.eps` | EPS | restored | `figures/pdf/dump/superglider.pdf` |
| `../fig/timepyrcub` | `fig-timepyrcub` (1.3) | `../fig/timepyrcub.eps` | `old/txt/fig/timepyrcub.eps` | EPS | restored | `figures/pdf/fig/timepyrcub.pdf` |
| `../dump/tsum-128x3-diag` | `dump-tsum-128x3-diag` (1.4) | `../dump/tsum-128x3-diag.ps` | `old/txt/dump/tsum-128x3-diag.ps` → `../dump-94/tsum-128x3-diag.ps`; `old/txt/dump-94/tsum-128x3-diag.ps` | EPS | restored | `figures/pdf/dump/tsum-128x3-diag.pdf` |
| `../dump/life-256x3-rel` | `dump-life-256x3-rel` (1.5) | `../dump/life-256x3-rel.ps` | `old/txt/dump/life-256x3-rel.ps` → `../dump-94/life-256x3-rel.ps`; `old/txt/dump-94/life-256x3-rel.ps` | EPS | restored | `figures/pdf/dump/life-256x3-rel.pdf` |
| `../dump/life-256x3-relmov` | `dump-life-256x3-relmov` (1.6) | `../dump/life-256x3-relmov.ps` | `old/txt/dump/life-256x3-relmov.ps` → `../dump-94/life-256x3-relmov.ps`; `old/txt/dump-94/life-256x3-relmov.ps` | EPS | restored | `figures/pdf/dump/life-256x3-relmov.pdf` |
| `../dump/anneal-256x3-rel` | `dump-anneal-256x3-rel` (1.7) | `../dump/anneal-256x3-rel.ps` | `old/txt/dump/anneal-256x3-rel.ps` → `../dump-94/anneal-256x3-rel.ps`; `old/txt/dump-94/anneal-256x3-rel.ps` | EPS | restored | `figures/pdf/dump/anneal-256x3-rel.pdf` |
| `../fig/transcub` | `fig-transcub` (1.8) | `../fig/transcub.eps` | `old/txt/fig/transcub.eps` | EPS | restored | `figures/pdf/fig/transcub.pdf` |
| `../dump/anneal-256x3-diag` | `dump-anneal-256x3-diag` (1.9) | `../dump/anneal-256x3-diag.ps` | `old/txt/dump/anneal-256x3-diag.ps` → `../dump-94/anneal-256x3-diag.ps`; `old/txt/dump-94/anneal-256x3-diag.ps` | EPS | restored | `figures/pdf/dump/anneal-256x3-diag.pdf` |
| `../dump/tsum-128x3-faces` | `dump-tsum-128x3-faces` (1.10) | `../dump/tsum-128x3-faces.ps` | `old/txt/dump/tsum-128x3-faces.ps` → `../dump-94/tsum-128x3-faces.ps`; `old/txt/dump-94/tsum-128x3-faces.ps` | EPS | restored | `figures/pdf/dump/tsum-128x3-faces.pdf` |
| `../dump/tsum-128x3-trans-bits` | `dump-tsum-128x3-trans-bits` (1.11) | `../dump/tsum-128x3-trans-bits.ps` | `old/txt/dump/tsum-128x3-trans-bits.ps` → `../dump-94/tsum-128x3-trans-bits.ps`; `old/txt/dump-94/tsum-128x3-trans-bits.ps` | EPS | restored | `figures/pdf/dump/tsum-128x3-trans-bits.pdf` |
| `../dump/tsum-128x3-trans-byte` | `dump-tsum-128x3-trans-byte` (1.12) | `../dump/tsum-128x3-trans-byte.ps` | `old/txt/dump/tsum-128x3-trans-byte.ps` → `../dump-94/tsum-128x3-trans-byte.ps`; `old/txt/dump-94/tsum-128x3-trans-byte.ps` | EPS | restored | `figures/pdf/dump/tsum-128x3-trans-byte.pdf` |
| `../dump/anneal-256x3-trans-bits` | `dump-anneal-256x3-trans-bits` (1.13) | `../dump/anneal-256x3-trans-bits.ps` | `old/txt/dump/anneal-256x3-trans-bits.ps` → `../dump-94/anneal-256x3-trans-bits.ps`; `old/txt/dump-94/anneal-256x3-trans-bits.ps` | EPS | restored | `figures/pdf/dump/anneal-256x3-trans-bits.pdf` |
| `../dump/life-256x3-trans-bits` | `dump-life-256x3-trans-bits` (1.14) | `../dump/life-256x3-trans-bits.ps` | `old/txt/dump/life-256x3-trans-bits.ps` → `../dump-94/life-256x3-trans-bits.ps`; `old/txt/dump-94/life-256x3-trans-bits.ps` | EPS | restored | `figures/pdf/dump/life-256x3-trans-bits.pdf` |
| `../dump/tsum-128x3-relmovedge` | `dump-tsum-128x3-relmovedge` (1.15) | `../dump/tsum-128x3-relmovedge.ps` | `old/txt/dump/tsum-128x3-relmovedge.ps` → `../dump-94/tsum-128x3-relmovedge.ps`; `old/txt/dump-94/tsum-128x3-relmovedge.ps` | EPS | restored | `figures/pdf/dump/tsum-128x3-relmovedge.pdf` |
| `../dump/anneal-sum-1k-8k` | `dump-anneal-sum-1k-8k` (1.16) | `../dump/anneal-sum-1k-8k.ps` | `old/txt/dump/anneal-sum-1k-8k.ps` → `../dump-93/anneal-sum-1k-8k.ps`; `old/txt/dump-93/anneal-sum-1k-8k.ps` | EPS | restored | `figures/pdf/dump/anneal-sum-1k-8k.pdf` |
| `../dump/anneal-sum-1k-8k-xv` | `dump-anneal-sum-1k-8k-xv` (1.17) | `../dump/anneal-sum-1k-8k-xv.ps` | `old/txt/dump/anneal-sum-1k-8k-xv.ps` → `../dump-93/anneal-sum-1k-8k-xv.ps`; `old/txt/dump-93/anneal-sum-1k-8k-xv.ps` | EPS | restored | `figures/pdf/dump/anneal-sum-1k-8k-xv.pdf` |
| `../dump/neighburhood-size-tbl-16xor9` | `dump-neighburhood-size-tbl-16xor9` (2.1) | `../dump/neighburhood-size-tbl-16xor9.ps` | `old/txt/dump/neighburhood-size-tbl-16xor9.ps` → `../dump-93/neighburhood-size-tbl-16xor9.ps`; `old/txt/dump-93/neighburhood-size-tbl-16xor9.ps` | EPS | restored | `figures/pdf/dump/neighburhood-size-tbl-16xor9.pdf` |
| `../dump/tsum-128-edge` | `dump-tsum-128-edge` (2.2) | `../dump/tsum-128-edge.ps` | `old/txt/dump/tsum-128-edge.ps` → `../dump-93/tsum-128-edge.ps`; `old/txt/dump-93/tsum-128-edge.ps` | EPS | restored | `figures/pdf/dump/tsum-128-edge.pdf` |
| `../dump/anneal-g128-s11` | `dump-anneal-g128-s11` (2.3) | `../dump/anneal-g128-s11.ps` | `old/txt/dump/anneal-g128-s11.ps` → `../dump-93/anneal-g128-s11.ps`; `old/txt/dump-93/anneal-g128-s11.ps` | EPS | restored | `figures/pdf/dump/anneal-g128-s11.pdf` |
| `../dump/tube-worm-mix` | `dump-tube-worm-mix` (2.4) | `../dump/tube-worm-mix.ps` | `old/txt/dump/tube-worm-mix.ps` → `../dump-93/tube-worm-mix.ps`; `old/txt/dump-93/tube-worm-mix.ps` | EPS | restored | `figures/pdf/dump/tube-worm-mix.pdf` |
| `../dump/tsum-grey` | `dump-tsum-grey` (2.5) | `../dump/tsum-grey.ps` | `old/txt/dump/tsum-grey.ps` → `../dump-93/tsum-grey.ps`; `old/txt/dump-93/tsum-grey.ps` | EPS | restored | `figures/pdf/dump/tsum-grey.pdf` |
| `../dump/tsum` | `dump-tsum` (2.6) | `../dump/tsum.ps` | `old/txt/dump/tsum.ps` → `../dump-93/tsum.ps`; `old/txt/dump-93/tsum.ps` | EPS | restored | `figures/pdf/dump/tsum.pdf` |
| `../dump/tsum-ray-one` | `dump-tsum-ray-one` (2.7) | `../dump/tsum-ray-one.ps` | `old/txt/dump/tsum-ray-one.ps` → `../dump-93/tsum-ray-one.ps`; `old/txt/dump-93/tsum-ray-one.ps` | EPS | restored | `figures/pdf/dump/tsum-ray-one.pdf` |
| `../dump/tsum-ray-all` | `dump-tsum-ray-all` (2.8) | `../dump/tsum-ray-all.ps` | `old/txt/dump/tsum-ray-all.ps` → `../dump-93/tsum-ray-all.ps`; `old/txt/dump-93/tsum-ray-all.ps` | EPS | restored | `figures/pdf/dump/tsum-ray-all.pdf` |
| `../plot/anneal-sum` | `plot-anneal-sum` (2.9) | `../plot/anneal-sum.ps` | `old/txt/plot/anneal-sum.ps` → `../plot-93/anneal-sum.ps`; `old/txt/plot-93/anneal-sum.ps` | PS | restored | `figures/pdf/plot/anneal-sum.pdf` |
| `../dump/anneal-sum` | `dump-anneal-sum` (2.10) | `../dump/anneal-sum.ps` | `old/txt/dump/anneal-sum.ps` → `../dump-93/anneal-sum.ps`; `old/txt/dump-93/anneal-sum.ps` | EPS | restored | `figures/pdf/dump/anneal-sum.pdf` |
| `../dump/life-time-xor` | `dump-life-time-xor` (2.11) | `../dump/life-time-xor.ps` | `old/txt/dump/life-time-xor.ps` → `../dump-93/life-time-xor.ps`; `old/txt/dump-93/life-time-xor.ps` | EPS | restored | `figures/pdf/dump/life-time-xor.pdf` |
| `../plot/lifex` | `plot-lifex` (2.12) | `../plot/lifex.ps` | `old/txt/plot/lifex.ps` → `../plot-93/lifex.ps`; `old/txt/plot-93/lifex.ps` | PS | restored | `figures/pdf/plot/lifex.pdf` |
| `../plot/lifex-sum-1` | `plot-lifex-sum-1+lifex-sum-2` (2.13) | `../plot/lifex-sum-1.ps` | `old/txt/plot/lifex-sum-1.ps` → `../plot-93/lifex-sum-1.ps`; `old/txt/plot-93/lifex-sum-1.ps` | PS | restored | `figures/pdf/plot/lifex-sum-1.pdf` |
| `../plot/lifex-sum-2` | `plot-lifex-sum-1+lifex-sum-2` (2.13) | `../plot/lifex-sum-2.ps` | `old/txt/plot/lifex-sum-2.ps` → `../plot-93/lifex-sum-2.ps`; `old/txt/plot-93/lifex-sum-2.ps` | PS | restored | `figures/pdf/plot/lifex-sum-2.pdf` |
| `../dump/life-3d-New` | `dump-life-3d-New` (2.14) | `../dump/life-3d-New.ps` | `old/txt/dump/life-3d-New.ps` → `../dump-93/life-3d-New.ps`; `old/txt/dump-93/life-3d-New.ps` | PS | restored | `figures/pdf/dump/life-3d-New.pdf` |
| `../dump/anneal-time-xor` | `dump-anneal-time-xor` (2.15) | `../dump/anneal-time-xor.ps` | `old/txt/dump/anneal-time-xor.ps` → `../dump-93/anneal-time-xor.ps`; `old/txt/dump-93/anneal-time-xor.ps` | EPS | restored | `figures/pdf/dump/anneal-time-xor.pdf` |
| `../plot/anneal-pop` | `plot-anneal-pop+anneal-pop-detail` (2.16) | `../plot/anneal-pop.ps` | `old/txt/plot/anneal-pop.ps` → `../plot-93/anneal-pop.ps`; `old/txt/plot-93/anneal-pop.ps` | PS | restored | `figures/pdf/plot/anneal-pop.pdf` |
| `../plot/anneal-pop-detail` | `plot-anneal-pop+anneal-pop-detail` (2.16) | `../plot/anneal-pop-detail.ps` | `old/txt/plot/anneal-pop-detail.ps` → `../plot-93/anneal-pop-detail.ps`; `old/txt/plot-93/anneal-pop-detail.ps` | PS | restored | `figures/pdf/plot/anneal-pop-detail.pdf` |
| `../plot/heart-pop` | `plot-heart-pop+heart-pop-detail` (2.17) | `../plot/heart-pop.ps` | `old/txt/plot/heart-pop.ps` → `../plot-93/heart-pop.ps`; `old/txt/plot-93/heart-pop.ps` | PS | restored | `figures/pdf/plot/heart-pop.pdf` |
| `../plot/heart-pop-detail` | `plot-heart-pop+heart-pop-detail` (2.17) | `../plot/heart-pop-detail.ps` | `old/txt/plot/heart-pop-detail.ps` → `../plot-93/heart-pop-detail.ps`; `old/txt/plot-93/heart-pop-detail.ps` | PS | restored | `figures/pdf/plot/heart-pop-detail.pdf` |
| `../dump/loop-1024` | `dump-loop-1024` (2.18) | `../dump/loop-1024.ps` | `old/txt/dump/loop-1024.ps` → `../dump-93/loop-1024.ps`; `old/txt/dump-93/loop-1024.ps` | EPS | restored | `figures/pdf/dump/loop-1024.pdf` |
| `../fig/func-1` | `fig-func-1` (2.19) | `../fig/func-1.ps` | `old/txt/fig/func-1.ps` | EPS | restored | `figures/pdf/fig/func-1.pdf` |
| `../fig/apply-1` | `fig-apply-1` (2.20) | `../fig/apply-1.ps` | `old/txt/fig/apply-1.ps` | EPS | restored | `figures/pdf/fig/apply-1.pdf` |
| `../fig/apply-2` | `fig-apply-2` (2.21) | `../fig/apply-2.ps` | `old/txt/fig/apply-2.ps` | PS | restored | `figures/pdf/fig/apply-2.pdf` |
| `../fig/func-2` | `fig-func-2` (2.22) | `../fig/func-2.ps` | `old/txt/fig/func-2.ps` | EPS | restored | `figures/pdf/fig/func-2.pdf` |
| `../fig/func-3` | `fig-func-3` (2.23) | `../fig/func-3.ps` | `old/txt/fig/func-3.ps` | EPS | restored | `figures/pdf/fig/func-3.pdf` |
| `../fig/func-4` | `fig-func-4` (2.24) | `../fig/func-4.ps` | `old/txt/fig/func-4.ps` | PS | restored | `figures/pdf/fig/func-4.pdf` |
| `../fig/func-7` | `fig-func-7` (2.25) | `../fig/func-7.ps` | `old/txt/fig/func-7.ps` | EPS | restored | `figures/pdf/fig/func-7.pdf` |
| `../fig/gap-pe` | `fig-gap-pe` (2.26) | `../fig/gap-pe.ps` | `old/txt/fig/gap-pe.ps` | EPS | restored | `figures/pdf/fig/gap-pe.pdf` |
| `../fig/gap` | `fig-gap` (2.27) | `../fig/gap.ps` | `old/txt/fig/gap.ps` | PS | restored | `figures/pdf/fig/gap.pdf` |
| `../fig/life-dfa` | `fig-life-dfa` (2.34) | `../fig/life-dfa.ps` | `old/txt/fig/life-dfa.ps` | EPS | restored | `figures/pdf/fig/life-dfa.pdf` |
| `../fig/life-tree` | `fig-life-tree` (2.35) | `../fig/life-tree.ps` | `old/txt/fig/life-tree.ps` | EPS | restored | `figures/pdf/fig/life-tree.pdf` |
| `../dump/cantata-1` | `dump-cantata-1` (2.36) | `../dump/cantata-1.ps` | `old/txt/dump/cantata-1.ps` → `../dump-94/cantata-1.ps`; `old/txt/dump-94/cantata-1.ps` | EPS | restored | `figures/pdf/dump/cantata-1.pdf` |
| `../dump/cantata-mk-rule` | `dump-cantata-mk-rule+cantata-cell` (2.37) | `../dump/cantata-mk-rule.ps` | `old/txt/dump/cantata-mk-rule.ps` → `../dump-94/cantata-mk-rule.ps`; `old/txt/dump-94/cantata-mk-rule.ps` | EPS | restored | `figures/pdf/dump/cantata-mk-rule.pdf` |
| `../dump/cantata-cell` | `dump-cantata-mk-rule+cantata-cell` (2.37) | `../dump/cantata-cell.ps` | `old/txt/dump/cantata-cell.ps` → `../dump-94/cantata-cell.ps`; `old/txt/dump-94/cantata-cell.ps` | EPS | restored | `figures/pdf/dump/cantata-cell.pdf` |
| `../plot/lambda` | `plot-lambda+flip` (3.1) | `../plot/lambda.ps` | `old/txt/plot/lambda.ps` → `../plot-94/lambda.ps`; `old/txt/plot-94/lambda.ps` | PS | restored | `figures/pdf/plot/lambda.pdf` |
| `../plot/flip` | `plot-lambda+flip` (3.1) | `../plot/flip.ps` | `old/txt/plot/flip.ps` → `../plot-94/flip.ps`; `old/txt/plot-94/flip.ps` | PS | restored | `figures/pdf/plot/flip.pdf` |
| `../plot/lambda-deriv` | `plot-lambda-deriv+flip-deriv` (3.2) | `../plot/lambda-deriv.ps` | `old/txt/plot/lambda-deriv.ps` → `../plot-94/lambda-deriv.ps`; `old/txt/plot-94/lambda-deriv.ps` | PS | restored | `figures/pdf/plot/lambda-deriv.pdf` |
| `../plot/flip-deriv` | `plot-lambda-deriv+flip-deriv` (3.2) | `../plot/flip-deriv.ps` | `old/txt/plot/flip-deriv.ps` → `../plot-94/flip-deriv.ps`; `old/txt/plot-94/flip-deriv.ps` | PS | restored | `figures/pdf/plot/flip-deriv.pdf` |
| `../plot/lambda-prob` | `plot-lambda-prob+flip-prob` (3.3) | `../plot/lambda-prob.ps` | `old/txt/plot/lambda-prob.ps` → `../plot-94/lambda-prob.ps`; `old/txt/plot-94/lambda-prob.ps` | PS | restored | `figures/pdf/plot/lambda-prob.pdf` |
| `../plot/flip-prob` | `plot-lambda-prob+flip-prob` (3.3) | `../plot/flip-prob.ps` | `old/txt/plot/flip-prob.ps` → `../plot-94/flip-prob.ps`; `old/txt/plot-94/flip-prob.ps` | PS | restored | `figures/pdf/plot/flip-prob.pdf` |
| `../plot/lambda-versus-prob` | `plot-lambda-versus-prob+flip-versus-prob` (3.4) | `../plot/lambda-versus-prob.ps` | `old/txt/plot/lambda-versus-prob.ps` → `../plot-94/lambda-versus-prob.ps`; `old/txt/plot-94/lambda-versus-prob.ps` | PS | restored | `figures/pdf/plot/lambda-versus-prob.pdf` |
| `../plot/flip-versus-prob` | `plot-lambda-versus-prob+flip-versus-prob` (3.4) | `../plot/flip-versus-prob.ps` | `old/txt/plot/flip-versus-prob.ps` → `../plot-94/flip-versus-prob.ps`; `old/txt/plot-94/flip-versus-prob.ps` | PS | restored | `figures/pdf/plot/flip-versus-prob.pdf` |
| `../plot/lambda-flip-hist` | `plot-lambda-flip-hist+lambda-versus-flip` (3.5) | `../plot/lambda-flip-hist.ps` | `old/txt/plot/lambda-flip-hist.ps` → `../plot-94/lambda-flip-hist.ps`; `old/txt/plot-94/lambda-flip-hist.ps` | PS | restored | `figures/pdf/plot/lambda-flip-hist.pdf` |
| `../plot/lambda-versus-flip` | `plot-lambda-flip-hist+lambda-versus-flip` (3.5) | `../plot/lambda-versus-flip.ps` | `old/txt/plot/lambda-versus-flip.ps` → `../plot-94/lambda-versus-flip.ps`; `old/txt/plot-94/lambda-versus-flip.ps` | PS | restored | `figures/pdf/plot/lambda-versus-flip.pdf` |
| `../plot/lambda-flip-ratio-sorted` | `plot-lambda-flip-ratio-sorted+lambda-flip-prob-sorted` (3.6) | `../plot/lambda-flip-ratio-sorted.ps` | `old/txt/plot/lambda-flip-ratio-sorted.ps` → `../plot-94/lambda-flip-ratio-sorted.ps`; `old/txt/plot-94/lambda-flip-ratio-sorted.ps` | PS | restored | `figures/pdf/plot/lambda-flip-ratio-sorted.pdf` |
| `../plot/lambda-flip-prob-sorted` | `plot-lambda-flip-ratio-sorted+lambda-flip-prob-sorted` (3.6) | `../plot/lambda-flip-prob-sorted.ps` | `old/txt/plot/lambda-flip-prob-sorted.ps` → `../plot-94/lambda-flip-prob-sorted.ps`; `old/txt/plot-94/lambda-flip-prob-sorted.ps` | PS | restored | `figures/pdf/plot/lambda-flip-prob-sorted.pdf` |
| `../plot/E-lambda-1` | `plot-E-lambda-1` (3.7) | `../plot/E-lambda-1.ps` | `old/txt/plot/E-lambda-1.ps` → `../plot-94/E-lambda-1.ps`; `old/txt/plot-94/E-lambda-1.ps` | PS | restored | `figures/pdf/plot/E-lambda-1.pdf` |
| `../dump/anneal-3d` | `dump-anneal-3d` (4.1) | `../dump/anneal-3d.ps` | `old/txt/dump/anneal-3d.ps` → `../dump-93/anneal-3d.ps`; `old/txt/dump-93/anneal-3d.ps` | EPS | restored | `figures/pdf/dump/anneal-3d.pdf` |
| `../dump/life-00` | `dump-life-00` (4.2) | `../dump/life-00.eps` | `old/txt/dump/life-00.eps` → `../dump-94/life-00.eps`; `old/txt/dump-94/life-00.eps` | EPS | restored | `figures/pdf/dump/life-00.pdf` |
| `../dump/anneal-00` | `dump-anneal-00` (4.3) | `../dump/anneal-00.eps` | `old/txt/dump/anneal-00.eps` → `../dump-94/anneal-00.eps`; `old/txt/dump-94/anneal-00.eps` | EPS | restored | `figures/pdf/dump/anneal-00.pdf` |
| `../dump/anneal-03` | `dump-anneal-03` (4.4) | `../dump/anneal-03.eps` | `old/txt/dump/anneal-03.eps` → `../dump-94/anneal-03.eps`; `old/txt/dump-94/anneal-03.eps` | EPS | restored | `figures/pdf/dump/anneal-03.pdf` |
| `../dump/anneal-02` | `dump-anneal-02` (4.5) | `../dump/anneal-02.eps` | `old/txt/dump/anneal-02.eps` → `../dump-94/anneal-02.eps`; `old/txt/dump-94/anneal-02.eps` | PS | restored | `figures/pdf/dump/anneal-02.pdf` |
| `../dump/anneal-01` | `dump-anneal-01` (4.6) | `../dump/anneal-01.eps` | `old/txt/dump/anneal-01.eps` → `../dump-94/anneal-01.eps`; `old/txt/dump-94/anneal-01.eps` | PS | restored | `figures/pdf/dump/anneal-01.pdf` |
| `../plot/anneal-01` | `plot-anneal-01` (4.7) | `../plot/anneal-01.eps` | `old/txt/plot/anneal-01.eps` → `../plot-94/anneal-01.eps`; `old/txt/plot-94/anneal-01.eps` → `anneal-size-10-front.eps`; `old/txt/plot-94/anneal-size-10-front.eps` | PS | restored | `figures/pdf/plot/anneal-01.pdf` |
| `../plot/anneal-02` | `plot-anneal-02` (4.8) | `../plot/anneal-02.eps` | `old/txt/plot/anneal-02.eps` → `../plot-94/anneal-02.eps`; `old/txt/plot-94/anneal-02.eps` → `anneal-size=1024-trans=30k+dump.eps`; `old/txt/plot-94/anneal-size=1024-trans=30k+dump.eps` | PS | restored | `figures/pdf/plot/anneal-02.pdf` |
| `../plot/anneal-03` | `plot-anneal-03` (4.9) | `../plot/anneal-03.eps` | `old/txt/plot/anneal-03.eps` → `../plot-94/anneal-03.eps`; `old/txt/plot-94/anneal-03.eps` → `anneal-size=1024-trans=82k+dump.eps`; `old/txt/plot-94/anneal-size=1024-trans=82k+dump.eps` | PS | restored | `figures/pdf/plot/anneal-03.pdf` |
| `../plot/anneal-04` | `plot-anneal-04` (4.10) | `../plot/anneal-04.eps` | `old/txt/plot/anneal-04.eps` → `../plot-94/anneal-04.eps`; `old/txt/plot-94/anneal-04.eps` → `anneal-size=128:1024-scaled.eps`; `old/txt/plot-94/anneal-size=128:1024-scaled.eps` | PS | restored | `figures/pdf/plot/anneal-04.pdf` |
| `../plot/anneal-05` | `plot-anneal-05` (4.11) | `../plot/anneal-05.eps` | `old/txt/plot/anneal-05.eps` → `../plot-94/anneal-05.eps`; `old/txt/plot-94/anneal-05.eps` → `anneal-size=256.eps`; `old/txt/plot-94/anneal-size=256.eps` | PS | restored | `figures/pdf/plot/anneal-05.pdf` |
| `../dump/xu-photo-1` | `dump-xu-photo-1` (5.1) | `../dump/xu-photo-1.ps` | `old/txt/dump/xu-photo-1.ps` → `../dump-93/xu-photo-1.ps`; `old/txt/dump-93/xu-photo-1.ps` | EPS | restored | `figures/pdf/dump/xu-photo-1.pdf` |
| `../dump/xu-photo-1-top` | `dump-xu-photo-1-top` (5.2) | `../dump/xu-photo-1-top.ps` | `old/txt/dump/xu-photo-1-top.ps` → `../dump-93/xu-photo-1-top.ps`; `old/txt/dump-93/xu-photo-1-top.ps` | EPS | restored | `figures/pdf/dump/xu-photo-1-top.pdf` |
| `../dump/xu-Cfilm-1-1` | `dump-xu-Cfilm-1-1` (5.3) | `../dump/xu-Cfilm-1-1.ps` | `old/txt/dump/xu-Cfilm-1-1.ps` → `../dump-93/xu-Cfilm-1-1.ps`; `old/txt/dump-93/xu-Cfilm-1-1.ps` | EPS | restored | `figures/pdf/dump/xu-Cfilm-1-1.pdf` |
| `../dump/xu-Cfilm-1-2` | `dump-xu-Cfilm-1-2` (5.4) | `../dump/xu-Cfilm-1-2.ps` | `old/txt/dump/xu-Cfilm-1-2.ps` → `../dump-93/xu-Cfilm-1-2.ps`; `old/txt/dump-93/xu-Cfilm-1-2.ps` | EPS | restored | `figures/pdf/dump/xu-Cfilm-1-2.pdf` |
| `../dump/xu-Cfilm-2-1` | `dump-xu-Cfilm-2-1` (5.5) | `../dump/xu-Cfilm-2-1.ps` | `old/txt/dump/xu-Cfilm-2-1.ps` → `../dump-93/xu-Cfilm-2-1.ps`; `old/txt/dump-93/xu-Cfilm-2-1.ps` | EPS | restored | `figures/pdf/dump/xu-Cfilm-2-1.pdf` |
| `../dump/xu-Cfilm-2-2` | `dump-xu-Cfilm-2-2` (5.6) | `../dump/xu-Cfilm-2-2.ps` | `old/txt/dump/xu-Cfilm-2-2.ps` → `../dump-93/xu-Cfilm-2-2.ps`; `old/txt/dump-93/xu-Cfilm-2-2.ps` | EPS | restored | `figures/pdf/dump/xu-Cfilm-2-2.pdf` |
| `../plot/rabbit-gnans-1` | `plot-rabbit-gnans-1+rabbit-gnans-2` (B.1) | `../plot/rabbit-gnans-1.ps` | `old/txt/plot/rabbit-gnans-1.ps` → `../plot-93/rabbit-gnans-1.ps`; `old/txt/plot-93/rabbit-gnans-1.ps` | PS | restored | `figures/pdf/plot/rabbit-gnans-1.pdf` |
| `../plot/rabbit-gnans-2` | `plot-rabbit-gnans-1+rabbit-gnans-2` (B.1) | `../plot/rabbit-gnans-2.ps` | `old/txt/plot/rabbit-gnans-2.ps` → `../plot-93/rabbit-gnans-2.ps`; `old/txt/plot-93/rabbit-gnans-2.ps` | PS | restored | `figures/pdf/plot/rabbit-gnans-2.pdf` |
| `../plot/rabbit-1` | `plot-rabbit-1+rabbit-1-512` (B.2) | `../plot/rabbit-1.ps` | `old/txt/plot/rabbit-1.ps` → `../plot-93/rabbit-1.ps`; `old/txt/plot-93/rabbit-1.ps` | PS | restored | `figures/pdf/plot/rabbit-1.pdf` |
| `../plot/rabbit-1-512` | `plot-rabbit-1+rabbit-1-512` (B.2) | `../plot/rabbit-1-512.ps` | `old/txt/plot/rabbit-1-512.ps` → `../plot-93/rabbit-1-512.ps`; `old/txt/plot-93/rabbit-1-512.ps` | PS | restored | `figures/pdf/plot/rabbit-1-512.pdf` |
| `../plot/rabbit-2` | `plot-rabbit-2+rabbit-3` (B.3) | `../plot/rabbit-2.ps` | `old/txt/plot/rabbit-2.ps` → `../plot-93/rabbit-2.ps`; `old/txt/plot-93/rabbit-2.ps` | PS | restored | `figures/pdf/plot/rabbit-2.pdf` |
| `../plot/rabbit-3` | `plot-rabbit-2+rabbit-3` (B.3) | `../plot/rabbit-3.ps` | `old/txt/plot/rabbit-3.ps` → `../plot-93/rabbit-3.ps`; `old/txt/plot-93/rabbit-3.ps` | PS | restored | `figures/pdf/plot/rabbit-3.pdf` |

## All candidates and supporting files

Candidates below include native figure sources, raster antecedents,
table data and thumbnails. Only the exact historical logged resource
is selected for conversion.

### ../dump/casNew

- `old/txt/dump/.xvpics/casNew.ps`: XV thumbnail/cache.
- `old/txt/dump/casNew.ps`: PS; → `old/txt/dump-93/casNew.ps`.
- `old/txt/dump-93/.xvpics/casNew.obj`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/casNew.ps`: XV thumbnail/cache.
- `old/txt/dump-93/casNew.obj`: other source/data.
- `old/txt/dump-93/casNew.ps`: PS.

### ../dump/superglider

- `old/txt/dump/.xvpics/superglider.eps`: XV thumbnail/cache.
- `old/txt/dump/superglider.eps`: EPS; →
  `old/txt/dump-94/superglider.eps`.
- `old/txt/dump-94/.xvpics/superglider.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/superglider.fig`: XV thumbnail/cache.
- `old/txt/dump-94/superglider.eps`: EPS.
- `old/txt/dump-94/superglider.fig`: FIG source.

### ../fig/timepyrcub

- `old/txt/fig/timepyrcub.eps`: EPS.
- `old/txt/fig/timepyrcub.fig`: FIG source.

### ../dump/tsum-128x3-diag

- `old/txt/dump/.xvpics/tsum-128x3-diag.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128x3-diag.ps`: EPS; →
  `old/txt/dump-94/tsum-128x3-diag.ps`.
- `old/txt/dump-94/.xvpics/tsum-128x3-diag.pgm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/tsum-128x3-diag.ps`: XV thumbnail/cache.
- `old/txt/dump-94/tsum-128x3-diag.pgm`: PNM raster.
- `old/txt/dump-94/tsum-128x3-diag.ps`: EPS.

### ../dump/life-256x3-rel

- `old/txt/dump/.xvpics/life-256x3-rel.ps`: XV thumbnail/cache.
- `old/txt/dump/life-256x3-rel.ps`: EPS; →
  `old/txt/dump-94/life-256x3-rel.ps`.
- `old/txt/dump-94/.xvpics/life-256x3-rel.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-256x3-rel.ps`: XV thumbnail/cache.
- `old/txt/dump-94/life-256x3-rel.pbm`: PNM raster.
- `old/txt/dump-94/life-256x3-rel.ps`: EPS.

### ../dump/life-256x3-relmov

- `old/txt/dump/.xvpics/life-256x3-relmov.ps`: XV thumbnail/cache.
- `old/txt/dump/life-256x3-relmov.ps`: EPS; →
  `old/txt/dump-94/life-256x3-relmov.ps`.
- `old/txt/dump-94/.xvpics/life-256x3-relmov.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-256x3-relmov.ps`: XV thumbnail/cache.
- `old/txt/dump-94/life-256x3-relmov.pbm`: PNM raster.
- `old/txt/dump-94/life-256x3-relmov.ps`: EPS.

### ../dump/anneal-256x3-rel

- `old/txt/dump/.xvpics/anneal-256x3-rel.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-256x3-rel.ps`: EPS; →
  `old/txt/dump-94/anneal-256x3-rel.ps`.
- `old/txt/dump-94/.xvpics/anneal-256x3-rel.pgm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-256x3-rel.ps`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-256x3-rel.pgm`: PNM raster.
- `old/txt/dump-94/anneal-256x3-rel.ps`: EPS.

### ../fig/transcub

- `old/txt/fig/transcub.eps`: EPS.
- `old/txt/fig/transcub.fig`: FIG source.

### ../dump/anneal-256x3-diag

- `old/txt/dump/.xvpics/anneal-256x3-diag.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-256x3-diag.ps`: EPS; →
  `old/txt/dump-94/anneal-256x3-diag.ps`.
- `old/txt/dump-94/.xvpics/anneal-256x3-diag.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-256x3-diag.ps`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-256x3-diag.pbm`: PNM raster.
- `old/txt/dump-94/anneal-256x3-diag.ps`: EPS.

### ../dump/tsum-128x3-faces

- `old/txt/dump/.xvpics/tsum-128x3-faces.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128x3-faces.ps`: EPS; →
  `old/txt/dump-94/tsum-128x3-faces.ps`.
- `old/txt/dump-94/.xvpics/tsum-128x3-faces.pgm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/tsum-128x3-faces.ps`: XV thumbnail/cache.
- `old/txt/dump-94/tsum-128x3-faces.pgm`: PNM raster.
- `old/txt/dump-94/tsum-128x3-faces.ps`: EPS.

### ../dump/tsum-128x3-trans-bits

- `old/txt/dump/.xvpics/tsum-128x3-trans-bits.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128x3-trans-bits.ps`: EPS; →
  `old/txt/dump-94/tsum-128x3-trans-bits.ps`.
- `old/txt/dump-94/.xvpics/tsum-128x3-trans-bits.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-94/.xvpics/tsum-128x3-trans-bits.ps`: XV
  thumbnail/cache.
- `old/txt/dump-94/tsum-128x3-trans-bits.pgm`: PNM raster.
- `old/txt/dump-94/tsum-128x3-trans-bits.ps`: EPS.

### ../dump/tsum-128x3-trans-byte

- `old/txt/dump/.xvpics/tsum-128x3-trans-byte.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128x3-trans-byte.ps`: EPS; →
  `old/txt/dump-94/tsum-128x3-trans-byte.ps`.
- `old/txt/dump-94/.xvpics/tsum-128x3-trans-byte.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-94/.xvpics/tsum-128x3-trans-byte.ps`: XV
  thumbnail/cache.
- `old/txt/dump-94/tsum-128x3-trans-byte.pgm`: PNM raster.
- `old/txt/dump-94/tsum-128x3-trans-byte.ps`: EPS.

### ../dump/anneal-256x3-trans-bits

- `old/txt/dump/.xvpics/anneal-256x3-trans-bits.ps`: XV
  thumbnail/cache.
- `old/txt/dump/anneal-256x3-trans-bits.ps`: EPS; →
  `old/txt/dump-94/anneal-256x3-trans-bits.ps`.
- `old/txt/dump-94/.xvpics/anneal-256x3-trans-bits.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-256x3-trans-bits.ps`: XV
  thumbnail/cache.
- `old/txt/dump-94/anneal-256x3-trans-bits.pgm`: PNM raster.
- `old/txt/dump-94/anneal-256x3-trans-bits.ps`: EPS.

### ../dump/life-256x3-trans-bits

- `old/txt/dump/.xvpics/life-256x3-trans-bits.ps`: XV thumbnail/cache.
- `old/txt/dump/life-256x3-trans-bits.ps`: EPS; →
  `old/txt/dump-94/life-256x3-trans-bits.ps`.
- `old/txt/dump-94/.xvpics/life-256x3-trans-bits.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-256x3-trans-bits.ps`: XV
  thumbnail/cache.
- `old/txt/dump-94/life-256x3-trans-bits.pgm`: PNM raster.
- `old/txt/dump-94/life-256x3-trans-bits.ps`: EPS.

### ../dump/tsum-128x3-relmovedge

- `old/txt/dump/.xvpics/tsum-128x3-relmovedge.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128x3-relmovedge.ps`: EPS; →
  `old/txt/dump-94/tsum-128x3-relmovedge.ps`.
- `old/txt/dump-94/.xvpics/tsum-128x3-relmovedge.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-94/.xvpics/tsum-128x3-relmovedge.ps`: XV
  thumbnail/cache.
- `old/txt/dump-94/tsum-128x3-relmovedge.pgm`: PNM raster.
- `old/txt/dump-94/tsum-128x3-relmovedge.ps`: EPS.

### ../dump/anneal-sum-1k-8k

- `old/txt/dump/.xvpics/anneal-sum-1k-8k.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-sum-1k-8k.ps`: EPS; →
  `old/txt/dump-93/anneal-sum-1k-8k.ps`.
- `old/txt/dump-93/.xvpics/anneal-sum-1k-8k.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-sum-1k-8k.ps`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-sum-1k-8k.pgm`: PNM raster.
- `old/txt/dump-93/anneal-sum-1k-8k.ps`: EPS.
- `old/txt-roff/dump/anneal-sum-1k-8k.pgm`: PNM raster.

### ../dump/anneal-sum-1k-8k-xv

- `old/txt/dump/.xvpics/anneal-sum-1k-8k-xv.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-sum-1k-8k-xv.ps`: EPS; →
  `old/txt/dump-93/anneal-sum-1k-8k-xv.ps`.
- `old/txt/dump-93/.xvpics/anneal-sum-1k-8k-xv.pgm`: XV
  thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-sum-1k-8k-xv.ps`: XV
  thumbnail/cache.
- `old/txt/dump-93/anneal-sum-1k-8k-xv.pgm`: PNM raster.
- `old/txt/dump-93/anneal-sum-1k-8k-xv.ps`: EPS.
- `old/txt-roff/dump/anneal-sum-1k-8k-xv.pgm`: PNM raster.

### ../dump/neighburhood-size-tbl-16xor9

- `old/txt/dump/.xvpics/neighburhood-size-tbl-16xor9.ps`: XV
  thumbnail/cache.
- `old/txt/dump/neighburhood-size-tbl-16xor9.ps`: EPS; →
  `old/txt/dump-93/neighburhood-size-tbl-16xor9.ps`.
- `old/txt/dump-93/.xvpics/neighburhood-size-tbl-16xor9.pbm`: XV
  thumbnail/cache.
- `old/txt/dump-93/.xvpics/neighburhood-size-tbl-16xor9.ps`: XV
  thumbnail/cache.
- `old/txt/dump-93/neighburhood-size-tbl-16xor9.pbm`: PNM raster.
- `old/txt/dump-93/neighburhood-size-tbl-16xor9.ps`: EPS.
- `old/txt-roff/dump/neighburhood-size-tbl-16xor9.pbm`: PNM raster.

### ../dump/tsum-128-edge

- `old/txt/dump/.xvpics/tsum-128-edge.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-128-edge.ps`: EPS; →
  `old/txt/dump-93/tsum-128-edge.ps`.
- `old/txt/dump-93/.xvpics/tsum-128-edge.ps`: XV thumbnail/cache.
- `old/txt/dump-93/tmp/tsum-128-edge.pbm`: PNM raster.
- `old/txt/dump-93/tsum-128-edge.ps`: EPS.

### ../dump/anneal-g128-s11

- `old/txt/dump/.xvpics/anneal-g128-s11.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-g128-s11.ps`: EPS; →
  `old/txt/dump-93/anneal-g128-s11.ps`.
- `old/txt/dump-93/.xvpics/anneal-g128-s11.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-g128-s11.ps`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-g128-s11.pbm`: PNM raster.
- `old/txt/dump-93/anneal-g128-s11.ps`: EPS.
- `old/txt-roff/dump/anneal-g128-s11.pbm`: PNM raster.

### ../dump/tube-worm-mix

- `old/cell/demos/tube-worm-mix.pbm`: PNM raster.
- `old/txt/dump/.xvpics/tube-worm-mix.ps`: XV thumbnail/cache.
- `old/txt/dump/tube-worm-mix.ps`: EPS; →
  `old/txt/dump-93/tube-worm-mix.ps`.
- `old/txt/dump-93/.xvpics/tube-worm-mix.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/tube-worm-mix.ps`: XV thumbnail/cache.
- `old/txt/dump-93/tube-worm-mix.pbm`: PNM raster.
- `old/txt/dump-93/tube-worm-mix.ps`: EPS.
- `old/txt-roff/dump/tube-worm-mix.pbm`: PNM raster.

### ../dump/tsum-grey

- `old/txt/dump/.xvpics/tsum-grey.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-grey.ps`: EPS; → `old/txt/dump-93/tsum-grey.ps`.
- `old/txt/dump-93/.xvpics/tsum-grey.ps`: XV thumbnail/cache.
- `old/txt/dump-93/tmp/tsum-grey.pgm`: PNM raster.
- `old/txt/dump-93/tsum-grey.ps`: EPS.

### ../dump/tsum

- `old/cas-1.1/src/rules/OLD/anneal/tsum.c`: other source/data.
- `old/cas-1.1/src/rules/OLD/tsum/tsum.c`: other source/data.
- `old/cas-1.1/src/rules/OLD/tsum+anneal/tsum.c`: other source/data.
- `old/cell/rule/tsum.t`: other source/data.
- `old/txt/dump/.xvpics/tsum.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum.ps`: EPS; → `old/txt/dump-93/tsum.ps`.
- `old/txt/dump-93/.xvpics/tsum.ps`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/tsum.scale`: XV thumbnail/cache.
- `old/txt/dump-93/tmp/tsum.pbm`: PNM raster.
- `old/txt/dump-93/tsum.ps`: EPS.
- `old/txt/dump-93/tsum.scale`: other source/data.
- `old/txt-roff/dump/tsum.scale`: other source/data.

### ../dump/tsum-ray-one

- `old/txt/dump/.xvpics/tsum-ray-one.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-ray-one.ps`: EPS; →
  `old/txt/dump-93/tsum-ray-one.ps`.
- `old/txt/dump-93/.xvpics/tsum-ray-one.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/tsum-ray-one.ps`: XV thumbnail/cache.
- `old/txt/dump-93/tsum-ray-one.pgm`: PNM raster.
- `old/txt/dump-93/tsum-ray-one.ps`: EPS.
- `old/txt-roff/dump/tsum-ray-one.pgm`: PNM raster.

### ../dump/tsum-ray-all

- `old/txt/dump/.xvpics/tsum-ray-all.ps`: XV thumbnail/cache.
- `old/txt/dump/tsum-ray-all.ps`: EPS; →
  `old/txt/dump-93/tsum-ray-all.ps`.
- `old/txt/dump-93/.xvpics/tsum-ray-all.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/tsum-ray-all.ps`: XV thumbnail/cache.
- `old/txt/dump-93/tsum-ray-all.pgm`: PNM raster.
- `old/txt/dump-93/tsum-ray-all.ps`: EPS.
- `old/txt-roff/dump/tsum-ray-all.pgm`: PNM raster.

### ../plot/anneal-sum

- `old/txt/dump/.xvpics/anneal-sum.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-sum.ps`: EPS; →
  `old/txt/dump-93/anneal-sum.ps`.
- `old/txt/dump-93/.xvpics/anneal-sum.ps`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-sum.ps`: EPS.
- `old/txt/dump-93/tmp/anneal-sum.pgm`: PNM raster.
- `old/txt/plot/anneal-sum.ps`: PS; → `old/txt/plot-93/anneal-sum.ps`.
- `old/txt/plot-93/Data/anneal-sum.data`: other source/data.
- `old/txt/plot-93/anneal-sum.plot`: other source/data.
- `old/txt/plot-93/anneal-sum.ps`: PS.
- `old/txt-roff/data/anneal-sum.data`: other source/data.
- `old/txt-roff/plot/anneal-sum.plot`: other source/data.

### ../dump/anneal-sum

- `old/txt/dump/.xvpics/anneal-sum.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-sum.ps`: EPS; →
  `old/txt/dump-93/anneal-sum.ps`.
- `old/txt/dump-93/.xvpics/anneal-sum.ps`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-sum.ps`: EPS.
- `old/txt/dump-93/tmp/anneal-sum.pgm`: PNM raster.
- `old/txt/plot/anneal-sum.ps`: PS; → `old/txt/plot-93/anneal-sum.ps`.
- `old/txt/plot-93/Data/anneal-sum.data`: other source/data.
- `old/txt/plot-93/anneal-sum.plot`: other source/data.
- `old/txt/plot-93/anneal-sum.ps`: PS.
- `old/txt-roff/data/anneal-sum.data`: other source/data.
- `old/txt-roff/plot/anneal-sum.plot`: other source/data.

### ../dump/life-time-xor

- `old/cell/life/life-time-xor.pbm`: PNM raster.
- `old/txt/dump/.xvpics/life-time-xor.ps`: XV thumbnail/cache.
- `old/txt/dump/life-time-xor.ps`: EPS; →
  `old/txt/dump-93/life-time-xor.ps`.
- `old/txt/dump-93/.xvpics/life-time-xor.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/life-time-xor.ps`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/life-time-xor.scale`: XV thumbnail/cache.
- `old/txt/dump-93/life-time-xor.pbm`: PNM raster.
- `old/txt/dump-93/life-time-xor.ps`: EPS.
- `old/txt/dump-93/life-time-xor.scale`: other source/data.
- `old/txt-roff/dump/life-time-xor.pbm`: PNM raster.
- `old/txt-roff/dump/life-time-xor.scale`: other source/data.

### ../plot/lifex

- `old/cell/life/lifex.sh`: other source/data.
- `old/cell/lifex`: missing/broken link; → `old/cell/data/cell/lifex`.
- `old/cell/rule/lifex.t`: other source/data.
- `old/txt/plot/lifex.ps`: PS; → `old/txt/plot-93/lifex.ps`.
- `old/txt/plot-93/lifex.plot`: other source/data.
- `old/txt/plot-93/lifex.ps`: PS.
- `old/txt-roff/plot/lifex.plot`: other source/data.

### ../plot/lifex-sum-1

- `old/cell/life/lifex-sum-1.ascii`: other source/data.
- `old/txt/dump/.xvpics/lifex-sum-1.ps`: XV thumbnail/cache.
- `old/txt/dump/lifex-sum-1.ps`: EPS; →
  `old/txt/dump-93/lifex-sum-1.ps`.
- `old/txt/dump-93/.xvpics/lifex-sum-1.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/lifex-sum-1.ps`: XV thumbnail/cache.
- `old/txt/dump-93/lifex-sum-1.pgm`: PNM raster.
- `old/txt/dump-93/lifex-sum-1.ps`: EPS.
- `old/txt/plot/lifex-sum-1.ps`: PS; →
  `old/txt/plot-93/lifex-sum-1.ps`.
- `old/txt/plot-93/Data/lifex-sum-1.data`: other source/data.
- `old/txt/plot-93/lifex-sum-1.plot`: other source/data.
- `old/txt/plot-93/lifex-sum-1.ps`: PS.
- `old/txt/tbl/lifex-sum-1.tbl`: LaTeX table (not an image).
- `old/txt/tbl/lifex-sum-1.texture`: other source/data.
- `old/txt-roff/data/lifex-sum-1.data`: other source/data.
- `old/txt-roff/dump/lifex-sum-1.pgm`: PNM raster.
- `old/txt-roff/plot/lifex-sum-1.plot`: other source/data.
- `old/txt-roff/tbl/lifex-sum-1.texture`: other source/data.

### ../plot/lifex-sum-2

- `old/cell/life/lifex-sum-2.ascii`: other source/data.
- `old/txt/dump/.xvpics/lifex-sum-2.ps`: XV thumbnail/cache.
- `old/txt/dump/lifex-sum-2.ps`: EPS; →
  `old/txt/dump-93/lifex-sum-2.ps`.
- `old/txt/dump-93/.xvpics/lifex-sum-2.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/lifex-sum-2.ps`: XV thumbnail/cache.
- `old/txt/dump-93/lifex-sum-2.pgm`: PNM raster.
- `old/txt/dump-93/lifex-sum-2.ps`: EPS.
- `old/txt/plot/lifex-sum-2.ps`: PS; →
  `old/txt/plot-93/lifex-sum-2.ps`.
- `old/txt/plot-93/Data/lifex-sum-2.data`: other source/data.
- `old/txt/plot-93/lifex-sum-2.plot`: other source/data.
- `old/txt/plot-93/lifex-sum-2.ps`: PS.
- `old/txt/tbl/lifex-sum-2.tbl`: LaTeX table (not an image).
- `old/txt/tbl/lifex-sum-2.texture`: other source/data.
- `old/txt-roff/data/lifex-sum-2.data`: other source/data.
- `old/txt-roff/dump/lifex-sum-2.pgm`: PNM raster.
- `old/txt-roff/plot/lifex-sum-2.plot`: other source/data.
- `old/txt-roff/tbl/lifex-sum-2.texture`: other source/data.

### ../dump/life-3d-New

- `old/txt/dump/.xvpics/life-3d-New.ps`: XV thumbnail/cache.
- `old/txt/dump/life-3d-New.ps`: PS; →
  `old/txt/dump-93/life-3d-New.ps`.
- `old/txt/dump-93/.xvpics/life-3d-New.obj`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/life-3d-New.ps`: XV thumbnail/cache.
- `old/txt/dump-93/life-3d-New.obj`: other source/data.
- `old/txt/dump-93/life-3d-New.ps`: PS.

### ../dump/anneal-time-xor

- `old/txt/dump/.xvpics/anneal-time-xor.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-time-xor.ps`: EPS; →
  `old/txt/dump-93/anneal-time-xor.ps`.
- `old/txt/dump-93/.xvpics/anneal-time-xor.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-time-xor.ps`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-time-xor.scale`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-time-xor.pbm`: PNM raster.
- `old/txt/dump-93/anneal-time-xor.ps`: EPS.
- `old/txt/dump-93/anneal-time-xor.scale`: other source/data.
- `old/txt-roff/dump/anneal-time-xor.pbm`: PNM raster.
- `old/txt-roff/dump/anneal-time-xor.scale`: other source/data.

### ../plot/anneal-pop

- `old/txt/plot/anneal-pop.ps`: PS; → `old/txt/plot-93/anneal-pop.ps`.
- `old/txt/plot-93/Data/anneal-pop.data`: other source/data.
- `old/txt/plot-93/anneal-pop.plot`: other source/data.
- `old/txt/plot-93/anneal-pop.ps`: PS.
- `old/txt-roff/data/anneal-pop.data`: other source/data.
- `old/txt-roff/plot/anneal-pop.plot`: other source/data.

### ../plot/anneal-pop-detail

- `old/txt/plot/anneal-pop-detail.ps`: PS; →
  `old/txt/plot-93/anneal-pop-detail.ps`.
- `old/txt/plot-93/anneal-pop-detail.plot`: other source/data.
- `old/txt/plot-93/anneal-pop-detail.ps`: PS.
- `old/txt-roff/plot/anneal-pop-detail.plot`: other source/data.

### ../plot/heart-pop

- `old/txt/plot/heart-pop.ps`: PS; → `old/txt/plot-93/heart-pop.ps`.
- `old/txt/plot-93/Data/heart-pop.data`: other source/data.
- `old/txt/plot-93/heart-pop.plot`: other source/data.
- `old/txt/plot-93/heart-pop.ps`: PS.
- `old/txt-roff/data/heart-pop.data`: other source/data.
- `old/txt-roff/plot/heart-pop.plot`: other source/data.

### ../plot/heart-pop-detail

- `old/txt/plot/heart-pop-detail.ps`: PS; →
  `old/txt/plot-93/heart-pop-detail.ps`.
- `old/txt/plot-93/heart-pop-detail.plot`: other source/data.
- `old/txt/plot-93/heart-pop-detail.ps`: PS.
- `old/txt-roff/plot/heart-pop-detail.plot`: other source/data.

### ../dump/loop-1024

- `old/txt/dump/.xvpics/loop-1024.ps`: XV thumbnail/cache.
- `old/txt/dump/loop-1024.ps`: EPS; → `old/txt/dump-93/loop-1024.ps`.
- `old/txt/dump-93/.xvpics/loop-1024.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/loop-1024.ps`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/loop-1024.scale`: XV thumbnail/cache.
- `old/txt/dump-93/loop-1024.pbm`: PNM raster.
- `old/txt/dump-93/loop-1024.ps`: EPS.
- `old/txt/dump-93/loop-1024.scale`: other source/data.
- `old/txt-roff/dump/loop-1024.pbm`: PNM raster.
- `old/txt-roff/dump/loop-1024.scale`: other source/data.

### ../fig/func-1

- `old/txt/fig/func-1.fig`: FIG source.
- `old/txt/fig/func-1.ps`: EPS.
- `old/txt/fig/func-1.scale`: other source/data.
- `old/txt-roff/fig/func-1.fig`: FIG source.
- `old/txt-roff/fig/func-1.scale`: other source/data.

### ../fig/apply-1

- `old/txt/fig/apply-1.fig`: FIG source.
- `old/txt/fig/apply-1.ps`: EPS.
- `old/txt/fig/apply-1.scale`: other source/data.
- `old/txt-roff/fig/apply-1.fig`: FIG source.
- `old/txt-roff/fig/apply-1.scale`: other source/data.

### ../fig/apply-2

- `old/txt/fig/apply-2.fig`: FIG source.
- `old/txt/fig/apply-2.ps`: PS.
- `old/txt/fig/apply-2.scale`: other source/data.
- `old/txt-roff/fig/apply-2.fig`: FIG source.
- `old/txt-roff/fig/apply-2.scale`: other source/data.

### ../fig/func-2

- `old/txt/fig/func-2.fig`: FIG source.
- `old/txt/fig/func-2.ps`: EPS.
- `old/txt/fig/func-2.scale`: other source/data.
- `old/txt-roff/fig/func-2.fig`: FIG source.
- `old/txt-roff/fig/func-2.scale`: other source/data.

### ../fig/func-3

- `old/txt/fig/func-3.fig`: FIG source.
- `old/txt/fig/func-3.ps`: EPS.
- `old/txt/fig/func-3.scale`: other source/data.
- `old/txt-roff/fig/func-3.fig`: FIG source.
- `old/txt-roff/fig/func-3.scale`: other source/data.

### ../fig/func-4

- `old/txt/fig/func-4.fig`: FIG source.
- `old/txt/fig/func-4.ps`: PS.
- `old/txt/fig/func-4.scale`: other source/data.
- `old/txt-roff/fig/func-4.fig`: FIG source.
- `old/txt-roff/fig/func-4.scale`: other source/data.

### ../fig/func-7

- `old/txt/fig/func-7.fig`: FIG source.
- `old/txt/fig/func-7.ps`: EPS.
- `old/txt/fig/func-7.scale`: other source/data.
- `old/txt-roff/fig/func-7.fig`: FIG source.
- `old/txt-roff/fig/func-7.scale`: other source/data.

### ../fig/gap-pe

- `old/txt/fig/gap-pe.fig`: FIG source.
- `old/txt/fig/gap-pe.ps`: EPS.
- `old/txt/fig/gap-pe.scale`: other source/data.
- `old/txt-roff/fig/gap-pe.fig`: FIG source.
- `old/txt-roff/fig/gap-pe.scale`: other source/data.

### ../fig/gap

- `old/txt/fig/gap.fig`: FIG source.
- `old/txt/fig/gap.ps`: PS.
- `old/txt/fig/gap.scale`: other source/data.
- `old/txt-roff/fig/gap.fig`: FIG source.
- `old/txt-roff/fig/gap.scale`: other source/data.

### ../fig/life-dfa

- `old/txt/fig/life-dfa.fig`: FIG source.
- `old/txt/fig/life-dfa.ps`: EPS.
- `old/txt/fig/life-dfa.scale`: other source/data.
- `old/txt-roff/fig/life-dfa.fig`: FIG source.
- `old/txt-roff/fig/life-dfa.scale`: other source/data.

### ../fig/life-tree

- `old/txt/fig/life-tree.fig`: FIG source.
- `old/txt/fig/life-tree.ps`: EPS.
- `old/txt/fig/life-tree.scale`: other source/data.
- `old/txt-roff/fig/life-tree.fig`: FIG source.
- `old/txt-roff/fig/life-tree.scale`: other source/data.

### ../dump/cantata-1

- `old/txt/dump/.xvpics/cantata-1.ps`: XV thumbnail/cache.
- `old/txt/dump/cantata-1.ps`: EPS; → `old/txt/dump-94/cantata-1.ps`.
- `old/txt/dump-94/.xvpics/cantata-1.ps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/cantata-1.wd`: XV thumbnail/cache.
- `old/txt/dump-94/cantata-1.ps`: EPS.
- `old/txt/dump-94/cantata-1.wd`: other source/data.

### ../dump/cantata-mk-rule

- `old/txt/dump/.xvpics/cantata-mk-rule.ps`: XV thumbnail/cache.
- `old/txt/dump/cantata-mk-rule.ps`: EPS; →
  `old/txt/dump-94/cantata-mk-rule.ps`.
- `old/txt/dump-94/.xvpics/cantata-mk-rule.ps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/cantata-mk-rule.wd`: XV thumbnail/cache.
- `old/txt/dump-94/cantata-mk-rule.ps`: EPS.
- `old/txt/dump-94/cantata-mk-rule.wd`: other source/data.

### ../dump/cantata-cell

- `old/txt/dump/.xvpics/cantata-cell.ps`: XV thumbnail/cache.
- `old/txt/dump/cantata-cell.ps`: EPS; →
  `old/txt/dump-94/cantata-cell.ps`.
- `old/txt/dump-94/.xvpics/cantata-cell.ps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/cantata-cell.wd`: XV thumbnail/cache.
- `old/txt/dump-94/cantata-cell.ps`: EPS.
- `old/txt/dump-94/cantata-cell.wd`: other source/data.

### ../plot/lambda

- `old/txt/plot/lambda.ps`: PS; → `old/txt/plot-94/lambda.ps`.
- `old/txt/plot-94/lambda.plot`: other source/data.
- `old/txt/plot-94/lambda.ps`: PS.

### ../plot/flip

- `old/txt/plot/flip.ps`: PS; → `old/txt/plot-94/flip.ps`.
- `old/txt/plot-94/flip.plot`: other source/data.
- `old/txt/plot-94/flip.ps`: PS.

### ../plot/lambda-deriv

- `old/txt/plot/lambda-deriv.ps`: PS; →
  `old/txt/plot-94/lambda-deriv.ps`.
- `old/txt/plot-94/lambda-deriv.plot`: other source/data.
- `old/txt/plot-94/lambda-deriv.ps`: PS.

### ../plot/flip-deriv

- `old/txt/plot/flip-deriv.ps`: PS; → `old/txt/plot-94/flip-deriv.ps`.
- `old/txt/plot-94/flip-deriv.plot`: other source/data.
- `old/txt/plot-94/flip-deriv.ps`: PS.

### ../plot/lambda-prob

- `old/txt/plot/lambda-prob.ps`: PS; →
  `old/txt/plot-94/lambda-prob.ps`.
- `old/txt/plot-94/lambda-prob.plot`: other source/data.
- `old/txt/plot-94/lambda-prob.ps`: PS.

### ../plot/flip-prob

- `old/txt/plot/flip-prob.ps`: PS; → `old/txt/plot-94/flip-prob.ps`.
- `old/txt/plot-94/flip-prob.plot`: other source/data.
- `old/txt/plot-94/flip-prob.ps`: PS.

### ../plot/lambda-versus-prob

- `old/txt/plot/lambda-versus-prob.ps`: PS; →
  `old/txt/plot-94/lambda-versus-prob.ps`.
- `old/txt/plot-94/lambda-versus-prob.plot`: other source/data.
- `old/txt/plot-94/lambda-versus-prob.ps`: PS.

### ../plot/flip-versus-prob

- `old/txt/plot/flip-versus-prob.ps`: PS; →
  `old/txt/plot-94/flip-versus-prob.ps`.
- `old/txt/plot-94/flip-versus-prob.plot`: other source/data.
- `old/txt/plot-94/flip-versus-prob.ps`: PS.

### ../plot/lambda-flip-hist

- `old/txt/plot/lambda-flip-hist.ps`: PS; →
  `old/txt/plot-94/lambda-flip-hist.ps`.
- `old/txt/plot-94/lambda-flip-hist.plot`: other source/data.
- `old/txt/plot-94/lambda-flip-hist.ps`: PS.

### ../plot/lambda-versus-flip

- `old/txt/plot/lambda-versus-flip.ps`: PS; →
  `old/txt/plot-94/lambda-versus-flip.ps`.
- `old/txt/plot-94/lambda-versus-flip.plot`: other source/data.
- `old/txt/plot-94/lambda-versus-flip.ps`: PS.

### ../plot/lambda-flip-ratio-sorted

- `old/txt/plot/lambda-flip-ratio-sorted.ps`: PS; →
  `old/txt/plot-94/lambda-flip-ratio-sorted.ps`.
- `old/txt/plot-94/lambda-flip-ratio-sorted.plot`: other source/data.
- `old/txt/plot-94/lambda-flip-ratio-sorted.ps`: PS.

### ../plot/lambda-flip-prob-sorted

- `old/txt/plot/lambda-flip-prob-sorted.ps`: PS; →
  `old/txt/plot-94/lambda-flip-prob-sorted.ps`.
- `old/txt/plot-94/lambda-flip-prob-sorted.plot`: other source/data.
- `old/txt/plot-94/lambda-flip-prob-sorted.ps`: PS.

### ../plot/E-lambda-1

- `old/txt/plot/E-lambda-1.ps`: PS; → `old/txt/plot-94/E-lambda-1.ps`.
- `old/txt/plot-94/E-lambda-1.plot`: other source/data.
- `old/txt/plot-94/E-lambda-1.ps`: PS.

### ../dump/anneal-3d

- `old/txt/dump/.xvpics/anneal-3d.ps`: XV thumbnail/cache.
- `old/txt/dump/anneal-3d.ps`: EPS; → `old/txt/dump-93/anneal-3d.ps`.
- `old/txt/dump-93/.xvpics/anneal-3d.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/anneal-3d.ps`: XV thumbnail/cache.
- `old/txt/dump-93/anneal-3d.pgm`: PNM raster; →
  `old/txt/dump-93/anneal-9x9x9-3d-he.pgm`.
- `old/txt/dump-93/anneal-3d.ps`: EPS.
- `old/txt-roff/dump/anneal-3d.pgm`: PNM raster; →
  `old/txt-roff/dump/anneal-9x9x9-3d-he.pgm`.

### ../dump/life-00

- `old/txt/dump/.xvpics/life-00.eps`: XV thumbnail/cache.
- `old/txt/dump/life-00.eps`: EPS; → `old/txt/dump-94/life-00.eps`.
- `old/txt/dump-94/.xvpics/life-00.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-00.margin`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-00.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/life-00.scale`: XV thumbnail/cache.
- `old/txt/dump-94/life-00.eps`: EPS.
- `old/txt/dump-94/life-00.margin`: other source/data.
- `old/txt/dump-94/life-00.pbm`: PNM raster; →
  `old/txt/dump-94/life-size=128-gen=128-init=0.5.pbm`.
- `old/txt/dump-94/life-00.scale`: other source/data.

### ../dump/anneal-00

- `old/txt/dump/.xvpics/anneal-00.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-00.eps`: EPS; →
  `old/txt/dump-94/anneal-00.eps`.
- `old/txt/dump-94/.xvpics/anneal-00.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-00.margin`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-00.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-00.scale`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-00.eps`: EPS.
- `old/txt/dump-94/anneal-00.margin`: other source/data.
- `old/txt/dump-94/anneal-00.pbm`: PNM raster; →
  `old/txt/dump-94/anneal-size=256-gen=256-init=0.5.pbm`.
- `old/txt/dump-94/anneal-00.scale`: other source/data.

### ../dump/anneal-03

- `old/txt/dump/.xvpics/anneal-03.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-03.eps`: EPS; →
  `old/txt/dump-94/anneal-03.eps`.
- `old/txt/dump-94/.xvpics/anneal-03.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.margin`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.scale`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-03.eps`: EPS.
- `old/txt/dump-94/anneal-03.margin`: other source/data.
- `old/txt/dump-94/anneal-03.pbm`: PNM raster; →
  `old/txt/dump-94/anneal-size=256-gen=1-559.pbm`.
- `old/txt/dump-94/anneal-03.scale`: other source/data.
- `old/txt/plot/anneal-03.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=82k+dump.eps`.
- `old/txt/plot-94/anneal-03.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=82k+dump.eps`.

### ../dump/anneal-02

- `old/txt/dump/.xvpics/anneal-02.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-02.eps`: PS; → `old/txt/dump-94/anneal-02.eps`.
- `old/txt/dump-94/.xvpics/anneal-02.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-02.obj`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-02.eps`: PS.
- `old/txt/dump-94/anneal-02.obj`: other source/data.
- `old/txt/plot/anneal-02.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=30k+dump.eps`.
- `old/txt/plot-94/anneal-02.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=30k+dump.eps`.

### ../dump/anneal-01

- `old/txt/dump/.xvpics/anneal-01.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-01.eps`: PS; → `old/txt/dump-94/anneal-01.eps`.
- `old/txt/dump-94/.xvpics/anneal-01.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-01.obj`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-01.eps`: PS.
- `old/txt/dump-94/anneal-01.obj`: other source/data.
- `old/txt/plot/anneal-01.eps`: PS; →
  `old/txt/plot-94/anneal-size-10-front.eps`.
- `old/txt/plot-94/anneal-01.eps`: PS; →
  `old/txt/plot-94/anneal-size-10-front.eps`.

### ../plot/anneal-01

- `old/txt/dump/.xvpics/anneal-01.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-01.eps`: PS; → `old/txt/dump-94/anneal-01.eps`.
- `old/txt/dump-94/.xvpics/anneal-01.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-01.obj`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-01.eps`: PS.
- `old/txt/dump-94/anneal-01.obj`: other source/data.
- `old/txt/plot/anneal-01.eps`: PS; →
  `old/txt/plot-94/anneal-size-10-front.eps`.
- `old/txt/plot-94/anneal-01.eps`: PS; →
  `old/txt/plot-94/anneal-size-10-front.eps`.

### ../plot/anneal-02

- `old/txt/dump/.xvpics/anneal-02.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-02.eps`: PS; → `old/txt/dump-94/anneal-02.eps`.
- `old/txt/dump-94/.xvpics/anneal-02.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-02.obj`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-02.eps`: PS.
- `old/txt/dump-94/anneal-02.obj`: other source/data.
- `old/txt/plot/anneal-02.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=30k+dump.eps`.
- `old/txt/plot-94/anneal-02.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=30k+dump.eps`.

### ../plot/anneal-03

- `old/txt/dump/.xvpics/anneal-03.eps`: XV thumbnail/cache.
- `old/txt/dump/anneal-03.eps`: EPS; →
  `old/txt/dump-94/anneal-03.eps`.
- `old/txt/dump-94/.xvpics/anneal-03.eps`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.margin`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.pbm`: XV thumbnail/cache.
- `old/txt/dump-94/.xvpics/anneal-03.scale`: XV thumbnail/cache.
- `old/txt/dump-94/anneal-03.eps`: EPS.
- `old/txt/dump-94/anneal-03.margin`: other source/data.
- `old/txt/dump-94/anneal-03.pbm`: PNM raster; →
  `old/txt/dump-94/anneal-size=256-gen=1-559.pbm`.
- `old/txt/dump-94/anneal-03.scale`: other source/data.
- `old/txt/plot/anneal-03.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=82k+dump.eps`.
- `old/txt/plot-94/anneal-03.eps`: PS; →
  `old/txt/plot-94/anneal-size=1024-trans=82k+dump.eps`.

### ../plot/anneal-04

- `old/txt/plot/anneal-04.eps`: PS; →
  `old/txt/plot-94/anneal-size=128:1024-scaled.eps`.
- `old/txt/plot-94/anneal-04.eps`: PS; →
  `old/txt/plot-94/anneal-size=128:1024-scaled.eps`.

### ../plot/anneal-05

- `old/txt/plot/anneal-05.eps`: PS; →
  `old/txt/plot-94/anneal-size=256.eps`.
- `old/txt/plot-94/anneal-05.eps`: PS; →
  `old/txt/plot-94/anneal-size=256.eps`.

### ../dump/xu-photo-1

- `old/txt/dump/.xvpics/xu-photo-1.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-photo-1.ps`: EPS; →
  `old/txt/dump-93/xu-photo-1.ps`.
- `old/txt/dump-93/.xvpics/xu-photo-1.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-photo-1.ps`: XV thumbnail/cache.
- `old/txt/dump-93/xu-photo-1.pgm`: PNM raster.
- `old/txt/dump-93/xu-photo-1.ps`: EPS.
- `old/txt-roff/dump/xu-photo-1.pgm`: PNM raster.

### ../dump/xu-photo-1-top

- `old/txt/dump/.xvpics/xu-photo-1-top.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-photo-1-top.ps`: EPS; →
  `old/txt/dump-93/xu-photo-1-top.ps`.
- `old/txt/dump-93/.xvpics/xu-photo-1-top.pbm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-photo-1-top.ps`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-photo-1-top.scale`: XV thumbnail/cache.
- `old/txt/dump-93/xu-photo-1-top.pbm`: PNM raster.
- `old/txt/dump-93/xu-photo-1-top.ps`: EPS.
- `old/txt/dump-93/xu-photo-1-top.scale`: other source/data.
- `old/txt-roff/dump/xu-photo-1-top.pbm`: PNM raster.
- `old/txt-roff/dump/xu-photo-1-top.scale`: other source/data.

### ../dump/xu-Cfilm-1-1

- `old/txt/dump/.xvpics/xu-Cfilm-1-1.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-Cfilm-1-1.ps`: EPS; →
  `old/txt/dump-93/xu-Cfilm-1-1.ps`.
- `old/txt/dump-93/.xvpics/xu-Cfilm-1-1.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-Cfilm-1-1.ps`: XV thumbnail/cache.
- `old/txt/dump-93/xu-Cfilm-1-1.pgm`: PNM raster.
- `old/txt/dump-93/xu-Cfilm-1-1.ps`: EPS.
- `old/txt-roff/dump/xu-Cfilm-1-1.pgm`: PNM raster.

### ../dump/xu-Cfilm-1-2

- `old/txt/dump/.xvpics/xu-Cfilm-1-2.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-Cfilm-1-2.ps`: EPS; →
  `old/txt/dump-93/xu-Cfilm-1-2.ps`.
- `old/txt/dump-93/.xvpics/xu-Cfilm-1-2.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-Cfilm-1-2.ps`: XV thumbnail/cache.
- `old/txt/dump-93/xu-Cfilm-1-2.pgm`: PNM raster.
- `old/txt/dump-93/xu-Cfilm-1-2.ps`: EPS.
- `old/txt-roff/dump/xu-Cfilm-1-2.pgm`: PNM raster.

### ../dump/xu-Cfilm-2-1

- `old/txt/dump/.xvpics/xu-Cfilm-2-1.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-Cfilm-2-1.ps`: EPS; →
  `old/txt/dump-93/xu-Cfilm-2-1.ps`.
- `old/txt/dump-93/.xvpics/xu-Cfilm-2-1.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-Cfilm-2-1.ps`: XV thumbnail/cache.
- `old/txt/dump-93/xu-Cfilm-2-1.pgm`: PNM raster.
- `old/txt/dump-93/xu-Cfilm-2-1.ps`: EPS.
- `old/txt-roff/dump/xu-Cfilm-2-1.pgm`: PNM raster.

### ../dump/xu-Cfilm-2-2

- `old/txt/dump/.xvpics/xu-Cfilm-2-2.ps`: XV thumbnail/cache.
- `old/txt/dump/xu-Cfilm-2-2.ps`: EPS; →
  `old/txt/dump-93/xu-Cfilm-2-2.ps`.
- `old/txt/dump-93/.xvpics/xu-Cfilm-2-2.pgm`: XV thumbnail/cache.
- `old/txt/dump-93/.xvpics/xu-Cfilm-2-2.ps`: XV thumbnail/cache.
- `old/txt/dump-93/xu-Cfilm-2-2.pgm`: PNM raster.
- `old/txt/dump-93/xu-Cfilm-2-2.ps`: EPS.
- `old/txt-roff/dump/xu-Cfilm-2-2.pgm`: PNM raster.

### ../plot/rabbit-gnans-1

- `old/txt/plot/rabbit-gnans-1.ps`: PS; →
  `old/txt/plot-93/rabbit-gnans-1.ps`.
- `old/txt/plot-93/Data/rabbit-gnans-1.data`: other source/data.
- `old/txt/plot-93/rabbit-gnans-1.plot`: other source/data.
- `old/txt/plot-93/rabbit-gnans-1.ps`: PS.
- `old/txt-roff/data/rabbit-gnans-1.data`: other source/data.
- `old/txt-roff/plot/rabbit-gnans-1.plot`: other source/data.

### ../plot/rabbit-gnans-2

- `old/txt/plot/rabbit-gnans-2.ps`: PS; →
  `old/txt/plot-93/rabbit-gnans-2.ps`.
- `old/txt/plot-93/Data/rabbit-gnans-2.data`: other source/data.
- `old/txt/plot-93/rabbit-gnans-2.plot`: other source/data.
- `old/txt/plot-93/rabbit-gnans-2.ps`: PS.
- `old/txt-roff/data/rabbit-gnans-2.data`: other source/data.
- `old/txt-roff/plot/rabbit-gnans-2.plot`: other source/data.

### ../plot/rabbit-1

- `old/txt/plot/rabbit-1.ps`: PS; → `old/txt/plot-93/rabbit-1.ps`.
- `old/txt/plot-93/rabbit-1.plot`: other source/data.
- `old/txt/plot-93/rabbit-1.ps`: PS.
- `old/txt-roff/plot/rabbit-1.plot`: other source/data.

### ../plot/rabbit-1-512

- `old/txt/plot/rabbit-1-512.ps`: PS; →
  `old/txt/plot-93/rabbit-1-512.ps`.
- `old/txt/plot-93/rabbit-1-512.plot`: other source/data.
- `old/txt/plot-93/rabbit-1-512.ps`: PS.
- `old/txt-roff/plot/rabbit-1-512.plot`: other source/data.

### ../plot/rabbit-2

- `old/txt/plot/rabbit-2.ps`: PS; → `old/txt/plot-93/rabbit-2.ps`.
- `old/txt/plot-93/rabbit-2.plot`: other source/data.
- `old/txt/plot-93/rabbit-2.ps`: PS.
- `old/txt-roff/plot/rabbit-2.plot`: other source/data.

### ../plot/rabbit-3

- `old/txt/plot/rabbit-3.ps`: PS; → `old/txt/plot-93/rabbit-3.ps`.
- `old/txt/plot-93/rabbit-3.plot`: other source/data.
- `old/txt/plot-93/rabbit-3.ps`: PS.
- `old/txt-roff/plot/rabbit-3.plot`: other source/data.
