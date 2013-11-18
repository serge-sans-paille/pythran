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
            return find(s,value,start,s.size());
        }
        long find(core::string const & s, core::string const& value) {
            return find(s,value,0,s.size());
        }
        PROXY(pythonic::__string__, find);

        template<class Iterable>
            typename std::enable_if<
                std::is_same<
                    typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                    std::random_access_iterator_tag
                > :: value,
                core::string
            >::type
            join(core::string const & s, Iterable && iterable) {
                /* first iterate over iterable to gather sizes */
                size_t n = s.size() * std::distance(iterable.begin(), iterable.end());
                for(auto const& iter:iterable)
                    n += __builtin__::len(iter);

                core::string out("");
                out.reserve(n);

                auto iter = iterable.begin();
                out += *iter;
                ++iter;
                for(;iter!=iterable.end();++iter) {
                    out += s ;
                    out += *iter ;
                }
                return out;
            }

        template<class Iterable>
            typename std::enable_if<
                not std::is_same<
                    typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                    std::random_access_iterator_tag
                > :: value,
                core::string
            >::type
            join(core::string const & s, Iterable && iterable) {
                
                core::string out;
                auto iter = iterable.begin();
                out += *iter;
                ++iter;
                for(;iter!=iterable.end();++iter) {
                    out += s ;
                    out += *iter ;
                }
                return out;
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

        bool startswith(core::string const& s, core::string const& prefix, long start=0, size_t end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            return (end - start) >= prefix.size() and s.compare(start, prefix.size(), prefix) == 0;
        }
        PROXY(pythonic::__string__, startswith);

        bool endswith(core::string const& s, core::string const& suffix, long start=0, size_t end=std::string::npos) {
            if(end == std::string::npos)
                end = s.size();
            long rstart = end - suffix.size();
            return rstart >= start and s.compare(rstart, suffix.size(), suffix) == 0;
        }
        PROXY(pythonic::__string__, endswith);

        core::string replace(core::string const& self, core::string const& old_pattern, core::string const& new_pattern, long count=std::numeric_limits<long>::max())
        {
            char const * needle = old_pattern.c_str();
            char const * new_needle = new_pattern.c_str();
            char const * new_needle_end = new_needle + new_pattern.size();
            char const * haystack = self.c_str();

            char const * haystack_next = strstr(haystack, needle);
            if(not count or not haystack_next) {
                return core::string(haystack);
            }
            else {
                size_t n = 1 + std::max(self.size(), self.size()* (1+new_pattern.size()) / (1+old_pattern.size()));
                char *buffer = new char[n];
                char *iter = buffer;
                do {
                    iter = std::copy(haystack, haystack_next, iter);
                    iter = std::copy(new_needle, new_needle_end, iter);
                    count -= 1;
                    haystack = haystack_next + old_pattern.size();
                    assert(size_t(iter - buffer) < n);
                } while(count and (haystack_next=strstr(haystack, needle)));
                std::copy(haystack, self.c_str() + self.size() + 1, iter);

                core::string replaced(buffer);
                delete [] buffer;
                return replaced;
            }

        }

        PROXY(pythonic::__string__, replace);

        core::string strip(core::string const& self, core::string const& to_del = " \n")
        {
            if(not self)
                return self;
            return core::string(self.begin() + self.find_first_not_of(to_del), self.begin() + self.find_last_not_of(to_del) + 1);
        }
        PROXY(pythonic::__string__, strip);

        core::list<core::string> split(core::string const& in, core::string const& sep = " \n", long maxsplit = -1)
        {
            core::string s = strip(in);
            core::list<core::string> res(0);
            size_t current = 0;
            size_t next = 0;
            long numsplit = 0;
            while (next != core::string::npos && (numsplit++<maxsplit || maxsplit==-1))
            {
                next = s.find_first_of( sep, current );
                res.push_back(s.substr( current, next - current ));
                current = next + 1;
            }
            if(next != core::string::npos)
            {
                current = next + 1;
                res.push_back(s.substr( current, s.size() - current ));    
            }
            return res;
        } 

        core::list<core::string> split(core::string const& s, none_type const&, long maxsplit = -1)
        {
            return split(s, " ", maxsplit);
        } 
        PROXY(pythonic::__string__, split);


        core::string lstrip(core::string const& self, core::string const& to_del = " ")
        {
            return core::string(self.begin() + self.find_first_not_of(to_del), self.end());
        }
        PROXY(pythonic::__string__, lstrip);

        core::string rstrip(core::string const& self, core::string const& to_del = " ")
        {
            return core::string(self.begin(), self.begin() + self.find_last_not_of(to_del) + 1);
        }
        PROXY(pythonic::__string__, rstrip);
    }
}
#endif
