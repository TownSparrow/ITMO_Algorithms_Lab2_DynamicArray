#include "pch.h"
#include <gtest/gtest.h>
#include "../DynamicArray/array.cpp"
#include <string>

using namespace std;

// Тест: Вставка в пустой массив
TEST(DynamicArrayTest, InsertIntoEmptyArray) {
  Array<int> arr;
  arr.Insert(42);
  EXPECT_EQ(arr.Size(), 1);
  EXPECT_EQ(arr[0], 42);
}

// Тест: Вставка элементов по индексу
TEST(DynamicArrayTest, InsertByIndex) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(1, 15); // Вставка в середину
  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(arr[1], 15);
}

// Тест: Удаление элемента
TEST(DynamicArrayTest, RemoveElement) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(30);
  arr.Remove(1); // Удаление элемента по индексу
  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 30);
}

// Тест: Обработка большого числа элементов
TEST(DynamicArrayTest, HandleLargeNumberOfElements) {
  Array<int> arr;
  for (int i = 0; i < 1000; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), 1000);
  EXPECT_EQ(arr[500], 500);
}

// Тест: Работа с типом std::string
TEST(DynamicArrayTest, HandleStringType) {
  Array<string> arr;
  arr.Insert("hello");
  arr.Insert("world");
  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr[0], "hello");
  EXPECT_EQ(arr[1], "world");
}

// Тест: Проверка работы итераторов
TEST(DynamicArrayTest, IteratorTraversal) {
  Array<int> arr;
  for (int i = 0; i < 5; ++i) {
    arr.Insert(i + 1);
  }

  auto it = arr.begin();
  int expected = 1;
  while (it != arr.end()) {
    EXPECT_EQ(*it, expected++);
    ++it;
  }
}

// Тест: Проверка работы обратных итераторов
TEST(DynamicArrayTest, ReverseIteratorTraversal) {
  Array<int> arr;
  for (int i = 0; i < 5; ++i) {
    arr.Insert(i + 1);
  }

  auto rit = arr.rbegin();
  int expected = 5;
  while (rit != arr.rend()) {
    EXPECT_EQ(*rit, expected--);
    ++rit;
  }
}

// Тест: Обработка вставки с перераспределением памяти
TEST(DynamicArrayTest, InsertWithResize) {
  Array<int> arr;
  for (int i = 0; i < 10; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}

// Тест: Проверка выхода за границу массива
TEST(DynamicArrayTest, OutOfBoundsAccess) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(30);

  // Проверка метода at
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(-1), std::out_of_range);
}

// Тест: Проверка конструкторов копирования и перемещения
TEST(DynamicArrayTest, CopyAndMoveConstructors) {
  Array<int> arr1;
  for (int i = 0; i < 5; ++i) {
    arr1.Insert(i + 1);
  }

  // Проверяем копирующий конструктор
  Array<int> arr2 = arr1;
  EXPECT_EQ(arr2.Size(), arr1.Size());
  for (int i = 0; i < arr1.Size(); ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }

  // Проверяем перемещающий конструктор
  Array<int> arr3 = std::move(arr1);
  EXPECT_EQ(arr3.Size(), arr2.Size());
  for (int i = 0; i < arr3.Size(); ++i) {
    EXPECT_EQ(arr3[i], arr2[i]);
  }
}

// Тест: Проверка оператора присваивания копированием
TEST(DynamicArrayTest, CopyAssignmentOperator) {
  Array<int> arr1;
  for (int i = 0; i < 5; ++i) {
    arr1.Insert(i + 1);
  }

  Array<int> arr2;
  arr2 = arr1;
  EXPECT_EQ(arr2.Size(), arr1.Size());
  for (int i = 0; i < arr1.Size(); ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }
}

// Тест: Проверка оператора присваивания перемещением
TEST(DynamicArrayTest, MoveAssignmentOperator) {
  Array<int> arr1;
  for (int i = 0; i < 5; ++i) {
    arr1.Insert(i + 1);
  }

  Array<int> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.Size(), 5);
  for (int i = 0; i < arr2.Size(); ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
}

// Тест: Проверка метода at на корректность
TEST(DynamicArrayTest, AtMethodTest) {
  Array<int> arr;
  arr.Insert(5);
  arr.Insert(10);
  arr.Insert(15);

  EXPECT_EQ(arr.at(0), 5);
  EXPECT_EQ(arr.at(1), 10);
  EXPECT_EQ(arr.at(2), 15);

  EXPECT_THROW(arr.at(3), std::out_of_range); // Выход за пределы
}

// сделать тест на ресайз!
// а вот и он
TEST(DynamicArrayTest, TriggerResizeTest) {
  Array<int> arr;

  int initialSizeMax = 8;  // начальная максимиальная емкость массива = 8
  EXPECT_EQ(arr.SizeMax(), initialSizeMax); // сначала проверяем начальную максимальную емкость по умолчанию

  int elementsToAdd = 12;  // количество элементов для переполнения
  for (int i = 0; i < elementsToAdd; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), elementsToAdd); // затем проверяем фактически сколько стало элементов в коллекции
  int expectedCapacity = initialSizeMax * 2;
  EXPECT_GE(arr.SizeMax(), expectedCapacity); // и если всё сработало, то и максимальная ёмкость должна была быть увеличена 

  // проверяем, что элементы остались корректными
  for (int i = 0; i < elementsToAdd; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}

// сделать тест на ресайз!
// а вот и он
TEST(DynamicArrayTest, TriggerResizeMoreTest) {
  Array<int> arr;

  int initialSizeMax = 8;  // начальная максимиальная емкость массива = 8
  EXPECT_EQ(arr.SizeMax(), initialSizeMax); // сначала проверяем начальную максимальную емкость по умолчанию

  int elementsToAdd = 20;  // количество элементов для переполнения
  for (int i = 0; i < elementsToAdd; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), elementsToAdd); // затем проверяем фактически сколько стало элементов в коллекции
  int expectedCapacity = initialSizeMax * 3;
  EXPECT_GE(arr.SizeMax(), expectedCapacity); // и если всё сработало, то и максимальная ёмкость должна была быть увеличена 

  // проверяем, что элементы остались корректными
  for (int i = 0; i < elementsToAdd; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}