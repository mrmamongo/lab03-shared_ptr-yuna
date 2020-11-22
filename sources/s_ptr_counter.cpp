//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo
#include "s_ptr_counter.hpp"

template <typename T>
auto s_ptr_counter<T>::GetCount() const noexcept -> size_t {
  return counter.load();
}
