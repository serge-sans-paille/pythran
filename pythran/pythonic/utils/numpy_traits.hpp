#ifndef PYTHONIC_UTILS_NUMPY_TRAITS_HPP
#define PYTHONIC_UTILS_NUMPY_TRAITS_HPP

namespace pythonic {
    namespace types {

        template<class T, size_t N>
            class ndarray;

        template<class A>
            class numpy_iexpr;

        template<class A, class F>
            class numpy_fexpr;

        template<class A, class ...S>
            class numpy_gexpr;

        template<class A>
            class numpy_texpr;
        template<class A>
            class numpy_texpr_2;

        template<class O, class A0, class A1>
            class numpy_expr;

        template<class T>
            class list;

        template<class T>
            struct is_ndarray {
              static constexpr bool value = false;
            };
        template<class T, size_t N>
          struct is_ndarray<ndarray<T,N>> {
            static constexpr bool value = true;
          };

        /* Type trait that checks if a type is a potential numpy expression parameter
         *
         * Only used to write concise expression templates
         */
        template<class T>
          struct is_array {
            static constexpr bool value = false;
          };
        template<class T, size_t N>
          struct is_array<ndarray<T,N>> {
            static constexpr bool value = true;
          };
        template<class A>
          struct is_array<numpy_iexpr<A>> {
            static constexpr bool value = true;
          };
        template<class A, class F>
          struct is_array<numpy_fexpr<A,F>> {
            static constexpr bool value = true;
          };
        template<class A, class... S>
          struct is_array<numpy_gexpr<A,S...>> {
            static constexpr bool value = true;
          };
        template<class A>
          struct is_array<numpy_texpr<A>> {
            static constexpr bool value = true;
          };
        template<class A>
          struct is_array<numpy_texpr_2<A>> {
            static constexpr bool value = true;
          };
        template<class O, class A0, class A1>
          struct is_array<numpy_expr<O,A0,A1>> {
            static constexpr bool value = true;
          };

        template<class T>
          struct is_numexpr_arg : is_array<T> {
          };
        template<class T>
          struct is_numexpr_arg<list<T>> {
            static constexpr bool value = true;
          };
    }
}

#endif
