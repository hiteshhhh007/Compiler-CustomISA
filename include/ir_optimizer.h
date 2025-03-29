#ifndef IR_OPTIMIZER_H
#define IR_OPTIMIZER_H

#include "semantic_analyzer.h"

typedef struct {
    int mac_steps;
    int partial_mults;
} OptimizedInfo;

OptimizedInfo optimize_ir(const MatrixIR *ir);

#endif
