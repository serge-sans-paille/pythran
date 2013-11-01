#ifndef PYTHONIC_SHARED_REF_H
#define PYTHONIC_SHARED_REF_H
#include <memory>
#include <utility>
#ifdef _OPENMP
#include <atomic>
#endif

namespace pythonic {

#ifdef _OPENMP
    typedef std::atomic_size_t atomic_size_t;
#else
    typedef size_t atomic_size_t;
#endif

    namespace impl {
        // Force construction of an uninitialized shared_ref
        struct no_memory{};

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
                        template<class... Types>
                            memory(Types&&... args)
                            : ptr( std::forward<Types>(args)... ), count(1)
                            {}
                    } *mem;

                public:

                    // Uninitialized ctor
                    shared_ref(no_memory const&) noexcept
                        : mem(nullptr)
                    {}
                    // Uninitialized ctor (rvalue ref)
                    shared_ref(no_memory &&) noexcept
                        : mem(nullptr)
                    {}

                    // Ctor allocate T and forward all arguments to T ctor
                    template<class... Types>
                        shared_ref(Types&&... args)
                            : mem( new memory(std::forward<Types>(args)...) )
                        {}

                    // Move Ctor
                    shared_ref(shared_ref<T>&& p) noexcept
                        : mem(p.mem)
                    {p.mem=nullptr;}

                    // Copy Ctor
                    shared_ref(shared_ref<T> const& p) noexcept
                        : mem(p.mem)
                    {if(mem) acquire();}

                    // Copy Ctor, again
                    // Without a non-const copy-ctor here, the greedy variadic template ctor takes over
                    shared_ref(shared_ref<T> & p) noexcept
                        : mem(p.mem)
                    {if(mem) acquire();}

                    ~shared_ref() noexcept
                    {dispose();}

                    // Magic swapperator, help for assignment operators
                    void swap(shared_ref<T> & rhs) noexcept {
                      using std::swap;
                      swap(mem, rhs.mem);
                    }

                    // Takes by copy so that acquire/release is handle by ctor
                    shared_ref<T>& operator=(shared_ref<T> p) noexcept
                    {
                        swap(p);
                        return *this;
                    }

                    T& operator*() const noexcept
                    {return mem->ptr;}

                    T* operator->() const noexcept
                    {return &mem->ptr;}

                    bool operator!=(shared_ref<T> const & other) const noexcept {
                        return mem != other.mem;
                    }

                    // Bump the count so that the object is NEVER deleted.
                    // OK this is a very bad design but it helps ndarray...
                    void external() {
                        ++mem->count;
                    }

                    // FIXME The interface is screwed, you won't be able to delete
                    // T since it was a member of the struct allocated with new
                    T* forget() {
                        T *ptr = &mem->ptr;
                        mem = nullptr;
                        return ptr;
                    }

                 private:
                    void dispose()
                    {
                        if(mem and --mem->count == 0)
                        {
                            delete mem;
                            mem = nullptr;
                        }
                    }
                    void acquire() {
                        ++mem->count;
                    }
            };

    }
}

#endif
