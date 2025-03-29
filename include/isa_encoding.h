#ifndef ISA_ENCODING_H
#define ISA_ENCODING_H

#define INST_NOP   0x0
#define INST_PROG  0x1
#define INST_EXE   0x2
#define INST_END   0x3
#define INST_INVALID (unsigned int)-1

#define EXEC_SHIFT 16
#define MEM_SHIFT  6

#define POINTER_MASK 0x3F
#define ROWADDR_MASK 0xFF
typedef unsigned int Instruction;

typedef struct {
    const char *name;
    unsigned int opcode;
} InstructionInfo;

unsigned int get_instruction_opcode(const char *name);

Instruction assemble_instruction(unsigned int instr_type, unsigned int pointer_value, int read_flag, int write_flag, unsigned int row_addr);

// +++ NEW Accessor Function Declarations +++
int get_instruction_table_size(void);
const InstructionInfo* get_instruction_info_by_index(int index);
// +++ END NEW +++

#endif
