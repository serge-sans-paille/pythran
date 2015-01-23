#ifndef PYTHONIC_TYPES_NUMPY_BROADCAST_HPP
#define PYTHONIC_TYPES_NUMPY_BROADCAST_HPP

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
            struct broadcasted {
                static const bool is_vectorizable = false;
                static const bool is_strided = false;
                typedef typename T::dtype dtype;
                typedef typename T::value_type value_type;
                static constexpr size_t value = T::value + 1;

                T const & ref;
                std::array<long, value> shape;

                broadcasted(T const& ref) : ref(ref), shape() {
                    shape[0] = 1;
                    std::copy(ref.shape.begin(), ref.shape.end(), shape.begin() + 1);
                }

                T const & operator[](long i) const { return ref;}
                T const & fast(long i) const { return ref;}
#ifdef USE_BOOST_SIMD
                template<class I> // template to prevent automatic instantiation, but the declaration is still needed
                void load(I) const {
                  typedef typename T::this_should_never_happen omg;
                }
#endif

                long flat_size() const { return 0;}

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
        template<class T, class B>
            struct broadcast {
                // Perform the type conversion here if it seems valid (although it is not always)
                typedef typename std::conditional<std::numeric_limits<T>::is_integer and std::numeric_limits<B>::is_integer,
                                          T,
                                          typename __combined<T, B>::type>::type dtype;
                static const bool is_vectorizable = types::is_vectorizable<dtype>::value;
                static const bool is_strided = false;
                typedef dtype value_type;
                static constexpr size_t value = 0;
                dtype _value;
#ifdef USE_BOOST_SIMD
                boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION> _splated ;
#endif

                broadcast() {}
                broadcast(dtype v) : _value(v)
#ifdef USE_BOOST_SIMD
                                     , _splated(boost::simd::splat<boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(_value))
#endif
                                     {}

                dtype operator[](long ) const {
                    return _value;
                }
                dtype fast(long ) const {
                    return _value;
                }
#ifdef USE_BOOST_SIMD
                template<class I>
                auto load(I) const -> decltype(this -> _splated) { return _splated; }
#endif
                long flat_size() const { return 0; }
            };
    }
}

#endif
