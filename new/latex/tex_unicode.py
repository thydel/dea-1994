"""Conservative accent canonicalization for this inventoried LaTeX tree.

This is a lexical reader, not a TeX interpreter. Only observed prose accent
forms are accepted; protected contexts remain byte-for-byte unchanged.
"""
from dataclasses import dataclass
import re

CONTROL = re.compile(r'\\(?:[A-Za-z@]+|[^A-Za-z@])')
ACCENTS = {
    r"\'e": 'é', r"\'E": 'É', r'\`a': 'à', r'\`e': 'è',
    r'\`u': 'ù', r'\^a': 'â', r'\^e': 'ê', r'\^i': 'î',
    r'\^o': 'ô', r'\^u': 'û', r'\"i': 'ï', r'\c{c}': 'ç',
}
# Braced arguments with the same letters are equally unambiguous.
ACCENTS.update({token[:2]+'{'+token[2]+'}': char
                for token, char in list(ACCENTS.items()) if len(token) == 3})
ACCENT_RE = re.compile('|'.join(re.escape(x) for x in
                             sorted(ACCENTS, key=len, reverse=True)))
MATH_ENVS = {'math', 'displaymath', 'equation', 'eqnarray', 'align',
             'alignat', 'gather', 'multline', 'flalign'}
LITERAL_ENVS = {'verbatim', 'Verbatim', 'lstlisting', 'minted', 'comment'}
IDENTIFIER_ARGS = {
    'label': 1, 'ref': 1, 'pageref': 1, 'eqref': 1, 'vref': 1,
    'input': 1, 'include': 1, 'includeonly': 1, 'bibliography': 1,
    'bibliographystyle': 1, 'nocite': 1, 'mysetref': 1,
    'mysoftref': 1, 'mysoftcite': 1, 'myrulecite': 1,
    'arule': 1, 'asoft': 1, 'avar': 1, 'email': 2,
    'url': 1, 'path': 1, 'includegraphics': 1,
    'mytable': 1, 'mycodetwocol': 1, 'mycodefull': 1,
    'myfigure': 4, 'myfigureR': 5, 'mytwofigure': 6,
}
for prefix in ['mydump', 'myplot', 'myfig']:
    for size in ['full', 'twothirds', 'half']:
        IDENTIFIER_ARGS[prefix+size] = 1
        IDENTIFIER_ARGS[prefix+size+'R'] = 2
for name in ['mytwodumpfull', 'mytwoplotfull', 'mytwoplotVfull',
             'mytwofigfull']:
    IDENTIFIER_ARGS[name] = 2

@dataclass(frozen=True)
class Span:
    start: int
    end: int
    context: str

@dataclass(frozen=True)
class Change:
    start: int
    end: int
    before: str
    after: str


def group_end(text, pos, opening='{', closing='}'):
    """Read balanced arguments without mistaking escaped braces/comments."""
    assert text[pos] == opening
    depth = 1
    i = pos+1
    while i < len(text):
        if text[i] == '\\':
            match = CONTROL.match(text, i)
            i = match.end() if match else i+1
            continue
        if text[i] == '%':
            end = text.find('\n', i)
            i = len(text) if end < 0 else end+1
            continue
        if opening == '[' and text[i] == '{':
            i = group_end(text, i)
            continue
        if text[i] == opening:
            depth += 1
        elif text[i] == closing:
            depth -= 1
            if depth == 0:
                return i+1
        i += 1
    raise ValueError(f'Argument non terminé à la position {pos}')


def arguments_end(text, pos, required):
    """Include optional arguments and the requested mandatory arguments."""
    remaining = required
    i = pos
    while remaining:
        while i < len(text) and text[i].isspace():
            i += 1
        if i < len(text) and text[i] == '%':
            end = text.find('\n', i)
            i = len(text) if end < 0 else end+1
            continue
        if i < len(text) and text[i] == '*':
            i += 1
        elif i < len(text) and text[i] == '[':
            i = group_end(text, i, '[', ']')
        elif i < len(text) and text[i] == '{':
            i = group_end(text, i)
            remaining -= 1
        else:
            raise ValueError(f'Argument attendu à la position {i}')
    return i


def delimited_end(text, pos, delimiter):
    i = pos
    while i < len(text):
        if text[i] == '%':
            end = text.find('\n', i)
            i = len(text) if end < 0 else end+1
            continue
        if text.startswith(delimiter, i):
            return i+len(delimiter)
        if text[i] == '\\':
            match = CONTROL.match(text, i)
            i = match.end() if match else i+1
        else:
            i += 1
    raise ValueError(f'Délimiteur non terminé : {delimiter!r}')


def protected_spans(text):
    spans = []
    i = 0
    while i < len(text):
        start = i
        context = None
        if text[i] == '%':
            end = text.find('\n', i)
            i = len(text) if end < 0 else end
            context = 'commentaire'
        elif text[i] == '$':
            delimiter = '$$' if text.startswith('$$', i) else '$'
            i = delimited_end(text, i+len(delimiter), delimiter)
            context = 'mathématiques'
        elif text[i] == '\\':
            match = CONTROL.match(text, i)
            if not match:
                i += 1
                continue
            command = match[0][1:]
            i = match.end()
            if command in ['(', '[']:
                i = delimited_end(text, i, r'\)' if command == '(' else r'\]')
                context = 'mathématiques'
            elif command == 'verb':
                if text[i:i+1] == '*':
                    i += 1
                delimiter = text[i]
                end = text.find(delimiter, i+1)
                if end < 0:
                    raise ValueError('Commande verb non terminée')
                i = end+1
                context = 'code/verbatim'
            elif command in ['begin', 'end']:
                i = arguments_end(text, i, 1)
                env = text[match.end():i].strip()[1:-1]
                if command == 'begin' and (
                        env.rstrip('*') in MATH_ENVS or env in LITERAL_ENVS):
                    i = delimited_end(text, i, r'\end{'+env+'}')
                    context = ('mathématiques' if env.rstrip('*') in MATH_ENVS
                               else 'code/verbatim')
                else:
                    context = 'nom d’environnement'
            elif command in ['newcommand', 'renewcommand', 'providecommand']:
                i = arguments_end(text, i, 2)
                context = 'définition de macro'
            elif (command in IDENTIFIER_ARGS or command.startswith('cite')
                  or command.startswith('myget')):
                i = arguments_end(text, i, IDENTIFIER_ARGS.get(command, 1))
                context = 'identifiant/ressource'
        else:
            i += 1
        if context:
            spans.append(Span(start, i, context))
    return spans


def prose_changes(text, start, end):
    i = start
    while i < end:
        # Only this exact, observed redundant group may be removed.
        if text.startswith(r'{\oe}', i):
            yield Change(i, i+5, r'{\oe}', 'œ')
            i += 5
        elif text[i] == '\\':
            accent = ACCENT_RE.match(text, i)
            if accent and accent.end() <= end:
                yield Change(i, accent.end(), accent[0], ACCENTS[accent[0]])
                i = accent.end()
            else:
                match = CONTROL.match(text, i)
                i = match.end() if match else i+1
        else:
            i += 1


def changes(text):
    start = 0
    for span in protected_spans(text):
        yield from prose_changes(text, start, span.start)
        start = span.end
    yield from prose_changes(text, start, len(text))


def normalize(text):
    """Canonical prose, exact original syntax in every other context."""
    pieces = []
    start = 0
    for change in changes(text):
        pieces.extend([text[start:change.start], change.after])
        start = change.end
    pieces.append(text[start:])
    return ''.join(pieces)
