CC          = gcc 
CFLAGS      = -ansi -Wall -pedantic 
GLOBAL_DEPS = globals.h 
EXE_DEPS    = parse.o operands.o line_structure.o label_structure.o code_img.o globals.o data_img.o extra_structure.o second_pass.o first_pass.o assembler.o

assembler        : $(EXE_DEPS) $(GLOBAL_DEPS) 
	$(CC) -g $(EXE_DEPS) $(CFLAGS)  -o $@

assembler.o      : assembler.c assembler.h $(GLOBAL_DEPS)
	$(CC) -c assembler.c $(CFLAGS) -o $@

parse.o	         : parse.c parse.h $(GLOBAL_DEPS)
	$(CC) -c parse.c $(CFLAGS) -o $@

operands.o       : operands.c operands.h $(GLOBAL_DEPS)
	$(CC) -c operands.c $(CFLAGS) -o $@

line_structure.o : line_structure.c line_structure.h $(GLOBAL_DEPS)
	$(CC) -c line_structure.c $(CFLAGS) -o $@

label_structure.o: label_structure.c label_structure.h $(GLOBAL_DEPS)
	$(CC) -c label_structure.c $(CFLAGS) -o $@

extra_structure.o: extra_structure.c extra_structure.h $(GLOBAL_DEPS)
	$(CC) -c extra_structure.c $(CFLAGS) -o $@

code_img.o       : code_img.c  code_img.h $(GLOBAL_DEPS)
	$(CC) -c code_img.c $(CFLAGS) -o $@
    
data_img.o       : data_img.c  data_img.h $(GLOBAL_DEPS)
	$(CC) -c data_img.c $(CFLAGS) -o $@
    
first_pass.o     : first_pass.c  first_pass.h $(GLOBAL_DEPS)
	$(CC) -c first_pass.c $(CFLAGS) -o $@
    
second_pass.o    : second_pass.c  second_pass.h $(GLOBAL_DEPS)
	$(CC) -c second_pass.c $(CFLAGS) -o $@
    
globals.o        : globals.c globals.h
	$(CC) -c globals.c $(CFLAGS) -o $@


clean:
	rm -rf *.o