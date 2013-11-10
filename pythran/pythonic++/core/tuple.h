#ifndef PYTHONIC_TUPLE_H
#define PYTHONIC_TUPLE_H

#include <tuple>
#include <algorithm>

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

        /* inspired by std::array implementation */
        template<typename T, size_t N>
            struct array
            {
                typedef T value_type;
                typedef value_type* pointer;
                typedef const value_type* const_pointer;
                typedef value_type& reference;
                typedef const value_type& const_reference;
                typedef value_type* iterator;
                typedef const value_type* const_iterator;
                typedef std::size_t size_type;
                typedef std::ptrdiff_t difference_type;
                typedef std::reverse_iterator<iterator> reverse_iterator;
                typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

                // Support for zero-sized arrays mandatory.
                value_type buffer[N ? N : 1];

                // No explicit construct/copy/destroy for aggregate type.

                void
                    fill(const value_type& __u)
                    { std::fill_n(begin(), size(), __u); }

                // Iterators.
                iterator
                    begin() noexcept
                    { return iterator(data()); }

                const_iterator
                    begin() const noexcept
                    { return const_iterator(data()); }

                iterator
                    end() noexcept
                    { return iterator(data() + N); }

                const_iterator
                    end() const noexcept
                    { return const_iterator(data() + N); }

                reverse_iterator 
                    rbegin() noexcept
                    { return reverse_iterator(end()); }

                const_reverse_iterator 
                    rbegin() const noexcept
                    { return const_reverse_iterator(end()); }

                reverse_iterator 
                    rend() noexcept
                    { return reverse_iterator(begin()); }

                const_reverse_iterator 
                    rend() const noexcept
                    { return const_reverse_iterator(begin()); }

                const_iterator
                    cbegin() const noexcept
                    { return const_iterator(&(buffer[0])); }

                const_iterator
                    cend() const noexcept
                    { return const_iterator(&(buffer[N])); }

                const_reverse_iterator 
                    crbegin() const noexcept
                    { return const_reverse_iterator(end()); }

                const_reverse_iterator 
                    crend() const noexcept
                    { return const_reverse_iterator(begin()); }

                // Capacity.
                constexpr size_type 
                    size() const noexcept { return N; }

                constexpr size_type 
                    max_size() const noexcept { return N; }

                constexpr bool 
                    empty() const noexcept { return size() == 0; }

                // Element access.
                reference
                    operator[](size_type __n)
                    { return buffer[__n]; }

                constexpr const_reference
                    operator[](size_type __n) const noexcept
                    { return buffer[__n]; }

                reference 
                    front()
                    { return *begin(); }

                const_reference 
                    front() const
                    { return *begin(); }

                reference 
                    back()
                    { return N ? *(end() - 1) : *end(); }

                const_reference 
                    back() const
                    { return N ? *(end() - 1) : *end(); }

                pointer
                    data() noexcept
                    { return &(buffer[0]); }

                const_pointer
                    data() const noexcept
                    { return &(buffer[0]); }

                template<size_t M>
                    bool operator==(array<T, M> const& other) const {
                        return N == M and std::equal(begin(), end(), other.begin()); 
                    }
                template<size_t M>
                    bool operator<(array<T, M> const& other) const {
                        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
                    }

                template<class... Types>
                    operator std::tuple<Types...>() const {
                        return std::tuple<Types...>(to_tuple_impl<N>()(*this));
                    }

                auto to_tuple() const -> decltype(to_tuple_impl<N>()(*this)) {
                    return to_tuple_impl<N>()(*this);
                }

                list<T> operator[](core::slice const& s){
                    core::slice norm = s.normalize(size());
                    list<T> out(norm.size());
                    for(long i=0; i< out.size(); i++)
                        out[i] = buffer[norm.lower + i * norm.step];
                    return out;
                }

                /* array */
                friend std::ostream& operator<<(std::ostream& os, core::array<T, N> const & v) {
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
                    return core::array<T, sizeof...(Types)>{{types...}};
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

#include <boost/functional/hash/extensions.hpp>

/* and boost's */
namespace pythonic {
    namespace core {
#ifdef BOOST_NO_CXX11_HDR_TUPLE
        template<class... Types>
            std::size_t hash_value(std::tuple<Types...>  const &x) {
                return std::hash<std::tuple<Types...>>()(x);
            }
#endif
        template<class T, size_t N>
            std::size_t hash_value(pythonic::core::array<T,N>  const &x) {
                return std::hash<pythonic::core::array<T,N>>()(x);
            }
    }
}


#endif

