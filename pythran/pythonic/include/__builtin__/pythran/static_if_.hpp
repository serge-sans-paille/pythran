#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/pythran/is_none.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    namespace details
    {
      template <class IsSame>
      struct static_if_;

      template <>
      struct static_if_<types::true_type> {
        static_if_(types::true_type)
        {
        }
        template <class F0, class F1>
        F0 operator()(F0 f0, F1 f1)
        {
          return f0;
        }
      };
      template <>
      struct static_if_<types::false_type> {
        static_if_(types::false_type)
        {
        }
        template <class F0, class F1>
        F1 operator()(F0 f0, F1 f1)
        {
          return f1;
        }
      };
      template <>
      struct static_if_<bool> {
        bool state_;
        static_if_(bool state) : state_(state)
        {
        }

        template <class F0, class F1>
        struct merged {
          bool state_;
          F0 f0;
          F1 f1;
          merged(bool state, F0 f0, F1 f1) : state_(state), f0(f0), f1(f1)
          {
          }
          template <class... Args>
          auto operator()(Args &&... args) const -> typename __combined<
              decltype(f0(std::forward<Args>(args)...)),
              decltype(f1(std::forward<Args>(args)...))>::type
          {
            if (state_)
              return f0(std::forward<Args>(args)...);
            else
              return f1(std::forward<Args>(args)...);
          }
        };

        template <class F0, class F1>
        merged<F0, F1> operator()(F0 f0, F1 f1)
        {
          return {state_, f0, f1};
        }
      };
    }
    template <class T, class F0, class F1>
    auto static_if_(T const &cond, F0 f0, F1 f1)
        -> decltype(details::static_if_<T>{cond}(f0, f1));

    template <class F0, class F1>
    auto static_if_(int const &cond, F0 f0, F1 f1)
        -> decltype(details::static_if_<bool>{(bool)cond}(f0, f1))
    {
      return details::static_if_<bool>{(bool)cond}(f0, f1);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::pythran, static_if_);
  }
}
PYTHONIC_NS_END

#endif
