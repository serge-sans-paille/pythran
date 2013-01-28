#ifndef PYTHONIC_MODULE_OMP_H
#define PYTHONIC_MODULE_OMP_H
#ifdef _OPENMP

#include <omp.h>

namespace pythonic {
    namespace omp {
#define EXPORT_OMP(fun_name) \
        template<class... T>\
        auto fun_name(T... args) -> decltype(omp_##fun_name(args...)) { return omp_##fun_name(args...); } \
        PROXY(pythonic::omp, fun_name)

        EXPORT_OMP(set_num_threads);
        EXPORT_OMP(get_num_threads);
        EXPORT_OMP(get_max_threads);
        EXPORT_OMP(get_thread_num);
        EXPORT_OMP(get_num_procs);
        EXPORT_OMP(in_parallel);
        EXPORT_OMP(set_dynamic);
        EXPORT_OMP(get_dynamic);
        EXPORT_OMP(set_nested);
        EXPORT_OMP(get_nested);
        EXPORT_OMP(init_lock);
        EXPORT_OMP(destroy_lock);
        EXPORT_OMP(set_lock);
        EXPORT_OMP(unset_lock);
        EXPORT_OMP(test_lock);
        EXPORT_OMP(init_nest_lock);
        EXPORT_OMP(destroy_nest_lock);
        EXPORT_OMP(set_nest_lock);
        EXPORT_OMP(unset_nest_lock);
        EXPORT_OMP(test_nest_lock);
        EXPORT_OMP(get_wtime);
        EXPORT_OMP(get_wtick);
        EXPORT_OMP(set_schedule);
        EXPORT_OMP(get_schedule);
        EXPORT_OMP(get_thread_limit);
        EXPORT_OMP(set_max_active_levels);
        EXPORT_OMP(get_max_active_levels);
        EXPORT_OMP(get_level);
        EXPORT_OMP(get_ancestor_thread_num);
        EXPORT_OMP(get_team_size);
        EXPORT_OMP(get_active_level);
        EXPORT_OMP(in_final);
#undef EXPORT_OMP
    }
}

#endif

#endif
