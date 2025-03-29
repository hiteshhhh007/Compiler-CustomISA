#ifndef SYNTAX_PARSER_H
#define SYNTAX_PARSER_H

typedef struct {
    int rows;
    int cols;
} ParsedInfo;

ParsedInfo parse_source(const char *source_code, int n);

#endif
