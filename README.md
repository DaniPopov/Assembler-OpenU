# Assembler-OpenU
This two pass assembler was written for an imaginary computer as a final project of the course 20465 - Systems Programming in C

## About

The final assignment of the C course (20465) at The Open University.

Semester 2021 B

Done by Daniel Popov and Maor Maayan 

The Project was graded 93

University explicit specification for the project:


## Usage

1. Run `make` to compile the assembler.
2. The assembler will generate output files with the same filenames and the following extensions:
- `.ent` - Entries file
- `.ext` - Externals file
- `.ob` - Object file              
3. Execute the assembler using the following command:
Run `./assembler yourFileName.as`
  
## Implementation Overview in Brief:

# 1.Macros Stage:
- The assembler processes the source (.as) file.
- It replaces macros with their content using a hash table.
- If it finds syntax errors, it reports them and moves to the next stage.
- Otherwise, it proceeds to the First Run stage.

# 2.First Pass:
- The assembler calculates the size of data and instruction sections.
- It adds symbols to the symbol table.
- Checks for code errors and logs them.
- If errors occur, it skips stage 3.

# 3.Between First and Second Pass:
- If the first run succeeds, the assembler updates data symbol addresses.
- Allocates memory for the target binary.
- Resets counters and proceeds to the second run.

# 4.Second Pass:
- The assembler converts code lines into binary.
- Inserts binary words into memory.
- Adds external operands to a table.
- Reports errors if label operands are missing in the symbol table.
- Completes the second run without exporting files if errors are found.

# 5.Output Generation:
- If the second run is error-free, it generates required output files (.ob, .ext, .ent).

The assembler repeats these 5 steps for each source file.
It ends the program after processing all source files.









