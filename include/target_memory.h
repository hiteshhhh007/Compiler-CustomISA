#ifndef TARGET_MEMORY_H
#define TARGET_MEMORY_H

#define INVALID_MATRIX_BASE (unsigned int)-1

typedef struct {
    const char identifier;
    unsigned int base_address;
} MatrixMemoryInfo;

unsigned int get_matrix_base_address(const char matrix_identifier);

unsigned int compute_memory_address(const char *matrix, int row, int col);

// +++ NEW Accessor Function Declarations +++
int get_matrix_memory_table_size(void);
const MatrixMemoryInfo* get_matrix_memory_info_by_index(int index);
// +++ END NEW +++

#endif
