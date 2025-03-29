#include "syntax_parser.h"

ParsedInfo parse_source(const char *source_code, int n) {
    (void)source_code;
    ParsedInfo info;
    info.rows = n;
    info.cols = n;
    return info;
}
