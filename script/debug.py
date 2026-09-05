""" `gdb` python script.

@file build.py
@brief Define tools for building the project.

Execute with:

```bash
$ gdb -q -x script/debug.py --args build/peroxide -d
```
"""

import gdb

class SongBreak(gdb.Breakpoint):
    
    def __init__(self, s):
        # super().__init__()
        self.label = s;

    def stop(self):
        print(f"\n========== {self.label} ==========")
        gdb.execute("info locals")

class NextClipBreakpoint(gdb.Breakpoint):
    def stop(self):
        print("\n========== pattern::next_clip ==========")

        try:
            print(f"i             = {gdb.parse_and_eval('i')}")
            print(f"j.size()      = {gdb.parse_and_eval('j.size()')}")
            print(f"repeat_count  = {gdb.parse_and_eval('repeat_count')}")
            print(f"current_repeat= {gdb.parse_and_eval('current_repeat')}")
        except gdb.error as e:
            print(f"Could not inspect variables: {e}")

        return True

class LoadBreakpoint(gdb.Breakpoint):
    def stop(self):
        print("\n========== song::load ==========")
        # print(gdb.execute("bt", to_string=True))
        return True


NextClipBreakpoint("pattern::next_clip()")
LoadBreakpoint("song::load(JSON)")
LoadBreakpoint("song::load(const str&)")
SongBreak("song::song(song (const hw7::str& s, JSON config)")
SongBreak("song_list::song_list(const hw7::str&, JSON)")

print("Debug breakpoints installed.")
