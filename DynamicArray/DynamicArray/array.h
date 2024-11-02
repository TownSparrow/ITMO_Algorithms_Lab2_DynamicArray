#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstdlib>
#include <cassert>
#include <utility>

template<typename T>
class Array {
public:
  Array(); // конструктор: объявление и выделение памяти
  ~Array(); // деструктор: освобождение памяти

  void Insert(const T& value); // вставка элемента в массив
  void Remove(int index); // удаление элемента из массива по индексу
  T& operator[] (int index); // оператор индексирования
  int Size() const; // размер массива

  class Iterator; // объявление итератора
  Iterator begin(); // возвращение первого элемента через итератор
  Iterator end(); // возвращение последнего элемента через итератор

private:
  void Resize(); // изменение размерности массива

  T* data_; // указатель на данные
  int capacity_; // вместимость массива
  int current_size_; // текущий размер массива
};

template<typename T>
class Array<T>::Iterator {
public:
  explicit Iterator(T* ptr) : ptr_(ptr) {}

  T& operator*() { return *ptr_; } // разыменование
  Iterator& operator++() { ++ptr_; return *this; } // префиксный инкремент
  bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; } // сравнение

private:
  T* ptr_;
};

#endif // ARRAY_H_
