#include "array.h"
#include <iostream>

// конструктор: объявление и выделение памяти
template<typename T>
Array<T>::Array() : data_(nullptr), capacity_(0), current_size_(0) {}

// деструктор: освобождение памяти
template<typename T>
Array<T>::~Array() {
    for (int i = 0; i < current_size_; ++i) {
        data_[i].~T();
    }
    free(data_);
}

// изменение размерности
template<typename T>
void Array<T>::Resize() {
    int new_capacity = capacity_ == 0 ? 8 : static_cast<int>(capacity_ * 1.6);
    T* new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));
    if (!new_data) {
        throw std::bad_alloc();    
    }

    for (int i = 0; i < current_size_; ++i) {
        new(new_data + i) T(std::move(data_[i]));
        data_[i].~T();
    }

    free(data_);
    data_ = new_data;
    capacity_ = new_capacity;
}

// вставка элемента
template<typename T>
void Array<T>::Insert(const T& value) {
    if (current_size_ >= capacity_) {
        Resize();
    }
    new(data_ + current_size_) T(value);
    ++current_size_;
}

// удаление элемента
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

// получение индекса через оператор
template<typename T>
T& Array<T>::operator[](int index) {
    return data_[index];
}

// получение размера массива
template<typename T>
int Array<T>::Size() const {
    return current_size_;
}

// реализация получения первого элемента массива через итератор
template<typename T>
typename Array<T>::Iterator Array<T>::begin() {
    return Iterator(data_);
}

// реализация получения последнего элемента массива через итератор
template<typename T>
typename Array<T>::Iterator Array<T>::end() {
    return Iterator(data_ + current_size_);
}

// объявление шаблона для различных типов
template class Array<int>;
template class Array<float>;
template class Array<double>;
template class Array<std::string>;
