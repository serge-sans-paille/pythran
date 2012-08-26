#ifndef PYTHONIC_MODULE_LIST_H
#define PYTHONIC_MODULE_LIST_H
namespace pythonic {
    namespace __list__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            none_type append(core::list<T> &seq, F const& value) {
                seq.push_back(value);
                return None;
            }
        template<class T, class F>
            none_type append(core::list<T> &seq, F&& value) {
                seq.push_back(value);
                return None;
            }
        PROXY(pythonic::__list__, append);

        template<class T, class F>
            none_type extend(core::list<T> &seq, core::list<F> const& add) {
                seq+=add;
                return None;
            }
        template<class T, class F>
            none_type extend(core::list<T> &seq, core::list<F> &add) {
                seq+=add;
                return None;
            }
        PROXY(pythonic::__list__, extend);

        //TODO: have to raise a valueError
        template<class T>
            long index(core::list<T> &seq, T& x) {
                return std::find(seq.begin(),seq.end(),x)-seq.begin();
            }
        VPROXY(pythonic::__list__, index);

        //TODO: have to raise a valueError
        template<class T>
            none_type remove(core::list<T> &seq, T& x) {
                seq.erase(index(seq,x));
                return None;
            }
        PROXY(pythonic::__list__, remove);

        template<class T>
            long count(core::list<T> &seq, T const& x) {
                return std::count(seq.begin(),seq.end(),x);
            }

        template<class T>
            long count(core::list<T> &seq, T &&x) {
                return std::count(seq.begin(),seq.end(),x);
            }

        VPROXY(pythonic::__list__,count);

        template<class T>
            none_type reverse(core::list<T> &seq) {
                std::reverse(seq.begin(),seq.end());
                return None;
            }

        PROXY(pythonic::__list__,reverse);

        template<class T>
            none_type sort(core::list<T> &seq) {
                std::sort(seq.begin(),seq.end());
                return None;
            }

        PROXY(pythonic::__list__,sort);

        template<class T, class F>
            none_type insert(core::list<T> &seq, long n, F const& value) {
                n = n%seq.size();
                if (n<0) n+=seq.size();
                seq.insert(n, value);
                return None;
            }

        template<class T, class F>
            none_type insert(core::list<T> &seq, long n, F && value) {
                n = n%seq.size();
                if (n<0) n+=seq.size();
                seq.insert(n, value);
                return None;
            }
        PROXY(pythonic::__list__, insert);
    }
}
#endif
