
# Matrix Multiplication Compiler (Custom ISA)

## Overview

This project implements a simplified compiler designed to translate the task of multiplying two square matrices (C = A * B) of a user-specified dimension `n` into a sequence of instructions for a custom Instruction Set Architecture (ISA).

It simulates several stages of a typical compiler pipeline:
1.  **Parsing:** (Simplified) Extracts the matrix dimension `n`.
2.  **Semantic Analysis:** (Simplified) Sets up the matrix dimensions for code generation.
3.  **Optimization:** (Placeholder) Currently returns fixed values, not performing real optimization.
4.  **Code Generation:** Translates the matrix multiplication logic into the custom ISA instructions.

The primary output is a text file (`output.isa`) containing the generated instruction sequence. The project also includes a utility to print internal lookup tables used during compilation.

## Features

*   Compiles matrix multiplication for user-defined size `n`.
*   Generates output in a **custom 24-bit Instruction Set Architecture (ISA)** format.
*   Uses OpenMP to potentially parallelize parts of the code generation process.
*   Includes simplified placeholders for Parsing, Semantic Analysis, and Optimization stages.
*   Provides a separate utility (`print_lookup_tables`) to display internal instruction opcode and matrix base address mappings.

## Directory Structure (Initial)

This is the structure of the source code repository *before* compilation or execution.

```bash
└── MatCompiler/
    ├── Makefile                 # Build script
    │
    ├── include/                 # Header files (.h) - Interfaces & Definitions
    │   ├── isa_generator.h
    │   ├── isa_encoding.h
    │   ├── target_memory.h
    │   ├── ir_optimizer.h
    │   ├── syntax_parser.h
    │   └── semantic_analyzer.h
    │
    └── src/                     
        ├── compiler_main.c     
        ├── isa_generator.c      
        ├── isa_encoding.c       
        ├── target_memory.c      
        ├── ir_optimizer.c      
        ├── syntax_parser.c     
        ├── semantic_analyzer.c  
        └── print_tables.c       
```

## Prerequisites

*   **GCC Compiler:** With C99 standard support.
*   **Make:** The build automation tool.
*   **OpenMP Library:** Required for parallel code generation (usually included with modern GCC).

On Debian/Ubuntu-based systems, you can install the necessary tools using:
```bash
sudo apt update
sudo apt install build-essential
```

## Building the Project

Navigate to the `MatCompiler` directory in your terminal.

1.  **(Optional) Clean previous builds:**
    ```bash
    make clean
    ```
    This removes any previously generated executables, object files, and `output.isa`.

2.  **Build the main compiler:**
    ```bash
    make
    ```
    This compiles all necessary source files and creates the `matrix_compiler` executable in the current directory (`MatCompiler/`).

3.  **Build the lookup table printer utility:**
    ```bash
    make print_tables
    ```
    This compiles and links the necessary files to create the `print_lookup_tables` executable.

## Running the Programs

1.  **Run the main compiler:**
    ```bash
    ./matrix_compiler
    ```
    The program will prompt you to:
    ```
    Enter matrix dimension n:
    ```
    Enter a positive integer (e.g., `2`) and press Enter. The compiler will simulate the stages and generate the `output.isa` file in the `MatCompiler` directory.

2.  **Run the lookup table printer:**
    ```bash
    ./print_lookup_tables
    ```
    This will print the contents of the internal Instruction Opcode Table and Matrix Base Address Table to your console.

## Directory Structure (After Building and Running)

After running `make`, `make print_tables`, and `./matrix_compiler` (e.g., with n=2), the directory structure will look like this (new/changed items marked):

```bash
└── MatCompiler/
    ├── Makefile                 # Build script
    ├── matrix_compiler          # <-- NEW: Main executable
    ├── print_lookup_tables      # <-- NEW: Utility executable
    ├── output.isa               # <-- NEW: Generated instruction sequence file
    │
    ├── include/                 # Header files (.h)
    │   ├── isa_generator.h
    │   ├── isa_encoding.h
    │   ├── target_memory.h
    │   ├── ir_optimizer.h
    │   ├── syntax_parser.h
    │   └── semantic_analyzer.h
    │
    └── src/                     # Source files (.c)
        ├── compiler_main.c
        ├── compiler_main.o      # <-- NEW: Object file
        ├── isa_generator.c
        ├── isa_generator.o      # <-- NEW: Object file
        ├── isa_encoding.c
        ├── isa_encoding.o       # <-- NEW: Object file
        ├── target_memory.c
        ├── target_memory.o      # <-- NEW: Object file
        ├── ir_optimizer.c
        ├── ir_optimizer.o       # <-- NEW: Object file
        ├── syntax_parser.c
        ├── syntax_parser.o      # <-- NEW: Object file
        ├── semantic_analyzer.c
        ├── semantic_analyzer.o  # <-- NEW: Object file
        ├── print_tables.c
        └── print_tables.o       # <-- NEW: Object file
```
*(Note: Object files (`*.o`) are intermediate compilation files and are typically removed by `make clean`)*

## Output File (`output.isa`) Explanation

The `output.isa` file contains the sequence of custom instructions generated by the compiler. It is structured as follows:

*   **Processing Blocks:** The file is divided into blocks, each starting with `Processing C[i][j]`, indicating the target element of the result matrix C.
    *   **Ordering:** **Important:** Due to the use of OpenMP (`#pragma omp parallel for collapse(2) nowait`) in `isa_generator.c`, the *order* in which these `Processing C[i][j]` blocks appear in the file is **not guaranteed** and may vary between runs.
*   **Read Instructions:** Within each block, lines like `READ A[i][k]: 0xHHHHHH` and `READ B[k][j]: 0xHHHHHH` specify the memory reads required. The `0xHHHHHH` is the encoded 24-bit instruction.
*   **Control Instructions:** After the reads for a specific `C[i][j]`, lines like `PROG: 0xHHHHHH`, `EXE: 0xHHHHHH`, and `END: 0xHHHHHH` are printed. These likely signal the start, execution, and end of the computation for that element on the target hardware.

## Custom ISA Format (24-bit)

**Highlight:** Each instruction generated in `output.isa` follows a specific 24-bit format, encoded as a 6-digit hexadecimal number (0xHHHHHH).

The 24 bits are allocated as follows:

| Bits    | Size  | Field Name    | Description                                     |
| :------ | :---- | :------------ | :---------------------------------------------- |
| `23-22` | 2 bits | Opcode Type   | Instruction type (0=NOP, 1=PROG, 2=EXE, 3=END) |
| `21-16` | 6 bits | Pointer       | Core address or microcode control value         |
| `15`    | 1 bit  | Read Flag     | 1 if the instruction involves a memory read     |
| `14`    | 1 bit  | Write Flag    | 1 if the instruction involves a memory write    |
| `13-0`  | 14 bits| Address       | Memory address component (lower 14 bits)        |

The `isa_encoding.c` module handles the packing of these fields into the final 24-bit instruction word.


## Future Work Ideas

*   Implement a simulator for the custom ISA.
*   Develop actual parsing (e.g., using Flex/Bison) for a simple input language.
*   Implement real optimization techniques.
*   Add robust unit and integration testing frameworks (e.g., Check, CUnit).
*   Improve error handling and reporting.
*   Enhance the memory model.

