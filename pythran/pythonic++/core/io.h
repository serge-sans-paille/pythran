#ifndef PYTHONIC_IO_H
#define PYTHONIC_IO_H

#include <iostream>
#include <string>

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

    /* @brief Convert EnvironmentError to a string.
     *
     * The number of arguments used when creating the EnvironmentError impact
     * the resulting "type" or formatting of the chain. We aim to mimic python
     * behavior of course:
     * - only one arg, then assume it can be converted to string,
     * - two args, then the first one is the errno, the next one a string,
     * - three args, like two args, adding "filename" as third one (after ':')
     * - four or more args, the "tuple" used to construct the exception
     *
     */
    std::ostream& operator<<(std::ostream& o, core::EnvironmentError const & e)
    {
        if(e.args.size()==1)
            return o << e.args[0];
        if(e.args.size()==2)
            return o << "[Errno " << e.args[0] << "] " << e.args[1];
        else if(e.args.size()==3)
            return o << "[Errno " << e.args[0] << "] " << e.args[1] << ": '" << e.args[2] << "'";
        else {
        	// Generate "('a', 'b', 'c', 'd') if a,b,c, and d are in e.args
            std::string listsep = "";
            o << "(";
            for(auto arg : e.args) {
                o << listsep << "'" << arg << "'";
                listsep=", ";
            }
            o << ")";
            return o;
        }
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

    template<class Ch, class Tr, class Tuple, int I>
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
