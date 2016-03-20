#ifndef PYTHONIC_ITERTOOLS_IFILTER_HPP
#define PYTHONIC_ITERTOOLS_IFILTER_HPP

#include "pythonic/include/itertools/ifilter.hpp"
#include "pythonic/utils/iterator.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/itertools/common.hpp"
#include "pythonic/utils/functor.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic
{

  namespace itertools
  {

    namespace details
    {
      template <typename Operator, typename List0>
      bool ifilter_iterator<Operator, List0>::test_filter(std::false_type)
      {
        return op(*iter);
      }

      template <typename Operator, typename List0>
      bool ifilter_iterator<Operator, List0>::test_filter(std::true_type)
      {
        return *iter;
      }

      template <typename Operator, typename List0>
      ifilter_iterator<Operator, List0>::ifilter_iterator(Operator _op,
                                                          List0 &_seq)
          : op(_op), iter(_seq.begin()), iter_end(_seq.end())
      {
        if (!test_filter(std::is_same<types::none_type, Operator>()))
          next_value();
      }

      template <typename Operator, typename List0>
      ifilter_iterator<Operator, List0>::ifilter_iterator(npos, Operator _op,
                                                          List0 &_seq)
          : op(_op), iter(_seq.end()), iter_end(_seq.end())
      {
      }

      template <typename Operator, typename List0>
      typename List0::value_type ifilter_iterator<Operator, List0>::
      operator*() const
      {
        return *iter;
      }

      template <typename Operator, typename List0>
      ifilter_iterator<Operator, List0> &ifilter_iterator<Operator, List0>::
      operator++()
      {
        next_value();
        return *this;
      }

      template <typename Operator, typename List0>
      void ifilter_iterator<Operator, List0>::next_value()
      {
        while (++iter != iter_end) {
          if (test_filter(std::is_same<types::none_type, Operator>()))
            return;
        }
      }

      template <typename Operator, typename List0>
      bool ifilter_iterator<Operator, List0>::
      operator==(ifilter_iterator const &other) const
      {
        return !(iter != other.iter);
      }

      template <typename Operator, typename List0>
      bool ifilter_iterator<Operator, List0>::
      operator!=(ifilter_iterator const &other) const
      {
        return iter != other.iter;
      }

      template <typename Operator, typename List0>
      bool ifilter_iterator<Operator, List0>::
      operator<(ifilter_iterator const &other) const
      {
        return iter != other.iter;
      }

      template <typename Operator, typename List0>
      ifilter<Operator, List0>::ifilter(Operator _op, List0 const &_seq)
          : utils::iterator_reminder<false, List0>(_seq),
            iterator(_op, this->value), end_iter(npos(), _op, this->value)
      {
      }

      template <typename Operator, typename List0>
      typename ifilter<Operator, List0>::iterator &
      ifilter<Operator, List0>::begin()
      {
        return *this;
      }

      template <typename Operator, typename List0>
      typename ifilter<Operator, List0>::iterator const &
      ifilter<Operator, List0>::begin() const
      {
        return *this;
      }

      template <typename Operator, typename List0>
      typename ifilter<Operator, List0>::iterator const &
      ifilter<Operator, List0>::end() const
      {
        return end_iter;
      }
    }

    template <typename Operator, typename List0>
    details::ifilter<typename std::remove_cv<
                         typename std::remove_reference<Operator>::type>::type,
                     typename std::remove_cv<
                         typename std::remove_reference<List0>::type>::type>
    ifilter(Operator &&_op, List0 &&_seq)
    {
      return {std::forward<Operator>(_op), std::forward<List0>(_seq)};
    }

    DEFINE_FUNCTOR(pythonic::itertools, ifilter);
  }
}
#endif
