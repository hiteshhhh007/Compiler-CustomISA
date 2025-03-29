#ifndef ISA_GENERATOR_H
#define ISA_GENERATOR_H

#include "semantic_analyzer.h"
#include "ir_optimizer.h"
#include "isa_encoding.h"

void generate_instruction_sequence(const MatrixIR *ir, const OptimizedInfo *opt);

#endif
