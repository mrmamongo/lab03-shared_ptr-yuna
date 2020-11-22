//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo

#ifndef SHARED_PTR_S_PTR_COUNTER_HPP_
#define SHARED_PTR_S_PTR_COUNTER_HPP_
#pragma once
#include <atomic>
#include <memory>
#include <vector>

template <typename T>
class s_ptr_counter {
 public:
 explicit s_ptr_counter(T* p): ptr(p), counter(1) {}

  void AddPointer() noexcept{
    ++counter;
  }

  void Clear() noexcept{
    if (!--counter) {
      ptr = nullptr;
      delete this;
    }
  }

  auto GetCount() const noexcept -> size_t;

 private:
  T* ptr;
  std::atomic<size_t> counter;
};


#endif  // SHARED_PTR_S_PTR_COUNTER_HPP_
