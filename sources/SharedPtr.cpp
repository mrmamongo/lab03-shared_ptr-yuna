//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo
#include "SharedPtr.hpp"


/*
 * =================CONSTRUCTORS=================
 */
template <typename T>
SharedPtr<T>::SharedPtr() noexcept
    : ptr(nullptr), counter(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&r) noexcept {
  ptr = std::move(r.ptr);
  counter = std::move(r.counter);
}
/*
 * =================OPERATORS====================
 */

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr<T> &r)
    noexcept -> SharedPtr<T> & {
  Clear();

  ptr = r.ptr;
  counter = r.counter;

  AddPoint();

  return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr<T> &&r)
    noexcept -> SharedPtr<T> & {
  Clear();

  ptr = std::move(r.ptr);
  counter = std::move(r.counter);

  return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return (ptr!= nullptr);
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T & {
  return *(ptr);
}


/*
 * =================PUBLIC METHODS===============
 */

template <typename T>
auto SharedPtr<T>::Get() const -> T * {
  return ptr;
}

template <typename T>
void SharedPtr<T>::Swap(SharedPtr<T> &r) {
  T* temp_p = std::move(ptr);
  s_ptr_counter<T>* temp_counter = std::move(counter);

  ptr = std::move(r.ptr);
  counter = std::move(r.counter);

  r.ptr = std::move(temp_p);
  r.counter = std::move(temp_counter);
}

template <typename T>
auto SharedPtr<T>::GetCount() const -> size_t {
  return (counter != nullptr) ? counter->GetCount(): 0;
}
