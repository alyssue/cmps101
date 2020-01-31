#-----------------------------------------------------------------------------
# Alyssa Melton 
# amelton@ucsc.edu
# CS101
# 5/15/18
# Makefile
#-----------------------------------------------------------------------------

MAINCLASS  = Sparse
JAVAC      = javac 
JAVASRC    = Sparse.java List.java Matrix.java
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

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