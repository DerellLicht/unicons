# makefile for unicons app
USE_SO = YES
USE_DEBUG = NO
USE_64BIT = NO
USE_UNICODE = YES

ifeq ($(USE_64BIT),YES)
TOOLS=d:\tdm64\bin
else
TOOLS=c:\tdm32\bin
#TOOLS=c:\mingw32\bin
endif

ifeq ($(USE_DEBUG),YES)
CFLAGS = -Wall -g -c
CxxFLAGS = -Wall -g -c
LFLAGS = -g
else
CFLAGS = -Wall -s -O3 -c -m32
LFLAGS = -s -O3 -m32
endif
CFLAGS += -Weffc++
CFLAGS += -Wno-write-strings
ifeq ($(USE_64BIT),YES)
CFLAGS += -DUSE_64BIT
endif

ifeq ($(USE_UNICODE),YES)
CFLAGS += -DUNICODE -D_UNICODE
LiFLAGS += -dUNICODE -d_UNICODE
LFLAGS += -dUNICODE -d_UNICODE

ifeq ($(USE_SO),YES)
CFLAGS += -DUSE_SO_METHOD
endif

endif

CPPSRC=unicons.cpp common.cpp conio_min.cpp

#  clang-tidy options
CHFLAGS = -header-filter=.*
CHTAIL = -- 
#CHTAIL += -Ider_libs
ifeq ($(USE_64BIT),YES)
CHTAIL += -DUSE_64BIT
endif
ifeq ($(USE_UNICODE),YES)
CHTAIL += -DUNICODE -D_UNICODE
endif

BIN=unicons.exe

#  shlwapi is required for one of the two wmain() solutions
#  Well, only required with *some* versions of MinGW ...
ifeq ($(USE_SO),YES)
LIBS=-lshlwapi
endif

OBJS = $(CPPSRC:.cpp=.o)

#**************************************************************************
%.o: %.cpp
	$(TOOLS)\g++ $(CFLAGS) $<

all: $(BIN)

clean:
	rm -f *.o *.exe *~ *.zip

dist:
	rm -f *.zip
	zip $(BIN).zip $(BIN) Readme.md 

wc:
	wc -l *.cpp

check:
	cmd /C "d:\clang\bin\clang-tidy.exe $(CHFLAGS) $(CPPSRC) $(CHTAIL)"

lint:
	cmd /C "c:\lint9\lint-nt +v -width(160,4) $(LiFLAGS) -ic:\lint9 mingw.lnt -os(_lint.tmp) lintdefs.cpp $(CPPSRC)"

depend: 
	makedepend $(CSRC) $(CPPSRC) $(CXXSRC)

$(BIN): $(OBJS)
	$(TOOLS)\g++ $(OBJS) $(LFLAGS) -o $(BIN) $(LIBS) 

# DO NOT DELETE

unicons.o: conio_min.h
common.o: common.h
conio_min.o: common.h conio_min.h
