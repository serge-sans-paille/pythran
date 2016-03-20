#ifndef PYTHONIC_INCLUDE_TYPES_SLICE_HPP
#define PYTHONIC_INCLUDE_TYPES_SLICE_HPP

#include "pythonic/include/types/NoneType.hpp"

namespace pythonic
{

  namespace types
  {

    struct contiguous_slice;

    struct normalized_slice {
      long lower, upper, step;
      normalized_slice();
      normalized_slice(long lower, long upper, long step = 1);

      template <class S>
      normalized_slice operator*(S const &other) const;

      long size() const;
      inline long get(long i) const;
    };

    struct slice {
      using normalized_type = normalized_slice;

      none<long> lower, upper;
      long step;
      slice(none<long> lower, none<long> upper, none<long> step = 1);
      slice();

      slice operator*(slice const &other) const;

      slice operator*(contiguous_slice const &other) const;

      /*
         Normalize change a[:-1] to a[:len(a)-1] to have positif index.
         It also check for value bigger than len(a) to fit the size of the
         container
         */
      normalized_slice normalize(long max_size) const;

      /*
       * An assert is raised when we can't compute the size without more
       * informations.
       */
      long size() const;

      long get(long i) const;
    };

    struct contiguous_normalized_slice {
      long lower, upper;
      static constexpr long step = 1;
      contiguous_normalized_slice();
      contiguous_normalized_slice(long lower, long upper);

      contiguous_normalized_slice
      operator*(contiguous_normalized_slice const &other) const;
      normalized_slice operator*(normalized_slice const &other) const;

      long size() const;

      inline long get(long i) const;
    };

    struct contiguous_slice {
      using normalized_type = contiguous_normalized_slice;
      long lower;
      none<long> upper;
      static const long step;
      contiguous_slice(none<long> lower, none<long> upper);
      contiguous_slice();

      contiguous_slice operator*(contiguous_slice const &other) const;

      slice operator*(slice const &other) const;

      /*
         Normalize change a[:-1] to a[:len(a)-1] to have positif index.
         It also check for value bigger than len(a) to fit the size of the
         container
         */
      contiguous_normalized_slice normalize(long max_size) const;

      long size() const;

      inline long get(long i) const;
    };

    const long contiguous_slice::step = 1;
  }
}

#endif
