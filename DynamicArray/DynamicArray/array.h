#ifndef ARRAY_H_
#define ARRAY_H_

#include <cassert>
#include <cstdlib>
#include <iterator>
#include <new>
#include <utility>

template<typename T>
class Array {
public:
  // Конструктор по умолчанию
  Array();

  // Деструктор освобождает выделенную память
  ~Array();

  // Вставка элемента в конец массива
  void Insert(const T& value);

  // Удаление элемента по индексу
  void Remove(int index);

  // Доступ по индексу
  T& operator[](int index);
  const T& operator[](int index) const;

  // Получение текущего размера
  int Size() const;

  // Методы begin и end для range-based for
  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

private:
  // Перераспределение памяти
  void Resize();

  T* data_;            // Указатель на данные массива
  int capacity_;       // Емкость массива
  int current_size_;   // Текущий размер массива
};

#endif // ARRAY_H_
