#include <iostream>

#include "value_holder.cpp"
class Any {
 public:
  // В классе Any должен быть конструктор,
  // который можно вызвать без параметров,
  // чтобы работал следующий код:
  //    Any empty; // empty ничего не хранит
  Any() : data_(nullptr){};

  // В классе Any должен быть шаблонный
  // конструктор от одного параметра, чтобы
  // можно было создавать объекты типа Any,
  // например, следующим образом:
  //    Any i(10); // i хранит значение 10
  template <typename T>
  Any(const T& value) : data_(new ValueHolder<T>(value)) {}

  // В классе Any также должен быть конструктор
  // копирования (вам поможет метод clone
  // интерфейса ICloneable)
  template <typename T>
  Any(const Any& other) : data_(other.data_ ? other.data_->clone() : nullptr) {}

  // Не забудьте про деструктор. Все выделенные
  // ресурсы нужно освободить.
  ~Any() { delete data_; }

  // В классе должен быть оператор присваивания и/или
  // шаблонный оператор присваивания, чтобы работал
  // следующий код:
  //    Any copy(i); // copy хранит 10, как и i
  //    empty = copy; // empty хранит 10, как и copy
  //    empty = 0; // а теперь empty хранит 0

  Any& operator=(const Any& other) {
    if (this != &other) {
      delete data_;
      data_ = other.data_ ? other.data_->clone() : nullptr;
    }
    return *this;
  }

  // Ну и наконец, мы хотим уметь получать хранимое
  // значение, для этого определите в классе Any
  // шаблонный метод cast, который возвращает
  // указатель на хранимое значение, или нулевой
  // указатель в случае несоответствия типов или
  // если объект Any ничего не хранит:
  //    int *iptr = i.cast<int>(); // *iptr == 10
  //    char *cptr = i.cast<char>(); // cptr == 0,
  //        // потому что i хранит int, а не char
  //    Any empty2;
  //    int *p = empty2.cast<int>(); // p == 0
  // При реализации можете использавать оператор dynamic_cast (см. ниже).
  template <typename T>
  T* cast() {
    ValueHolder<T>* holder = dynamic_cast<ValueHolder<T>*>(data_);
    if (holder) {
      return &(holder->data_);
    } else {
      return nullptr;
    }
  }

 private:
  ICloneable* data_;
  // Поля и дополнительные методы определите сами
};
