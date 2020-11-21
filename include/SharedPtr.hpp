//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <vector>
#include <memory>
#include "s_ptr_counter.hpp"
#include <string>
#include <utility>

using std::string;

template <typename T>
class SharedPtr {
 public:
  SharedPtr() noexcept;

  explicit SharedPtr(T* p);

  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r)  noexcept;

  ~SharedPtr() noexcept;
  auto operator=(const SharedPtr& r) noexcept -> SharedPtr&;
  auto operator=(SharedPtr&& r)   noexcept -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;// ?? Указатель должен быть удалён сразу,
                         // как только счётчик становится равен 0

  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto Get() const -> T*;
  void Swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  auto GetCount() const -> size_t;

 private:
  void AddPoint();

  void Clear();

 private:
  T* ptr;
  s_ptr_counter<T>* counter;
};

#endif  // INCLUDE_SHAREDPTR_HPP_
