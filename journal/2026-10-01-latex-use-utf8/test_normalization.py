"""Regression checks for semantic comparison and protected TeX contexts."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'new/latex'))
from tex_unicode import normalize


class NormalizationTests(unittest.TestCase):
    def test_observed_prose_forms_and_grouped_ligature(self):
        self.assertEqual(normalize(r"Universit\'e, \`a, \^etre, fa\c{c}on, "
                                   r'{\oe}uvre, na\"if, \'E'),
                         'Université, à, être, façon, œuvre, naïf, É')
        self.assertEqual(normalize(r"\'{e}"), 'é')

    def test_headings_captions_and_semantic_text_macros(self):
        source = (r"\section[R\'esum\'e]{R\'esum\'e d'exp\'eriences} "
                  r"\mydumpfullR[t]{.8}{name}{R\'esum\'e}"
                  r"{Exp\'erience}{Une \aconcept{r\`egle}.}")
        expected = (r'\section[Résumé]{Résumé d’expériences} '
                    r'\mydumpfullR[t]{.8}{name}{Résumé}'
                    r'{Expérience}{Une \aconcept{règle}.}')
        # Apostrophe punctuation is deliberately not normalized.
        expected = expected.replace('d’expériences', "d'expériences")
        self.assertEqual(normalize(source), expected)

    def test_protected_material_is_exact(self):
        samples = [
            r"$x = \'e$", r"$$x=\'e$$", r"\(x=\'e\)",
            r"\[x=\'e\]", r"\begin{eqnarray}x=\'e\end{eqnarray}",
            r"\begin{verbatim}Universit\'e\end{verbatim}",
            r"\verb|Universit\'e|", r"\verb*|Universit\'e|",
            "% Universit\\'e\n", r"\label{\'e}", r"\cite[\'e]{key}",
            r"\input{\'e.tex}", r"\mygetref{\'e}",
            r"\mydumpfull{\'e}{Caption}{Caption}{Text}",
            r"\newcommand{\foo}[1]{\'e#1}", r"\arule{\'e}",
            r"\asoft{\'e}", r"\email{\'e}{domain}",
            r"\oe uvre", r"\oe{}uvre",
        ]
        for source in samples:
            with self.subTest(source=source):
                self.assertEqual(normalize(source), source)

    def test_escapes_and_comments_do_not_confuse_delimiters(self):
        self.assertEqual(normalize(r"\$ \'e \% \'e \\\'e"),
                         r'\$ é \% é \\é')
        source = "$x % $ ignored\n= \\'e$ Universit\\'e"
        self.assertEqual(normalize(source), source[:-len(r"Universit\'e")]
                         + 'Université')

    def test_semantic_comparison_rejects_unrelated_changes(self):
        source = r"\section{Universit\'e} $x=1$ \label{id} \cite{Key}"
        literal = r'\section{Université} $x=1$ \label{id} \cite{Key}'
        self.assertEqual(normalize(source), normalize(literal))
        for before, after in [('Université', 'Universités'), ('x=1', 'x=2'),
                              ('{id}', '{other}'), ('{Key}', '{Other}')]:
            self.assertNotEqual(normalize(source),
                                normalize(literal.replace(before, after)))
        self.assertNotEqual(normalize(r"$\'e$"), normalize('$é$'))


if __name__ == '__main__':
    unittest.main()
