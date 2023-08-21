# Assembler-OpenU
This two pass assembler was written for an imaginary computer as a final project of the course 20465 - Systems Programming in C

## About

The final assignment of the C course (20465) at The Open University.

Semester 2021 B

Done by Daniel Popov

The Project was graded 93

## Usage

1. Run `make` to compile the assembler:
The assembler will generate output files with the same filenames and the following extensions:
- `.ent` - Entries file
- `.ext` - Externals file
- `.ob` - Object file              
2. Execute the assembler using the following command:
Run `./assembler yourFileName.as`
The assembler will output .ent, .ext and .ob files.
  
## Files Structure
- `assembler.c` - Main program.
- `first_pass.c` - Implementation of the first pass algorithm.
- `parser.c` - Parses each line from the input `.as` file as part of `first_pass.c`.
- `first_analyze.c` - Analyzes the line after it has been parsed by `parser.c`. This is the execution of `first_pass.c`.
- `second_pass.c` - Implementation of the second pass algorithm.
- `errors.c` - Thorough error checking during the first and second pass.
- `output.c` - Creates `.ext`, `.ent`, and `.ob` output files.


