#ifndef PYTHONIC_MODULE_STRING_H
#define PYTHONIC_MODULE_STRING_H
#include <algorithm>
#include <cctype>
#include <iostream>

namespace pythonic {
    namespace string {
       core::string const ascii_lowercase("abcdefghijklmnopqrstuvwxyz"); 
       core::string const ascii_uppercase("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 
       core::string const ascii_letters = ascii_lowercase + ascii_uppercase; 
       core::string const digits("0123456789"); 
       core::string const hexdigits("0123456789abcdefABCDEF"); 
       core::string const octdigits("01234567"); 
    }
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
                copy[0] = ::toupper(s[0]);
                std::transform(s.begin()+1, s.end(), copy.begin()+1, ::tolower);
                return copy;
            }
        }
        PROXY(pythonic::__string__, capitalize);

        core::string lower(core::string const & s)
        {
            core::string copy = s;
            std::transform(s.begin(),s.end(), copy.begin(), ::tolower);
            return copy;
        }
        PROXY(pythonic::__string__, lower);

        core::string upper(core::string const & s)
        {
            core::string copy = s;
            std::transform(s.begin(),s.end(), copy.begin(), ::toupper);
            return copy;
        }
        PROXY(pythonic::__string__, upper);

        core::list<core::string> split(core::string const& s, core::string const& sep = " ", long maxsplit = -1)
        {
            core::list<core::string> res(0);
            size_t current;
            size_t next = -1;
            long numsplit = 0;
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

        bool endswith(core::string const& s, core::string const& suffix, long start=0, size_t end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            long rstart = end - suffix.size() - start;
            return rstart >= 0 and s.compare(rstart, suffix.size(), suffix) == 0;
        }
        PROXY(pythonic::__string__, endswith);

        core::string replace(core::string const& self, core::string const& old_pattern, core::string const& new_pattern, long count=std::numeric_limits<long>::max()) {
            core::string replaced(self);
            replaced.reserve(1 + std::max(self.size(), self.size()* new_pattern.size() / (1+old_pattern.size())));

            size_t pos = 0;
            while(count and (pos = replaced.find(old_pattern, pos)) != std::string::npos)
            {
                replaced.replace(pos, old_pattern.length(), new_pattern);
                pos += new_pattern.length();
                count-=1;
            }
            return replaced;
        }
        PROXY(pythonic::__string__, replace);

    }
}
#endif
