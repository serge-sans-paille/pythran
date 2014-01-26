#ifndef PYTHONIC_OPERATOR_ITEMGETTER_HPP
#define PYTHONIC_OPERATOR_ITEMGETTER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/int_.hpp"

namespace pythonic {

    namespace operator_ {
        struct itemgetter_return {
            long i;
            itemgetter_return(long const& item=-1) : i(item){}
            template<class A>
                auto operator()(A const& a) const -> decltype(a[i]) {
                    return a[i];
                }
        };


        itemgetter_return itemgetter(long item)
        {
            return itemgetter_return(item);
        }

        template<typename... Types>
            struct itemgetter_tuple_return {

                std::tuple<Types...> items;

                itemgetter_tuple_return(Types... items) : items(items...) {
                }

                itemgetter_tuple_return(){
                }

                template<class T, class A, size_t I>
                    void helper(T & t, A const& a, utils::int_<I>) const {
                        std::get<I>(t) = a[std::get<I>(items)];
                        helper(t,a, utils::int_<I-1>());
                    }
                template<class T, class A>
                    void helper(T& t, A const& a, utils::int_<0>) const {
                        std::get<0>(t) = a[std::get<0>(items)];
                    }

                template<class A>
                    auto operator()(A const& a) const -> std::tuple< typename std::remove_cv<typename std::remove_reference<decltype(a[std::declval<Types>()])>::type>::type ... > {
                        std::tuple< typename std::remove_cv<typename std::remove_reference<decltype(a[std::declval<Types>()])>::type>::type ... > t;
                        helper(t, a, utils::int_<sizeof...(Types)-1>());
                        return t;
                    }
            };

        template<class... L>
            auto itemgetter(long const& item1, long const& item2, L ... items) -> itemgetter_tuple_return<long,long, L...>
            {
                return itemgetter_tuple_return<long,long , L...>(item1, item2, items...);
            }

        PROXY(pythonic::operator_, itemgetter);
    }

}

#endif

