#ifndef PYTHONIC_NUMPY_SELECT_HPP
#define PYTHONIC_NUMPY_SELECT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class U>
            types::ndarray<T,N> select(types::list<types::ndarray<U,N>> const& condlist, types::list<types::ndarray<T,N>> const& choicelist, T _default = 0)
            {
                types::ndarray<T,N> out(choicelist[0].shape, _default);
                for(size_t i=0; i<out.size(); ++i)
                {
                    for(int j=0; j<condlist.size(); ++j)
                    {
                        if(condlist[j].buffer[i])
                        {
                            out.buffer[i] = choicelist[j].buffer[i];
                            break;
                        }
                    }
                }
                return out;
            }

        template<class T, size_t N, class U>
            auto select(types::list<U> const& condlist, types::list<types::ndarray<T,N>> const& choicelist, T _default = 0) 
            -> decltype(select(std::declval<types::list<typename types::numpy_expr_to_ndarray<U>::type>>(), choicelist, _default))
            {
                types::list<typename types::numpy_expr_to_ndarray<U>::type> condition(condlist.size());
                for(int i=0; i<condlist.size(); ++i)
                    condition[i] = asarray(condlist[i]);
                return select(condition, choicelist);
            }

        template<class T, size_t N, class U>
            auto select(types::list<types::ndarray<T,N>> const& condlist, types::list<U> const& choicelist, T _default = 0) 
            -> decltype(select(condlist, std::declval<types::list<typename types::numpy_expr_to_ndarray<U>::type>>(), _default))
            {
                types::list<typename types::numpy_expr_to_ndarray<U>::type> choice(choicelist.size());
                for(int i=0; i<choicelist.size(); ++i)
                    choice[i] = asarray(choicelist[i]);
                return select(condlist, choice);
            }

        template<class V, class U>
            auto select(types::list<V> const& condlist, types::list<U> const& choicelist, typename types::numpy_expr_to_ndarray<U>::T _default = 0) 
            -> decltype(select(std::declval<types::list<typename types::numpy_expr_to_ndarray<V>::type>>(), std::declval<types::list<typename types::numpy_expr_to_ndarray<U>::type>>(), _default))
            {
                types::list<typename types::numpy_expr_to_ndarray<U>::type> choice(choicelist.size());
                types::list<typename types::numpy_expr_to_ndarray<V>::type> condition(condlist.size());
                for(int i=0; i<choicelist.size(); ++i)
                    choice[i] = asarray(choicelist[i]);
                for(int i=0; i<condlist.size(); ++i)
                    condition[i] = asarray(condlist[i]);
                return select(condition, choice);
            }

        NUMPY_EXPR_TO_NDARRAY0(select)
            PROXY(pythonic::numpy, select);

    }

}

#endif

