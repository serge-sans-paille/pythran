#ifndef PYTHONIC_TYPES_FILE_HPP
#define PYTHONIC_TYPES_FILE_HPP

#include "pythonic/include/types/file.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/attr.hpp"
#include "pythonic/__builtin__/IOError.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/__builtin__/RuntimeError.hpp"
#include "pythonic/__builtin__/StopIteration.hpp"

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

    /// _file implementation

    _file::_file() : f(nullptr)
    {
    }

    // TODO : no check on file existance?
    _file::_file(types::str const &filename, types::str const &strmode)
        : f(fopen(filename.c_str(), strmode.c_str()))
    {
    }

    FILE *_file::operator*() const
    {
      return f;
    }

    _file::~_file()
    {
      if (f)
        fclose(f);
    }

    /// file implementation

    // Constructors
    file::file() : data(utils::no_memory())
    {
    }

    file::file(types::str const &filename, types::str const &strmode)
        : data(utils::no_memory()), mode(strmode), name(filename),
          newlines('\n')
    {
      open(filename, strmode);
    }

    // Iterators
    file::iterator file::begin()
    {
      return {*this};
    }

    file::iterator file::end()
    {
      return {*this, file::iterator::npos()};
    }

    // Modifiers
    void file::open(types::str const &filename, types::str const &strmode)
    {
      const char *smode = strmode.c_str();
      // Python enforces that the mode, after stripping 'U', begins with 'r',
      // 'w' or 'a'.
      if (*smode == 'U') {
        ++smode;
      } // Not implemented yet

      data = utils::shared_ref<container_type>(filename, smode);
      if (not**data)
        throw types::IOError("Couldn't open file " + filename);
      is_open = true;
    }

    void file::close()
    {
      fclose(**data);
      data->f = nullptr;
      is_open = false;
    }

    bool file::closed() const
    {
      return not is_open;
    }

    types::str const &file::getmode() const
    {
      return mode;
    }

    types::str const &file::getname() const
    {
      return name;
    }

    types::str const &file::getnewlines() const
    {
      // Python seems to always return none... Doing the same in
      // getattr<newlines>
      return newlines;
    }

    bool file::eof()
    {
      return ::feof(**data);
    }

    void file::flush()
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      fflush(**data);
    }

    int file::fileno() const
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      return ::fileno(**data);
    }

    bool file::isatty() const
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      return ::isatty(this->fileno());
    }

    types::str file::next()
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (feof(**data) && mode.find_first_of("ra") == -1)
        // If we are at eof on reading mode throw exception
        throw StopIteration("file.next() : EOF reached.");
      return readline();
    }

    types::str file::read(int size)
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (mode.find_first_of("r+") == -1)
        throw IOError("File not open for reading");
      if (size == 0 or (feof(**data) && mode.find_first_of("ra") == -1))
        return types::str();
      int curr_pos = tell();
      seek(0, SEEK_END);
      size = size < 0 ? tell() - curr_pos : size;
      seek(curr_pos);
      char *content = new char[size + 1];
      // This part needs a new implementation of types::str(char*) to avoid
      // unnecessary copy.
      types::str res(content, fread(content, sizeof(char), size, **data));
      delete[] content;
      return res;
    }

    types::str file::readline(long size)
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (mode.find_first_of("r+") == -1)
        throw IOError("File not open for reading");
      constexpr static long BUFFER_SIZE = 1024;
      types::str res;
      char read_str[BUFFER_SIZE];

      for (long i = 0; i < size; i += BUFFER_SIZE) {
        // +1 because we read the last chunk so we don't want to count \0
        if (fgets(read_str, std::min(BUFFER_SIZE - 1, size - i) + 1, **data))
          res += read_str;
        if (feof(**data) or res[-1] == '\n')
          break;
      }
      return res;
    }

    types::list<types::str> file::readlines(int sizehint)
    {
      // Official python doc specifies that sizehint is used as a max of chars
      // But it has not been implemented in the standard python interpreter...
      types::str str;
      types::list<types::str> lst(0);
      while ((str = readline()))
        lst.push_back(str);
      return lst;
    }

    void file::seek(int offset, int whence)
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END)
        throw IOError("file.seek() :  Invalid argument.");
      fseek(**data, offset, whence);
    }

    int file::tell() const
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      return ftell(**data);
    }

    void file::truncate(int size)
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (mode.find_first_of("wa+") == -1)
        throw IOError("file.write() :  File not opened for writing.");
      if (size < 0)
        size = this->tell();
      int error = ftruncate(fileno(), size);
      if (error == -1)
        throw RuntimeError(strerror(errno));
    }

    void file::write(types::str const &str)
    {
      if (not is_open)
        throw ValueError("I/O operation on closed file");
      if (mode.find_first_of("wa+") == -1)
        throw IOError("file.write() :  File not opened for writing.");
      fwrite(str.c_str(), sizeof(char), str.size(), **data);
    }

    template <class T>
    void file::writelines(T const &seq)
    {
      auto end = seq.end();
      for (auto it = seq.begin(); it != end; ++it)
        write(*it);
    }

    /// file_iterator implementation
    // TODO : What if the file disappears before the end?
    // Like in :
    // for line in open("myfile"):
    //     print line
    file_iterator::file_iterator(file &ref)
        : f(ref), curr(ref.readline()), position(ref.tell())
    {
    }

    file_iterator::file_iterator(file &ref, npos)
        : f(ref), curr(), position(-1){};

    bool file_iterator::operator==(file_iterator const &f2) const
    {
      return position == f2.position;
    }

    bool file_iterator::operator!=(file_iterator const &f2) const
    {
      return position != f2.position;
    }

    bool file_iterator::operator<(file_iterator const &f2) const
    {
      // Not really elegant...
      // Equivalent to 'return *this != f2;'
      return position != f2.position;
    }

    file_iterator &file_iterator::operator++()
    {
      // Check if ftell == -1 when fgetpos(FILE *stream, fpos_t eof) == 0
      if (f.eof())
        return *this;
      curr = f.readline();
      position = f.eof() ? -1 : f.tell();
      return *this;
    }

    types::str const &file_iterator::operator*() const
    {
      return curr;
    }
  }
}

/* pythran attribute system { */
namespace pythonic
{
  namespace types
  {
    namespace __file
    {

      bool getattr<attr::CLOSED>::operator()(file const &f)
      {
        return f.closed();
      }

      str const &getattr<attr::MODE>::operator()(file const &f)
      {
        return f.getmode();
      }

      str const &getattr<attr::NAME>::operator()(file const &f)
      {
        return f.getname();
      }

      // Python seems to always return none... Doing the same.
      none_type getattr<attr::NEWLINES>::operator()(file const &f)
      {
        return __builtin__::None;
      }
    }
  }

  namespace __builtin__
  {
    template <int I>
    auto getattr(pythonic::types::file const &f)
        -> decltype(pythonic::types::__file::getattr<I>()(f))
    {
      return pythonic::types::__file::getattr<I>()(f);
    }
  }
}

/* } */

#endif
