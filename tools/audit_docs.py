import os
import glob
import re

docs = glob.glob('docs/**/*.md', recursive=True)
print(f'Total markdown files: {len(docs)}')

for doc in sorted(docs):
    if 'doxygen' in doc:
        continue
    with open(doc, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    # Check for hardcoded local absolute paths
    local_paths = re.findall(r'file:///[^\s\)\"\\]+', content)
    if local_paths:
        print(f'{doc}: found local file URIs: {local_paths}')

    # Check for esp32-s3_bsp references
    if 'esp32-s3_bsp' in content:
        print(f'{doc}: contains esp32-s3_bsp')

    # Check for broken markdown links
    links = re.findall(r'\[([^\]]+)\]\(([^)]+)\)', content)
    for text, link in links:
        if link.startswith('http') or link.startswith('#') or link.startswith('mailto:') or link.startswith('file:'):
            continue
        link_path = link.split('#')[0]
        if not link_path:
            continue
        target = os.path.normpath(os.path.join(os.path.dirname(doc), link_path))
        if not os.path.exists(target):
            print(f'{doc}: broken link -> {link} (resolved: {target})')
