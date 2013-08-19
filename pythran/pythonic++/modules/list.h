#ifndef PYTHONIC_MODULE_LIST_H
#define PYTHONIC_MODULE_LIST_H
namespace pythonic {
    namespace __list__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            none_type append(core::list<T> &seq, F const& value) {
                seq.push_back(value);
                return __builtin__::None;
            }
        template<class T, class F>
            none_type append(core::list<T> &seq, F&& value) {
                seq.push_back(value);
                return __builtin__::None;
            }
        template<class F>
            none_type append(core::empty_list &seq, F&& value) {
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, append);

        template<class T, class F>
            none_type extend(core::list<T> &seq, core::list<F> const& add) {
                seq+=add;
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, extend);

        //TODO: have to raise a valueError
        template<class T>
            long index(core::list<T> &seq, T const& x) {
                return seq.index(x);
            }
        template<class T>
            long index(core::list<T> &&seq, T const& x) {
                return seq.index(x);
            }
        PROXY(pythonic::__list__, index);

        //TODO: have to raise a valueError
        template<class T>
            none_type remove(core::list<T> &seq, T const & x) {
                seq.erase(index(seq,x));
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, remove);

        template<class T>
            long count(core::list<T> &seq, T const& x) {
                return std::count(seq.begin(),seq.end(),x);
            }

        template<class T>
            long count(core::list<T> &seq, T &&x) {
                return std::count(seq.begin(),seq.end(),std::forward<T>(x));
            }
        template<class T>
            long count(core::list<T> &&seq, T &&x) {
                return std::count(seq.begin(),seq.end(),std::forward<T>(x));
            }

        PROXY(pythonic::__list__,count);

        template<class T>
            none_type reverse(core::list<T> &seq) {
                std::reverse(seq.begin(),seq.end());
                return __builtin__::None;
            }

        PROXY(pythonic::__list__,reverse);

        template<class T>
            none_type sort(core::list<T> &seq) {
                std::sort(seq.begin(),seq.end());
                return __builtin__::None;
            }

        PROXY(pythonic::__list__,sort);

        template<class T, class F>
            none_type insert(core::list<T> &seq, long n, F const& value) {
                n = n%(1+seq.size());
                if (n<0) n+=seq.size();
                seq.insert(n, value);
                return __builtin__::None;
            }

        template<class T, class F>
            none_type insert(core::list<T> &seq, long n, F && value) {
                n = n%(1+seq.size()); // +1 because we want to be able to insert at the end of seq
                if (n<0) n+=seq.size();
                seq.insert(n, value);
                return __builtin__::None;
            }
        PROXY(pythonic::__list__, insert);
    }

    BUILTIN_CLASS(__list__)
}
#endif
