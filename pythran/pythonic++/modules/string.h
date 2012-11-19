#ifndef PYTHONIC_MODULE_STRING_H
#define PYTHONIC_MODULE_STRING_H

#include <boost/algorithm/string.hpp>  

namespace pythonic {
    namespace __string__ { /* to avoid conflict with the string intrinsic */
        long find(core::string const & s, core::string const& value, size_t start, long long end) {
            long a = s.find(value,start);
            return (a>end)?-1:a;
        }
        long find(core::string const & s, core::string const& value, size_t start) {
            return find(s,value,start,s.length());
        }
        long find(core::string const & s, core::string const& value) {
            return find(s,value,0,s.length());
        }
        PROXY(pythonic::__string__, find);

        template<class T>
            core::string join(core::string const & s, T const & iterable) {
                auto b = iterable.begin();
                std::ostringstream out;
                out << *b;
                b++;
                for(;b!=iterable.end();b++)
                    out << s << *b;
                return out.str();
        }
        PROXY(pythonic::__string__, join);
        core::string capitalize(core::string const & s)
        {
            core::string copy = s;
            boost::algorithm::to_lower(copy);
            copy[0]=std::toupper(copy[0]);
            return copy;
        }
        PROXY(pythonic::__string__, capitalize);
        core::list<core::string> split(core::string const& s, core::string const& sep = " ", int maxsplit = -1)
        {
            core::list<core::string> res(0);
            size_t current;
            size_t next = -1;
            size_t numsplit = 0;
            do
            {
                current = next + 1;
                next = s.find_first_of( sep, current );
                res.push_back(s.substr( current, next - current ));
            }
            while (next != core::string::npos && (numsplit++<maxsplit || maxsplit==-1));
            return res;
        } 
        PROXY(pythonic::__string__, split);
    }
}
#endif
