"""Wrap edited prose at 70 columns, retaining tables and fenced code."""
from pathlib import Path
import re
import textwrap

ROOT = Path(__file__).resolve().parents[2]


def fill(block):
    text = ' '.join(line.strip() for line in block)
    # Preserve machine-sensitive inline code as indivisible tokens.
    text = re.sub(r'`[^`]+`', lambda m: m[0].replace(' ', '\x00'), text)
    indent = '  ' if text.startswith('- ') else ''
    text = textwrap.fill(text, width=70, subsequent_indent=indent,
                         break_long_words=False, break_on_hyphens=False)
    return text.replace('\x00', ' ')


def wrap(text):
    output, block = [], []
    fenced = False
    for line in text.splitlines():
        if line.startswith('```'):
            if block:
                output.append(fill(block))
                block = []
            output.append(line)
            fenced = not fenced
        elif fenced or not line or line.startswith(('#', '|')):
            if block:
                output.append(fill(block))
                block = []
            output.append(line)
        else:
            if line.startswith('- ') and block:
                output.append(fill(block))
                block = []
            block.append(line)
    if block:
        output.append(fill(block))
    return '\n'.join(output)+'\n'


if __name__ == '__main__':
    for name in ['README.md', 'VALIDATION.md']:
        path = ROOT / 'new/latex' / name
        path.write_text(wrap(path.read_text()))
