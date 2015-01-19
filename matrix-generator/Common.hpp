#ifndef COMMON_HPP
#define COMMON_HPP

namespace Parameters
{
    enum cmd_line_params {
        NONE,
        FILL_RANDOM = 1,
        MATRIX_ROWS = 2,
        MATRIX_COLUMNS = 4,
        MATRIX_TRANSPOSE = 8,
        INPUT_FILE = 16,
        OUTPUT_FILE = 32,
        IS_CSV_OUTPUT = 64,
        IS_BINARY_INPUT = 128
    };
}

bool testFlag(int mask, int flag);

#endif // COMMON_HPP
