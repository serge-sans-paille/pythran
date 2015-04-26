#ifndef PYTHONIC_TYPES_TUPLE_HPP
#define PYTHONIC_TYPES_TUPLE_HPP

#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/types/list.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/seq.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <tuple>
#include <algorithm>

namespace std {
    template<class F0, class S0, class F1, class S1>
        bool operator==(pair<F0,S0> const& self, tuple<F1,S1> const& other)
        {
            return self.first == get<0>(other) and self.second == get<1>(other);
        }
    template<class F0, class S0, class F1, class S1>
        bool operator==(pair<const F0,S0> const& self, tuple<F1,S1> const& other)
        {
            return self.first == get<0>(other) and self.second == get<1>(other);
        }
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...>
operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> const& t1)
{
    return std::tuple_cat(t0, t1);
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...>
operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> const& t1)
{
    return std::tuple_cat(std::forward<Types0...>(t0), t1);
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...>
operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> && t1)
{
    return std::tuple_cat(t0, std::forward<Types1...>(t1));
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...>
operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> && t1)
{
    return std::tuple_cat(std::forward<Types0...>(t0), std::forward<Types1...>(t1));
}


namespace pythonic {

    namespace types {

        namespace details {
            template<class E, size_t Value> void init_shape(array<long, Value>& res, E const& e, utils::int_<1>) {
              res[Value - 1] = e.size();
            }
            template<class E, size_t Value, size_t L> void init_shape(array<long, Value>& res, E const& e, utils::int_<L>) {
              res[Value - L] = e.size();
              init_shape(res, e[0], utils::int_<L-1>{});
            }
        }


        /* helper to extract the tail of a tuple, and pop the head
         */
        template<int Offset, class T, int... N>
            auto make_tuple_tail(T const& t, utils::seq<N...>)
            -> decltype(std::make_tuple(std::get<Offset + 1 + N>(t)...))
            {
                return std::make_tuple(std::get<Offset + 1 + N>(t)...);
            }

        template<class S, class... Stail>
            std::tuple<Stail...>
            tuple_tail(std::tuple<S, Stail...> const& t)
            {
                return make_tuple_tail<0>(t, typename utils::gens<sizeof...(Stail)>::type{});
            }

        template<class S, class... Stail>
            auto tuple_pop(std::tuple<S, Stail...> const& t)
            -> decltype(make_tuple_tail<count_trailing_long<Stail...>::value>(t, typename utils::gens<sizeof...(Stail) - count_trailing_long<Stail...>::value>::type{}))
            {
                return make_tuple_tail<count_trailing_long<Stail...>::value>(t, typename utils::gens<sizeof...(Stail) - count_trailing_long<Stail...>::value>::type{});
            }

        template<class A, int... I>
          auto array_to_tuple(A const& a, utils::seq<I...>) -> decltype(std::make_tuple(a[I-1]...)) {
            return std::make_tuple(a[I-1]...);
          }

        /* inspired by std::array implementation */
        template<typename T, size_t N>
        template<class E>
            long array<T, N>::_flat_size(E const& e, utils::int_<1>) const
            {
                return N;
            }

        template<typename T, size_t N>
        template<class E, size_t L>
            long array<T, N>::_flat_size(E const& e, utils::int_<L>) const
            {
                return N * _flat_size(e[0], utils::int_<L-1>{});
            }

        template<typename T, size_t N>
            long array<T, N>::flat_size() const
            {
                return _flat_size(*this, utils::int_<value>{});
            }

        template<typename T, size_t N>
            void array<T, N>::fill(const value_type& __u)
            {
                std::fill_n(begin(), size(), __u);
            }

        // Iterators.
        template<typename T, size_t N>
            typename array<T, N>::iterator array<T, N>::begin() noexcept
            {
                return typename array<T, N>::iterator(data());
            }

        template<typename T, size_t N>
            typename array<T, N>::const_iterator
            array<T, N>::begin() const noexcept
            {
                return typename array<T, N>::const_iterator(data());
            }

        template<typename T, size_t N>
            typename array<T, N>::iterator array<T, N>::end() noexcept
            {
                return typename array<T, N>::iterator(data() + N);
            }

        template<typename T, size_t N>
            typename array<T, N>::const_iterator
            array<T, N>::end() const noexcept
            {
                return typename array<T, N>::const_iterator(data() + N);
            }

        template<typename T, size_t N>
            typename array<T, N>::reverse_iterator 
            array<T, N>::rbegin() noexcept
            {
                return typename array<T, N>::reverse_iterator(end());
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reverse_iterator 
            array<T, N>::rbegin() const noexcept
            {
                return typename array<T, N>::const_reverse_iterator(end());
            }

        template<typename T, size_t N>
            typename array<T, N>::reverse_iterator 
            array<T, N>::rend() noexcept
            {
                return typename array<T, N>::reverse_iterator(begin());
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reverse_iterator 
            array<T, N>::rend() const noexcept
            {
                return typename array<T, N>::const_reverse_iterator(begin());
            }

        template<typename T, size_t N>
            typename array<T, N>::const_iterator
            array<T, N>::cbegin() const noexcept
            {
                return typename array<T, N>::const_iterator(&(buffer[0]));
            }

        template<typename T, size_t N>
            typename array<T, N>::const_iterator
            array<T, N>::cend() const noexcept
            {
                return typename array<T, N>::const_iterator(&(buffer[N]));
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reverse_iterator 
            array<T, N>::crbegin() const noexcept
            {
                return typename array<T, N>::const_reverse_iterator(end());
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reverse_iterator 
            array<T, N>::crend() const noexcept
            {
                return typename array<T, N>::const_reverse_iterator(begin());
            }

        // Capacity.
        template<typename T, size_t N>
            constexpr typename array<T, N>::size_type
            array<T, N>:: size() const noexcept
            {
                return N;
            }

        template<typename T, size_t N>
            constexpr typename array<T, N>::size_type 
            array<T, N>::max_size() const noexcept
            {
                return N;
            }

        template<typename T, size_t N>
            constexpr bool array<T, N>::empty() const noexcept
            {
                return size() == 0;
            }

        // Element access.
        template<typename T, size_t N>
            typename array<T, N>::reference array<T, N>::fast(long n)
            {
                return buffer[n];
            }

        template<typename T, size_t N>
            constexpr typename array<T, N>::const_reference
            array<T, N>::fast(long n) const noexcept
            {
                return buffer[n];
            }

#ifdef USE_BOOST_SIMD
        template<typename T, size_t N>
            auto array<T, N>::load(long i) const
            -> decltype(boost::simd::load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(&buffer[0], i))
            {
                return boost::simd::load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(&buffer[0], i);
            }

        template<typename T, size_t N>
        template<class V>
            void array<T, N>::store(V &&v, long i)
            {
                boost::simd::store(v, &buffer[0], i);
            }
#endif

        template<typename T, size_t N>
            typename array<T, N>::reference
            array<T, N>::operator[](typename array<T, N>::size_type __n)
            {
                return buffer[__n];
            }

        template<typename T, size_t N>
            typename array<T, N>::reference
            array<T, N>::fast(typename array<T, N>::size_type __n)
            {
                return buffer[__n];
            }

        template<typename T, size_t N>
            constexpr typename array<T, N>::const_reference
            array<T, N>::operator[](typename array<T, N>::size_type __n) const noexcept
            {
                return buffer[__n];
            }

        template<typename T, size_t N>
            constexpr typename array<T, N>::const_reference
            array<T, N>::fast(typename array<T, N>::size_type __n) const noexcept
            {
                return buffer[__n];
            }

        template<typename T, size_t N>
            typename array<T, N>::reference array<T, N>::front()
            {
                return *begin();
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reference 
            array<T, N>::front() const
            {
                return *begin();
            }

        template<typename T, size_t N>
            typename array<T, N>::reference array<T, N>::back()
            {
                return N ? *(end() - 1) : *end();
            }

        template<typename T, size_t N>
            typename array<T, N>::const_reference array<T, N>::back() const
            {
                return N ? *(end() - 1) : *end();
            }

        template<typename T, size_t N>
            typename array<T, N>::pointer array<T, N>::data() noexcept
            {
                return &(buffer[0]);
            }

        template<typename T, size_t N>
            typename array<T, N>::const_pointer
            array<T, N>::data() const noexcept
            {
                return &(buffer[0]);
            }

        template<typename T, size_t N>
        template<size_t M>
            bool array<T, N>::operator==(array<T, M> const& other) const
            {
                return N == M and std::equal(begin(), end(), other.begin()); 
            }

        template<typename T, size_t N>
        template<size_t M>
            bool array<T, N>::operator<(array<T, M> const& other) const
            {
                return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
            }

        template<typename T, size_t N>
        template<size_t M>
            array<T, N + M> array<T, N>::operator+(array<T, M> const& other) const
            {
                array<T, N + M> result;
                auto next = std::copy(begin(), end(), result.begin());
                std::copy(other.begin(), other.end(), next);
                return result;
            }
        template<typename T, size_t N>
        template<class... Types>
            array<T, N>::operator std::tuple<Types...>() const {
                return array_to_tuple(*this, typename utils::gens<N+1>::type{});
            }

        template<typename T, size_t N>
            auto array<T, N>::to_tuple() const -> decltype(array_to_tuple(*this, typename utils::gens<N+1>::type{})) {
                return array_to_tuple(*this, typename utils::gens<N+1>::type{});
            }

        /* array */
        template<class T, size_t N>
            std::ostream& operator<<(std::ostream& os, types::array<T, N> const & v)
            {
                os << '(';
                auto iter = v.begin();
                if(iter != v.end())
                {
                    while(iter+1 != v.end())
                        os << *iter++ << ", ";
                    os << *iter;
                }
                return os << ')';
            }

        template<typename T, size_t N>
            array<long, array<T,N>::value> array<T,N>::shape() const {
                array<long, value> res;
                details::init_shape(res, *this, utils::int_<value>{});
                return res;
            }

        template<bool Same, class... Types>
            auto _make_tuple<Same, Types...>::operator()(Types&&... types)
            -> decltype(std::make_tuple(std::forward<Types>(types)...))
            {
                return std::make_tuple(std::forward<Types>(types)...);
            }

        template<class... Types>
            types::array<typename alike<Types...>::type, sizeof...(Types)>
            _make_tuple<true, Types...>::operator()(Types &&... types)
            {
                return {{std::forward<Types>(types)...}};
            }


        template<class... Types>
            auto make_tuple(Types&&... types)
            -> decltype(_make_tuple<alike<Types...>::value, Types...>()(std::forward<Types>(types)...))
            {
                return _make_tuple<alike<Types...>::value, Types...>()(std::forward<Types>(types)...);
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

}

/* specialize std::get */
namespace std {
    template <size_t I, class T, size_t N>
        typename pythonic::types::array<T,N>::reference
        get(pythonic::types::array<T,N>& t)
        {
            return t[I];
        }

    template <size_t I, class T, size_t N>
        typename pythonic::types::array<T,N>::const_reference
        get(pythonic::types::array<T,N> const & t)
        {
            return t[I];
        }

}


/* hashable tuples, as proposed in http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set */
namespace {

    inline size_t hash_combiner(size_t left, size_t right) //replacable
    {
        return left^right;
    }

    template<size_t index, class...types>
        size_t hash_impl<index, types...>::operator()(size_t a, const std::tuple<types...>& t) const
        {
            using nexttype = typename std::tuple_element<index, std::tuple<types...>>::type;
            hash_impl<index-1, types...> next;
            size_t b = std::hash<nexttype>()(std::get<index>(t));
            return next(hash_combiner(a, b), t);
        }

    template<class...types>
        size_t hash_impl<0, types...>::operator()(size_t a, const std::tuple<types...>& t) const
        {
            using nexttype = typename std::tuple_element<0, std::tuple<types...>>::type;
            size_t b = std::hash<nexttype>()(std::get<0>(t));
            return hash_combiner(a, b);
        }
}


/* specialize std::hash */
namespace std {
    template<class...Types>
        size_t hash<std::tuple<Types...>>::operator()(std::tuple<Types...> const& t) const
        {
            const size_t begin = std::tuple_size<std::tuple<Types...>>::value-1;
            return hash_impl<begin, Types...>()(1, t); //1 should be some largervalue
        }

    template<class T, size_t N>
        size_t hash<pythonic::types::array<T,N>>::operator()(pythonic::types::array<T,N> const& l) const
        {
            size_t seed = 0;
            hash<T> h;
            for(auto const &iter: l)
                seed ^= h(iter) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
}

#include <boost/functional/hash/extensions.hpp>

/* and boost's */
namespace pythonic {
    namespace types {
#ifdef BOOST_NO_CXX11_HDR_TUPLE
        template<class... Types>
            std::size_t hash_value(std::tuple<Types...>  const &x)
            {
                return std::hash<std::tuple<Types...>>()(x);
            }
#endif
        template<class T, size_t N>
            std::size_t hash_value(pythonic::types::array<T,N>  const &x)
            {
                return std::hash<pythonic::types::array<T,N>>()(x);
            }
    }
}

namespace pythonic {

    namespace types {
        template<class Ch, class Tr, class Tuple, size_t I>
            void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, utils::int_<I>)
            {
                print_tuple(os, t, utils::int_<I-1>());
                os << ", " << std::get<I>(t);
            }

        template<class Ch, class Tr, class Tuple>
            void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, utils::int_<0>)
            {
                os << std::get<0>(t);
            }

        template<class Ch, class Traits, class... Args>
            std::ostream& operator<<(std::basic_ostream<Ch,Traits>& os, std::tuple<Args...> const& t)
            {
                os << '(';
                print_tuple(os, t, utils::int_<sizeof...(Args)-1>());
                return os << ')';
            }
    }
}


#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include "pythonic/python/extract.hpp"
#include "pythonic/utils/seq.hpp"
#include "pythonic/utils/fwd.hpp"

namespace pythonic {

    template<typename... Types>
        python_to_pythran< std::tuple<Types...> >::python_to_pythran()
        {
            static bool registered=false;
            utils::fwd(python_to_pythran<Types>()...);
            if(not registered) {
                registered = true;
                boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< std::tuple<Types...> >());
            }
        }

    template<typename... Types>
        void* python_to_pythran< std::tuple<Types...> >::convertible(PyObject* obj_ptr)
        {
            if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__"))
                return 0;
            return obj_ptr;
        }

    template<typename... Types>
    template<int ...S>
        void python_to_pythran< std::tuple<Types...> >::do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, utils::seq<S...>)
        {
            void* storage=((boost::python::converter::rvalue_from_python_storage<std::tuple<Types...>>*)(data))->storage.bytes;
            new (storage) std::tuple<Types...>( boost::python::extract< typename std::tuple_element<S, std::tuple<Types...> >::type >(PyTuple_GetItem(obj_ptr,S))...);
            data->convertible=storage;
        }

    template<typename... Types>
        void python_to_pythran< std::tuple<Types...> >::construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            do_construct(obj_ptr, data, typename utils::gens< std::tuple_size<std::tuple<Types...> >::value>::type());
        }

    template<typename T, size_t N>
        python_to_pythran< types::array<T, N> >::python_to_pythran()
        {
            static bool registered=false;
            python_to_pythran<T>();
            if(not registered)
            {
                registered=true;
                boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< types::array<T,N> >());
            }
        }

    template<typename T, size_t N>
        void* python_to_pythran< types::array<T, N> >::convertible(PyObject* obj_ptr)
        {
            if(!PyTuple_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__"))
                return 0;
            return obj_ptr;
        }

    template<typename T, size_t N>
    template<int ...S>
        void python_to_pythran< types::array<T, N> >::do_construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data, utils::seq<S...>)
        {
            void* storage=((boost::python::converter::rvalue_from_python_storage<types::array<T,N>>*)(data))->storage.bytes;
            new (storage) types::array<T,N>{{boost::python::extract<T>(PyTuple_GetItem(obj_ptr,S))...}};
            data->convertible=storage;
        }

    template<typename T, size_t N>
        void python_to_pythran< types::array<T, N> >::construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            do_construct(obj_ptr, data, typename utils::gens<N>::type());
        }

    template<typename K, typename V>
        PyObject* custom_pair_to_tuple<K, V>::convert(std::pair<K,V> const & t)
        {
            return PyTuple_Pack(2,
                    boost::python::incref(boost::python::object(t.first).ptr()),
                    boost::python::incref(boost::python::object(t.second).ptr()));
        }

    template<typename K, typename V>
        pythran_to_python< std::pair<K,V> >::pythran_to_python()
        {
            pythran_to_python<K>();
            pythran_to_python<V>();
            register_once<std::pair<K,V>, custom_pair_to_tuple<K,V>>();
        }

    template<typename... Types>
    template<int ...S>
        PyObject* custom_tuple_to_tuple<Types...>::do_convert( std::tuple<Types...> const & t, utils::seq<S...>)
        {
            return PyTuple_Pack(sizeof...(Types), boost::python::incref(boost::python::object(std::get<S>(t)).ptr())...);
        }

    template<typename... Types>
        PyObject* custom_tuple_to_tuple<Types...>::convert(std::tuple<Types...> const & t)
        {
            return do_convert(t, typename utils::gens<sizeof...(Types) >::type());
        }

    template<typename... Types>
        pythran_to_python< std::tuple<Types...> >::pythran_to_python()
        {
            utils::fwd(pythran_to_python<Types>()...);
            register_once<std::tuple<Types...>, custom_tuple_to_tuple<Types...>>();
        }

    template<typename T, size_t N>
        PyObject* custom_array_to_tuple<T, N>::convert(types::array<T,N> const & t)
        {
            size_t n = t.size();
            PyObject* obj = PyTuple_New(n);
            for(size_t i=0; i<n; ++i)
                PyTuple_SET_ITEM(obj, i, boost::python::incref(boost::python::object(t[i]).ptr()));
            return obj;
        }

    template<typename T, size_t N>
        pythran_to_python< types::array<T,N> >::pythran_to_python()
        {
            pythran_to_python<T>();
            register_once<types::array<T,N>, custom_array_to_tuple<T,N>>();
        }
}
#endif

#endif
