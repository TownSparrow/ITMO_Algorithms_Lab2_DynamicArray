#include "array.h"
#include <iostream>

int main() {
  Array<int> a;

  // вставка чисел от 1 до 10 в массив
  for (int i = 0; i < 10; ++i) {
    a.Insert(i + 1);
  }

  // умножение каждого элемента на 2 с использованием итератора
  for (auto& elem : a) {
    elem *= 2;
  }

  // вывод элементов массива
  for (const auto& elem : a) {
    std::cout << elem << std::endl;
  }

  return 0;
}
