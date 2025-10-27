import os
import sys

snippets = []

def escape_lua_string(s: str) -> str:
    """Escape backslashes and quotes for Lua string literals."""
    return s.replace("\\", "\\\\").replace('"', '\\"')

for root, _, files in os.walk('.'):
    if '.git' in root:
        continue

    for filename in files:
        name, ext = os.path.splitext(filename)
        if ext != '.cpp':
            continue

        if any(s.startswith(f'  s("{name}"') for s in snippets):
            print(f"Error: duplicate snippet {name}", file=sys.stderr)
            sys.exit(1)

        path = os.path.join(root, filename)
        with open(path, 'r', encoding='utf-8') as f:
            lines = [line.rstrip('\n') for line in f]

        # Optional description from first comment line
        desc = ""
        if lines and lines[0].strip().startswith('//'):
            desc = lines[0].strip().lstrip('/').strip()
            lines = lines[1:]

        # Escape special chars
        escaped_lines = [f'"{escape_lua_string(line)}"' for line in lines]

        if desc:
            snippet = f'  s({{ trig = "{name}", desc = "{escape_lua_string(desc)}" }}, t({{ {", ".join(escaped_lines)} }})),'
        else:
            snippet = f'  s("{name}", t({{ {", ".join(escaped_lines)} }})),'

        snippets.append(snippet)
        print(f"Generated snippet {name}", file=sys.stderr)

# Write LuaSnip file
with open('cpp.lua', 'w', encoding='utf-8') as f:
    f.write("-- Auto-generated LuaSnip snippets for C++\n")
    f.write("return {\n")
    f.write('\n'.join(snippets))
    f.write("\n}\n")

print("All snippets written to cpp.lua", file=sys.stderr)
