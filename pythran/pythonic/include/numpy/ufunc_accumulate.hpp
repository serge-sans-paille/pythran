#ifndef UFUNC_NAME
#error missing UFUNC_NAME
#endif

// clang-format off
#include INCLUDE_FILE(pythonic/include/numpy,UFUNC_NAME)
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
      accumulate(T const &a);
      DECLARE_FUNCTOR(pythonic::numpy::UFUNC_NAME, accumulate);
    }
  }
}
