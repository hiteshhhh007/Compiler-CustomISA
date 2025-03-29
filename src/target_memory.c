#include <stddef.h>
#include "target_memory.h"

static const MatrixMemoryInfo matrix_memory_table[] = {
    {'A', 0x10},
    {'B', 0x80}
};
static const int matrix_memory_table_size = sizeof(matrix_memory_table) / sizeof(matrix_memory_table[0]);


unsigned int get_matrix_base_address(const char matrix_identifier) {
    for (int i = 0; i < matrix_memory_table_size; ++i) {
        if (matrix_identifier == matrix_memory_table[i].identifier) {
            return matrix_memory_table[i].base_address;
        }
    }
    return INVALID_MATRIX_BASE;
}


unsigned int compute_memory_address(const char *matrix, int row, int col) {
    if (matrix == NULL || matrix[0] == '\0') {
        return INVALID_MATRIX_BASE;
    }

    unsigned int base = get_matrix_base_address(matrix[0]);
    if (base == INVALID_MATRIX_BASE) {
        return 0; // Or perhaps INVALID_MATRIX_BASE
    }

    int stride = 10;
    return base + row * stride + col;
}

// +++ NEW Accessor Function Definitions +++
int get_matrix_memory_table_size(void) {
    return matrix_memory_table_size;
}

const MatrixMemoryInfo* get_matrix_memory_info_by_index(int index) {
    if (index >= 0 && index < matrix_memory_table_size) {
        return &matrix_memory_table[index];
    }
    return NULL; // Index out of bounds
}
// +++ END NEW +++
