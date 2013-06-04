#ifndef PYTHONIC_TUPLE_H
#define PYTHONIC_TUPLE_H

#include <tuple>

template<class F, class S>
bool operator==(std::pair<F,S> const& self, std::tuple<F,S> const& other) {
    return self.first == std::get<0>(other) and self.second == std::get<1>(other);
}
template<class T0, size_t N0, class T1, size_t N1>
bool operator==(std::array<T0,N0> const& self, std::array<T1,N1> const& other) {
    return N0 == N1 and std::equal(self.begin(), self.end(), other.begin());
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

    template<size_t index, class...types>
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

            template<size_t I>
                struct to_tuple_impl {
                    template<class T, size_t N>
                        auto operator()(std::array<T,N> const& l) const -> decltype(std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]))) {
                            return std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]));
                        }
                };
            template<>
                struct to_tuple_impl<1> {
                    template<class T, size_t N>
                        std::tuple<T> operator()(std::array<T,N> const& l) const {
                            return std::tuple<T>(l[0]);
                        }
                };
            template<>
                struct to_tuple_impl<0> {
                    template<class T, size_t N>
                        std::tuple<> operator()(std::array<T,N> const& l) const {
                            return std::tuple<>();
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
                std::array<typename are_same<Types...>::type, sizeof...(Types)> operator()(Types... types) {
                    typedef typename are_same<Types...>::type T;
                    return std::array<T, sizeof...(Types)>({{types...}});
                }
            };

        template<class... Types>
            auto make_tuple(Types&&... types) -> decltype(_make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...)) {
                return _make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...);
            }

        template<class T, size_t N, class... Types>
            auto operator+(std::tuple<Types...> const& t, std::array<T,N> const& lt)
            -> decltype( std::tuple_cat(t, lt.to_tuple()))
            {
                return std::tuple_cat(t, lt.to_tuple());
            }
        template<class T, size_t N, class... Types>
            auto operator+(std::array<T,N> const& lt, std::tuple<Types...> const& t)
            -> decltype( std::tuple_cat(lt.to_tuple(), t) )
            {
                return std::tuple_cat(lt.to_tuple(), t);
            }

    }
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
        struct hash<std::array<T,N>> {
            size_t operator()(std::array<T,N> const& l) const {
                size_t seed = 0;
                hash<T> h;
                for(auto const &iter: l) 
                    seed ^= h(l) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
            }
        };
}

#endif

