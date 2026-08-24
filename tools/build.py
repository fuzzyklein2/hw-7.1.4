"""Build utilities.

@file build.py
@brief Define tools for building the project.


"""

# Python modules
import os
from pathlib import Path
import shutil
import subprocess

# Packages
from grep import grep
import nbformat

# Local modules
from .constants import *
from .picts import *
from .read_lines import read_lines

# Constants
OPTIONS = { # kwargs for `run`
    "text" : True, # Ensures utf-8 encoding.
    "capture_output" : True,
    # "check" : True
}

ERROR_CODES = [
    "Success"
    "Out of sync with GitHub"
    "Error staging files for commit"
    "Error commiting changes"
    "Error pushing repository"
    "Unknown"
]

def combine_headers():
    FILES = [
        "macros",
        "types",
        "constants",
        "datetime",
        "str",
        "fs",
        "filter",
        "config",
        "environment",
        "logging",
        "globals",
        "program"
    ]
    PREFIX = Path("include")
    SUFFIX = "hpp"
    
    def suffix(s:str)->str:
        """ Return `SUFFIX` unless `s` is "macro". """
        return SUFFIX if s != "macros" else "h"
    
    REGEX = "#include"
    g = grep(REGEX)
    text = EMPTY_STR
    
    for f in FILES:
        p = PREFIX / (f + PERIOD + suffix(f))
        # print(f"{NEWLINE + str(p)}:{NEWLINE}")
        result = (p).read_text() | g
        text += NEWLINE + str(result)
    
    print(text)
    
    CONTENT_MARKER = "// --*-- content marker for hw7.hpp"
    
    lines = sorted([s[9:] for s in text.split(NEWLINE) if s != EMPTY_STR])
    
    lines = [s for s in lines if not Path(s.strip('"')).stem in FILES]
    
    lines = set(lines)
    
    output = """/**
     * @file hw7.hpp
     *
     * Single header for `hw7`.
     */
    
    // # System headers
    
    """
    
    for s in lines:
        output += f'#include {s + NEWLINE}'
    for f in FILES:
        output += Path(PREFIX / (f + PERIOD + suffix(f))).read_text().partition(CONTENT_MARKER)[2]
    
    Path("hw7/hw7.hpp").write_text(output)
    print(f"{CHECK_PICT}File `hw7/hw7.hpp` generated.")
    return 0

# Functions
def compile(target:str)->int:
    """ Build the target with meson.

        @param target Name of the target in meson.build.
        @return Error code.
    """
    tokens = f"meson compile -C build {target}".split()
    # Run meson
    process = subprocess.run(tokens, **OPTIONS)

    if process.returncode:
        outfile = Path(f"logs/{target}_build.log") # Receives stdout from meson.
        outfile.write_text(process.stdout)
        print(f"{ERROR_PICT}Build error!")
        OUTPUT = read_lines(outfile)
        # This seems to work for meson output. It may work for g++ too.
        print(NEWLINE.join([s for s in OUTPUT[3:] if not (s.startswith('c') or s.startswith('INFO')) and s.find(PARENT)]))
        return process.returncode
    else:
        print(f"{CHECK_PICT}Build successful")

    return 0

def test(target:str)->int:
    """ Test the target.

        @param target The name of the executable.
        @return Error code.
    """
    # For now, a successful build means the module passed.
    # A target file with no suffix should be an executable.
    # For this project, for now, executables with 0 arguments, options or input should have 0 output.
    EXE = Path(f"build/{target}")
    if EXE.exists():
        print(f"{INFO_PICT}Testing {target}...")
        process = subprocess.run([f"build/{target}"], **OPTIONS)
        ERROR_CODE = process.returncode
        if ERROR_CODE:
            outfile = Path(f"logs/{target}_test.log")
            print(f"{ERROR_PICT}{target} returned error code: {ERROR_CODE}: {ERROR_CODES[min(ERROR_CODE, len(ERROR_CODES) - 1)]}")
            return ERROR_CODE
        if process.stdout:
            print(f"""stdout:{NEWLINE}{process.stdout}{NEWLINE}""")            
        if process.stderr:
            print(f"""stderr:{NEWLINE}{process.stderr}{NEWLINE}""")
        print(f"{CHECK_PICT}Testing complete.")

        return 0

def clear():
    """ Clear the outputs of all Jupyter notebook code cells. """
    # print("Running `clear()`...")
    for path in Path("lab").glob("*.ipynb"):
        notebook = nbformat.read(path, as_version=4)
        # print(f"Clearing {path}")

        for cell in notebook.cells:
            if cell.cell_type == "code":
                cell.outputs = []
                cell.execution_count = None

        nbformat.write(notebook, path)
        print(f"{CHECK_PICT}Jupyter output cleared.")
        return 0
    
def docs()->int:
    """ Generate the project documentation. """
    # rm -rf docs
    # doxygen
    DOCS = Path("docs")
    if DOCS.exists():
        shutil.rmtree(DOCS, onexc=lambda s: print(f"""{ERROR_PICT}Folder {s} does not exist! 🤨
    """))
    process = subprocess.run(["doxygen"], **OPTIONS)
    if not process.returncode:
        print(f"{CHECK_PICT}Docs generated")

    return 0
    
def commit(target:str, message:str)->int:
    """ Add changes, commit them, and push repository to GitHub. """
    tokens = ["git", "status"]
    process = subprocess.run(tokens, **OPTIONS)
    ERROR_CODE = process.returncode
    if ERROR_CODE:
        outfile = Path(f"logs/{target}_test.log")
        print(f"{ERROR_PICT}{target} returned error code: {ERROR_CODE}: {ERROR_CODES[min(ERROR_CODE, len(ERROR_CODES) - 1)]}")
    if process.stdout: # This is really long and boring. 🙄
        # print(f"""stdout:{NEWLINE}{process.stdout}{NEWLINE}""")
        outfile = Path(f"logs/{target}_git_output.txt")
        outfile.write_text(process.stdout)
        lines = read_lines(outfile)
        # print(lines[5])
        if not lines[1].startswith("Your branch is up to date with"):
            print(f"{STOP_PICT}Branch is not up to date!")
            return 1
        
    if process.stderr: # Should probably print this no matter what if it exists.
        print(f"""stderr:{NEWLINE}{process.stderr}{NEWLINE}""")

    tokens = ["git", "add", "."]
    process = subprocess.run(tokens, **OPTIONS)
    if process.returncode:
        print(f"{STOP_PICT}Error adding files!")
        return 2
    else: print(f"{CHECK_PICT}Modified files staged for commit.")

    tokens = ["git", "commit", "-m", message]
    process = subprocess.run(tokens, **OPTIONS)
    if process.returncode:
        print(f"{STOP_PICT}Error committing changes!")
        return 3
    else: print(f"{CHECK_PICT}Changes commited to repository.")
        
    tokens = ["git", "push"]
    process = subprocess.run(tokens, **OPTIONS)
    if process.returncode:
        print(f"{STOP_PICT}Error pushing repository to GitHub!")
        return 4
    else: print(f"{CHECK_PICT}Repository pushed to GitHub.")

    return 0

def build(target:str, message:str)->int:
    """ Build a target object.

        * Compile the object.
        * Test the executable.
        * Generate the project documentation.
        * Stage changes for git.
        * Commit the changes.
        * Push changes to GitHub.

        @param target Name of the target in meson.build.
        @message Commit message for git.
        @return Error code.
    """
    result = combine_headers()
    if result:
        print(f"{STOP_PICT}Error combining headers!")
        return result
    result = compile(target)
    if result:
        print(f"{STOP_PICT}Error compiling {target}!")
        return result
    result = test(target)
    if result:
        print(f"{STOP_PICT}Testing {target} failed!")
        return result
    result = clear()
    if result:
        print(f"{STOP_PICT}Error clearing jupyter output!")
        return result        
    result = docs()
    if result:
        print(f"{STOP_PICT}doxygen error!")
        return result
    result = commit(target, message)
    if result:
        print(f"{STOP_PICT}Error revising repository!")
        return result
    return 0