//**********************************************************************************
//  Copyright (c) 2025 Derell Licht
//  unicons.cpp - demo program for various Unicode-handling operations
//  
//  Good example string: unicons derelict cornucopia "буяновский страйкбол"
//**********************************************************************************

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "conio_min.h"

//lint -esym(818, argv)   Pointer parameter 

//  per Jason Hood, this turns off MinGW's command-line expansion, 
//  so we can handle wildcards like we want to.                    
//lint -e765  external '_CRT_glob' could be made static
//lint -e714  Symbol '_CRT_glob' not referenced
int _CRT_glob = 0 ;

//********************************************************************************
//  This define is moved to Makefile
// #define  USE_SO_METHOD
// #undef  USE_SO_METHOD

//********************************************************************************
//  this solution is from:
//  https://github.com/coderforlife/mingw-unicode-main/
//********************************************************************************
#ifndef  USE_SO_METHOD
#if defined(__GNUC__) && defined(_UNICODE)

#ifndef __MSVCRT__
#error Unicode main function requires linking to MSVCRT
#endif

#include <wchar.h>
#include <stdlib.h>

extern int _CRT_glob;
extern 
#ifdef __cplusplus
"C" 
#endif
void __wgetmainargs(int*,wchar_t***,wchar_t***,int,int*);

#ifdef MAIN_USE_ENVP
int wmain(int argc, wchar_t *argv[], wchar_t *envp[]);
#else
int wmain(int argc, wchar_t *argv[]);
#endif

int main() 
{
   wchar_t **enpv, **argv;
   int argc, si = 0;
   __wgetmainargs(&argc, &argv, &enpv, _CRT_glob, &si); // this also creates the global variable __wargv
#ifdef MAIN_USE_ENVP
   return wmain(argc, argv, enpv);
#else
   return wmain(argc, argv);
#endif
}

#endif //defined(__GNUC__) && defined(_UNICODE)
#endif

//********************************************************************************
#ifdef  USE_SO_METHOD
int main(void) 
#else
int wmain(int argc, wchar_t *argv[])
#endif
{
   int idx ;

   console_init() ;
   
   //********************************************************************************
   //  got this solution from:
   //  https://stackoverflow.com/questions/79642663/mingw-and-wmain-undefined-reference-to-winmain16/79642996#79642996
   //********************************************************************************
#ifdef  USE_SO_METHOD
   LPWSTR *argv;
   int argc;

   // Get the command line string
   LPWSTR commandLine = GetCommandLineW();

   // Convert the command line string to an array of arguments
   argv = CommandLineToArgvW(commandLine, &argc);

   if (argv == NULL) {
       wprintf(L"CommandLineToArgvW failed\n");
       return 1;
   } 
#endif   
    
   //  okay, the cause of this, is that apparently I have to use 
   //  double-backslash to put a quote after a backslash...
   //  But forward slash works fine...
   // > medialist glock17\"буяновский страйкбол"
   // arg 1: [glock17"буяновский]
   // arg 2: [страйкбол]
   
   // > medialist glock17\\"буяновский страйкбол"
   // filespec: D:\SourceCode\Git\media_list\glock17\буяновский страйкбол\*, fcount: 3
   
   //  unicons derelict cornucopia "буяновский страйкбол"
   //  normally, this index would start at 1,
   //  but we want to confirm that the executable filename is being picked up... 
   for (idx=0; idx<argc; idx++) {
      TCHAR *p = argv[idx] ;
      u_int slen = _tcslen(p);
      dputsf(L"arg %u, len %u: [%s]\n", idx, slen, p);
      dnewline();
   }

#ifdef  USE_SO_METHOD
   // Free the memory allocated by CommandLineToArgvW
   LocalFree(argv);
#endif   

   restore_console_attribs();
   return 0;
}

