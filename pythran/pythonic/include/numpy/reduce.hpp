#ifndef PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP
#define PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP

#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/utils/neutral.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/memory/functions/aligned_store.hpp>
#endif

#include <algorithm>

namespace pythonic {

    namespace numpy {

        template<class Op, size_t N, bool vector_form>
            struct _reduce;

        template<class Op, bool vector_form>
            struct _reduce<Op, 1, vector_form>
            {
                template <class E, class F>
                    F operator()(E e, F acc);
            };

#ifdef USE_BOOST_SIMD
        template<class Op>
            struct _reduce<Op, 1, true>
            {
                template <class E, class F>
                    F operator()(E e, F acc);
            };
#endif

        template<class Op, size_t N, bool vector_form>
            struct _reduce
            {
                template<class E, class F>
                    F operator()(E e, F acc);
            };


        namespace {
            template<class E>
                using reduce_result_type = typename std::conditional<std::is_same<typename E::dtype, bool>::value, long, typename E::dtype>::type;
        }

        template<class Op, class E>
            reduce_result_type<E>
            reduce(E const& expr, types::none_type _ = types::none_type());

        template<class Op, class E>
            auto reduce(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(reduce<Op>(array))>::type;

        namespace {
            template<class E>
                using reduced_type = types::ndarray<typename E::dtype, E::value - 1>;
        }

        template<class Op, class E>
            typename std::enable_if<E::value != 1, reduced_type<E>>::type
            reduce(E const& array, long axis);
    }

}

#endif
