#ifndef PYTHONIC_MODULE_SET_H
#define PYTHONIC_MODULE_SET_H
namespace pythonic {
    namespace __set__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            void add(core::set<T> &s, F const& value) {
                s.add(value);
            }
        PROXY(pythonic::__set__, add);
    }
}
#endif
