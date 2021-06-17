#ifndef TRIGO_FUN
#error missing TRIGO_FUN
#endif

namespace wrapper
{
  template <class T>

  inline float TRIGO_FUN(float x)
  {
    return xsimd::TRIGO_FUN(xsimd::simd_type<float>{x})[0];
  }
  inline double TRIGO_FUN(double x)
  {
    return xsimd::TRIGO_FUN(xsimd::simd_type<double>{x})[0];
  }

  template <class OtherType>
  auto TRIGO_FUN(OtherType x) -> decltype(xsimd::TRIGO_FUN(x))
  {
    return xsimd::TRIGO_FUN(x);
  }
}
#undef TRIGO_FUN
