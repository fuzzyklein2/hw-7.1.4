# GDB

[Debugging with GDB](https://sourceware.org/gdb/current/onlinedocs/gdb)

[Advanced GDB](https://interrupt.memfault.com/blog/advanced-gdb)

[8 gdb tricks](https://blogs.oracle.com/linux/8-gdb-tricks-you-should-know)

[Viewing Data](https://cgi.cse.unsw.edu.au/~learn/debugging/modules/gdb_viewing_data/)

To use GDB (GNU Debugger) to debug a program, you follow a four-step workflow: compiling with debug symbols, starting GDB, controlling execution, and inspecting state. [1, 2]  
Here is the essential guide to debugging your C or C++ program with GDB: [1, 3]  
1. Compile with Debug Symbols 
You must tell your compiler to include debugging information. Without this, GDB cannot show you your source code or variable names. Use the  flag: [1, 3, 4]  
2. Start GDB 
Launch GDB by passing your compiled executable as an argument: [1, 3]  
💡 Pro-Tip: Once inside GDB, press  +  followed by  (or type ) to switch to TUI mode, which splits your terminal to show your live source code alongside the command line. [5]  
3. Essential GDB Commands 
Once the GDB prompt () appears, use these punchy short-key commands to control and inspect your program: [2, 6]  
🚀 Execution •  (or ): Starts execution from the beginning. You can append arguments here if your program requires them (e.g., ). 
•  (or ): Resumes execution until the next breakpoint or a crash occurs. 
•  (or ): Exits GDB. [1, 3, 5, 7, 8]  

🛑 Breakpoints •  (or ): Sets a breakpoint to pause execution at a specific line (e.g., ). 
• : Pauses right as a specific function begins (e.g., ). 
• : Lists all currently set breakpoints. 
• : Removes a breakpoint by its ID number. [1, 5, 6, 7, 8]  

🧭 Navigation (Stepping) •  (or ): Executes the next line of code but steps over functions without entering them. 
•  (or ): Executes the next line of code, stepping into a function if one is called. 
• : Steps out of the current function, executing the rest of it and stopping right after it returns. [2, 6, 7]  

🔍 Inspection •  (or ): Displays the current value of a variable (e.g., ). 
•  (or ): Shows the lines of source code surrounding your current position. 
•  (or ): Prints the call stack trace. This is incredibly useful if your program crashes (like a Segmentation Fault) because it reveals exactly which nested function calls led to the crash. 
• : Lists all local variables and their values in the current frame. [1, 2, 3, 5, 6, 9]  

Quick Example Workflow 
If you want to catch a bug in a loop at line 20: 

1. Start GDB:  
2. Set a pause point:  
3. Run the program:  
4. When it stops at line 20, check your data:  
5. Move forward one line:  
6. Repeat step 4 to see if the variable changed correctly. [2, 3, 10]  

[1] https://www.youtube.com/watch?v=u6iXfpBDU3w
[2] https://www.cs.toronto.edu/~krueger/csc209h/tut/gdb_tutorial.html
[3] https://www.youtube.com/watch?v=ny6y0pPO--4
[4] https://www.youtube.com/watch?v=Dq8l1_-QgAc
[5] https://www.youtube.com/watch?v=tYdr01P5tBQ
[6] https://medium.com/havingfun/debugging-c-code-with-gdb-90adb2f3da96
[7] https://betterexplained.com/articles/debugging-with-gdb/
[8] https://web.eecs.umich.edu/~sugih/pointers/summary.html
[9] https://courses.cms.caltech.edu/cs11/material/cpp/mike/misc/gdb.html
[10] https://www.youtube.com/watch?v=MTkDTjdDP3c

You can absolutely ditch the 80's man pages. For a clean, modern interface, you can read the official [GNU GDB Online Documentation](https://sourceware.org/gdb/current/onlinedocs/gdb) directly in your browser. [1] 
To streamline your current project and cleanly manage variable tracking without drowning in out-of-scope errors, use the following configuration and automation tricks:
## 1. Let GDB Handle Scope Filtering Automatically
If you tell GDB to track a variable, it is actually smart enough to handle scopes on its own. [2] 
Instead of manually typing print x at every step, use the display command: [1, 2] 

(gdb) display my_variable


* 
* How it helps you: Every single time your code pauses (via next, step, or a breakpoint), GDB will automatically print my_variable.
* The Scope Filter Feature: If execution jumps into a different function or block where my_variable does not exist, GDB automatically suppresses it and temporarily hides it. It won't throw annoying errors. The absolute second execution returns to a block where the variable is accessible, it instantly pops back onto your screen.
* If you want to stop tracking it altogether, just use undisplay [id_number]. [1, 2, 3] 
* 

## 2. Automate Local Variable Dumps on Breakpoints
If you want to completely skip typing variable names and just see what is relevant right now, you can bind a macro to your breakpoints. [4, 5] 
When you set a breakpoint, tell GDB to automatically execute info locals (which lists every accessible variable in your current frame) and then keep waiting for you: [4, 6] 

(gdb) break main.c:25
(gdb) commands
 > silent
 > info locals
 > end

Now, every time you hit that breakpoint, GDB will silently wipe away the usual breakpoint noise, spit out only the active, accessible variables, and wait for your next command. [5] 
## 3. Create a Project-Specific .gdbinit File
To avoid configuring this every time you launch the debugger, you can automate your entire setup for this specific project. Create a hidden text file named .gdbinit in your project's root folder. [4] 
Populate it with configuration tweaks like these to make the data much easier to read: [4, 7] 

# ~/.gdbinit or /your/project/.gdbinit

# 1. Clean up the variable layouts (expand nested structs nicely)
set print pretty on
set print array on

# 2. Automatically save your command history between sessions
set history save on
set history size 10000

# 3. Automatically launch into the split-screen source code layout (TUI)
layout src

(Note: For security reasons, modern GDB might require you to explicitly allow local files. If it complains when launching, add set auto-load safe-path /path/to/your/project to your global ~/.gdbinit file).
Would you like help writing a customized .gdbinit script tailored specifically to how your project builds or runs?

[1] [https://sourceware.org](https://sourceware.org/gdb/current/onlinedocs/gdb)
[2] [https://www.zeuthen.desy.de](https://www.zeuthen.desy.de/unix/unixguide/infohtml/gdb/Auto-Display.html)
[3] [https://visualgdb.com](https://visualgdb.com/gdbreference/commands/display)
[4] [https://interrupt.memfault.com](https://interrupt.memfault.com/blog/advanced-gdb)
[5] [https://blogs.oracle.com](https://blogs.oracle.com/linux/8-gdb-tricks-you-should-know)
[6] [https://cgi.cse.unsw.edu.au](https://cgi.cse.unsw.edu.au/~learn/debugging/modules/gdb_viewing_data/)
[7] [https://www.math.utah.edu](https://www.math.utah.edu/docs/info/gdb_9.html)
