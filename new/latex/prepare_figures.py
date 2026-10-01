"""Stage exact historical bytes, then mechanically convert local PS/EPS."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import argparse
import hashlib
import json
import subprocess
import shutil
import re
import tempfile

ROOT = Path(__file__).resolve().parent
REPO = ROOT.parent.parent
GS_FLAGS = ['-dSAFER', '-dBATCH', '-dNOPAUSE', '-sDEVICE=pdfwrite',
            '-dCompatibilityLevel=1.5', '-dEPSCrop',
            '-dAutoRotatePages=/None', '-dOmitInfoDate=true',
            '-dOmitID=true', '-dOmitXMP=true']


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def convert(entry):
    source = ROOT / entry['staged_source']
    assert source.is_file(), f'Missing local source: {source}; run --stage'
    assert digest(source) == entry['selected']['sha256'], source
    output = ROOT / entry['derivative']
    output.parent.mkdir(parents=True, exist_ok=True)
    # Converter only reads staged input. Temporary outputs are local too.
    with tempfile.TemporaryDirectory(dir=output.parent) as temporary:
        result = Path(temporary) / 'figure.pdf'
        flags = list(GS_FLAGS)
        bounds = None
        if entry['selected']['format'] == 'PS':
            boxes = re.findall(rb'^%%BoundingBox:\s*([-+.\d]+)\s+([-+.\d]+)\s+([-+.\d]+)\s+([-+.\d]+)', source.read_bytes(), re.M)
            assert boxes, source
            bounds = [float(x) for x in boxes[-1]]
            x0,y0,x1,y1 = bounds
            flags.remove('-dEPSCrop')
            flags += ['-dFIXEDMEDIA', f'-dDEVICEWIDTHPOINTS={x1-x0:g}',
                      f'-dDEVICEHEIGHTPOINTS={y1-y0:g}']
        command = ['gs', *flags, '-sOutputFile='+str(result)]
        if bounds:
            command += ['-c', f'<</PageOffset [{-bounds[0]:g} {-bounds[1]:g}]>> setpagedevice', '-f']
        command.append(str(source))
        proc = subprocess.run(command, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT)
        info = subprocess.check_output(['pdfinfo', str(result)], text=True) \
            if proc.returncode == 0 and result.exists() else ''
        if proc.returncode or 'Pages:           1' not in info:
            return {'render_status': 'technically unusable',
                    'conversion_error': proc.stdout.decode(errors='replace')}
        output.write_bytes(result.read_bytes())
    return {'render_status': 'restored', 'derivative_sha256': digest(output),
            'conversion': {'tool': 'Ghostscript', 'flags': flags, 'bounding_box': bounds,
                           'source_sha256': digest(source),
                           'log': proc.stdout.decode(errors='replace')}}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--stage', action='store_true',
                        help='Copy inventoried historical sources once')
    parser.add_argument('--verify-reproducible', action='store_true')
    args = parser.parse_args()
    manifest_path = ROOT / 'figure-manifest.json'
    manifest = json.loads(manifest_path.read_text())
    entries = [e for e in manifest['images'] if e['status'] in
               ['conversion required', 'directly reusable']]
    if args.stage:
        for entry in entries:
            source = REPO / entry['selected']['resolved_path']
            target = ROOT / entry['staged_source']
            assert digest(source) == entry['selected']['sha256'], source
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(source, target)
        print(len(entries), 'exact historical sources staged locally')
    previous = {e['resource']: e.get('derivative_sha256') for e in entries}
    with ThreadPoolExecutor(max_workers=4) as executor:
        results = list(executor.map(convert, entries))
    for entry, result in zip(entries, results):
        entry.update(result)
        if args.verify_reproducible:
            assert previous[entry['resource']] == result.get('derivative_sha256'), \
                f'Non-reproducible derivative: {entry["resource"]}'
    if args.verify_reproducible:
        manifest['derivatives_reproducibility_verified'] = True
    manifest['ghostscript_version'] = subprocess.check_output(
        ['gs', '--version'], text=True).strip()
    manifest_path.write_text(json.dumps(manifest, ensure_ascii=False,
                                       indent=2)+'\n')
    from figure_inventory import report
    (ROOT / 'FIGURES.md').write_text(report(manifest))
    # Files use generated filenames, with safe macro names independent of paths.
    lines = ['% Generated from figure-manifest.json by prepare_figures.py.']
    for entry in entries:
        if entry.get('render_status') == 'restored':
            lines.append(r'\expandafter\def\csname historical@'+
                         entry['resource']+r'\endcsname{'+entry['derivative']+'}')
    (ROOT / 'figures-map.tex').write_text('\n'.join(lines)+'\n')
    counts = {state: sum(e.get('render_status') == state for e in entries)
              for state in ['restored', 'technically unusable']}
    print(counts)


if __name__ == '__main__':
    main()
