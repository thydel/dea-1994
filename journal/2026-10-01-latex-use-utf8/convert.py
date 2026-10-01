"""Execute the inventoried, context-aware prose conversion once."""
from pathlib import Path
import collections
import json
import sys

JOURNAL = Path(__file__).resolve().parent
ROOT = JOURNAL.parents[1]
sys.path.insert(0, str(ROOT / 'new/latex'))
from tex_unicode import changes, normalize

inventory = json.loads((JOURNAL / 'accent-inventory.json').read_text())
prepared = []
for filename, expected in inventory['files'].items():
    path = ROOT / filename
    before = path.read_text()
    edits = list(changes(before))
    assert len(edits) == expected['converted'], filename
    assert dict(collections.Counter(x.before for x in edits)) == \
        expected['forms'], filename
    after = normalize(before)
    assert after.count('\n') == before.count('\n'), filename
    assert not list(changes(after)), filename
    if before != after:
        prepared.append((path, after))
# Validate the whole proposed conversion before writing any source.
for path, after in prepared:
    path.write_text(after)
print(f'{len(prepared)} fichiers convertis ; '
      f'{sum(x["converted"] for x in inventory["files"].values())} '
      'occurrences de prose remplacées.')
