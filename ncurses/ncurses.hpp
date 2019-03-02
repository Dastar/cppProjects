// thread safe

#ifndef ILRD_NCURSES_HPP
#define ILRD_NCURSES_HPP

#include <mutex>     // std::mutex
#include <ncurses.h> // tui
#include <string>    // std::string
#include <vector>    // std::vector

namespace ilrd {

class NCurses {
public:
    // throws std::bad_alloc if failed to init screen
    // throws std::runtime_error if failed to block signals
    explicit NCurses(bool disable_signals = false);
    ~NCurses();

    int get_rows() const;
    int get_cols() const;

    void println(const std::string& str, int row = 0, int col = 0);

    std::string get_line(int row = 0, int col = 0);
    std::string get_line(const std::string& msg, int row = 0, int col = 0);

    void move(int row = 0, int col = 0);

    NCurses(NCurses&&) = default;
    NCurses(const NCurses&) = default;
    NCurses& operator=(NCurses&&) = default;
    NCurses& operator=(const NCurses&) = default;

private:
    int m_max_rows;
    int m_max_cols;

    std::vector<WINDOW*> m_windows;
    std::mutex m_lock;
};

} // namespace ilrd

#endif // ILRD_NCURSES_HPP
