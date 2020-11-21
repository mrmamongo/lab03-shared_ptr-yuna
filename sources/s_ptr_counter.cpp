//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo
#include "../include/s_ptr_counter.hpp"

template <typename T>
void s_ptr_counter<T>::AddPointer() noexcept {
  ++counter;
}

template <typename T>
auto s_ptr_counter<T>::GetCount() const noexcept -> int {
  return counter.load();
}

template <typename T>
void s_ptr_counter<T>::Clear() noexcept {
  if (!--counter) {
    ptr = nullptr;
    delete this;
  }
}
