import os
import sys

output_lines = []

for root, _, files in os.walk('.'):
    if '.git' in root:
        continue

    for filename in files:
        name, extension = os.path.splitext(filename)
        extension = extension.lstrip('.')

        if extension != 'cpp':
            continue

        path = os.path.join(root, filename)
        with open(path, 'r') as f:
            body = [line.rstrip('\n') for line in f]

        # SnipMate format:
        # snippet <name>
        #     <body>
        output_lines.append(f"snippet {name}")
        output_lines.extend([f"\t{line}" if line.strip() != "" else "" for line in body])
        output_lines.append("")  # blank line after each snippet

        print(f"Generated snippet {name}", file=sys.stderr)

# Write to cpp.snippets
with open('cpp.snippets', 'w') as f:
    f.write("\n".join(output_lines))

print("All snippets written to cpp.snippets", file=sys.stderr)

