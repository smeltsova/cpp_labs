#include <iostream>

template <typename T>
class Array {
 public:
  explicit Array(size_t size, const T& value = T())
      : size_(size), data_(new T[size_]) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = value;
    }
  }

  Array(const Array& other) : size_(other.size_), data_(new T[size_]) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  Array(Array&& other) : size_(other.size_), data_(other.data_) {
    other.size_ = 0;
    other.data_ = nullptr;
  }

  ~Array() { delete[] data_; }

  Array& operator=(const Array& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      data_ = new T[size_];
      for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  Array& operator=(Array&& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      data_ = other.data_;
      other.size_ = 0;
      other.data_ = nullptr;
    }
    return *this;
  }

  size_t size() const { return size_; }

  T& operator[](size_t idx) {
    if (idx < size_) {
      return data_[idx];
    }
    throw std::out_of_range("Index out of range");
  }

  const T& operator[](size_t idx) const {
    if (idx < size_) {
      return data_[idx];
    }
    throw std::out_of_range("Index out of range");
  }

 private:
  size_t size_;
  T* data_;
};