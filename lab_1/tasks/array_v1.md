# Задача № 1

Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.

template <typename T>
class Array
{
public: 
    // Список операций:
    //
    explicit Array(size_t, const T&);
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array(const Array &);
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    Array(const Array &&);
    //   конструктор перемещения
    //
    ~Array();
    //   деструктор, если он вам необходим.
    //
    Array& operator=(const Array &);
    //   оператор копирующего присваивания.
    //
    Array& operator=(Array &&);
    //   оператор перемещающего присваивания.
    //
    size_t size() const;
    //   возвращает размер массива (количество
    //                              элементов).
    //
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;
    //   две версии оператора доступа по индексу.
private:
    // поля определите сами
};
```


# Задача № 1

Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.

Implement template class Array<T>.

template <typename T>
class Array
{
public: 
    explicit Array(size_t, const T&);
    Array(const Array &);
    Array(const Array &&);
    ~Array();
    Array& operator=(const Array &);
    Array& operator=(Array &&);
    size_t size() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;
private:
    // something
};
```