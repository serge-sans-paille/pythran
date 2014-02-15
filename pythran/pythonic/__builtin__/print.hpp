#ifndef PYTHONIC_BUILTIN_PRINT_HPP
#define PYTHONIC_BUILTIN_PRINT_HPP

#include <iostream>

namespace pythonic {

    namespace __builtin__ {

        namespace detail {
            template<class T>
                std::ostream& print(std::ostream& os, T const & t) {
                    return os << t;
                }
        }

        void print_nonl() {
        }
        template< typename T, typename... Types>
            void print_nonl(T const& value, Types const&... values) {
                detail::print(std::cout, value);
                if(sizeof...(Types) > 0)
                    std::cout << ' ';
                print_nonl(values...);
            }

        void print() {
            std::cout << std::endl;
        }

        template< typename T, typename... Types>
            void print(T const& value, Types const&... values) {
                detail::print(std::cout, value);
                if(sizeof...(values) > 0)
                    std::cout << ' ';
                print(values...);
            }

    }


}

#endif
