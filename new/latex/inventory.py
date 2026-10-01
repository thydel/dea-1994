"""Generate the human-readable resource audit from executed TeX resource calls."""
from pathlib import Path
import re
root=Path(__file__).resolve().parent
labels=dict(re.findall(r'\\newlabel\{([^}]+)\}\{\{([^}]+)\}', ''.join(p.read_text() for p in (root/'chapters').glob('*.aux'))))
lines=['# Inventaire des ressources de la phase 1','','Inventaire issu des appels réellement exécutés, consignés dans `main.resources`. Les légendes et textes explicatifs restent dans les chapitres, sans modification. Les labels composés correspondent aux figures à plusieurs ressources.','','## Images et listings différés','','| Type | Ressource attendue | Fichier historique disponible | Label(s) et numéro(s) | Appel dans le texte |','|---|---|---|---|---|']
for record in (root/'main.resources').read_text().splitlines():
    kind,resource=record.split(': ',1)
    parts=Path(resource).parts; directory,name=parts[-2:]
    historical=root/'../../old/txt'/directory
    available=sorted(p.name for p in historical.glob(name+'.*') if not p.name.endswith('~'))
    prefix='code' if kind=='code' else directory
    refs=[f'`{label}` ({num})' for label,num in labels.items() if not label.endswith('-section') and label.startswith(prefix+'-') and name in label[len(prefix)+1:].split('+')]
    locations=[]
    for p in sorted((root/'chapters').glob('*.tex')):
        for n,line in enumerate(p.read_text().splitlines(),1):
            if '{'+name+'}' in line and re.match(r'\s*\\my(?!get|soft|rule)',line):
                locations.append(f'[{p.name}](chapters/{p.name}), ligne {n}')
    lines.append('| '+ ' | '.join([kind,f'`{resource}`',', '.join('`'+p+'`' for p in available) or 'Aucun fichier retrouvé',', '.join(refs) or 'Sans label numéroté', '; '.join(locations) or 'Appel indirect'])+' |')
lines+=['','## Tables incluses','','Les dix tableaux sont compilés directement. Aucun tableau n’est neutralisé.','','| Source locale | Label et numéro |','|---|---|']
for p in sorted((root/'tables').glob('*.tbl')):
    label='tbl-'+p.stem
    lines.append(f'| [tables/{p.name}](tables/{p.name}) | `{label}` ({labels[label]}) |')
lines+=['','## Limites et ambiguïtés conservées','','- Les noms de ressource sont ceux des macros historiques, même lorsqu’ils ne comportent pas d’extension. Les chemins affichés sont informatifs et ne sont jamais chargés par TeX.','- Les fichiers `.tex` des listings externes sont des sorties historiques de `lgrind`, pas du texte scientifique à reformuler ; leur inclusion complète est différée.','- Les listings `verbatim` présents dans les chapitres restent intégralement inclus.','- Aucune ambiguïté scientifique n’a nécessité de substitution de contenu. Les formulations, coquilles et valeurs historiques restent conservées.','']
(root/'RESSOURCES.md').write_text('\n'.join(lines))
