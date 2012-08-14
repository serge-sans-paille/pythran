#ifndef PYTHONIC_MODULE_SET_H
#define PYTHONIC_MODULE_SET_H
namespace pythonic {
    namespace __set__ { /* to avoid conflict with the list intrinsic */
        template<class T, class F>
            void add(core::set<T> &s, F const& value) {
                s.add(value);
            }
        PROXY(pythonic::__set__, add);

	template<class T>
	    void clear(core::set<T> & set) {
		set.clear();
	}
        PROXY(pythonic::__set__, clear);

	template<class T, class U>
		void delete_(core::set<T> & set, U const& elem){
			set.delete_(elem);
		}
        PROXY(pythonic::__set__, delete_);

	template<class T, class U>
		void discard(core::set<T> & set, U const& elem){
			set.discard(elem);
		}
        PROXY(pythonic::__set__, discard);

	template<class T, class U>
	    bool isdisjoint(core::set<T> const& calling_set, core::set<U> const& arg_set) {
		return calling_set.isdisjoint(arg_set);
	}
        PROXY(pythonic::__set__, isdisjoint);
    }
}
#endif
