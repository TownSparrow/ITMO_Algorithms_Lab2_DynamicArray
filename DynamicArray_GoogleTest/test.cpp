#include "pch.h"
#include <gtest/gtest.h>
#include "../DynamicArray/array.cpp"
#include <string>

using namespace std;

// ����: ������� � ������ ������
TEST(DynamicArrayTest, InsertIntoEmptyArray) {
  Array<int> arr;
  arr.Insert(42);
  EXPECT_EQ(arr.Size(), 1);
  EXPECT_EQ(arr[0], 42);
}

// ����: ������� ��������� �� �������
TEST(DynamicArrayTest, InsertByIndex) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(1, 15); // ������� � ��������
  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(arr[1], 15);
}

// ����: �������� ��������
TEST(DynamicArrayTest, RemoveElement) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(30);
  arr.Remove(1); // �������� �������� �� �������
  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 30);
}

// ����: ��������� �������� ����� ���������
TEST(DynamicArrayTest, HandleLargeNumberOfElements) {
  Array<int> arr;
  for (int i = 0; i < 1000; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), 1000);
  EXPECT_EQ(arr[500], 500);
}

// ����: ������ � ����� std::string
TEST(DynamicArrayTest, HandleStringType) {
  Array<string> arr;
  arr.Insert("hello");
  arr.Insert("world");
  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr[0], "hello");
  EXPECT_EQ(arr[1], "world");
}

// ����: �������� ������ ����������
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

// ����: �������� ������ �������� ����������
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

// ����: ��������� ������� � ������������������ ������
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

// ����: �������� ������ �� ������� �������
TEST(DynamicArrayTest, OutOfBoundsAccess) {
  Array<int> arr;
  arr.Insert(10);
  arr.Insert(20);
  arr.Insert(30);

  // �������� ������ at
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(-1), std::out_of_range);
}

// ����: �������� ������������� ����������� � �����������
TEST(DynamicArrayTest, CopyAndMoveConstructors) {
  Array<int> arr1;
  for (int i = 0; i < 5; ++i) {
    arr1.Insert(i + 1);
  }

  // ��������� ���������� �����������
  Array<int> arr2 = arr1;
  EXPECT_EQ(arr2.Size(), arr1.Size());
  for (int i = 0; i < arr1.Size(); ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }

  // ��������� ������������ �����������
  Array<int> arr3 = std::move(arr1);
  EXPECT_EQ(arr3.Size(), arr2.Size());
  for (int i = 0; i < arr3.Size(); ++i) {
    EXPECT_EQ(arr3[i], arr2[i]);
  }
}

// ����: �������� ��������� ������������ ������������
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

// ����: �������� ��������� ������������ ������������
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

// ����: �������� ������ at �� ������������
TEST(DynamicArrayTest, AtMethodTest) {
  Array<int> arr;
  arr.Insert(5);
  arr.Insert(10);
  arr.Insert(15);

  EXPECT_EQ(arr.at(0), 5);
  EXPECT_EQ(arr.at(1), 10);
  EXPECT_EQ(arr.at(2), 15);

  EXPECT_THROW(arr.at(3), std::out_of_range); // ����� �� �������
}

// ������� ���� �� ������!
// � ��� � ��
TEST(DynamicArrayTest, TriggerResizeTest) {
  Array<int> arr;

  int initialSizeMax = 8;  // ��������� ������������� ������� ������� = 8
  EXPECT_EQ(arr.SizeMax(), initialSizeMax); // ������� ��������� ��������� ������������ ������� �� ���������

  int elementsToAdd = 12;  // ���������� ��������� ��� ������������
  for (int i = 0; i < elementsToAdd; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), elementsToAdd); // ����� ��������� ���������� ������� ����� ��������� � ���������
  int expectedCapacity = initialSizeMax * 2;
  EXPECT_GE(arr.SizeMax(), expectedCapacity); // � ���� �� ���������, �� � ������������ ������� ������ ���� ���� ��������� 

  // ���������, ��� �������� �������� �����������
  for (int i = 0; i < elementsToAdd; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}

// ������� ���� �� ������!
// � ��� � ��
TEST(DynamicArrayTest, TriggerResizeMoreTest) {
  Array<int> arr;

  int initialSizeMax = 8;  // ��������� ������������� ������� ������� = 8
  EXPECT_EQ(arr.SizeMax(), initialSizeMax); // ������� ��������� ��������� ������������ ������� �� ���������

  int elementsToAdd = 20;  // ���������� ��������� ��� ������������
  for (int i = 0; i < elementsToAdd; ++i) {
    arr.Insert(i);
  }
  EXPECT_EQ(arr.Size(), elementsToAdd); // ����� ��������� ���������� ������� ����� ��������� � ���������
  int expectedCapacity = initialSizeMax * 3;
  EXPECT_GE(arr.SizeMax(), expectedCapacity); // � ���� �� ���������, �� � ������������ ������� ������ ���� ���� ��������� 

  // ���������, ��� �������� �������� �����������
  for (int i = 0; i < elementsToAdd; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}