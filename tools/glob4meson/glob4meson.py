from pathlib import Path

def glob4meson():
    # ---------- Configuration ----------
    src_dir = Path('source')
    meson_file = Path('meson.build')
    
    # Extensions to include
    exts = ['.c', '.cp', '.cc', '.cpp']
    
    # ---------- Step 1: Scan src/ ----------
    src_files = sorted(f.as_posix() for f in src_dir.iterdir() if f.suffix in exts)
    
    if not src_files:
        print("No source files found in src/.")
    else:
        print(f"Found {len(src_files)} source files:")
        for f in src_files:
            print(f"  {f}")
    
    # ---------- Step 2: Update meson.build ----------
    # We'll look for a placeholder line: '# --- AUTOGEN_SRC_START ---'
    # and replace the block until '# --- AUTOGEN_SRC_END ---'
    # Users need to put these markers in meson.build
    
    if not meson_file.exists():
        raise FileNotFoundError(f"{meson_file} not found.")
    
    with meson_file.open('r') as f:
        lines = f.readlines()
    
    new_lines = []
    inside_block = False
    
    for line in lines:
        if '# --- AUTOGEN_SRC_START ---' in line:
            inside_block = True
            new_lines.append(line)
            # insert new src_files list here
            new_lines.append('src_files = [\n')
            for fpath in src_files:
                new_lines.append(f"  '{fpath}',\n")
            new_lines.append(']\n')
            continue
        if '# --- AUTOGEN_SRC_END ---' in line:
            inside_block = False
        if not inside_block:
            new_lines.append(line)
    
    with meson_file.open('w') as f:
        f.writelines(new_lines)
    
    print(f"meson.build updated with {len(src_files)} source files.")

if __name__ == "__main__":
    print(f"Running {__file__}")
    glob4meson()
    