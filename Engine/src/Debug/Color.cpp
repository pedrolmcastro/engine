#include "Precompiled.hpp"

#include "Color.hpp"

using namespace std;
using namespace Engine;


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
