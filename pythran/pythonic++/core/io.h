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
    namespace core {
        std::ostream& operator<<(std::ostream& os, string const & s) {
            return os << s.c_str();
        }
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

    /* ndarray */

    template<class T, size_t N>
        std::ostream& operator<<(std::ostream& os, core::ndarray<T,N> const& e)
        {
            std::array<long, N> strides;
            auto shape = e.shape;
            strides[N-1] = shape[N-1];
            if(strides[N-1]==0)
                return os << "[]";
            std::transform(strides.rbegin(), strides.rend() -1, shape.rbegin() + 1, strides.rbegin() + 1, std::multiplies<long>());
            size_t depth = N;
            int step = -1;
            std::ostringstream oss;
            auto e_count = e.size();
            oss << *std::max_element(e.buffer, e.buffer+ e_count);
            int size = oss.str().length();
            T* iter = e.buffer;
            int max_modulo = 1000;

            os << "[";
            if( shape[0] != 0)
            do {
                if(depth==1)
                {
                    os.width(size);
                    os << *iter++;
                    for(int i=1; i<shape[N-1]; i++)
                    {
                        os.width(size+1);
                        os << *iter++;
                    }
                    step = 1;
                    depth++;
                    max_modulo = std::lower_bound(strides.begin(), strides.end(), iter - e.buffer, [](int comp, int val){ return val%comp!=0; }) - strides.begin();
                }
                else if(max_modulo + depth == N + 1)
                {
                    depth--;
                    step = -1;
                    os << "]";
                    for(size_t i=0;i<depth;i++)
                        os << std::endl;
                    for(size_t i=0;i<N-depth;i++)
                        os << " ";
                    os << "[";
                }
                else
                {
                    depth+=step;
                    if(step==1)
                        os << "]";
                    else
                        os << "[";
                }
            }
            while(depth != N+1);

            return os << "]";
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
            if(v == __builtin__::None) return os << "None";
            else return os << v.data;
        }

    std::ostream& operator<<(std::ostream& os, none_type const &) {
        return os << "None";
    }

    /* tuple */

    template<class Ch, class Tr, class Tuple, size_t I>
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
#endif
