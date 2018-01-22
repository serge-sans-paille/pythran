#ifndef PYTHONIC_BUILTIN_STR_MOD_HPP
#define PYTHONIC_BUILTIN_STR_MOD_HPP

#include "pythonic/__builtin__/str/__mod__.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <boost/format.hpp>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace str
  {

    namespace details
    {
      template <class Tuple>
      void fmt(boost::format &f, Tuple const &a, utils::int_<1>)
      {
        f % std::get<std::tuple_size<Tuple>::value - 1>(a);
      }
      template <class Tuple, size_t I>
      void fmt(boost::format &f, Tuple const &a, utils::int_<I>)
      {
        fmt(f % std::get<std::tuple_size<Tuple>::value - I>(a), a,
            utils::int_<I - 1>());
      }
    }

    template <class T>
    types::str __mod__(types::str const &s, T const &arg)
    {
      const boost::format fmter(s.get_data());
      return (boost::format(fmter) % arg).str();
    }

    template <class... Ts>
    types::str __mod__(types::str const &s, std::tuple<Ts...> const &args)
    {
      boost::format fmter(s.get_data());
      details::fmt(fmter, args, utils::int_<sizeof...(Ts)>());
      return fmter.str();
    }
    template <size_t N, class T>
    types::str __mod__(types::str const &s, types::array<T, N> const &args)
    {
      boost::format fmter(s.get_data());
      details::fmt(fmter, args, utils::int_<N>());
      return fmter.str();
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::str, __mod__);
  }
}
PYTHONIC_NS_END
#endif
