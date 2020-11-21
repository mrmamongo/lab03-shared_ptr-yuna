//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo
#include "../include/SharedPtr.hpp"


/*
 * =================CONSTRUCTORS=================
 */
template <typename T>
SharedPtr<T>::SharedPtr<T>() noexcept
    : ptr(nullptr), counter(nullptr) {

}
template <typename T>
SharedPtr<T>::SharedPtr<T>(T *p) {
  std::unique_ptr<T> temp(p);

  counter = new s_ptr_counter<T>(temp.get());

  ptr = temp.release();
}

template <typename T>
SharedPtr<T>::SharedPtr<T>(SharedPtr<T> &&r) noexcept {
  ptr = std::move(r.ptr);
  counter = std::move(r.counter);
}

template <typename T>
SharedPtr<T>::SharedPtr<T>(const SharedPtr<T> &r)
    : ptr(r.ptr), counter(r.counter) {
  AddPoint();
}

template <typename T>
SharedPtr<T>::~SharedPtr<T>() noexcept {
  Clear();
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

template <typename T>
auto SharedPtr<T>::operator->() const -> T * {
  return ptr;
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

/*
 * =================PRIVATE METHODS==============
 */

template <typename T>
void SharedPtr<T>::AddPoint() {
  if (counter) {
    counter->AddPointer();
  }
}

template <typename T>
void SharedPtr<T>::Clear() {
  if (counter) {
    counter->Clear();
  }
}