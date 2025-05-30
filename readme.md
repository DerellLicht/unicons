unicons - a compact utility that demonstrates some solutions to dealing with 
          a Unicode console environment.

github page: https://github.com/DerellLicht/unicons

This simple utility demonstrates solutions to several difficulties related to
building Unicode applications in MinGW.

issues:

1. "@WinMain16 is not defined", when wmain() is in fact present.
   Apparently MinGW simply does not support wmain(), by default, in most toolchain versions.
   
   This application provides two different solutions to this issue; 
   > the solution which is selected with USE_SO_METHOD is a simpler, easier to understand 
     solution, for folks who are familiar with MinGW.
     
   > The solution when USE_SO_METHOD is *not* defined, is a little more subtle,
     but does not require linking to shlwapi.lib (actually, libshlwapi.a in MinGW).
     This method also provides the familiar wmain() interface that C/C++ programmers 
     are familiar with.
     
   Nonetheless, both solutions work very nicely, and will accept Unicode strings
   (including filenames) as input.
   
2. Output Unicode text to console
   This is a notorious problem in Windows consoles; 
   The conio_min module provides a rudimentary solution to this problem...
   
   First, open your application :
   `console_init() ;`
   and exit with:
   `restore_console_attribs();`
   
   Then within your code, use the `dputs()` function to output Unicode text to the console.
   The library also provides the `dputsf()` function which acts like `printf()`, but 
   provides output via `dputs()`...
   
   