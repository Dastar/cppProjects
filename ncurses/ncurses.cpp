#include <cctype>    // std::isprint

#include "ncurses.hpp"

namespace ilrd {

NCurses::NCurses(bool disable_signals)
{
    if (nullptr == initscr()) {
        throw std::bad_alloc();
    }

    if (disable_signals && ERR == raw()) {
        throw std::runtime_error("failed to disable signals");
    }

    getmaxyx(stdscr, m_max_rows, m_max_cols);
}

NCurses::~NCurses()
{
    endwin();
}

int NCurses::get_rows() const
{
    return m_max_rows;
}

int NCurses::get_cols() const
{
    return m_max_cols;
}

void NCurses::println(const std::string& str, int row, int col)
{
    std::lock_guard<std::mutex> lock(m_lock);
    move(row, col);
    clrtoeol();
    printw(str.c_str());
    refresh();
}

std::string NCurses::get_line(const std::string& msg, int row, int col)
{
    int c(0);
    std::string str("");
    noecho();
    keypad(stdscr, TRUE);

    while (c != '\n') {
        println(msg + str, row, col);

        c = getch();
        if (std::isprint(c)) {
            str += c;
        } else if (c == KEY_BACKSPACE && str.size()) {
            str.pop_back();
        }
    }

    println("", row, col);
    return str;
}

std::string NCurses::get_line(int row, int col)
{
    return get_line("", row, col);
}

void NCurses::move(int row, int col)
{
    ::move(row, col);
}

} // namespace ilrd
