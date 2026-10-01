"""Verify unchanged PDF text and every rendered page after conversion."""
from pathlib import Path
import hashlib
import json
import subprocess
import tempfile

JOURNAL = Path(__file__).resolve().parent
ROOT = JOURNAL.parents[1]
PDF = ROOT / 'new/latex/main.pdf'
baseline = json.loads((JOURNAL / 'baseline.json').read_text())
text = subprocess.check_output(['pdftotext', '-layout', str(PDF), '-'])
text_hash = hashlib.sha256(text).hexdigest()
assert text_hash == baseline['pdf_layout_text_sha256'], \
    'Le texte extrait ou sa disposition ont changé.'
with tempfile.TemporaryDirectory(prefix='dea-utf8-render-') as temporary:
    prefix = str(Path(temporary) / 'page')
    subprocess.run(['pdftoppm', '-r', str(baseline['raster_dpi']), '-png',
                    str(PDF), prefix], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    pages = sorted(Path(temporary).glob('page-*.png'))
    hashes = [hashlib.sha256(p.read_bytes()).hexdigest() for p in pages]
    assert len(hashes) == baseline['pages'], 'Pagination modifiée.'
    differing = [i+1 for i, (a, b) in enumerate(zip(
        baseline['page_png_sha256'], hashes)) if a != b]
    assert not differing, f'Pages au rendu différent : {differing}'
result = {
    'baseline_git_reference': baseline['git_reference'],
    'pages': len(hashes),
    'layout_text_sha256': text_hash,
    'layout_text_identical': True,
    'all_page_rasters_identical': True,
    'raster_dpi': baseline['raster_dpi'],
}
(JOURNAL / 'output-validation.json').write_text(
    json.dumps(result, ensure_ascii=False, indent=2)+'\n')
print(json.dumps(result, ensure_ascii=False, indent=2))
