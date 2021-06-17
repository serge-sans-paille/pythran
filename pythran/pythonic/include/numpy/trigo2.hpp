#ifndef TRIGO_FUN
#error missing TRIGO_FUN
#endif

namespace wrapper
{
  template <class T>

  inline float TRIGO_FUN(float x, float y)
  {
    return xsimd::TRIGO_FUN(xsimd::simd_type<float>{x},
                            xsimd::simd_type<float>{y})[0];
  }
  inline double TRIGO_FUN(double x, double y)
  {
    return xsimd::TRIGO_FUN(xsimd::simd_type<double>{x},
                            xsimd::simd_type<double>{y})[0];
  }

  template <class OtherType>
  auto TRIGO_FUN(OtherType x, OtherType y) -> decltype(xsimd::TRIGO_FUN(x, y))
  {
    return xsimd::TRIGO_FUN(x, y);
  }
}
#undef TRIGO_FUN
