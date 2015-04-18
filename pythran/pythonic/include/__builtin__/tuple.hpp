#ifndef PYTHONIC_INCLUDE_BUILTIN_TUPLE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_TUPLE_HPP

#include "pythonic/utils/proxy.hpp"

#include "pythonic/types/tuple.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class... Types>
            std::tuple<Types...> tuple(std::tuple<Types...> const& t);


        template <class Iterable>
            struct _tuple
            {
                types::list<typename Iterable::value_type> operator()(Iterable i);
            };

        template <class T>
            struct _tuple<types::list<T>> {
                types::list<T> operator()(types::list<T> const& i);
            };

        template <class Iterable> /* this is far from perfect, but how to cope with the difference between python tuples and c++ ones ? */
            typename std::enable_if<types::len_of<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value < 0,
                                    types::list<typename std::iterator_traits<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::iterator>::value_type>
                                   >::type
            tuple(Iterable&& i);

        template<class StaticIterable> /* specialization if we are capable to statically compute the size of the input */
            typename std::enable_if<types::len_of<typename std::remove_cv<typename std::remove_reference<StaticIterable>::type>::type>::value >= 0,
                                    types::array<typename std::iterator_traits<typename std::remove_cv<typename std::remove_reference<StaticIterable>::type>::type::iterator>::value_type,
                                             types::len_of<typename std::remove_cv<typename std::remove_reference<StaticIterable>::type>::type>::value>
                                   >::type
            tuple(StaticIterable&& i);

        PROXY_DECL(pythonic::__builtin__, tuple);

    }

}

#endif
