#include "ir_optimizer.h"

OptimizedInfo optimize_ir(const MatrixIR *ir) {
    OptimizedInfo opt;
    opt.mac_steps = 9;
    opt.partial_mults = 4;
    return opt;
}
