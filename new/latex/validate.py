"""Acceptance checks against the historical sources, not just PDF existence."""
from pathlib import Path
import re, subprocess, json
from tex_unicode import normalize, changes
ROOT=Path(__file__).resolve().parent
import os
os.chdir(ROOT)
old=Path('../../old/txt/tex')
chapters=['title','abstract','intro-top','obj-space','obj-time','obj-law','rule-space','about-anneal','conclusion','ann-rules','ann-rabbit','ann-caw','soft-tools','biblio']
# Documented technical edits plus equivalent prose accent representation.
# Mathematics, identifiers, code, macros and comments remain exact source.
for name in chapters+['intro-part-1','intro-part-2','nocite']:
    expected=(old/(name+'.tex')).read_text(encoding='ascii')
    if name=='title': expected=expected.replace(r'\today','27 septembre 1994')
    if name=='intro-top': expected=expected.replace(r'\input{intro-part-',r'\input{chapters/intro-part-')
    if name=='biblio': expected=expected.replace('  journal,','  bib/journal,').replace('Bib/','bib/')
    actual = Path('chapters', name+'.tex').read_text()
    assert normalize(actual) == normalize(expected), f'Contenu modifié: {name}'
    assert not list(changes(actual)), f'Accents TeX en prose: {name}'
for p in Path('tables').glob('*.tbl'):
    assert p.read_text()==(old.parent/'tbl'/p.name).read_bytes().decode('latin1'), p
for p in Path('bib').glob('*.bib'):
    assert p.read_text()==(old/'Bib'/p.name).read_bytes().decode('latin1'), p
for name in ['simple','ref-and-cite','spl','email','num-in-bib']:
    assert Path('compat',name+'.tex').read_text()==(old/'Sty'/(name+'.sty')).read_text('ascii')
main=Path('main.tex').read_text()
assert re.findall(r'\\include\{chapters/([^}]+)\}',main)==chapters
assert main.index(r'\appendix')<main.index(r'\include{chapters/ann-rules}')
log=Path('main.log').read_text(encoding='latin1')
for forbidden in ['undefined','multiply defined','LaTeX Error','Missing character','Overfull','Rerun to get','may have changed','Warning']:
    assert forbidden not in log, forbidden
assert not re.search(r'(?:Warning|Error|error message)',Path('main.blg').read_text())
inputs=[line[6:] for line in Path('main.fls').read_text().splitlines() if line.startswith('INPUT ')]
assert not any(re.search(r'\.(?:eps|ps)$',p,re.I) or 'mytex.fmt' in p or '/old/' in p for p in inputs)
for name in chapters+['intro-part-1','intro-part-2','nocite']:
    assert any(p.endswith('/'+name+'.tex') for p in inputs),f'Non compilé: {name}'
for p in Path('tables').glob('*.tbl'):
    assert any(x.endswith('/'+p.name) for x in inputs),f'Table non compilée: {p}'
def labels(text):
    return dict(re.findall(r'\\newlabel\{([^}]+)\}\{\{([^}]+)\}',text))
a=labels(''.join((old/(name+'.aux')).read_text('latin1') for name in chapters))
b=labels(''.join(p.read_text() for p in Path('chapters').glob('*.aux')))
assert a==b, 'Labels ou numéros différents de 1994'
def keys(text):
    return set(re.findall(r'\\bibitem(?:\[[\s\S]*?\])?\{([^}]+)\}',text))
a=keys((old/'top.bbl').read_text('latin1'));b=keys(Path('main.bbl').read_text())
assert a==b, f'Clés bibliographiques: manque {a-b}, ajout {b-a}'
counts={}
for ext in ['toc','lof','lot']:
    n=Path('main.'+ext).read_text().count(r'\contentsline')
    assert n==(old/('top.'+ext)).read_text('latin1').count(r'\contentsline')
    assert re.findall(r'\\numberline\s*\{([^}]+)\}',Path('main.'+ext).read_text()) == re.findall(r'\\numberline\s*\{([^}]+)\}',(old/('top.'+ext)).read_text('latin1')), 'Ordre des entrées: '+ext
    counts[ext]=n
subprocess.run(['git','diff','--exit-code','HEAD','--','old'],cwd=ROOT.parent.parent,check=True,stdout=subprocess.DEVNULL)
assert not subprocess.check_output(['git','ls-files','--others','--exclude-standard','old'],cwd=ROOT.parent.parent).strip()
info=subprocess.check_output(['pdfinfo','main.pdf'],text=True)
assert '(A4)' in info
pages=int(re.search(r'Pages:\s+(\d+)',info)[1])
text=subprocess.check_output(['pdftotext','main.pdf','-'],text=True)
assert '27 septembre 1994' in text and 'Bibliographie' in text
assert '\ufffd' not in text and '??' not in text
resources=Path('main.resources').read_text().splitlines()
# Every restored call must match exactly one documented local derivative.
import hashlib
from collections import Counter
manifest=json.loads(Path('figure-manifest.json').read_text())
restored=[e for e in manifest['images'] if e.get('render_status')=='restored']
assert Counter(x.split(': ',1)[1] for x in resources if x.startswith('image-restored: ')) == Counter(e['resource'] for e in restored)
assert len(resources)==102 and len(restored)==88
loaded={str((ROOT/p).resolve()) for p in inputs if p.lower().endswith('.pdf')}
expected={str((ROOT/e['derivative']).resolve()) for e in restored}
assert loaded==expected, f'Undocumented or missing image: {loaded^expected}'
for entry in restored:
    for key, hashvalue in [('staged_source',entry['selected']['sha256']),('derivative',entry['derivative_sha256'])]:
        local=(ROOT/entry[key]).resolve()
        assert local.is_relative_to(ROOT)
        assert hashlib.sha256(local.read_bytes()).hexdigest()==hashvalue, local
    original=(ROOT.parent.parent/entry['selected']['resolved_path']).resolve()
    assert hashlib.sha256(original.read_bytes()).hexdigest()==entry['selected']['sha256']
    bounds=re.findall(rb'^%%(?:HiRes)?BoundingBox:\s*([-+.\d]+)\s+([-+.\d]+)\s+([-+.\d]+)\s+([-+.\d]+)',(ROOT/entry['staged_source']).read_bytes(),re.M)[-1]
    x0,y0,x1,y1=map(float,bounds)
    dimensions=re.search(r'Page size:\s*([\d.]+) x ([\d.]+)',subprocess.check_output(['pdfinfo',entry['derivative']],text=True))
    w,h=map(float,dimensions.groups())
    # EPS writers round integer boxes; their precise boxes differ by <=1 pt.
    assert abs(w-(x1-x0))<=1.1 and abs(h-(y1-y0))<=1.1, entry['resource']
    assert entry['conversion']['source_sha256']==entry['selected']['sha256']
    assert entry['historical_log_path'] in (old/'top.log').read_text('latin1')
    assert entry['historical_log_path'].rsplit('.',1)[0]==entry['resource']
summary={'pages':pages,'labels':len(labels(''.join(p.read_text() for p in Path('chapters').glob('*.aux')))),'bibliographie':len(b),**counts,'images_reintegrees':len(restored),'figures_illustrees':len({x['label'] for e in restored for x in e['labels']}),'provenance_images_verifiee':True,'images_differees':sum(x.startswith('image:') for x in resources),'codes_differes':sum(x.startswith('code:') for x in resources),'tables_incluses':len(list(Path('tables').glob('*.tbl'))),'underfull_hbox':log.count('Underfull \\hbox'),'old_inchange':True,'references_non_resolues':0,'citations_non_resolues':0,'conservation_unicode_semantique':True,'accents_tex_prose_restants':0}
Path('validation.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2)+'\n')
print(json.dumps(summary,ensure_ascii=False,indent=2))
