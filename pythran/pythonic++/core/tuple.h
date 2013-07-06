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
            template<class T, size_t N>
            struct array;

            template<size_t I>
                struct to_tuple_impl {
                    template<class T, size_t N>
                        auto operator()(core::array<T,N> const& l) const -> decltype(std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]))) {
                            return std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]));
                        }
                };
            template<>
                struct to_tuple_impl<1> {
                    template<class T, size_t N>
                        std::tuple<T> operator()(core::array<T,N> const& l) const {
                            return std::tuple<T>(l[0]);
                        }
                };
            template<>
                struct to_tuple_impl<0> {
                    template<class T, size_t N>
                        std::tuple<> operator()(core::array<T,N> const& l) const {
                            return std::tuple<>();
                        }
                };

        template<class T, size_t N>
        struct array: public std::array<T,N>
        {
            array(std::initializer_list<T> l) : std::array<T,N>() {
                std::copy(l.begin(), l.end(), this->begin());
            }
            array() : std::array<T,N>() {}
            array(array<T,N> const& l) : std::array<T,N>(l) {}
            array(array<T,N>&& l) : std::array<T,N>(std::move(l)) {}
            template<class U>
                array(array<U,N> const& l) : std::array<T,N>() {
                    std::copy(l.begin(), l.end(), this->begin());
                }
            template<class... Types>
                operator std::tuple<Types...>() const {
                    return std::tuple<Types...>(to_tuple_impl<N>()(*this));
                }

            auto to_tuple() const -> decltype(to_tuple_impl<N>()(*this)) {
                return to_tuple_impl<N>()(*this);
            }
            template<class T1, size_t N1>
                bool operator==(pythonic::core::array<T1,N1> const& other) const {
                    return N == N1 and std::equal(this->begin(), this->end(), other.begin());
                }
            core::array<T,N>& operator=(core::array<T,N> const& t){
                std::copy(t.begin(), t.end(), this->begin());
                return *this;
            }
            using std::array<T,N>::operator[];
            list<T> operator[](core::slice const& s){
                long lower, upper, step;
                lower = s.lower;
                step = s.step;
                upper = s.upper;
                if(s.step<0)
                {
                    if(s.upper<0) upper += N;
                    if(s.lower<0) lower += N;
                    else if(s.lower > N) lower= N;
                    list<T> out((upper - lower)/step);
                    for(int i=0; i< out.size(); i++)
                        out[i] = std::array<T,N>::operator[](upper + i * step);
                    return out;
                }
                else
                {   
                    if(s.lower<0) lower += N;
                    if(s.upper<0) upper += N;
                    else if(s.upper>N) upper = N;
                    list<T> out((upper - lower)/step);
                    for(int i=0; i< out.size(); i++)
                        out[i] = std::array<T,N>::operator[](lower + i * step);
                    return out;
                }
            }

            /* array */
                friend std::ostream& operator<<(std::ostream& os, core::array<T,N> const & v) {
                    os << '(';
                    auto iter = v.begin();
                    if(iter != v.end()) {
                        while(iter+1 != v.end())
                            os << *iter++ << ", ";
                        os << *iter;
                    }
                    return os << ')';
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
                auto operator()(Types&&... types) -> decltype(std::make_tuple(std::forward<Types>(types)...)){
                    return std::make_tuple(std::forward<Types>(types)...);
                }
            };
        template<class... Types>
            struct _make_tuple<true, Types...> {
                core::array<typename are_same<Types...>::type, sizeof...(Types)> operator()(Types... types) {
                    typedef typename are_same<Types...>::type T;
                    return core::array<T, sizeof...(Types)>({types...});
                }
            };

        template<class... Types>
            auto make_tuple(Types&&... types) -> decltype(_make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...)) {
                return _make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...);
            }

        template<class T, size_t N, class... Types>
            auto operator+(std::tuple<Types...> const& t, core::array<T,N> const& lt)
            -> decltype( std::tuple_cat(t, lt.to_tuple()))
            {
                return std::tuple_cat(t, lt.to_tuple());
            }
        template<class T, size_t N, class... Types>
            auto operator+(core::array<T,N> const& lt, std::tuple<Types...> const& t)
            -> decltype( std::tuple_cat(lt.to_tuple(), t) )
            {
                return std::tuple_cat(lt.to_tuple(), t);
            }

    }
}
/* specialize std::get */
namespace std {
    template <size_t I, class T, size_t N>
        typename pythonic::core::array<T,N>::reference get( pythonic::core::array<T,N>& t) { return t[I]; }
    template <size_t I, class T, size_t N>
        typename pythonic::core::array<T,N>::const_reference get( pythonic::core::array<T,N> const & t) { return t[I]; }

    template <size_t I, class T, size_t N>
        struct tuple_element<I, pythonic::core::array<T,N> > {
            typedef typename pythonic::core::array<T,N>::value_type type;
        };
    template<class T, size_t N>
        struct tuple_size<pythonic::core::array<T,N>> {
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
        struct hash<pythonic::core::array<T,N>> {
            size_t operator()(pythonic::core::array<T,N> const& l) const {
                size_t seed = 0;
                hash<T> h;
                for(auto const &iter: l) 
                    seed ^= h(iter) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
            }
        };
}

#endif

