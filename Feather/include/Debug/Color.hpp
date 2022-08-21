#pragma once


#include <ostream>

namespace Feather::Debug {
    // RAII to apply ANSI colors to an ostream
    class Color {
    public:
        enum class Code { RED = 9, GREEN = 10, YELLOW = 11, BLUE = 12, MAGENTA = 13, CYAN = 14, WHITE = 15};

        Color(std::ostream& output, Code code = Code::WHITE): output(output) {
            output << "\033[38;5;" << static_cast<std::underlying_type<Code>::type>(code) << 'm';
        }

        ~Color() {
            output << "\033[0m";
        }

    private:
        std::ostream& output;
    };
}
