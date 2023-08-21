# Assembler-OpenU
This two pass assembler was written for an imaginary computer as a final project of the course 20465 - Systems Programming in C

## About

The final assignment of the C course (20465) at The Open University.

Semester 2021 B

Done by Daniel Popov and Maor Maayan 

The Project was graded 93

## Usage

1. Run `make` to compile the assembler.
2. The assembler will generate output files with the same filenames and the following extensions:
- `.ent` - Entries file
- `.ext` - Externals file
- `.ob` - Object file              
3. Execute the assembler using the following command:
Run `./assembler yourFileName.as`
  
## Files Structure
- `assembler.c` - Main program.
- `code_img.c` - Linked list implementation used to represent Image Code funtions.
- `data_img.c` - Encode and print the Image Data of the assembler.
- `extra_structure.c` - Stores and prints the entries and externals varible usage into .ext .ent files.
- `first_pass.c` - Implementation of the first pass algorithm.
- `globals.c` - Defines the lookup table and functions getting data from it.
- 
- `parser.c` - Parses each line from the input `.as` file as part of `first_pass.c`.
- `first_analyze.c` - Analyzes the line after it has been parsed by `parser.c`. This is the execution of `first_pass.c`.
- `second_pass.c` - Implementation of the second pass algorithm.
- `errors.c` - Thorough error checking during the first and second pass.
- `output.c` - Creates `.ext`, `.ent`, and `.ob` output files.


