#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_BROADCAST_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_BROADCAST_HPP

#include <array>

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include "pythonic/types/vectorizable_type.hpp"

namespace pythonic {

    namespace types {

        /* Type adaptor for broadcasted array values
         *
         * Used when the args of a binary operator do not have the same dimensions:
         * in that case their first dimension always yields a copy
         */
        template<class T>
            struct broadcasted
            {
                static const bool is_vectorizable = false;
                static const bool is_strided = false;
                using dtype = typename T::dtype;
                using value_type = typename T::value_type;
                static constexpr size_t value = T::value + 1;

                T const & ref;
                array<long, value> _shape;
                array<long, value> const& shape() const;

                broadcasted(T const& ref);

                T const & operator[](long i) const;
                T const & fast(long i) const;
#ifdef USE_BOOST_SIMD
                template<class I> // template to prevent automatic instantiation, but the declaration is still needed
                    void load(I) const;
#endif

                long flat_size() const;

            };

        /* Type adaptor for scalar values
         *
         * Have them behave like infinite arrays of that value
         *
         * B is the original type of the broadcast value, and T is the type of the expression it is combined with
         * if both B and T are integer types, we choose T instead of B to prevent automatic conversion into larger types
         *
         * That way, np.ones(10, dtype=np.uint8) + 1 yields an array of np.uint8, although 1 is of type long
         */
        template<class dtype, bool is_vectorizable>
            struct broadcast_base
            {
                dtype _value;
                template<class V>
                    broadcast_base(V v);
                template<class I>
                    void load(I) const;
            };

#ifdef USE_BOOST_SIMD
        template<class dtype>
            struct broadcast_base<dtype, true>
            {
                dtype _value;
                boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION> _splated ;
                template<class V>
                    broadcast_base(V v);
                template<class I>
                    auto load(I) const
                    -> decltype(this -> _splated);
            };
#endif

        template<class T, class B>
            struct broadcast
            {
                // Perform the type conversion here if it seems valid (although it is not always)
                using dtype = typename std::conditional<std::is_integral<T>::value and std::is_integral<B>::value,
                                                        T,
                                                        typename __combined<T, B>::type>::type;
                static const bool is_vectorizable = types::is_vectorizable<dtype>::value;
                static const bool is_strided = false;
                using value_type = dtype;
                static constexpr size_t value = 0;

                broadcast_base<dtype, is_vectorizable> _base;

                broadcast() = default;
                template<class V>
                    broadcast(V v);

                dtype operator[](long ) const;
                dtype fast(long ) const;
                template<class I>
                    auto load(I i) const
                    -> decltype(this -> _base.load(i));
                long flat_size() const;
            };
    }
}

#endif
