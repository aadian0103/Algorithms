# generate cpp snippet for vscode
import os
import json
import sys

snippets = {}

for root, _, files in os.walk('.'):
    # Skip .git folders
    if '.git' in root:
        continue

    for filename in files:
        name, extension = os.path.splitext(filename)
        extension = extension.lstrip('.')  # remove the leading dot

        if extension != 'cpp':
            continue

        # Avoid duplicates
        if name in snippets:
            print(f'Error: duplicate snippet {name}', file=sys.stderr)
            exit(1)

        path = os.path.join(root, filename)
        with open(path, 'r') as f:
            body = [line.rstrip('\n') for line in f]  # preserve indentation
            snippet = {
                "prefix": name,
                "body": body,
                "description": f"Snippet from {filename}"
            }
            snippets[name] = snippet

        print(f'Generated snippet {name}', file=sys.stderr)

# Write to cpp.json
with open('cpp.json', 'w') as f:
    json.dump(snippets, f, indent=2)

print('All snippets generated in cpp.json', file=sys.stderr)
