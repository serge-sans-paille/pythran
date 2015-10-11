#ifndef PYTHONIC_UTILS_SHARED_REF_HPP
#define PYTHONIC_UTILS_SHARED_REF_HPP

#include "pythonic/include/utils/shared_ref.hpp"

#include <memory>
#include <utility>
#include <unordered_map>
#ifdef _OPENMP
#include <atomic>
#endif

namespace pythonic
{

  namespace utils
  {

    /** Light-weight shared_ptr like-class
     *
     *  Unlike std::shared_ptr, it allocates the memory itself using new.
     */
    template <class T>
    template <class... Types>
    shared_ref<T>::memory::memory(Types &&... args)
        : ptr(std::forward<Types>(args)...), count(1), foreign(nullptr)
    {
    }

    template <class T>
    shared_ref<T>::shared_ref(no_memory const &) noexcept : mem(nullptr)
    {
    }

    template <class T>
    shared_ref<T>::shared_ref(no_memory &&) noexcept : mem(nullptr)
    {
    }

    template <class T>
    template <class... Types>
    shared_ref<T>::shared_ref(Types &&... args)
        : mem(new memory(std::forward<Types>(args)...))
    {
    }

    template <class T>
    shared_ref<T>::shared_ref(shared_ref<T> &&p) noexcept : mem(p.mem)
    {
      p.mem = nullptr;
    }

    template <class T>
    shared_ref<T>::shared_ref(shared_ref<T> const &p) noexcept : mem(p.mem)
    {
      if (mem)
        acquire();
    }

    template <class T>
    shared_ref<T>::shared_ref(shared_ref<T> &p) noexcept : mem(p.mem)
    {
      if (mem)
        acquire();
    }

    template <class T>
    shared_ref<T>::~shared_ref() noexcept
    {
      dispose();
    }

    template <class T>
    void shared_ref<T>::swap(shared_ref<T> &rhs) noexcept
    {
      using std::swap;
      swap(mem, rhs.mem);
    }

    template <class T>
    shared_ref<T> &shared_ref<T>::operator=(shared_ref<T> p) noexcept
    {
      swap(p);
      return *this;
    }

    template <class T>
    T &shared_ref<T>::operator*() const noexcept
    {
      return mem->ptr;
    }

    template <class T>
    T *shared_ref<T>::operator->() const noexcept
    {
      return &mem->ptr;
    }

    template <class T>
    bool shared_ref<T>::operator!=(shared_ref<T> const &other) const noexcept
    {
      return mem != other.mem;
    }

    template <class T>
    void shared_ref<T>::external(extern_type obj_ptr)
    {
      mem->foreign = obj_ptr;
    }

    template <class T>
    T *shared_ref<T>::forget()
    {
      T *ptr = &mem->ptr;
      mem = nullptr;
      return ptr;
    }

    template <class T>
    inline extern_type shared_ref<T>::get_foreign()
    {
      return mem->foreign;
    }

    template <class T>
    void shared_ref<T>::dispose()
    {
      if (mem and --mem->count == 0) {
        if (mem->foreign) {
#ifdef ENABLE_PYTHON_MODULE
          Py_DECREF(mem->foreign);
#endif
        } else
          delete mem;
        mem = nullptr;
      }
    }

    template <class T>
    void shared_ref<T>::acquire()
    {
      ++mem->count;
    }
  }
}

#endif
