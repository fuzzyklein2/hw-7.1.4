from datetime import datetime as dt
from functools import singledispatch
import inspect
import os
from pathlib import Path
from pprint import pprint as pp
import sys

from grep import grep
from IPython.display import display, Markdown
import pyperclip
from rich import print as rp
from rich.columns import Columns
from rich.console import Console

from .constants import *
from .picts import *

def error(s:str):
    rp(ERROR_PICT + '[red]ERROR[/red]: ' + s)

def warn(s:str):
    rp(WARNING_PICT + '[yellow]WARNING[/yellow]: ' + s)

def critical(s:str):
    rp(CRITICAL_PICT + '[red]CRITICAL[/red]: ' + s)

def info(s:str):
    rp(INFO_PICT + '[cyan]INFO[/cyan]: ' + s)

def debug(s:str):
    rp(DEBUG_PICT + '[green]DEBUG[/green]; ' + s)

def columnize(L:list[str]):
    """ Arrange the list of strings into columns. `rich` handles spacing of its color strings. """
    Console().print(Columns(sorted(L), expand=True, equal=True))

def display_doc(func):
    """
    Display a function or class docstring as Markdown in Jupyter Lab
    safely, avoiding duplicated headers.
    """
    doc = func.__doc__ or ""
    # Split lines and remove any that are blank at the start
    lines = doc.splitlines()
    while lines and not lines[0].strip():
        lines.pop(0)
    cleaned_doc = "\n".join(lines)
    display(Markdown(cleaned_doc))

@singledispatch
def empty(arg)->bool:
    """Print an error message and depart."""
    error(f': empty : bad argument : {arg} : Argument must be a `list`.')

@empty.register
def _(L:list)->bool:
    """ @return `True` if the `list` is empty, `False` otherwise.
    """
    return len(L) == 0

@singledispatch
def display_source(arg)->None:
    """Print an error message and depart."""
    error(f': display_source : bad argument : {arg} : Argument must be str or Path')

@display_source.register
def _(s:str, lang:str='python')->None:
    display(Markdown(f'```{lang}\n{s}'))

@display_source.register
def _(p:Path, lang:str='python')->None:
    display_source(p.read_text(), lang=lang)

@display_source.register
def _(obj:object, lang:str='python')->None:
    display_source(inspect.getsource(obj))

def cwd():
    """Return the current working directory."""
    return Path.cwd()

def pwd():
    """Print `cwd()` and return it."""
    CWD = cwd()
    print(f'{FOLDER_PICT}Current working directory: {CWD}')
    return CWD

def cd(p:str|Path)->Path|None:
    """Change the current working directory."""
    p = Path(p)
    if not p.exists():
        print(f'{WARNING_PICT}WARNING: Directory {str(p)} does not exist!')
        return
    os.chdir(p)
    return p

def hidden(p: Path | str | None) -> bool:
    return any(map(lambda s: s.startswith('.'), p.parts))

def lsd(p: Path | str | None = None, output = True) -> list[Path]:
    """ List the given directory.
        @todo This needs to have a recursive option.
    """
    if not p: p = Path.cwd()
    p = Path(p)
    paths = [path for path in p.glob('*') if not hidden(path)]
    if output:
        pp(list(map(str, paths)))
    return paths

def public(obj)->list:
    """Return the (supposedly) "public" members of the given object."""
    return sorted([s for s in dir(obj) if not s.startswith('_')])

def doxify(text, print_result=True):
    # Just add comment delimiters and asterisks.
    lines = text.split('\n')[1:]
    result = ['/**']
    result.extend([' * ' + s for s in lines])
    result.pop()
    result.append(' */')
    result = '\n'.join(result)
    if print_result: print(result)
    pyperclip.copy(result + NEWLINE)
    print("Docstring copied to clipboard")
    return result

def grepy(
    pattern,
    project_name
):
    """
        Find `pattern` in the project source directory, presumed to be in `CWD`.
    """
    DEBUG = True

    REGEX = grep(pattern, words_only=True)
    FILES = lsd(project_name, output=False)
    for f in FILES:
        if f.suffix.lstrip(PERIOD) in SRC_FILE_EXTS:
            t = f.read_text()
            m = t | REGEX
        
            LINES = t.split(NEWLINE)
            line_nos = list(m.matches.matching_lines())
            # print(f"`lines` is a {type(m.matches.matching_lines)}.")
            # lines = list(m.matches.matching_lines())
        
            if line_nos:
                n = max(map(lambda i: len(str(i)), line_nos))
                lines = [
                    f"{str(i).rjust(n)}: {LINES[i].lstrip()}"
                    for i in line_nos
                    if not (
                        LINES[i].lstrip().startswith('/') or
                        LINES[i].lstrip().startswith('*') or
                        LINES[i].lstrip().startswith('//')
                    )
                ]
            
                if lines:
                    rp(f"{pattern} found in [yellow]{f.name}[/yellow]:")
                    # lines = [s.lstrip() for s in lines]
                    for s in lines:
                        print(s)

def now(as_str=False):
    """
        Return the current date and time.
    """
    if as_str: return str(dt.now())
    return dt.now()