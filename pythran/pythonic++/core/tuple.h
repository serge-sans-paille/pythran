#ifndef PYTHONIC_TUPLE_H
#define PYTHONIC_TUPLE_H

template<class F, class S>
bool operator==(std::pair<F,S> const& self, std::tuple<F,S> const& other) {
    return self.first == std::get<0>(other) and self.second == std::get<1>(other);
}

#endif

