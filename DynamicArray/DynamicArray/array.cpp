#include "array.h"
#include <string>

// Конструктор по умолчанию: выделяет память под базовый размер массива
template<typename T>
Array<T>::Array() : data_(nullptr), capacity_(8), current_size_(0) {
  data_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
  if (!data_) throw std::bad_alloc();
}

// Деструктор освобождает выделенную память
template<typename T>
Array<T>::~Array() {
  for (int i = 0; i < current_size_; ++i) {
    data_[i].~T();
  }
  free(data_);
}

// Перераспределение памяти при достижении емкости
template<typename T>
void Array<T>::Resize() {
  int new_capacity = capacity_ == 0 ? 8 : static_cast<int>(capacity_ * 1.6);
  T* new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));
  if (!new_data) throw std::bad_alloc();

  for (int i = 0; i < current_size_; ++i) {
    new(new_data + i) T(std::move(data_[i]));
    data_[i].~T();
  }

  free(data_);
  data_ = new_data;
  capacity_ = new_capacity;
}

// Вставка элемента в конец массива
template<typename T>
void Array<T>::Insert(const T& value) {
  if (current_size_ >= capacity_) {
    Resize();
  }
  new(data_ + current_size_) T(value);
  ++current_size_;
}

// Удаление элемента по индексу
template<typename T>
void Array<T>::Remove(int index) {
  assert(index >= 0 && index < current_size_);
  data_[index].~T();
  for (int i = index; i < current_size_ - 1; ++i) {
    new(data_ + i) T(std::move(data_[i + 1]));
    data_[i + 1].~T();
  }
  --current_size_;
}

// Доступ к элементу по индексу
template<typename T>
T& Array<T>::operator[](int index) {
  assert(index >= 0 && index < current_size_);
  return data_[index];
}

// Доступ к элементу по индексу с учётом константы
template<typename T>
const T& Array<T>::operator[](int index) const {
  assert(index >= 0 && index < current_size_);
  return data_[index];
}

// Возвращает текущий размер массива
template<typename T>
int Array<T>::Size() const {
  return current_size_;
}

// Итератор begin() для поддержки range-based for
template<typename T>
T* Array<T>::begin() {
  return data_;
}

// То же самое, но для константы
template<typename T>
const T* Array<T>::begin() const {
  return data_;
}

// Итератор end() для поддержки range-based for
template<typename T>
T* Array<T>::end() {
  return data_ + current_size_;
}

// То же самое, но для константы
template<typename T>
const T* Array<T>::end() const {
  return data_ + current_size_;
}

// Инстанцирование шаблона для типов
template class Array<int>;
template class Array<float>;
template class Array<double>;
template class Array<std::string>;
