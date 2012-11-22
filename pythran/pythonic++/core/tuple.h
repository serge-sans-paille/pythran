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

#endif

