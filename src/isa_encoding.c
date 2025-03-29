#include <string.h>
#include <stddef.h> // For NULL check in accessor
#include "isa_encoding.h"

static const InstructionInfo instruction_table[] = {
    {"NOP",  INST_NOP},
    {"PROG", INST_PROG},
    {"EXE",  INST_EXE},
    {"END",  INST_END}
};
static const int instruction_table_size = sizeof(instruction_table) / sizeof(instruction_table[0]);

unsigned int get_instruction_opcode(const char *name) {
    for (int i = 0; i < instruction_table_size; ++i) {
        if (strcmp(name, instruction_table[i].name) == 0) {
            return instruction_table[i].opcode;
        }
    }
    return INST_INVALID;
}


Instruction assemble_instruction(unsigned int instr_type, unsigned int pointer_value, int read_flag, int write_flag, unsigned int row_addr) {
    unsigned int exec_bits = (instr_type << 6) | (pointer_value & POINTER_MASK);
    unsigned int mem_bits = ((read_flag & 0x1) << 9) | ((write_flag & 0x1) << 8) | (row_addr & ROWADDR_MASK);
    Instruction instr = (exec_bits << EXEC_SHIFT) | (mem_bits << MEM_SHIFT);
    return instr;
}

// +++ NEW Accessor Function Definitions +++
int get_instruction_table_size(void) {
    return instruction_table_size;
}

const InstructionInfo* get_instruction_info_by_index(int index) {
    if (index >= 0 && index < instruction_table_size) {
        return &instruction_table[index];
    }
    return NULL; // Index out of bounds
}
// +++ END NEW +++
