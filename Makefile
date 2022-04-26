#OS-related macros
ifeq ($(OS),Windows_NT)
	EXPORTSOURCE = export.bat
	CLEANCOMMAND = del
else
	EXPORTSOURCE = sh exportLD.sh
	CLEANCOMMAND = rm -rf
endif

CXX = gcc
CFLAGS = -Wall -Werror -pedantic -g
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

#Library-related macros
LIBSOURCE = board moves display save
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

#Application-related macros
EXESOURCE = main
TARGET = $(EXESOURCE:=.exe)
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#Running the program
run: $(TARGET)
	@echo "\nRunning the executable" $(TARGET)
	$(EXPORTSOURCE) $(TARGET)
all: $(TARGET) 

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBSOURCEOFILE)
	@echo "\nGenerating the executable" $@ "from" $<
	$(CXX) $(EXESOURCEOFILE) -L $(LIBCORENAME) $(LIBSDIR) -o $(TARGET)  $(LIBSOURCEOFILE)


#Generating an object file from a C file having the same name
.c.o:
	@echo "\nGenerating object file (.o)" $@ "from c source file (.c)" $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

clean:
	@echo "Cleaning temporary files"
	$(CLEANCOMMAND) *.o *.so *.dll *.exe