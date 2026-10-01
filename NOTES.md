# Notes

Working notes for observations and possible follow-up work. These are not
validated findings or implementation directives.

## 2026-10-01 — First visual comparison of historical and reconstructed PDFs

- **Source/listing material:** some source material visible in the historical
  document does not appear to have been reintegrated. Determine what remains
  deferred and why.
- **Layout and spacing:** page occupancy differs in places. In particular, the
  résumé/introductory material that fitted on one historical page now appears
  to occupy two. Check whether historical line-spacing or other local layout
  settings have not yet been reproduced.
- **Figure sizing/rendering:** some restored figures appear to have different
  dimensions or page-occupancy ratios after PS/EPS-to-PDF conversion. Compare
  historical and reconstructed rendering more closely, including bounding-box
  handling and historical TeX scaling.
- **Bibliography encoding:** verify whether the bibliography was actually
  converted to UTF-8. Initial visual inspection suggests that it may still use
  its historical encoding. Check the bibliography source and BibTeX processing
  before treating this as a confirmed defect.
