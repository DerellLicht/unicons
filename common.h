//**********************************************************************************
//  Copyright (c) 1998-2025 Derell Licht                       
//  common.cpp - common library functions
//**********************************************************************************

//lint -esym(756, u64, uchar)  global typedef not referenced
//lint -esym(755, FILE_ATTRIBUTE_VOLID) global macro not referenced

typedef  unsigned long long   u64 ;
typedef  unsigned char        uchar ;
typedef  unsigned long        ulong ;
typedef  unsigned int         uint ;
typedef  unsigned char        u8  ;
typedef  unsigned short       u16 ;
typedef  unsigned int         u32 ;

//lint -esym(755, ZERO, ETX, LF, BSP, CR, CtrlC, SPC, STX)

#define  STX      2
#define  ETX      3
#define  CtrlC    3
#define  BSP      8
#define  HTAB     9
#define  CR       13
#define  LF       10
#define  SPC      32
#define  ZERO     48

//  this definition was excluded by WINNT.H
#define FILE_ATTRIBUTE_VOLID  0x00000008

#define  MAX_FILE_LEN      1024
#define  MAX_UNICODE_LEN   1024

#define  LOOP_FOREVER   true

#define  MAXLINE        1024

#define  MAX_EXT_SIZE   8

//lint -esym(758, u64toul)  global union referenced
//lint -esym(768, u64toul::i, u64toul::u)

typedef union ul2uc_u {
   unsigned       ul ;
   unsigned short us[2] ;
   unsigned char  uc[4] ;
} ul2uc_t;

union u64toul {
   ULONGLONG i ;
   ulong u[2] ;
};

//lint -esym(552, base_len)   Symbol not accessed
//lint -esym(759, base_len)   header declaration for symbol could be moved from header to module
extern TCHAR base_path[MAX_FILE_LEN+1] ;
extern unsigned base_len ;  //  length of base_path

//  debug functions
int hex_dump(u8 *bfr, int bytes, unsigned addr);
int hex_dump(u8 *bfr, int bytes);

TCHAR *get_system_message(void);
TCHAR *get_system_message(DWORD errcode);
int syslog(const TCHAR *fmt, ...);
WCHAR *ascii2unicode(char const * const AsciiStr);
char *unicode2ascii(WCHAR const * const UnicodeStr);

// ULLONG_MAX = 18,446,744,073,709,551,615
#define  MAX_ULL_COMMA_LEN  26
char *convert_to_commas(ULONGLONG uli, char *outstr);

bool IsCharNum(char inchr);
void strip_newlines(char *rstr);
char *next_field(char *q);

