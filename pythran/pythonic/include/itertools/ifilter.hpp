#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IFILTER_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IFILTER_HPP

#include "pythonic/include/utils/iterator.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/itertools/common.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic
{

  namespace itertools
  {

    namespace details
    {

      template <typename Operator, typename List0>
      struct ifilter_iterator : std::iterator<std::forward_iterator_tag,
                                              typename List0::value_type> {
        using sequence_type = typename std::remove_cv<
            typename std::remove_reference<List0>::type>::type;

        Operator op;
        typename List0::iterator iter;
        // FIXME : iter_end should be const because ifilter should be evaluate
        // only once. Some tests doesn't work with it for now because of
        // uncorrect itertools.product implementation
        typename List0::iterator iter_end;

        bool test_filter(std::true_type);
        bool test_filter(std::false_type);

        ifilter_iterator() = default;
        ifilter_iterator(Operator _op, List0 &_seq);
        ifilter_iterator(npos, Operator _op, List0 &_seq);

        typename List0::value_type operator*() const;

        ifilter_iterator &operator++();
        void next_value();

        bool operator==(ifilter_iterator const &other) const;
        bool operator!=(ifilter_iterator const &other) const;
        bool operator<(ifilter_iterator const &other) const;
      };

      // Inherit from iterator_reminder to keep a reference on the iterator
      // and avoid a dangling reference
      // FIXME: It would be better to have a copy only if needed but Pythran
      // typing is not good enough for this as arguments have
      // remove_cv/remove_ref
      template <typename Operator, typename List0>
      struct ifilter : utils::iterator_reminder<false, List0>,
                       ifilter_iterator<Operator, List0> {

        using value_type = typename List0::value_type;
        using iterator = ifilter_iterator<Operator, List0>;

        iterator end_iter;

        ifilter() = default;
        ifilter(Operator _op, List0 const &_seq);

        iterator &begin();
        iterator const &begin() const;
        iterator const &end() const;
      };
    }

    template <typename Operator, typename List0>
    details::ifilter<typename std::remove_cv<
                         typename std::remove_reference<Operator>::type>::type,
                     typename std::remove_cv<
                         typename std::remove_reference<List0>::type>::type>
    ifilter(Operator &&_op, List0 &&_seq);

    DECLARE_FUNCTOR(pythonic::itertools, ifilter);
  }
}
#endif
