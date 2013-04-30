#ifndef PYTHONIC_TUPLE_H
#define PYTHONIC_TUPLE_H

#include <tuple>

template<class F, class S>
bool operator==(std::pair<F,S> const& self, std::tuple<F,S> const& other) {
    return self.first == std::get<0>(other) and self.second == std::get<1>(other);
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> const& t1) {
    return std::tuple_cat(t0, t1);
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> const& t1) {
    return std::tuple_cat(std::forward<Types0...>(t0), t1);
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> && t1) {
    return std::tuple_cat(t0, std::forward<Types1...>(t1));
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> && t1) {
    return std::tuple_cat(std::forward<Types0...>(t0), std::forward<Types1...>(t1));
}

/* hashable tuples, as proposed in http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set */
namespace {
    size_t hash_combiner(size_t left, size_t right) //replacable
    { return left^right;}

    template<int index, class...types>
        struct hash_impl {
            size_t operator()(size_t a, const std::tuple<types...>& t) const {
                typedef typename std::tuple_element<index, std::tuple<types...>>::type nexttype;
                hash_impl<index-1, types...> next;
                size_t b = std::hash<nexttype>()(std::get<index>(t));
                return next(hash_combiner(a, b), t); 
            }
        };
    template<class...types>
        struct hash_impl<0, types...> {
            size_t operator()(size_t a, const std::tuple<types...>& t) const {
                typedef typename std::tuple_element<0, std::tuple<types...>>::type nexttype;
                size_t b = std::hash<nexttype>()(std::get<0>(t));
                return hash_combiner(a, b); 
            }
        };
}
namespace pythonic {
    template<class Tuple, class Container>
        void tuple_dump(Tuple const& t, Container& c, int_<0>) {
            c[0]=std::get<0>(t);
        }

    template<class Tuple, class Container, size_t I>
        void tuple_dump(Tuple const& t, Container& c, int_<I>) {
            c[I]=std::get<I>(t);
            tuple_dump(t,c, int_<I-1>());
        }
}
 

/* make_tuple wrapper to generate a tuple-like container */
namespace pythonic {

    namespace core {

        template<class T, size_t N>
            struct ltuple : public list<T> {
                ltuple(std::initializer_list<T> l) : list<T>(std::move(l)) {
                }
                ltuple() : list<T>(N) {
                }
                ltuple(ltuple<T,N> const& l) : list<T>(l) {
                }
                ltuple(ltuple<T,N> & l) : list<T>(l) {
                }
                template<class Iter>
                ltuple(Iter b, Iter e): list<T>(b,e) {
                }


            };

        template<class... Types>
            struct are_same;
        template<>
            struct are_same<> {
                static bool const value = false;
            };
        template<class T>
            struct are_same<T> {
                static bool const value = true;
                typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
            };
        template<class T, class... Types>
            struct are_same<T, Types...> {
                static bool const value = are_same<Types...>::value and std::is_same<typename std::remove_cv<typename std::remove_reference<T>::type>::type, typename are_same<Types...>::type>::value;
                typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
            };

        template<bool Same, class... Types>
            struct _make_tuple {
                std::tuple<Types...> operator()(Types... types) {
                    return std::tuple<Types...>(types...);
                }
            };
        template<class... Types>
            struct _make_tuple<true, Types...> {
                ltuple<typename are_same<Types...>::type, sizeof...(Types)> operator()(Types... types) {
                    typedef typename are_same<Types...>::type T;
                    return ltuple<T, sizeof...(Types)>({types...});
                }
            };

        template<class... Types>
            auto make_tuple(Types&&... types) -> decltype(_make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...)) {
                return _make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...);
            }
    }
}
/* specialize std::get */
namespace std {
    template <size_t I, class T, size_t N>
        typename pythonic::core::ltuple<T,N>::reference get( pythonic::core::ltuple<T,N>& t) { return t[I]; }
    template <size_t I, class T, size_t N>
        typename pythonic::core::ltuple<T,N>::const_reference get( pythonic::core::ltuple<T,N> const & t) { return t[I]; }

    template <size_t I, class T, size_t N>
        struct tuple_element<I, pythonic::core::ltuple<T,N> > {
            typedef typename pythonic::core::ltuple<T,N>::value_type type;
        };
    template<class T, size_t N>
        struct tuple_size<pythonic::core::ltuple<T,N>> {
            static const size_t value = N;
        };
}
/* specialize std::hash */
namespace std {
    template<class...Types>
        struct hash<std::tuple<Types...>> {
            size_t operator()(std::tuple<Types...> const& t) const {
                const size_t begin = std::tuple_size<std::tuple<Types...>>::value-1;
                return hash_impl<begin, Types...>()(1, t); //1 should be some largervalue
            }
        };
    template<class T, size_t N>
        struct hash<pythonic::core::ltuple<T,N>> {
            size_t operator()(pythonic::core::ltuple<T,N> const& l) const {
                size_t seed = 0;
                hash<T> h;
                for(auto const &iter: l) 
                    seed ^= h(l) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
            }
        };
}

#endif

