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
LIBCORENAME = display
LIBTARGET :=lib$(LIBCORENAME)$(DLLEXT)
LIBSOURCE = $(LIBCORENAME)
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

#Application-related macros
EXESOURCE = main
TARGET = $(EXESOURCE:=.exe)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#Running the program
run: $(TARGET)
	@echo "Running the executable" $(TARGET)
	$(EXPORTSOURCE) $(TARGET)
all: $(TARGET) 

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET)
	@echo "Generating the executable" $@ "from" $<
	$(CXX) $(EXESOURCEOFILE) -L $(LIBCORENAME) $(LIBSDIR) -o $(TARGET) -lm

#Generating the library binary code
$(LIBTARGET): $(LIBSOURCEOFILE)
	@echo "Generating the library binary code .so from object files (.o)" $@
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)
	

#Generating an object file from a C file having the same name
.c.o:
	@echo "Generating object file (.o)" $@ "from c source file (.c)" $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

clean:
	@echo "Cleaning temporary files"
	$(CLEANCOMMAND) *.o *~ *.so *.dll *.exe