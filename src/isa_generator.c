#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "isa_generator.h"
#include "target_memory.h"
#include "isa_encoding.h"

void generate_instruction_sequence(const MatrixIR *ir, const OptimizedInfo *opt) {
    (void)opt;

    printf("Generating instruction sequence...\n");

    FILE *file = fopen("output.isa", "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open output.isa for writing.\n");
        return;
    }

    #pragma omp parallel
    {
        #pragma omp for collapse(2) nowait
        for (int i = 0; i < ir->rows_A; i++) {
            for (int j = 0; j < ir->cols_B; j++) {
                #pragma omp critical
                {
                    fprintf(file, "Processing C[%d][%d]\n", i, j);
                }

                for (int k = 0; k < ir->cols_A; k++) {
                    Instruction inst_read_A = assemble_instruction(INST_NOP, 0, 1, 0, compute_memory_address("A", i, k));
                    Instruction inst_read_B = assemble_instruction(INST_NOP, 0, 1, 0, compute_memory_address("B", k, j));

                    #pragma omp critical
                    {
                        fprintf(file, "READ A[%d][%d]: 0x%06X\n", i, k, inst_read_A);
                        fprintf(file, "READ B[%d][%d]: 0x%06X\n", k, j, inst_read_B);
                    }
                }

                #pragma omp critical
                {
                    Instruction inst_prog = assemble_instruction(INST_PROG, 0x0A, 0, 0, 0);
                    Instruction inst_exe = assemble_instruction(INST_EXE, 0x14, 0, 0, 0);
                    Instruction inst_end = assemble_instruction(INST_END, 0, 0, 0, 0);

                    fprintf(file, "PROG: 0x%06X\n", inst_prog);
                    fprintf(file, "EXE: 0x%06X\n", inst_exe);
                    fprintf(file, "END: 0x%06X\n", inst_end);
                }
            }
        }
    }

    fclose(file);
    printf("Instruction sequence generated and saved to output.isa\n");
}
