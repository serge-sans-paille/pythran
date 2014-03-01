#ifndef PYTHONIC_PYTHON_EXPORT_HPP
#define PYTHONIC_PYTHON_EXPORT_HPP

#define pythran_export_start(module, funcname, ...) \
    namespace __pythran_##module{\
    template <int N> \
    struct funcname##_globals {\
    };\
    \
    template<>\
    struct funcname##_globals<__COUNTER__> {\
        template<typename combiner, typename or_type>\
        using global_type = or_type;\
    }; \
    \
    pythran_export_multi(module, funcname, ##__VA_ARGS__)

#define pythran_export_multi(module, funcname, ...) pythran_export_multi_I(__COUNTER__, module, funcname, ##__VA_ARGS__)
#define pythran_export_multi_I(N, module, funcname, ...) \
    template<> \
    struct funcname##_globals<N> { \
        template<typename combiner, typename or_type> \
        using global_type = funcname##_globals<N-1>::template global_type<combiner, typename combiner::template type<or_type, ##__VA_ARGS__>::instanciation>; \
    };

#define pythran_export_end(module, funcname, ...) pythran_export_end_I(__COUNTER__, module, funcname, ##__VA_ARGS__)
#define pythran_export_end_I(N, module, funcname, ...) \
    pythran_export_multi_I(N, module, funcname, ##__VA_ARGS__) \
    template <class combiner, class or_type> \
    typename pythonic::assignable<funcname##_globals<N>::global_type<combiner, or_type> >::type \
    funcname##_global_type(int) {}\
    } /*End namespace */

#define pythran_export_solo(module, funcname, ...) \
    pythran_export_start(module, funcname, ##__VA_ARGS__) \
    template <class combiner, class or_type> \
    typename pythonic::assignable<funcname##_globals<__COUNTER__-1>::global_type<combiner, or_type> >::type \
    funcname##_global_type(int) {}\
    } /*End namespace */

#endif //PYTHONIC_PYTHON_EXPORT_HPP
