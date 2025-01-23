#pragma once

#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <algorithm>

// Шаблонный класс динамического массива
template<typename T>
class Array final {
private:
  T* data_;                               // Указатель на данные массива
  int sizeMax_;                           // Максимальный размер массива
  int sizeCurrent_;                       // Текущий размер массива
  static constexpr int sizeDefault_ = 8;  // Размер массива по умолчанию

  void Resize_(int new_size);         // Перераспределение памяти
  void Clear_();                      // Очистка массива
  void Swap_(Array& other) noexcept;  // Обмен значениями

public:
  // Вложенные классы итераторов
  class Iterator;
  class ConstIterator;
  class ReverseIterator;
  class ConstReverseIterator;

  // Конструкторы и деструктор
  Array();                                       // Конструктор по умолчанию
  explicit Array(int user_size);                 // Пользовательский конструктор
  Array(const Array& other);                     // Конструктор копирования
  Array(Array&& other) noexcept;                 // Конструктор перемещения
  ~Array();                                      // Деструктор

  // Операторы присваивания
  Array& operator=(const Array& other);          // Оператор присваивания копированием
  Array& operator=(Array&& other) noexcept;      // Оператор присваивания перемещением

  // Методы доступа
  T& operator[](int index);                      // Оператор индексирования (неконстантный)
  const T& operator[](int index) const;          // Оператор индексирования (константный)

  const T& at(int index) const;                  // Проверка выхода за границу массива (константная)
  T& at(int index);                              // Проверка выхода за границу массива (неконстантная)

  // Основные методы
  int Size() const;                              // Получение текущего размера массива
  int SizeMax() const;                           // Получение максимального размера массива
  int Insert(const T& value);                    // Вставка элемента в конец
  int Insert(int index, const T& value);         // Вставка элемента по индексу
  void Remove(int index);                        // Удаление элемента

  // Итераторы
  Iterator begin();                      // Итератор на начало массива
  Iterator end();                        // Итератор на конец массива
  ConstIterator cbegin() const;          // Константный итератор на начало массива
  ConstIterator cend() const;            // Константный итератор на конец массива
  ReverseIterator rbegin();              // Обратный итератор на начало массива
  ReverseIterator rend();                // Обратный итератор на конец массива
  ConstReverseIterator crbegin() const;  // Константный обратный итератор на начало массива
  ConstReverseIterator crend() const;    // Константный обратный итератор на конец массива
};
