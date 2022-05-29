#OS-related macros
ifeq ($(OS),Windows_NT)
    DLLEXT := .dll
	EXPORTSOURCE = export.bat
	CLEANCOMMAND = del
else
    DLLEXT := .so
	EXPORTSOURCE = sh exportLD.sh
	CLEANCOMMAND = rm -rf
endif

CXX = gcc
CFLAGS = -Wall -Werror -pedantic -fpic -g
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

#Library-related macros
GAMELIBCORENAME = game
INTERFACELIBCORENAME = interface
GAMELIBTARGET :=lib$(GAMELIBCORENAME)$(DLLEXT)
INTERFACELIBTARGET :=lib$(INTERFACELIBCORENAME)$(DLLEXT)
GAMELIBSOURCE = moves save board interface
INTERFACELIBSOURCE = moves save board interface
GAMELIBSOURCEOFILE = $(GAMELIBSOURCE:=.o)
INTERFACELIBSOURCEOFILE = $(INTERFACELIBSOURCE:=.o)

#Application-related macros
EXESOURCE = main
TARGET = $(EXESOURCE:=.exe)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#Running the program
run: $(TARGET)
	@echo "\n Running the executable" $(TARGET)
	$(EXPORTSOURCE) $(TARGET)

all: $(TARGET) 

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(GAMELIBTARGET) $(INTERFACELIBTARGET)
	@echo "\nGenerating the executable " $@ "from " $<
	$(CXX) $(EXESOURCEOFILE) -l$(GAMELIBCORENAME) -l$(INTERFACELIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm

#Generating the library binary code
$(GAMELIBTARGET): $(GAMELIBSOURCEOFILE)
	@echo "\nGenerating the library binary code (.so or .dll) from object files (.o) " $@
	$(CXX) $(CFLAGS) -shared $(GAMELIBSOURCEOFILE) -o $(GAMELIBTARGET)

$(INTERFACELIBTARGET): $(INTERFACELIBSOURCEOFILE)
	@echo "\nGenerating the library binary code (.so or .dll) from object files (.o) " $@
	$(CXX) $(CFLAGS) -shared $(INTERFACELIBSOURCEOFILE) -o $(INTERFACELIBTARGET)

#Generating an object file from a C file having the same name
.c.o:
	@echo "\nGenerating object file (.o)" $@ " from c source file (.c)" $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

clean:
	@echo "\n Cleaning temporary files"
	$(CLEANCOMMAND) *.o *~ *.so *.dll *.exe *.save *saves.txt