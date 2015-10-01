#ifndef PYTHONIC_INCLUDE_UTILS_SHARED_REF_HPP
#define PYTHONIC_INCLUDE_UTILS_SHARED_REF_HPP

#include <memory>
#include <utility>
#include <unordered_map>
#ifdef _OPENMP
#include <atomic>
#endif

namespace pythonic
{
#ifdef ENABLE_PYTHON_MODULE
  using extern_type = PyObject *;
#else
  using extern_type = void *;
#endif

#ifdef _OPENMP
  using atomic_size_t = std::atomic_size_t;
#else
  using atomic_size_t = size_t;
#endif

  namespace utils
  {

    // Force construction of an uninitialized shared_ref
    struct no_memory {
    };

    /** Light-weight shared_ptr like-class
     *
     *  Unlike std::shared_ptr, it allocates the memory itself using new.
     */
    template <class T>
    class shared_ref
    {
    private:
      struct memory {
        T ptr;
        atomic_size_t count;
        extern_type foreign;
        template <class... Types>
        memory(Types &&... args);
      } * mem;

    public:
      // This attributs exists for non-Python code to avoid #ifdef everywhere

      // Uninitialized ctor
      shared_ref(no_memory const &) noexcept;

      // Uninitialized ctor (rvalue ref)
      shared_ref(no_memory &&) noexcept;

      // Ctor allocate T and forward all arguments to T ctor
      template <class... Types>
      shared_ref(Types &&... args);

      // Move Ctor
      shared_ref(shared_ref<T> &&p) noexcept;

      // Copy Ctor
      shared_ref(shared_ref<T> const &p) noexcept;

      // Copy Ctor, again
      // Without a non-const copy-ctor here, the greedy variadic template ctor
      // takes over
      shared_ref(shared_ref<T> &p) noexcept;

      ~shared_ref() noexcept;

      // Magic swapperator, help for assignment operators
      void swap(shared_ref<T> &rhs) noexcept;

      // Takes by copy so that acquire/release is handle by ctor
      shared_ref<T> &operator=(shared_ref<T> p) noexcept;

      T &operator*() const noexcept;

      T *operator->() const noexcept;

      bool operator!=(shared_ref<T> const &other) const noexcept;

      // Save pointer to the external object to decref once we doesn't
      // use it anymore
      void external(extern_type obj_ptr);

      // FIXME The interface is screwed, you won't be able to delete
      // T since it was a member of the struct allocated with new
      T *forget();

      inline extern_type get_foreign();

    private:
      void dispose();
      void acquire();
    };
  }
}

#endif
