#include "Precompiled.hpp"

#include "Debug/Color.hpp"

using namespace std;
using namespace Feather;


Color::Color(Foreground fore, Background back) {
    cout << "\e[0;" << int(fore);

    if (back != Background::NONE) {
        cout << ';' << int(back);
    }

    cout << 'm';
}

Color::~Color() {
    cout << "\e[K\e[0m";
}
