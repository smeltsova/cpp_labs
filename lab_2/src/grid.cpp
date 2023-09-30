#include <cassert>
#include <memory>

template <typename T>
class Grid final {
 public:
  using value_type = T;
  using size_type = unsigned;

 private:
  T* const data;
  size_type const y_size, x_size;

 public:
  Grid(T* data, size_type y_size, size_type x_size)
      : data(allocate(y_size, x_size)), y_size(y_size), x_size(x_size) {
    size_type full_size = x_size * y_size;
    for (size_type i = 0; i < full_size; ++i) {
      new (data + i) T(data[i]);
    }
  }

  Grid(Grid<T> const& other) : Grid(other.data, other.y_size, other.x_size) {}

  Grid(Grid<T>&& other)
      : data(std::exchange(other.data, nullptr)),
        y_size(std::exchange(other.y_size, 0)),
        x_size(std::exchange(other.x_size, 0)) {}

  Grid<T>& operator=(Grid<T>& other) {
    Grid<T> copy = other;
    swap(other);
    return *this;
  }

  Grid<T>& operator=(Grid<T>&& other) {
    Grid<T> copy = std::move(other);
    swap(other);
    return *this;
  }

  Grid(T const& t) : Grid(std::addressof(t), 1, 1) {}

  Grid(size_type y_size, size_type x_size, T const& t = T())
      : data(allocate(y_size, x_size)), y_size(y_size), x_size(x_size) {
    size_type full_size = x_size * y_size;
    for (size_type i = 0; i < full_size; ++i) {
      new (data + i) T(t);
    }
  }

  ~Grid<T>() {
    size_type full_size = x_size * y_size;
    if (full_size) {
      for (size_type i = 0; i < full_size; ++i) {
        data[i].~T();
      }
      delete[] reinterpret_cast<char*>(data);
    }
  }

  T operator()(size_type y_idx, size_type x_idx) const {
    return data[y_idx * x_size + x_idx];
  }

  T& operator()(size_type y_idx, size_type x_idx) {
    return data[y_idx * x_size + x_idx];
  }

  T* operator[](size_type y_idx) { return data + y_idx * x_size; }

  const T* operator[](size_type y_idx) const { return data + y_idx * x_size; }

  Grid<T>& operator=(T const& t) {
    for (auto it = data, end = data + x_size * y_size; it != end; ++it) *it = t;
    return *this;
  }

  size_type get_y_size() const { return y_size; }
  size_type get_x_size() const { return x_size; }

  void swap(Grid<T> other) {
    std::swap(data, other.data);
    // std::swap(x_size, other.x_size);
    // std::swap(y_size, other.y_size);
  }

 private:
  T* allocate(size_type x_sz, size_type y_sz) {
    size_type full_size = x_sz * y_sz;
    return reinterpret_cast<T*>(new char[full_size]);
  }
};

int main() {
  Grid<float> g(3, 2, 0.0f);
  assert(3 == g.get_y_size());
  assert(2 == g.get_x_size());

  using gsize_t = Grid<int>::size_type;

  for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
      assert(0.0f == g[y_idx][x_idx]);
  for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
      g[y_idx][x_idx] = 1.0f;

  for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
      assert(1.0f == g(y_idx, x_idx));
  return 0;
}