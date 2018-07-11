#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <iterator>
#include <type_traits>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace anonymous
  {

    inline types::empty_list list();
    inline types::empty_list list(types::empty_list);

    template <class Iterable>
    types::list<typename std::decay<typename std::iterator_traits<
        typename std::remove_reference<Iterable>::type::iterator>::value_type>::
                    type>
    list(Iterable &&t);
  }

  DEFINE_FUNCTOR(pythonic::__builtin__::anonymous, list);
}
PYTHONIC_NS_END

#endif
