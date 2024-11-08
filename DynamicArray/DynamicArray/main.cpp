#include "array.h"
#include <iostream>

int main() {
  Array<int> a;

  // Вставка чисел от 1 до 10 в массив
  for (int i = 0; i < 10; ++i) {
    a.Insert(i + 1);
  }

  // Умножение каждого элемента на 2 с использованием range-based for
  for (auto& elem : a) {
    elem *= 2;
  }

  // Вывод элементов массива
  for (const auto& elem : a) {
    std::cout << elem << std::endl;
  }

  return 0;
}
