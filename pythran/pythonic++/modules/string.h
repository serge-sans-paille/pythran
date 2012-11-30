#ifndef PYTHONIC_MODULE_STRING_H
#define PYTHONIC_MODULE_STRING_H
#include <algorithm>
#include <cctype>
#include <iostream>

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

        template<class Iterable>
            core::string join(core::string const & s, Iterable && iterable) {
                std::ostringstream out;
                auto iter = iterable.begin();
                out << *iter;
                ++iter;
                for(;iter!=iterable.end();++iter)
                    out << s << *iter;
                return out.str();
            }
        PROXY(pythonic::__string__, join);

        core::string capitalize(core::string const & s)
        {
            if(s.empty()) return s;
            else {
                core::string copy = s;
                ::toupper(*copy.begin());
                std::transform(copy.begin()+1, copy.end(), copy.begin()+1, ::tolower);
                return copy;
            }
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

        bool endswith(core::string const& s, core::string const& suffix, long start=0, long end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            long rstart = end - suffix.size() - start;
            return rstart >= 0 and s.compare(rstart, suffix.size(), suffix) == 0;
        }
        PROXY(pythonic::__string__, endswith);

    }
}
#endif
