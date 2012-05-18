#ifndef PYTHONIC_LIST_H
#define PYTHONIC_LIST_H
namespace pythonic {
    namespace __list__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            void append(sequence<T> &seq, F const& value) {
                seq.push_back(value);
            }
        template<class T, class F>
            void insert(sequence<T> &seq, size_t n, F const& value) {
                seq.insert(n, value);
            }
    }
}
#endif
