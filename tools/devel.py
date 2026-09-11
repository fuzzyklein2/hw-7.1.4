from pathlib import Path
import re

def extract_comments(p: Path)->list:
    COMMENT_PATTERN = r"/\*(.*?)\*/"
    assert(p.exists())
    text = p.read_text()
    L = re.findall(COMMENT_PATTERN, text, re.DOTALL)
    return L