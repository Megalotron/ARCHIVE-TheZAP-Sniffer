#include <gtest/gtest.h>
#include "logger.hpp"

class OSRedirector {
private:
    std::ostringstream _oss{};
    std::streambuf *_backup{};
    std::ostream &_c;

public:
    OSRedirector(OSRedirector &) = delete;
    OSRedirector &operator=(OSRedirector &) = delete;

    OSRedirector(std::ostream &c) : _c(c) {
        _backup = _c.rdbuf();
        _c.rdbuf(_oss.rdbuf());
    }

    ~OSRedirector() {
        _c.rdbuf(_backup);
    }

    const std::string getContent() {
        _oss << std::flush;
        return _oss.str();
    }
};

TEST(logger, basic_test)
{
    OSRedirector osr(std::cout);
    tools::logger(tools::log::injector, "Hello World! ", 1, " - ", 3.14, ';');
    EXPECT_EQ(osr.getContent().ends_with("Hello World! 1 - 3.14;\n"), true);
}