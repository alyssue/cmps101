#------------------------------------------------------------------------------
# Alyssa Melton
# Alyssa Melton 
# amelton@ucsc.edu
# CS101
# 4/10/18
# Makefile
#------------------------------------------------------------------------------ 

MAINCLASS  = Lex
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 
SUBMIT	   = submit cmps101-pt.s18 pa1 Lex.java List.java Makefile README ListClient.java
CHECK	   = ls /afs/cats.ucsc.edu/class/cmps101-pt.s18/pa1/amelton

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit: 
	$(SUBMIT)

check:
	$(CHECK)
