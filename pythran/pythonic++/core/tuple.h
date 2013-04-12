#ifndef PYTHONIC_TUPLE_H
#define PYTHONIC_TUPLE_H

template<class F, class S>
bool operator==(std::pair<F,S> const& self, std::tuple<F,S> const& other) {
    return self.first == std::get<0>(other) and self.second == std::get<1>(other);
}

template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> const& t1) {
    return std::tuple_cat(t0, t1);
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> const& t1) {
    return std::tuple_cat(std::forward<Types0...>(t0), t1);
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const& t0, std::tuple<Types1...> && t1) {
    return std::tuple_cat(t0, std::forward<Types1...>(t1));
}
template<class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> && t0, std::tuple<Types1...> && t1) {
    return std::tuple_cat(std::forward<Types0...>(t0), std::forward<Types1...>(t1));
}

/* hashable tuples, as proposed in http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set */
//namespace {
    size_t hash_combiner(size_t left, size_t right) //replacable
    { return left^right;}

    template<int index, class...types>
        struct hash_impl {
            size_t operator()(size_t a, const std::tuple<types...>& t) const {
                typedef typename std::tuple_element<index, std::tuple<types...>>::type nexttype;
                hash_impl<index-1, types...> next;
                size_t b = std::hash<nexttype>()(std::get<index>(t));
                return next(hash_combiner(a, b), t); 
            }
        };
    template<class...types>
        struct hash_impl<0, types...> {
            size_t operator()(size_t a, const std::tuple<types...>& t) const {
                typedef typename std::tuple_element<0, std::tuple<types...>>::type nexttype;
                size_t b = std::hash<nexttype>()(std::get<0>(t));
                return hash_combiner(a, b); 
            }
        };
//}
 
namespace std {
    template<class...Types>
        struct hash<std::tuple<Types...>> {
            size_t operator()(std::tuple<Types...> const& t) const {
                const size_t begin = std::tuple_size<std::tuple<Types...>>::value-1;
                return hash_impl<begin, Types...>()(1, t); //1 should be some largervalue
            }
        };
}

#endif

