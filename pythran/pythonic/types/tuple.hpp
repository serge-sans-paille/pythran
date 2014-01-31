#ifndef PYTHONIC_TYPES_TUPLE_HPP
#define PYTHONIC_TYPES_TUPLE_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/slice.hpp"
#include "pythonic/types/list.hpp" // because of [] operator that returns a list
#include "pythonic/types/content_of.hpp"
#include "pythonic/utils/int_.hpp"


#include <tuple>
#include <algorithm>

namespace std {
    template<class F, class S>
        bool operator==(pair<F,S> const& self, tuple<F,S> const& other) {
            return self.first == get<0>(other) and self.second == get<1>(other);
        }
    template<class F, class S>
        bool operator==(pair<const F,S> const& self, tuple<F,S> const& other) {
            return self.first == get<0>(other) and self.second == get<1>(other);
        }
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

    namespace types {

        template<class T, size_t N>
            struct array;

        template<size_t I>
            struct to_tuple_impl {
                template<class T, size_t N>
                    auto operator()(types::array<T,N> const& l) const -> decltype(std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]))) {
                        return std::tuple_cat(to_tuple_impl<I-1>()(l), std::tuple<T>(l[I-1]));
                    }
            };
        template<>
            struct to_tuple_impl<1> {
                template<class T, size_t N>
                    std::tuple<T> operator()(types::array<T,N> const& l) const {
                        return std::tuple<T>(l[0]);
                    }
            };
        template<>
            struct to_tuple_impl<0> {
                template<class T, size_t N>
                    std::tuple<> operator()(types::array<T,N> const& l) const {
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

                list<T> operator[](types::slice const& s){
                    types::slice norm = s.normalize(size());
                    list<T> out(norm.size());
                    for(long i=0; i< out.size(); i++)
                        out[i] = buffer[norm.lower + i * norm.step];
                    return out;
                }

                /* array */
                friend std::ostream& operator<<(std::ostream& os, types::array<T, N> const & v) {
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
                types::array<typename are_same<Types...>::type, sizeof...(Types)> operator()(Types... types) {
                    typedef typename are_same<Types...>::type T;
                    return types::array<T, sizeof...(Types)>{{types...}};
                }
            };

        template<class... Types>
            auto make_tuple(Types&&... types) -> decltype(_make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...)) {
                return _make_tuple<are_same<Types...>::value, Types...>()(std::forward<Types>(types)...);
            }

        template<class T, size_t N, class... Types>
            auto operator+(std::tuple<Types...> const& t, types::array<T,N> const& lt)
            -> decltype( std::tuple_cat(t, lt.to_tuple()))
            {
                return std::tuple_cat(t, lt.to_tuple());
            }
        template<class T, size_t N, class... Types>
            auto operator+(types::array<T,N> const& lt, std::tuple<Types...> const& t)
            -> decltype( std::tuple_cat(lt.to_tuple(), t) )
            {
                return std::tuple_cat(lt.to_tuple(), t);
            }

    }
    template<class... Types>
        struct assignable<std::tuple<Types...>>{
            typedef std::tuple<typename assignable<Types>::type...> type;
        };

    template<class T, size_t N>
        struct assignable<pythonic::types::array<T,N> >{
            typedef pythonic::types::array<typename assignable<T>::type, N> type;
        };

}
/* specialize remove_cv */
namespace std {

    template <class K, class V>
        struct remove_cv< std::pair<const K, V> > {
            typedef std::pair<K, V> type;
        };
}

/* specialize std::get */
namespace std {
    template <size_t I, class T, size_t N>
        typename pythonic::types::array<T,N>::reference get( pythonic::types::array<T,N>& t) { return t[I]; }
    template <size_t I, class T, size_t N>
        typename pythonic::types::array<T,N>::const_reference get( pythonic::types::array<T,N> const & t) { return t[I]; }

    template <size_t I, class T, size_t N>
        class tuple_element<I, pythonic::types::array<T,N> > {
            public:
                typedef typename pythonic::types::array<T,N>::value_type type;
        };
    template<class T, size_t N>
        class tuple_size<pythonic::types::array<T,N>> {
            public:
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
        struct hash<pythonic::types::array<T,N>> {
            size_t operator()(pythonic::types::array<T,N> const& l) const {
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
    namespace types {
#ifdef BOOST_NO_CXX11_HDR_TUPLE
        template<class... Types>
            std::size_t hash_value(std::tuple<Types...>  const &x) {
                return std::hash<std::tuple<Types...>>()(x);
            }
#endif
        template<class T, size_t N>
            std::size_t hash_value(pythonic::types::array<T,N>  const &x) {
                return std::hash<pythonic::types::array<T,N>>()(x);
            }
    }
}

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"
template<class K, class... Types>
struct __combined<indexable<K>, std::tuple<Types...>> {
    typedef std::tuple<Types...> type;
};

template<class K, class... Types>
struct __combined<std::tuple<Types...>, indexable<K>> {
    typedef std::tuple<Types...> type;
};

template<class K, class T, size_t N>
struct __combined<indexable<K>, pythonic::types::array<T,N>> {
    typedef pythonic::types::array<T,N> type;
};

template<class K, class T, size_t N>
struct __combined<pythonic::types::array<T,N>, indexable<K>> {
    typedef pythonic::types::array<T,N> type;
};
template<class K, class T, size_t N>
struct __combined<container<K>, pythonic::types::array<T,N>> {
    typedef pythonic::types::array<typename __combined<T,K>::type ,N> type;
};

template<class K, class T, size_t N>
struct __combined<pythonic::types::array<T,N>, container<K>> {
    typedef pythonic::types::array<typename __combined<T,K>::type ,N> type;
};

template<class T, size_t N>
struct __combined<pythonic::types::array<T,N>, pythonic::types::array<T,N>> {
    typedef pythonic::types::array<T ,N> type;
};
template <class K, class V, class T, size_t N>
struct __combined<indexable_container<K,V>,pythonic::types::array<T,N>> {
    typedef pythonic::types::array<typename __combined<V,T>::type, N> type;
};

template <class K, class V, class T, size_t N>
struct __combined<pythonic::types::array<T,N>, indexable_container<K,V>> {
    typedef pythonic::types::array<typename __combined<T,V>::type, N> type;
};
template<class... t0, class... t1>
struct __combined<std::tuple<t0...>, std::tuple<t1...>> {
    typedef std::tuple<typename __combined<t0,t1>::type ...> type;  // no further combination
};
template<class t, size_t n, class... types>
struct __combined<pythonic::types::array<t,n>, std::tuple<types...>> {
    typedef std::tuple<types...> type;
};
template<class t, size_t n, class... types>
struct __combined<std::tuple<types...>, pythonic::types::array<t,n>> {
    typedef std::tuple<types...> type;
};
template<class t00, class t01, class t10, class t11>
struct __combined<std::pair<t00, t01>, std::pair<t10, t11>> {
    typedef std::pair<typename __combined<t00,t10>::type, typename __combined<t01,t11>::type> type;  // no further combination
};

/* } */

// specialize content_of
namespace pythonic {

    namespace types {
        template<class T>
            struct content_of< std::tuple<T> > {
                typedef T type;
            };
        template<class T, size_t N>
            struct content_of< array<T,N> > {
                typedef T type;
            };
        template<class T, class... Types>
            struct content_of< std::tuple<T, Types...> > {
                typedef typename std::enable_if<
                    std::is_same<
                    T,
                    typename content_of< std::tuple<Types...> >::type
                        >::value,
                    T
                        >::type	type;
            };
        template<class Ch, class Tr, class Tuple, size_t I>
            void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, utils::int_<I>){
                print_tuple(os, t, utils::int_<I-1>());
                os << ", " << std::get<I>(t);
            }

        template<class Ch, class Tr, class Tuple>
            void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, utils::int_<0>){
                os << std::get<0>(t);
            }

        template<class Ch, class Traits, class... Args>
            std::ostream& operator<<(std::basic_ostream<Ch,Traits>& os,
                    std::tuple<Args...> const& t)
            {
                os << '(';
                print_tuple(os, t, utils::int_<sizeof...(Args)-1>());
                return os << ')';
            }
    }
}



#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/utils/seq.hpp"
#include "pythonic/utils/fwd.hpp"

namespace pythonic {

    template<typename... Types>
        struct python_to_pythran< std::tuple<Types...> >{
            python_to_pythran(){
                static bool registered=false;
                utils::fwd(python_to_pythran<Types>()...);
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< std::tuple<Types...> >());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
                return obj_ptr;
            }

            template<int ...S>
                static void do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, utils::seq<S...>){
                    void* storage=((boost::python::converter::rvalue_from_python_storage<std::tuple<Types...>>*)(data))->storage.bytes;
                    new (storage) std::tuple<Types...>( boost::python::extract< typename std::tuple_element<S-1, std::tuple<Types...> >::type >(PyTuple_GetItem(obj_ptr,S-1))...);
                    data->convertible=storage;
                }

            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                do_construct(obj_ptr, data, typename utils::gens< std::tuple_size<std::tuple<Types...> >::value + 1>::type());
            }
        };

    template<typename T, size_t N>
        struct python_to_pythran< types::array<T, N> >{
            python_to_pythran(){
                static bool registered=false;
                python_to_pythran<T>();
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< types::array<T,N> >());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
                return obj_ptr;
            }

            template<int ...S>
                static void do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, utils::seq<S...>){
                    void* storage=((boost::python::converter::rvalue_from_python_storage<types::array<T,N>>*)(data))->storage.bytes;
                    new (storage) types::array<T,N>{{boost::python::extract<T>(PyTuple_GetItem(obj_ptr,S - 1))...}};
                    data->convertible=storage;
                }

            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                do_construct(obj_ptr, data, typename utils::gens<N + 1>::type());
            }
        };
    template<typename K, typename V>
        struct custom_pair_to_tuple {
            static PyObject* convert(std::pair<K,V> const & t) {
                return PyTuple_Pack(2,
                        boost::python::incref(boost::python::object(t.first).ptr()),
                        boost::python::incref(boost::python::object(t.second).ptr()));
            }
        };

    template<typename K, typename V>
        struct pythran_to_python< std::pair<K,V> > {
            pythran_to_python() {
                pythran_to_python<K>();
                pythran_to_python<V>();
                register_once<std::pair<K,V>, custom_pair_to_tuple<K,V>>();
            }
        };

    template<typename... Types>
        struct custom_tuple_to_tuple {
            template<int ...S>
                static PyObject* do_convert( std::tuple<Types...> const & t, utils::seq<S...>) {
                    return PyTuple_Pack(sizeof...(Types), boost::python::incref(boost::python::object(std::get<S - 1>(t)).ptr())...);
                }
            static PyObject* convert(std::tuple<Types...> const & t) {
                return do_convert(t, typename utils::gens< 1 + sizeof...(Types) >::type());
            }
        };

    template<typename... Types>
        struct pythran_to_python< std::tuple<Types...> > {
            pythran_to_python() {
                utils::fwd(pythran_to_python<Types>()...);
                register_once<std::tuple<Types...>, custom_tuple_to_tuple<Types...>>();
            }
        };

    template<typename T, size_t N>
        struct custom_array_to_tuple {
            static PyObject* convert(types::array<T,N> const & t) {
                size_t n = t.size();
                PyObject* obj = PyTuple_New(n);
                for(size_t i=0; i<n; ++i)
                    PyTuple_SET_ITEM(obj, i, boost::python::incref(boost::python::object(t[i]).ptr()));
                return obj;
            }
        };

    template<typename T, size_t N>
        struct pythran_to_python< types::array<T,N> > {
            pythran_to_python() {
                pythran_to_python<T>();
                register_once<types::array<T,N>, custom_array_to_tuple<T,N>>();
            }
        };

}
#endif

#endif
