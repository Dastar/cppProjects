#include <string>
#include <iostream>
#include <vector>

#include "ncurses.hpp"

using namespace ilrd;

int main()
{
    NCurses tui(true);
    std::string str(tui.get_line("MSG: "));
    tui.println(str, 5, 0);
    tui.get_line();

    return 0;
}
