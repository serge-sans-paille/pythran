#ifndef PYTHONIC_INCLUDE_TYPES_FILE_HPP
#define PYTHONIC_INCLUDE_TYPES_FILE_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/utils/shared_ref.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/attr.hpp"
#include "pythonic/include/__builtin__/IOError.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"
#include "pythonic/include/__builtin__/RuntimeError.hpp"
#include "pythonic/include/__builtin__/StopIteration.hpp"

#include <fstream>
#include <iterator>
#include <cstring>
#include <string>
#include <cstdio>
#include <unistd.h>

namespace pythonic
{

  namespace types
  {
    class file;

    struct file_iterator
        : std::iterator<std::forward_iterator_tag, types::str, ptrdiff_t,
                        types::str *, types::str /* no ref */> {
    private:
      file &f;
      types::str curr;
      int position;

    public:
      using value_type = types::str;

      struct npos {
      };

      file_iterator(file &ref);
      file_iterator(file &ref, npos);
      bool operator==(file_iterator const &f2) const;
      bool operator!=(file_iterator const &f2) const;
      bool operator<(file_iterator const &f2) const;
      file_iterator &operator++();
      types::str const &operator*() const;
    };

    struct _file {
      FILE *f;
      _file();
      _file(types::str const &filename, types::str const &strmode = "r");
      FILE *operator*() const;
      ~_file();
    };

    class file
    {

    private:
      using container_type = _file;
      utils::shared_ref<container_type> data;
      bool is_open;
      types::str mode, name, newlines;

    public:
      // Types
      using iterator = file_iterator;
      using value_type = types::str;

      // Constructors
      file();
      file(types::str const &filename, types::str const &strmode = "r");

      // Iterators
      iterator begin();
      iterator end();

      // Modifiers
      void open(types::str const &filename, types::str const &strmode);

      void close();

      bool closed() const;

      types::str const &getmode() const;

      types::str const &getname() const;

      types::str const &getnewlines() const;

      bool eof();

      void flush();

      int fileno() const;

      bool isatty() const;

      types::str next();

      types::str read(int size = -1);

      types::str readline(long size = std::numeric_limits<long>::max());

      types::list<types::str> readlines(int sizehint = -1);

      void seek(int offset, int whence = SEEK_SET);

      int tell() const;

      void truncate(int size = -1);

      void write(types::str const &str);

      template <class T>
      void writelines(T const &seq);
    };
  }
}

/* pythran attribute system { */
namespace pythonic
{
  namespace types
  {
    namespace __file
    {

      template <int I>
      struct getattr;

      template <>
      struct getattr<attr::CLOSED> {
        bool operator()(file const &f);
      };

      template <>
      struct getattr<attr::MODE> {
        str const &operator()(file const &f);
      };

      template <>
      struct getattr<attr::NAME> {
        str const &operator()(file const &f);
      };

      template <>
      struct getattr<attr::NEWLINES> {
        // Python seems to always return none... Doing the same.
        none_type operator()(file const &f);
      };
    }
  }

  namespace __builtin__
  {
    template <int I>
    auto getattr(pythonic::types::file const &f)
        -> decltype(pythonic::types::__file::getattr<I>()(f));
  }
}

/* } */

#endif
