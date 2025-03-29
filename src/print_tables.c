#include <stdio.h>
#include "isa_encoding.h"     // Include to get InstructionInfo and accessors
#include "target_memory.h"  // Include to get MatrixMemoryInfo and accessors

int main() {
    printf("--- Instruction Opcode Table ---\n");
    printf("Name\tOpcode\n");
    printf("----\t------\n");

    int instr_count = get_instruction_table_size();
    for (int i = 0; i < instr_count; ++i) {
        const InstructionInfo *info = get_instruction_info_by_index(i);
        if (info != NULL) {
            printf("%s\t0x%X\n", info->name, info->opcode);
        }
    }

    printf("\n--- Matrix Base Address Table ---\n");
    printf("Identifier\tBase Address\n");
    printf("----------\t------------\n");

    int matrix_count = get_matrix_memory_table_size();
    for (int i = 0; i < matrix_count; ++i) {
        const MatrixMemoryInfo *info = get_matrix_memory_info_by_index(i);
        if (info != NULL) {
            printf("%c\t\t0x%X\n", info->identifier, info->base_address);
        }
    }

    printf("\n");
    return 0;
}
