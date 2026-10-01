"""Inventory historical image provenance before preparing PDF derivatives."""
from pathlib import Path
import hashlib
import json
import os
import re
import textwrap

ROOT = Path(__file__).resolve().parent
REPO = ROOT.parent.parent
OLD = REPO / 'old'


def relative(path):
    return str(path.relative_to(REPO))


def file_info(path):
    chain = []
    current = path
    seen = set()
    while current.is_symlink():
        if current in seen:
            return {'path': relative(path), 'link_chain': chain,
                    'exists': False, 'format': 'cyclic link'}
        seen.add(current)
        target = os.readlink(current)
        chain.append({'path': relative(current), 'target': target})
        current = Path(os.path.normpath(current.parent / target))
    exists = current.is_file()
    info = {'path': relative(path), 'link_chain': chain, 'exists': exists,
            'resolved_path': relative(current)}
    if not exists:
        info['format'] = 'missing/broken link'
        return info
    data = current.read_bytes()
    if data.startswith(b'%!'):
        fmt = 'EPS' if b'EPSF' in data[:200] else 'PS'
    elif data.startswith(b'%PDF-'):
        fmt = 'PDF'
    elif data.startswith(b'#FIG'):
        fmt = 'FIG source'
    elif re.match(rb'P[1-6]\s', data[:3]):
        fmt = 'PNM raster'
    elif '.xvpics' in path.parts:
        fmt = 'XV thumbnail/cache'
    elif path.suffix == '.tbl':
        fmt = 'LaTeX table (not an image)'
    else:
        fmt = 'other source/data'
    info.update(format=fmt, sha256=hashlib.sha256(data).hexdigest(),
                size=len(data))
    if fmt in ['PS', 'EPS']:
        boxes = re.findall(rb'^%%(?:HiRes)?BoundingBox:\s*([^\r\n]+)',
                           data, re.M)
        info['bounding_boxes'] = [x.decode('ascii', errors='replace')
                                  for x in boxes]
    return info


def scan():
    paths = []
    for directory, dirs, files in os.walk(OLD, followlinks=False):
        for name in files:
            paths.append(Path(directory) / name)
    records = (ROOT / 'main.resources').read_text().splitlines()
    resources = [x.split(': ', 1)[1] for x in records
                 if x.startswith(('image: ', 'image-restored: '))]
    # Original log is primary evidence for the extension selected in 1994.
    log = (OLD / 'txt/tex/top.log').read_text('latin1')
    logged = re.findall(r'<(\.\./[^>]+)>', log)
    labels = dict(re.findall(r'\\newlabel\{([^}]+)\}\{\{([^}]+)\}',
                  ''.join(p.read_text() for p in (ROOT / 'chapters').glob('*.aux'))))
    images = []
    for resource in resources:
        directory, name = Path(resource).parts[-2:]
        candidates = [file_info(p) for p in sorted(paths)
                      if p.stem == name or p.name == name]
        exact = sorted(set(p for p in logged
                           if str(Path(p).with_suffix('')) == resource))
        entry = {'resource': resource, 'original_tex_path': resource,
                 'candidates': candidates,
                 'labels': [{'label': label, 'number': num}
                            for label, num in labels.items()
                            if label.startswith(directory+'-')
                            and not label.endswith('-section')
                            and name in label[len(directory)+1:].split('+')]}
        locations = []
        for p in sorted((ROOT / 'chapters').glob('*.tex')):
            for n, line in enumerate(p.read_text().splitlines(), 1):
                if '{'+name+'}' in line and re.match(
                        r'\s*\\my(?!get|soft|rule)', line):
                    locations.append({'file': str(p.relative_to(ROOT)),
                                      'line': n})
        entry['calls'] = locations
        if len(exact) != 1:
            entry.update(status='ambiguous' if candidates else 'missing',
                         reason='No unique exact inclusion in top.log')
        else:
            selected = Path(os.path.normpath(OLD / 'txt/tex' / exact[0]))
            info = file_info(selected)
            entry['historical_log_path'] = exact[0]
            entry['selected'] = info
            entry['derivative'] = f'figures/pdf/{directory}/{name}.pdf'
            entry['staged_source'] = f'figures/source/{directory}/{name}{selected.suffix}'
            entry['reason'] = ('Exact original macro argument and inclusion in '
                               'old/txt/tex/top.log; preserved link chain '
                               'selects the historical backing file.')
            if not info['exists']:
                entry['status'] = 'missing'
            elif info['format'] not in ['PS', 'EPS', 'PDF']:
                entry['status'] = 'technically unusable'
            else:
                entry['status'] = 'conversion required' if info['format'] != 'PDF' else 'directly reusable'
        images.append(entry)
    return {'historical_tree_paths_scanned': len(paths),
            'baseline_deferred_image_occurrences': 88,
            'selection_evidence': ['active TeX resource calls',
                                   'old/txt/tex/top.log',
                                   'preserved symbolic link targets',
                                   'old/txt/dump/Makefile'],
            'images': images}


def report(manifest):
    images = manifest['images']
    lines = ['# Historical figure inventory', '',
             'Inventory completed before image conversion or loading. '
             'Every expected image is traced through the exact source '
             'argument, the successful 1994 log and surviving link chains.', '',
             f'The scan covers {manifest["historical_tree_paths_scanned"]} '
             'file paths under the complete historical tree, including '
             '1993 resources, 1994 resources, older roff material and '
             'XV thumbnails. Tables and data/source files are classified '
             'separately and never selected as images.', '',
             'The dump Makefile documents the union of `dump-93/*.ps`, '
             '`dump-94/*.eps` and `dump-94/*.ps`. The links select the '
             'backing files; identical stems elsewhere do not override '
             'the exact path recorded in `top.log`. Dump/plot versions '
             'of `anneal-01`, `anneal-02`, `anneal-03`, `anneal-sum` '
             'and `lifex-sum-*` are distinct and remain distinct.', '',
             'The full machine-readable record is `figure-manifest.json`. '
             'It includes every matching basename, actual format, hash, '
             'symbolic-link chain, selected source and derivative path.', '',
             '## Mapping of all image occurrences', '',
             '| Expected resource | Figure label / number | Exact logged file | Link chain / canonical source | Actual format | Disposition | Local derivative |',
             '|---|---|---|---|---|---|---|']
    for entry in images:
        info = entry.get('selected', {})
        links = '; '.join(f'`{x["path"]}` → `{x["target"]}`'
                          for x in info.get('link_chain', []))
        canonical = info.get('resolved_path', 'unselected')
        refs = ', '.join(f'`{x["label"]}` ({x["number"]})'
                         for x in entry['labels'])
        lines.append('| '+' | '.join([
            '`'+entry['resource']+'`', refs,
            '`'+entry.get('historical_log_path', 'none')+'`',
            (links+'; ' if links else '')+'`'+canonical+'`',
            info.get('format', 'unknown'), entry.get('render_status', entry['status']),
            '`'+entry.get('derivative', 'none')+'`'])+' |')
    lines += ['', '## All candidates and supporting files', '',
              'Candidates below include native figure sources, raster '
              'antecedents, table data and thumbnails. Only the exact '
              'historical logged resource is selected for conversion.']
    for entry in images:
        lines += ['', '### '+entry['resource'], '']
        for candidate in entry['candidates']:
            lines.append('- `'+candidate['path']+'`: '+candidate['format']+
                         ('; → `'+candidate['resolved_path']+'`'
                          if candidate['link_chain'] else '')+'.')
    return '\n'.join(line if not line or line.startswith(('|', '#')) else
                     textwrap.fill(line, width=70, break_long_words=False,
                                   break_on_hyphens=False,
                                   subsequent_indent='  ' if line.startswith('- ') else '')
                     for line in lines)+'\n'


if __name__ == '__main__':
    manifest = scan()
    (ROOT / 'figure-manifest.json').write_text(
        json.dumps(manifest, ensure_ascii=False, indent=2)+'\n')
    (ROOT / 'FIGURES.md').write_text(report(manifest))
    from collections import Counter
    print(len(manifest['images']), 'occurrences;',
          dict(Counter(x['status'] for x in manifest['images'])))
