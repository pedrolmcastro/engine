#include "Precompiled.hpp"

#include "Debug/Color.hpp"

using namespace std;
using namespace Feather;


Debug::Color::Color(Foreground fore, Background back) {
    cout << "\e[0;" << int(fore);

    if (back != Background::NONE) {
        cout << ';' << int(back);
    }

    cout << 'm';
}

Debug::Color::~Color() {
    cout << "\e[K\e[0m";
}
