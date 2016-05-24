#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_FEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_FEXPR_HPP

#include "pythonic/include/types/nditerator.hpp"

namespace pythonic
{

  namespace types
  {

    /* Expression template for numpy expressions - filter
     */
    template <class Arg, class F>
    // numpy_fexpr is a wrapper around a ndarray. It stores raw indices of
    // values
    // where filters information is True so that we can jump to the correct
    // value
    // in the ndarray buffer in O(1)
    struct numpy_fexpr {
      static const bool is_vectorizable = false;
      static const bool is_strided = true;
      // TODO accept multidimensionnal filtered expression
      //>>> a = numpy.arange(2*3*4).reshape(2,3,4)
      // array([[[ 0,  1,  2,  3],
      //        [ 4,  5,  6,  7],
      //        [ 8,  9, 10, 11]],
      //       [[12, 13, 14, 15],
      //        [16, 17, 18, 19],
      //        [20, 21, 22, 23]]])
      //>>> a[[0,1],[0,1], [0, 0]]
      // array([ 0, 16])
      static constexpr size_t value = 1;
      using value_type = typename std::remove_reference<Arg>::type::dtype;
      using dtype = typename std::remove_reference<Arg>::type::dtype;

      using iterator = nditerator<numpy_fexpr>;
      using const_iterator = const_nditerator<numpy_fexpr>;

      typename assignable<typename std::remove_reference<Arg>::type>::type arg;
      array<long, value> _shape;
      array<long, value> const &shape() const;
      utils::shared_ref<raw_array<long>> indices;
      long *buffer;

      numpy_fexpr() = default;
      numpy_fexpr(numpy_fexpr const &) = default;
      numpy_fexpr(numpy_fexpr &&) = default;
      numpy_fexpr(Arg const &arg, F const &filter);

      template <class FIter, class O>
      void _copy_mask(FIter fiter, FIter fend, O &out, long &index,
                      utils::int_<1>);

      template <class FIter, class O, size_t N>
      void _copy_mask(FIter fiter, FIter fend, O &out, long &index,
                      utils::int_<N>);

      template <class E>
      typename std::enable_if<is_iterable<E>::value, numpy_fexpr &>::type
      operator=(E const &expr);

      template <class E>
      typename std::enable_if<not is_iterable<E>::value, numpy_fexpr &>::type
      operator=(E const &expr);

      numpy_fexpr &operator=(numpy_fexpr const &expr);

      template <class E>
      numpy_fexpr &operator+=(E const &expr);

      template <class E>
      numpy_fexpr &operator-=(E const &expr);

      template <class E>
      numpy_fexpr &operator*=(E const &expr);

      template <class E>
      numpy_fexpr &operator/=(E const &expr);

      template <class E>
      numpy_fexpr &operator&=(E const &expr);

      template <class E>
      numpy_fexpr &operator|=(E const &expr);

      template <class E>
      numpy_fexpr &operator>>=(E const &expr);

      template <class E>
      numpy_fexpr &operator<<=(E const &expr);

      const_iterator begin() const;
      const_iterator end() const;

      iterator begin();
      iterator end();

      dtype fast(long i) const;
      dtype &fast(long i);
#ifdef USE_BOOST_SIMD
      using simd_iterator = const_simd_nditerator<numpy_fexpr>;
      simd_iterator vbegin() const;
      simd_iterator vend() const;
      template <class I> // template to prevent automatic instantiation when the
      // type is not vectorizable
      void load(I) const;
#endif
      auto operator[](long i) const -> decltype(this->fast(i));
      auto operator[](long i) -> decltype(this->fast(i));

      template <class E>
      typename std::enable_if<is_numexpr_arg<E>::value,
                              numpy_fexpr<numpy_fexpr, E>>::type
      fast(E const &expr) const;

      template <class E>
      typename std::enable_if<is_numexpr_arg<E>::value,
                              numpy_fexpr<numpy_fexpr, E>>::type
      operator[](E const &expr) const;

      long flat_size() const;
    };
  }

  template <class Arg, class F>
  struct assignable<types::numpy_fexpr<Arg, F>> {
    using type = types::ndarray<typename types::numpy_fexpr<Arg, F>::dtype,
                                types::numpy_fexpr<Arg, F>::value>;
  };

  template <class Arg, class F>
  struct lazy<types::numpy_fexpr<Arg, F>> {
    using type =
        types::numpy_fexpr<typename lazy<Arg>::type, typename lazy<F>::type>;
  };
}

#endif
