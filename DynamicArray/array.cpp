#include "array.h"
#include <new> // Для placement new

// Прямой итератор
template <typename T>
class Array<T>::Iterator {
private:
  T* current_;

public:
  Iterator(T* start) : current_(start) {}

  T& operator*() const { return *current_; }
  Iterator& operator++() { ++current_; return *this; }                         // Префиксный ++
  Iterator operator++(int) { Iterator temp = *this; ++current_; return temp; } // Постфиксный ++
  bool operator!=(const Iterator& other) const { return current_ != other.current_; }
};

// Константный прямой итератор
template <typename T>
class Array<T>::ConstIterator {
private:
  const T* current_;

public:
  ConstIterator(const T* start) : current_(start) {}

  const T& operator*() const { return *current_; }
  ConstIterator& operator++() { ++current_; return *this; }
  ConstIterator operator++(int) { ConstIterator temp = *this; ++current_; return temp; }
  bool operator!=(const ConstIterator& other) const { return current_ != other.current_; }
};

// Обратный итератор
template <typename T>
class Array<T>::ReverseIterator {
private:
  T* current_;

public:
  ReverseIterator(T* start) : current_(start - 1) {}

  T& operator*() const { return *current_; }
  ReverseIterator& operator++() { --current_; return *this; }
  ReverseIterator operator++(int) { ReverseIterator temp = *this; --current_; return temp; }
  bool operator!=(const ReverseIterator& other) const { return current_ != other.current_; }
};

// Константный обратный итератор
template <typename T>
class Array<T>::ConstReverseIterator {
private:
  const T* current_;

public:
  ConstReverseIterator(const T* start) : current_(start - 1) {}

  const T& operator*() const { return *current_; }
  ConstReverseIterator& operator++() { --current_; return *this; }
  ConstReverseIterator operator++(int) { ConstReverseIterator temp = *this; --current_; return temp; }
  bool operator!=(const ConstReverseIterator& other) const { return current_ != other.current_; }
};

// Конструктор по умолчанию
template<typename T>
Array<T>::Array() : sizeMax_(sizeDefault_), sizeCurrent_(0) {
  data_ = static_cast<T*>(malloc(sizeMax_ * sizeof(T)));
  if (!data_) throw std::bad_alloc();
}

// Пользовательский конструктор
template<typename T>
Array<T>::Array(int user_size) : sizeMax_(user_size), sizeCurrent_(0) {
  data_ = static_cast<T*>(malloc(sizeMax_ * sizeof(T)));
  if (!data_) throw std::bad_alloc();
}

// Конструктор копирования
template<typename T>
Array<T>::Array(const Array& other) : sizeMax_(other.sizeMax_), sizeCurrent_(other.sizeCurrent_) {
  data_ = static_cast<T*>(malloc(sizeMax_ * sizeof(T)));
  if (!data_) throw std::bad_alloc();
  for (int i = 0; i < sizeCurrent_; ++i) {
    new (data_ + i) T(other.data_[i]);
  }
}

// Конструктор перемещения
template<typename T>
Array<T>::Array(Array&& other) noexcept : data_(other.data_), sizeMax_(other.sizeMax_), sizeCurrent_(other.sizeCurrent_) {
  other.data_ = nullptr;
  other.sizeMax_ = 0;
  other.sizeCurrent_ = 0;
}

// Деструктор
template<typename T>
Array<T>::~Array() {
  Clear_();
  free(data_);
}

// Оператор присваивания копированием
template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
  if (this != &other) {
    Array temp(other);
    Swap_(temp);
  }
  return *this;
}

// Оператор присваивания перемещением
template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
  if (this != &other) {
    Swap_(other);
  }
  return *this;
}

// Оператор индексирования (неконстантный)
template<typename T>
T& Array<T>::operator[](int index) {
  assert(index >= 0 && index < sizeCurrent_);
  return data_[index];
}

// Оператор индексирования (константный)
template<typename T>
const T& Array<T>::operator[](int index) const {
  assert(index >= 0 && index < sizeCurrent_);
  return data_[index];
}

// Метод at (неконстантный)
template<typename T>
T& Array<T>::at(int index) {
  if (index < 0 || index >= sizeCurrent_) {
    throw std::out_of_range("Индекс вне границ массива... Ну вы поняли.");
  }
  return data_[index];
}

// Метод at (константный)
template<typename T>
const T& Array<T>::at(int index) const {
  if (index < 0 || index >= sizeCurrent_) {
    throw std::out_of_range("Индекс вне границ массива... Ну вы поняли.");
  }
  return data_[index];
}

// Получение размера массива
template<typename T>
int Array<T>::Size() const {
  return sizeCurrent_;
}

// Метод для получения текущей емкости
template<typename T>
int Array<T>::SizeMax() const {
  return sizeMax_;
}

// Вставка элемента в конец массива
template<typename T>
int Array<T>::Insert(const T& value) {
  return Insert(sizeCurrent_, value);
}

// Вставка элемента по индексу
template<typename T>
int Array<T>::Insert(int index, const T& value) {
  assert(index >= 0 && index <= sizeCurrent_);
  if (sizeCurrent_ >= sizeMax_) {
    Resize_(sizeMax_ * 2);
  }
  for (int i = sizeCurrent_; i > index; --i) {
    if constexpr (std::is_move_constructible_v<T>) {
      new (data_ + i) T(std::move(data_[i - 1]));
      data_[i - 1].~T();
    } else {
      new (data_ + i) T(data_[i - 1]);
      data_[i - 1].~T();
    }
  }
  new (data_ + index) T(value);
  ++sizeCurrent_;
  return index;
}

// Удаление элемента
template<typename T>
void Array<T>::Remove(int index) {
  assert(index >= 0 && index < sizeCurrent_);

  if constexpr (std::is_move_constructible_v<T>) {
    for (int i = index; i < sizeCurrent_ - 1; ++i) {
      new (data_ + i) T(std::move(data_[i + 1]));
      //data_[i] = std::move_if_noexcept(data_[i + 1]);
    }
  } else {
    for (int i = index; i < sizeCurrent_; ++i) {
      new (data_ + i) T(data_[i + 1]);
      //data_[i].operator = (data_[i + 1]);
    }
  }
  data_[sizeCurrent_ - 1].~T();
  --sizeCurrent_;
}

// Увеличение емкости массива
template<typename T>
void Array<T>::Resize_(int new_size) {
  T* new_data = static_cast<T*>(malloc(new_size * sizeof(T)));
  if (!new_data) throw std::bad_alloc();  
  if constexpr (std::is_move_constructible_v<T>) {
    for (int i = 0; i < sizeCurrent_; ++i) {
      new (new_data + i) T(std::move(data_[i]));  
      data_[i].~T();
    }
  }
  else if constexpr (std::is_copy_constructible_v<T>) {
    for (int i = 0; i < sizeCurrent_; ++i) {
      new (new_data + i) T(data_[i]); 
      data_[i].~T();
    }
  }
  else {
    static_assert(std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>,
      "Тип должен поддерживать либо перемещение, либо копирование!");
  }

  free(data_);  
  data_ = new_data;  
  sizeMax_ = new_size;  
}



// Очистка массива
template<typename T>
void Array<T>::Clear_() {
  for (int i = 0; i < sizeCurrent_; ++i) {
    data_[i].~T();
  }
  sizeCurrent_ = 0;
}

// Замена элементов местами
template<typename T>
void Array<T>::Swap_(Array& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(sizeMax_, other.sizeMax_);
  std::swap(sizeCurrent_, other.sizeCurrent_);
}


// Итераторы
template<typename T>
typename Array<T>::Iterator Array<T>::begin() { return Iterator(data_); }

template<typename T>
typename Array<T>::Iterator Array<T>::end() { return Iterator(data_ + sizeCurrent_); }

template<typename T>
typename Array<T>::ConstIterator Array<T>::cbegin() const { return ConstIterator(data_); }

template<typename T>
typename Array<T>::ConstIterator Array<T>::cend() const { return ConstIterator(data_ + sizeCurrent_); }

template<typename T>
typename Array<T>::ReverseIterator Array<T>::rbegin() { return ReverseIterator(data_ + sizeCurrent_); }

template<typename T>
typename Array<T>::ReverseIterator Array<T>::rend() { return ReverseIterator(data_); }

template<typename T>
typename Array<T>::ConstReverseIterator Array<T>::crbegin() const { return ConstReverseIterator(data_ + sizeCurrent_); }

template<typename T>
typename Array<T>::ConstReverseIterator Array<T>::crend() const { return ConstReverseIterator(data_); }
