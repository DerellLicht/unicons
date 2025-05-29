//**********************************************************************************
//  Copyright (c) 2025 Derell Licht
//  unicons.cpp - demo program for various Unicode-handling operations
//**********************************************************************************

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "conio_min.h"

#define  VER_NUMBER "1.00"

//lint -esym(843, Version, ShortVersion) could be declared as const
TCHAR *Version = _T("UniCons, Version " VER_NUMBER " ") ;   //lint !e707
TCHAR *ShortVersion = _T(" UniCons " VER_NUMBER " ") ;       //lint !e707

//  per Jason Hood, this turns off MinGW's command-line expansion, 
//  so we can handle wildcards like we want to.                    
//lint -e765  external '_CRT_glob' could be made static
//lint -e714  Symbol '_CRT_glob' not referenced
int _CRT_glob = 0 ;

#define  MAX_FILE_LEN   1024

//********************************************************************************
// #define  USE_SO_METHOD
#undef  USE_SO_METHOD

#ifndef  USE_SO_METHOD

//********************************************************************************
//  this solution is from:
//  https://github.com/coderforlife/mingw-unicode-main/
//********************************************************************************
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
static TCHAR file_spec[MAX_FILE_LEN+1] = _T("") ;

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
    LPWSTR *szArglist;
    int nArgs;

    // Get the command line string
    LPWSTR commandLine = GetCommandLineW();

    // Convert the command line string to an array of arguments
    szArglist = CommandLineToArgvW(commandLine, &nArgs);

    if (szArglist == NULL) {
        wprintf(L"CommandLineToArgvW failed\n");
        return 1;
    } 
    else {
        for (idx = 0; idx < nArgs; idx++) {
            // wprintf(L"%d: %s\n", i, szArglist[i]);
            TCHAR *p = szArglist[idx] ;
            _tcsncpy(file_spec, p, MAX_FILE_LEN);
            file_spec[MAX_FILE_LEN] = 0 ;
        }
    }

    // Free the memory allocated by CommandLineToArgvW
    LocalFree(szArglist);
#else
   //  okay, cause of this, is that apparently I have to use double-backslash
   //  to put a quote after a backslash...
   //  But forward slash works fine...
   // > medialist glock17\"?????????? ?????????"
   // arg 1: [glock17"??????????]
   // arg 2: [?????????]

   // > medialist glock17\\"?????????? ?????????"
   // filespec: D:\SourceCode\Git\media_list\glock17\?????????? ?????????\*, fcount: 3
   
   for (idx=1; idx<argc; idx++) {
      TCHAR *p = argv[idx] ;
      _tcsncpy(file_spec, p, MAX_FILE_LEN);
      file_spec[MAX_FILE_LEN] = 0 ;
   }
#endif   

   if (file_spec[0] == 0) {
      _tcscpy(file_spec, _T("."));
   }
   
   dputsf(L"input file: %s\n", file_spec);

   restore_console_attribs();
   return 0;
}

