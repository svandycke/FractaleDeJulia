#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 03/02/2014

SHELL = /bin/sh
# définition des commandes utilisées
CPP = g++
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
PG_FLAGS =
WITH_THREAD = -DWITH_THREAD

CPPFLAGS = -Wall -O3 
CFLAGS = 
LDFLAGS = -lopencv_highgui -lopencv_imgproc -lopencv_core -std=c++11

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
        CFLAGS += 
        LDFLAGS +=   
endif

#définition des fichiers et dossiers
PROGNAME = Fractal_de_julia
PACKAGE=$(PROGNAME)
VERSION = 1.0
distdir = $(PACKAGE)-$(VERSION)
HEADERS = 
SOURCES = window.cpp
OBJ = $(SOURCES:.cpp=.o)
DOXYFILE = documentation/Doxyfile
EXTRAFILES =
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(DOXYFILE) $(EXTRAFILES)

all:
	$(CPP) $(SOURCES) -o $(PROGNAME) $(LDFLAGS)

thread:
	$(CPP) $(SOURCES) -o $(PROGNAME) $(LDFLAGS) $(WITH_THREAD)


#%.o: %.cpp
#	$(CPPC) $(CPPFLAGS) $(CFLAGS) -c $<  -o $@

dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)

distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)

doc: $(DOXYFILE)
	cat $< | sed -e "s/PROJECT_NAME *=.*/PROJECT_NAME = $(PROGNAME)/" | sed -e "s/PROJECT_NUMBER *=.*/PROJECT_NUMBER = $(VERSION)/" >> $<.new
	mv -f $<.new $<
	cd documentation && doxygen && cd ..

clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz gmon.out core.* documentation/*~ shaders/*~ documentation/html
