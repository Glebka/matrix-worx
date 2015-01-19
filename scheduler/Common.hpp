#ifndef COMMON_HPP
#define COMMON_HPP

namespace Parameters
{
    enum cmd_line_params {
        NONE,
        MATRIX_A = 1,
        MATRIX_B = 2,
        HOSTS = 4,
        OUTPUT_FILE = 8,
        IS_CSV_OUTPUT= 16,
    };
}

bool testFlag(int mask, int flag);

#endif // COMMON_HPP
