//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo

#ifndef SHARED_PTR_S_PTR_COUNTER_HPP
#define SHARED_PTR_S_PTR_COUNTER_HPP
#pragma once
#include <atomic>
#include <memory>
#include <vector>

template <typename T>
class s_ptr_counter {
 public:
 explicit s_ptr_counter(T* p): ptr(p), counter(1) {}

  void AddPointer() {
      ++counter;
  }

  void Clear() {
        if(--counter) {
          delete ptr;
          delete this;
        }
  }

  auto GetCount() -> size_t {
    return counter.load();
  }

 private:
  T* ptr;
  std::atomic<size_t> counter;
};


#endif  // SHARED_PTR_S_PTR_COUNTER_HPP
