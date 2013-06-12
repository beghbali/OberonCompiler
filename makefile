PROGRAM    = oberon
DPROGRAM   = oberon_debug    
LEXER      = oberon_lexer
OBJECTS   = y.tab.o oberon.o lexer.o errorhandler.o parserError.o \
	    lexerlib.o parserlib.o buffer.o parser.o lib.o symboltable.o \
	    stack.o ASTnode.o semchecker.o binaryexpr.o global.o value.o \
	    type.o codegen.o machine.o
DOBJECTS   = y.tab.o oberon.o lexer.o errorhandler.o parserError.o \
	     lexerlib.o parserlib.o buffer.o parser.o lib.o symboltable.o \
	     stack.o ASTnode.o semchecker.o binaryexpr.o debug.o global.o \
	     value.o type.o codegen.o machine.o
LEXER_OBJECTS = oberon_lexer_main.o lexer.o errorhandler.o LexerTester.o \
	     lexerlib.o buffer.o 
PURIFY     = purify
COMPILER   = g++
DEBUGFLAGS = -g
CFLAGS     = -c -O
OTHER_CFLAGS = -fno-default-inline -fnonnull-objects 
DATE       = `date "+%m.%d.20%y_%H:%M"`
OBERON_MIMICK_COMPILER = gcc
OBERON_ASSEMBLY_TARGET = oberon.s

$(PROGRAM): $(OBJECTS)
	-@echo "linking into oberon..."
	$(COMPILER) -o $@ $(OBJECTS)

$(DPROGRAM): $(DOBJECTS)
	$(COMPILER) -o $@ $(DEBUGFLAGS) $(DOBJECTS)

$(LEXER): y.tab.h $(LEXER_OBJECTS)
	$(COMPILER) -o $@ $(LEXER_OBJECTS)

$(PURIFY): $(OBJECTS)
	-@echo "linking into oberon..."
	$(PURIFY) $(COMPILER) -o $(PROGRAM) $(OBJECTS)

y.tab.h: 
	-@echo "building Lexer(oberon lexer only)..."
	yacc -d oberon.y
	-@rm y.tab.c

y.tab.c: oberon.y
	-@echo "generating y.tab.c && y.tab.h ..."
	yacc -d oberon.y

y.tab.o: y.tab.c
	-@echo "compiling..."
	$(COMPILER) $(DEBUGFLAGS) $(CFLAGS) $(OTHER_CFLAGS) y.tab.c 

%.o:%.cpp
	$(COMPILER) $(DEBUGFLAGS) $(CFLAGS) $(OTHER_CFLAGS) $<

clean:
	-@\rm -rf $(PROGRAM) $(OBJECTS) core y.tab.h y.tab.c *.o *.obe *~ *#   

new:
	-@make clean
	-@make $(PROGRAM)

newd:   touch oberon.cpp
	-@make $(DPROGRAM)

backup:
	tar cvf - *.cpp *.h *.y makefile  | gzip > backups/semchecker.$(DATE).tar.Z

compile:
	$(OBERON_MIMICK_COMPILER) $(OBERON_ASSEMBLY_TARGET)
