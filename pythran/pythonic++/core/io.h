#ifndef PYTHONIC_IO_H
#define PYTHONIC_IO_H

#include <iostream>

namespace pythonic {
    void print_nonl() {
    }
    template< typename T, typename... Types>
        void print_nonl(T const& value, Types const&... values) {
            std::cout << value << ' ';
            print_nonl(values...);
        }

    void print() {
        std::cout << std::endl;
    }

    template< typename T, typename... Types>
        void print(T const& value, Types const&... values) {
            std::cout << value << ' ';
            print(values...);
        }

    template<class T>
        std::ostream& operator<<(std::ostream& os, sequence<T> const & v) {
            os << '[';
            auto iter = v.begin();
            if(iter != v.end()) {
                while(iter+1 != v.end())
                    os << *iter++ << ", ";
                os << *iter;
            }
            return os << ']';
        }

    template<class T>
        std::ostream& operator<<(std::ostream& os, none<T> const & v) {
            if(v == None) return os << "None";
            else return os << v.data;
        }

    std::ostream& operator<<(std::ostream& os, none_type const &) {
        return os << "None";
    }

    template<std::size_t> struct int_{}; // compile-time counter

    template<class Ch, class Tr, class Tuple, std::size_t I>
        void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, int_<I>){
            print_tuple(os, t, int_<I-1>());
            os << ", " << std::get<I>(t);
        }

    template<class Ch, class Tr, class Tuple>
        void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, int_<0>){
            os << std::get<0>(t);
        }

    template<class Ch, class Traits, class... Args>
        std::ostream& operator<<(std::basic_ostream<Ch,Traits>& os,
                std::tuple<Args...> const& t)
        {
            os << '(';
            print_tuple(os, t, int_<sizeof...(Args)-1>());
            return os << ')';
        }
}
#endif
