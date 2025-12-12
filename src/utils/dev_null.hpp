

#include <ostream>
#include <streambuf>
namespace
{
// A stream buffer that discards all output
class null_streambuf : public std::streambuf
{
private:
    // Ignore characters by pretending the write succeeded
    int overflow(int c) override
    {
        return traits_type::not_eof(c); // Indicate success
    }
};

class null_ostream : public std::ostream
{

public:
    null_ostream() : std::ostream(&m_buf) {}

    null_streambuf m_buf;
};
} // namespace

namespace utils
{

null_ostream devnull{};
} // namespace utils
