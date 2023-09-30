
struct ICloneable {
  virtual ICloneable* clone() const = 0;
  virtual ~ICloneable() {}
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder : virtual public ICloneable {
  ValueHolder(const T& data) : data_(data){};
  ICloneable* clone() const override { return new ValueHolder<T>(data_); };
  ~ValueHolder(){};
  T data_;
};  // дальше самостоятельно
