#ifndef UFUNC_NAME
#error missing UFUNC_NAME
#endif

// clang-format off
#include INCLUDE_FILE(pythonic/numpy,UFUNC_NAME)
// clang-format on

namespace pythonic
{
  namespace numpy
  {
    namespace UFUNC_NAME
    {
      template <class T>
      types::ndarray<
          decltype(std::declval<pythonic::numpy::functor::UFUNC_NAME>()(
              std::declval<typename T::dtype>(),
              std::declval<typename T::dtype>())),
          T::value>
      accumulate(T const &a)
      {
        types::ndarray<decltype(
                           std::declval<pythonic::numpy::functor::UFUNC_NAME>()(
                               std::declval<typename T::dtype>(),
                               std::declval<typename T::dtype>())),
                       T::value> res(a.shape(), __builtin__::None);
        std::partial_sum(a.begin(), a.end(), res.begin(),
                         pythonic::numpy::functor::UFUNC_NAME{});
        return res;
      }
      DEFINE_FUNCTOR(pythonic::numpy::UFUNC_NAME, accumulate);
    }
  }
}
