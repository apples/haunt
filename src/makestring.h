#ifndef MAKESTRING_H_INCLUDED
#define MAKESTRING_H_INCLUDED

#include <string>
#include <sstream>

template <typename derp>
inline std::string makeString(const derp &n)
{
    std::stringstream stream;
    stream << n;
    return stream.str();
}

#endif // MAKESTRING_H_INCLUDED
