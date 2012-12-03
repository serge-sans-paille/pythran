#ifndef PYTHONIC_IO_H
#define PYTHONIC_IO_H

#include <iostream>

namespace pythonic {

    /* a few empty_* types */
    std::ostream& operator<<(std::ostream& os, core::empty_dict const & ) {
        return os << "{}";
    }

    std::ostream& operator<<(std::ostream& os, core::empty_list const & ) {
        return os << "[]";
    }

    /* string */
    std::ostream& operator<<(std::ostream& os, core::string const & s) {
        return os << s.c_str();
    }

    /* list */

    template<class T>
        std::ostream& operator<<(std::ostream& os, core::list<T> const & v) {
            os << '[';
            auto iter = v.begin();
            if(iter != v.end()) {
                while(iter+1 != v.end())
                    os << *iter++ << ", ";
                os << *iter;
            }
            return os << ']';
        }

    /* exception */

    std::ostream& operator<<(std::ostream& o, core::BaseException const & e)
    {
        return o << e.args;
    }

    std::ostream& operator<<(std::ostream& o, core::EnvironmentError const & e)
    {
        if(e.args.size()==2)
            return o << "[Errno " << e.args[0] << "] " << e.args[1];
        else if(e.args.size()==3)
            return o << "[Errno " << e.args[0] << "] " << e.args[1] << ": '" << e.args[2] << "'";
        else
            return o << e.args;
    }

    /* set */

    template<class T>
        std::ostream& operator<<(std::ostream& os, core::set<T> const & v) {
            os << '{';
            auto iter = v.begin();
            if(iter != v.end()) {
                auto niter = iter ; ++niter;
                while(niter++ != v.end())
                    os << *iter++ << ", ";
                os << *iter;
            }
            return os << '}';
        }

    std::ostream& operator<<(std::ostream& os, core::empty_set const & ) {
        return os << "{}";
    }
    /* dict */
    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, std::pair<K,V> const & p) {
            os << p.first << ": ";
            return os << p.second ;
        }
    template<class K, class V>
        std::ostream& operator<<(std::ostream& os, core::dict<K,V> const & v) {
            os << '{';
            auto iter = v.item_begin();
            if(iter != v.item_end()) {
                auto niter = iter ; ++niter;
                while(niter != v.item_end()) {
                    os << *iter << ", ";
                    ++niter, ++iter;
                }
                os << *iter ;
            }
            return os << '}';
        }

    /* none */

    template<class T>
        std::ostream& operator<<(std::ostream& os, none<T> const & v) {
            if(v == None) return os << "None";
            else return os << v.data;
        }

    std::ostream& operator<<(std::ostream& os, none_type const &) {
        return os << "None";
    }

    /* tuple */

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

    /* generic */
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
            detail::print(std::cout, value) << ' ';
            print_nonl(values...);
        }

    void print() {
        std::cout << std::endl;
    }

    template< typename T, typename... Types>
        void print(T const& value, Types const&... values) {
            detail::print(std::cout, value) << ' ';
            print(values...);
        }
}
#endif
