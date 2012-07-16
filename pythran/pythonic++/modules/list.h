#ifndef PYTHONIC_MODULE_LIST_H
#define PYTHONIC_MODULE_LIST_H
namespace pythonic {
    namespace __list__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            void append(core::list<T> &seq, F const& value) {
                seq.push_back(value);
            }
        template<class T, class F>
            void append(core::list<T> &seq, F&& value) {
                seq.push_back(value);
            }
        PROXY(pythonic::__list__, append);
        template<class T, class F>
            void insert(core::list<T> &seq, size_t n, F const& value) {
                seq.insert(n, value);
            }
        PROXY(pythonic::__list__, insert);
    }
}
#endif
