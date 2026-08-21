"""
    @file __init__.py
    
    Maybe `doxygen` just recognizes the triple-quotes.
"""

print("Initializing glob4meson...")

import json
from pathlib import Path
from pprint import pprint as pp
from .._git_tools import get_upstream_url
from .._last_saved_date import last_saved_datetime as LSD
print(f"Current working directory: {Path.cwd()}")
DATA_FILE = Path("data/data.json")
with DATA_FILE.open() as f:
    DATA = json.load(f)
pp(DATA)

__doc__ = f"""Add `source/*` to `meson.build`.


========== ⚠️  WARNING! ⚠️  ==========

This project is currently under construction.
Stay tuned for updates.

## Version

{DATA["version"]}

## Author

{DATA["author"]}

## Date

{LSD(__file__).date()}

## Usage

### Jupyter
```python
from tools.glob4meson import glob4meson as g4m
g4m()
```

### Terminal
From the project directory:
```bash
bin/g4m
```

### Script
The intended usage. Call just before building objects or executables.
@see Terminal. 

## System Requirements

{Path("tools/glob4meson/requirements.txt").read_text()}

@see [GitHub]({get_upstream_url()})

"""
