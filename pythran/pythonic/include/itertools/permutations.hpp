#ifndef PYTHONIC_INCLUDE_ITERTOOLS_PERMUTATIONS_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_PERMUTATIONS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/__builtin__/range.hpp"

#include <iterator>
#include <vector>
#include <algorithm>

namespace pythonic
{

  namespace itertools
  {
    /** Permutation iterator
     *
     *  It wraps a vector and provide an iteration over every possible
     *  permutation of the vector. The permutations are represented as lists
     *  of elements.
     *
     *  The following iterator:
     *
     *  permutations_iterator([0, 1, 2])
     *
     *  yelds the following suite:
     *
     *  [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
     *
     */
    template <class T>
    struct permutations_iterator
        : std::iterator<std::forward_iterator_tag,
                        types::list<typename T::value_type>, ptrdiff_t,
                        types::list<typename T::value_type> *,
                        types::list<typename T::value_type> /* no ref*/
                        > {
      // Vector of inputs, contains elements to permute
      std::vector<typename T::value_type> pool;

      // The current permutation as a list of index in the pool
      // Internally it always has the same size as the pool, even if the
      // external view is limited
      types::list<int> curr_permut;

      // Size of the "visible" permutation
      size_t _size;
      bool end; // sentinel marker

      permutations_iterator();
      permutations_iterator(std::vector<typename T::value_type> const &iter,
                            size_t num_elts, bool end);

      /** Build the permutation visible from the "outside" */
      types::list<typename T::value_type> operator*() const;

      /*  Generate next permutation
       *
       *  If the size of the permutation is smaller than the size of the
       *  pool, we may have to iterate multiple times
       */
      permutations_iterator &operator++();
      bool operator!=(permutations_iterator const &other) const;
      bool operator==(permutations_iterator const &other) const;
      bool operator<(permutations_iterator const &other) const;
    };

    template <class T>
    // FIXME document why this inheritance???
    struct _permutations : permutations_iterator<T> {
      using value_type = T;
      using iterator = permutations_iterator<T>;

      _permutations();
      _permutations(T iter, int elts);

      iterator const &begin() const;
      iterator begin();
      iterator end() const;
    };

    template <typename T0>
    _permutations<T0> permutations(T0 iter, int num_elts);

    template <typename T0>
    _permutations<T0> permutations(T0 iter);

    DECLARE_FUNCTOR(pythonic::itertools, permutations);
  }
}

#endif
