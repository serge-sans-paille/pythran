#ifndef PYTHONIC_MODULE_DICT_H
#define PYTHONIC_MODULE_DICT_H
template<class T> class dict_container;

namespace pythonic {
    namespace __dict__ { /* to avoid conflict with the dict intrinsic */

        template<class K, class V>
            void clear(core::dict<K,V> &d) {
                d.clear();
            }
        PROXY(pythonic::__dict__, clear);

        template<class Iterable, class V=none_type>
            core::dict<typename std::remove_reference<Iterable>::type::value_type, V> fromkeys(Iterable && iter, V const & v = __builtin__::None) {
                core::dict<typename std::remove_reference<Iterable>::type::value_type,V> D;
                D=core::empty_dict();
                for(auto const& i: iter) D[i]=v;
                return D;
            }
        PROXY(pythonic::__dict__, fromkeys);

        template<class K, class V, class W, class X>
            V get(core::dict<K,V> const &d, W const& k, X const &default_) {
                return d.get(k,default_);
            }
        template<class K, class V, class W>
            none<V> get(core::dict<K,V> const &d, W const& k) {
                return d.get(k);
            }
        template<class W, class X>
            X get(core::empty_dict const &, W const& , X const &default_) {
                return default_;
            }
        template<class T, class I, class J>
            decltype(std::declval<T>()+std::declval<J>()) get(::dict_container<T>, I , J );
        PROXY(pythonic::__dict__, get);

        template<class K, class V, class W>
            bool has_key(core::dict<K,V> const &d, W const& k) {
                return d.find(k) != d.item_end();
            }
        PROXY(pythonic::__dict__, has_key);

        template<class K, class V>
            core::list< std::tuple<K,V> > items(core::dict<K,V> const &d) {
                return core::list< std::tuple<K,V> >(d.item_begin(), d.item_end());
            }
        PROXY(pythonic::__dict__, items);

        template<class K, class V>
            auto iteritems(core::dict<K,V> d) -> decltype(d.iteritems()){
                return d.iteritems();
            }
        PROXY(pythonic::__dict__, iteritems);

        template<class K, class V>
            auto iterkeys(core::dict<K,V> d) -> decltype(d.iterkeys()){
                return d.iterkeys();
            }
        PROXY(pythonic::__dict__, iterkeys);

        template<class K, class V>
            auto itervalues(core::dict<K,V> d) -> decltype(d.itervalues()){
                return d.itervalues();
            }
        PROXY(pythonic::__dict__, itervalues);

        template<class K, class V>
            core::list<K> keys(core::dict<K,V> const &d) {
                return core::list<K>(d.key_begin(), d.key_end());
            }
        PROXY(pythonic::__dict__, keys);

        template<class K, class V, class W, class X>
            V pop(core::dict<K,V> d, W const& k, X const &default_) {
                return d.pop(k,default_);
            }
        template<class K, class V, class W>
            V pop(core::dict<K,V> d, W const& k) {
                return d.pop(k);
            }
        PROXY(pythonic::__dict__, pop);

        template<class K, class V>
            std::tuple<K,V> popitem(core::dict<K,V> d) {
                return d.popitem();
            }
        PROXY(pythonic::__dict__, popitem);

        template<class K, class V>
            core::list<V> values(core::dict<K,V> const &d) {
                return core::list<V>(d.value_begin(), d.value_end());
            }
        PROXY(pythonic::__dict__, values);

        template<class K, class V, class W, class X>
            V setdefault(core::dict<K,V> &d, W const & k, X const &default_) {
                return d.setdefault(k,default_);
            }
        template<class K, class V, class W>
            V setdefault(core::dict<K,V> &d, W const & k) {
                return d.get(k);
            }
        template<class K, class V, class W, class X>
            V setdefault(core::dict<K,V> &&d, W const & k, X const &default_) {
                return d.setdefault(k,default_);
            }
        template<class K, class V, class W>
            V setdefault(core::dict<K,V> &&d, W const & k) {
                return d.get(k);
            }
        PROXY(pythonic::__dict__, setdefault);

        template<class K, class V, class Iterable>
            none_type update(core::dict<K,V> d, Iterable const & k) {
                d.update(k);
                return __builtin__::None;
            }
        PROXY(pythonic::__dict__, update);

        template<class K, class V>
            core::dict_items<core::dict<K,V>> viewitems(core::dict<K,V> const &d) {
                return d.viewitems();
            }
        PROXY(pythonic::__dict__, viewitems);

        template<class K, class V>
            core::dict_keys<core::dict<K,V>> viewkeys(core::dict<K,V> const &d) {
                return d.viewkeys();
            }
        PROXY(pythonic::__dict__, viewkeys);

        template<class K, class V>
            core::dict_values<core::dict<K,V>> viewvalues(core::dict<K,V> const &d) {
                return d.viewvalues();
            }
        PROXY(pythonic::__dict__, viewvalues);
    }

    BUILTIN_CLASS(__dict__)
}
#endif
