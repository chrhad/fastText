/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <ios>
#include <istream>

namespace fasttext {

class File {
 public:
  File();
  virtual ~File();

  virtual std::istream& seekg(std::streampos pos) = 0;
  virtual std::istream& seekg(std::streampos off, std::ios_base::seekdir way) = 0;
  virtual std::streampos tellg() = 0;
  virtual bool is_open() = 0;
  virtual void close() = 0;
  virtual void clear() = 0;

  virtual std::istream& stream() = 0;
};

template<class T>
class FileWrapper : public File {
 protected:
  T in_;

 public:
  FileWrapper();
  FileWrapper(const char* filename, std::ios_base::openmode mode=std::ios_base::in);
  FileWrapper(const std::string& filename, std::ios_base::openmode mode=std::ios_base::in);
  
  std::istream& seekg(std::streampos pos);
  std::istream& seekg(std::streampos off, std::ios_base::seekdir way);
  std::streampos tellg();
  void clear();

  bool is_open();
  void close();

  std::istream& stream();
};

template<class T>
FileWrapper<T>::FileWrapper() : File() {}

template<class T>
FileWrapper<T>::FileWrapper(const char* filename, std::ios_base::openmode mode) :
in_(filename, mode) {}

template<class T>
FileWrapper<T>::FileWrapper(const std::string& filename, std::ios_base::openmode mode) :
in_(filename.c_str(), mode) {}

template<class T>
std::istream& FileWrapper<T>::seekg(std::streampos pos) {
  return in_.seekg(pos);
}

template<class T>
std::istream& FileWrapper<T>::seekg(std::streampos off, std::ios_base::seekdir way) {
  return in_.seekg(off, way);
}

template<class T>
std::streampos FileWrapper<T>::tellg() {
  return in_.tellg();
}

template<class T>
void FileWrapper<T>::clear() {
  return in_.clear();
}

template<class T>
bool FileWrapper<T>::is_open() {
  return in_.rdbuf()->is_open();
}

template<class T>
void FileWrapper<T>::close() {
  in_.close();
}

template<class T>
std::istream& FileWrapper<T>::stream() {
  return dynamic_cast<std::istream&>(in_);
}

}
