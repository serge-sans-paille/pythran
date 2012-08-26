#ifndef PYTHONIC_STRING_H
#define PYTHONIC_STRING_H
#include <string>

namespace pythonic {
    namespace core {
        using std::string;
    }
}
template<typename T>
pythonic::core::string operator*(pythonic::core::string const & s, T const & t) {
    size_t n=t;
    pythonic::core::string other;
    other.resize(s.size()*n,'a');
    auto where = other.begin();
    for(size_t i=0;i<n; i++, where+=s.size())
        std::copy(s.begin(), s.end(), where);
    return other;
}

#endif
