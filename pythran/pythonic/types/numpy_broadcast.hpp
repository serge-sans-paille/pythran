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
    template<class T>
      struct broadcast_iterator : public std::iterator<std::random_access_iterator_tag, T>
      {
        T const & ref;
        broadcast_iterator(T const& ref) : ref{ref}
        {}

        T const& operator*() const { return ref; }
        broadcast_iterator operator++() { return *this; }
        void next() {}
        long operator-(broadcast_iterator) const { return 0; }
        bool operator!=(broadcast_iterator) const { return true;}
        bool operator==(broadcast_iterator) const { return false;}
        broadcast_iterator operator-=(size_t) const { return *this;}
        bool operator<(broadcast_iterator) const { return true;}
        broadcast_iterator& operator=(broadcast_iterator const& that) {
          assert(&ref == &that.ref);
          return *this;
        }
      };

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
                typedef broadcast_iterator<T> const_iterator;

                T const & ref;
                array<long, value> shape;

                broadcasted(T const& ref, long wide) : ref(ref), shape() {
                    shape[0] = wide;
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
                const_iterator begin() const { return const_iterator(ref); }
                const_iterator end() const { return const_iterator(ref); }
                bool is_broadcasting() const { return false; }

                long size() const { return std::accumulate(shape.begin(), shape.end(), 0L, std::multiplies<long>{});}

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
                std::array<long, 1> const shape;
                typedef broadcast_iterator<dtype> const_iterator;
                const_iterator begin() const { return const_iterator(_value); }
                const_iterator end() const { return const_iterator(_value); }
#ifdef USE_BOOST_SIMD
                boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION> _splated ;
#endif

                broadcast() {}
                broadcast(dtype v, long shape) : _value(v), shape{{shape}}
#ifdef USE_BOOST_SIMD
                                     , _splated(boost::simd::splat<boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(_value))
#endif
                                     { }

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
                long size() const { return shape[0]; }
                bool is_broadcasting() const { return false; }
            };
    }
}

#endif
