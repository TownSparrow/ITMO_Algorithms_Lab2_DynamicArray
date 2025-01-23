// Константный прямой итератор для класса Array
template<typename T>
class Array<T>::ConstIterator {
private:
  const T* current_;  // Текущий элемент
  const T* end_;      // Конец диапазона итерации

public:
  // Конструктор итератора
  ConstIterator(const T* start, const T* end) : current_(start), end_(end) {}

  // Получение текущего элемента (только для чтения)
  const T& get() const {
    return *current_;
  }

  // Переход к следующему элементу
  void next() {
    if (hasNext()) {
      ++current_;
    }
  }

  // Проверка, есть ли следующий элемент
  bool hasNext() const {
    return current_ < end_;
  }
};
