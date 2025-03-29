#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "syntax_parser.h"

typedef struct {
    int rows_A;
    int cols_A;
    int cols_B;
} MatrixIR;

MatrixIR perform_semantic_analysis(ParsedInfo pinfo);

#endif
