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

	template<class T>
	    core::set<T> copy(core::set<T> const& set) {
		return set.copy();
	}
        PROXY(pythonic::__set__, copy);

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

	template<typename T, typename... Types> 
	core::set<T> union_(core::set<T> const& set, Types const&... others){
		return set.union_(others...);
	}
        PROXY(pythonic::__set__, union_);

	template<typename T, typename... Types> 
	core::set<T> intersection(core::set<T> const& set, core::set<Types> const&... others){
		return set.intersection(others...);
	}
        PROXY(pythonic::__set__, intersection);

	template<typename T, typename... Types> 
	core::set<T> difference(core::set<T> const& set, Types const&... others){
		return set.difference(others...);
	}
        PROXY(pythonic::__set__, difference);

	template<typename T, typename U> 
	core::set<T> symmetric_difference(core::set<T> const& set, U const& other){
		return set.symmetric_difference(other);
	}
        PROXY(pythonic::__set__, symmetric_difference);

	template<class T, class U>
	bool issuperset(core::set<T> const& set, core::set<U> const& other){
		return set.issuperset(other);
	}
        PROXY(pythonic::__set__, issuperset);

 	template<class T, class U>
	bool issubset(core::set<T> const& set, core::set<U> const& other){
		return set.issubset(other);
	}
        PROXY(pythonic::__set__, issubset);
   }
}
#endif
