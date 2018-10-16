#ifndef TRIGO_FUN
#error missing TRIGO_FUN
#endif

namespace wrapper
{

  inline float TRIGO_FUN(float x)
  {
    return xsimd::TRIGO_FUN(xsimd::batch<float, 1>{x})[0];
  }
  inline double TRIGO_FUN(double x)
  {
    return xsimd::TRIGO_FUN(xsimd::batch<double, 1>{x})[0];
  }

  template <class OtherType>
  auto TRIGO_FUN(OtherType x) -> decltype(xsimd::TRIGO_FUN(x))
  {
    return xsimd::TRIGO_FUN(x);
  }
}
#undef TRIGO_FUN
