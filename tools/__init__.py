"""
    @file __init__.py
    
    Maybe `doxygen` just recognizes the triple-quotes.
"""
#!/usr/bin/env python3

# from importlib import import_module
# from pathlib import Path
# import sys

# from ._imports import import_chain

# def get_project_nv(s: str | Path) -> (str, str):
#     # debug(f'{type(s)=}')
#     COMPONENTS = Path(s).resolve().name.split('-')
#     # print(f'Current working directory: {Path(s).resolve()}')
#     return ('-'.join(COMPONENTS[:-1]), COMPONENTS[-1])

# PACKAGE_NAME = import_chain()[0]
# # print(f'{PACKAGE_NAME=}')
# if PACKAGE_NAME.startswith('_pyrepl') or "ipykernel" in sys.modules or PACKAGE_NAME.startswith('runpy'):
#     PACKAGE_NAME, VERSION = get_project_nv('.')
#     # print(PACKAGE_NAME)

# try:
#     _metadata = import_module(f'{PACKAGE_NAME}._metadata')
#     globals().update(vars(_metadata))
# except ModuleNotFoundError: # Most likely happens in a Jupyter notebook or a console
#                             # Appears to happen in pydoc as well.
#     from ._metadata import *

print("Initializing glob4meson...")

import json
from pathlib import Path
from pprint import pprint as pp
from ._git_tools import get_upstream_url
from ._last_saved_date import last_saved_datetime as LSD
print(f"Current working directory: {Path.cwd()}")
DATA_FILE = Path("data/data.json")
with DATA_FILE.open() as f:
    DATA = json.load(f)
pp(DATA)

__doc__ = f"""Generate a list of source files and insert them into `meson.build`.


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

{Path("tools/requirements.txt").read_text()}

@see [GitHub]({get_upstream_url()})

"""

CWD = Path.cwd()

from .glob4meson.glob4meson import glob4meson as g4m

