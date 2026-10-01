"""Run BibTeX, then converge all cross-references (at most eight TeX passes)."""
from pathlib import Path
import subprocess, hashlib

def signature():
    paths=sorted(p for pattern in ['*.aux','chapters/*.aux','*.toc','*.lof','*.lot'] for p in Path('.').glob(pattern))
    return hashlib.sha256(b''.join(p.read_bytes() for p in paths)).digest()
def tex(n):
    with open(f'build-pass-{n}.txt','w') as log:
        subprocess.run(['pdflatex','-interaction=nonstopmode','-halt-on-error','-file-line-error','-recorder','main.tex'],stdout=log,stderr=subprocess.STDOUT,check=True)
tex(1)
with open('build-bibtex.txt','w') as log:
    subprocess.run(['bibtex','main'],stdout=log,stderr=subprocess.STDOUT,check=True)
for n in range(2,9):
    previous=signature(); tex(n)
    if previous==signature():
        print(f'Compilation stabilisée après {n} passes LaTeX et BibTeX.'); break
else:
    raise SystemExit('Les références ne se stabilisent pas après huit passes.')
