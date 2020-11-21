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
  SharedPtr() noexcept: ptr(nullptr), counter(nullptr) {}

  explicit SharedPtr(T* p){
      std::unique_ptr<T> temp(p);

      counter = new s_ptr_counter<T>(temp.get());

      ptr = temp.release();
  }
  SharedPtr(const SharedPtr& r): ptr(r.ptr), counter(r.counter){
    AddPoint();
  }
  SharedPtr(SharedPtr&& r)  noexcept{
      ptr = r.ptr;
      counter = r.counter;
      AddPoint();
  }
  ~SharedPtr() noexcept{
      Clear();
  }
  auto operator=(const SharedPtr& r) noexcept -> SharedPtr& {
      Clear();

      ptr = r.ptr;
      counter = r.counter;

      AddPoint();

      return *this;
  }
  auto operator=(SharedPtr&& r)   noexcept -> SharedPtr&{
      Clear();

      ptr = r.ptr;
      counter = r.counter;

      AddPoint();

      return *this;
  }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const {
      return (ptr!= nullptr);
  } // ?? Указатель должен быть удалён сразу,
                         // как только счётчик становится равен 0

  auto operator*() const -> T& {
      return *(ptr);
  }
  auto operator->() const -> T* {
      return ptr;
  }

  auto Get() const -> T* {
      return ptr;
  }
  void Swap(SharedPtr& r) {
      T* temp_p = std::move(ptr);
      s_ptr_counter<T>* temp_counter = std::move(counter);

      ptr = std::move(r.ptr);
      counter = std::move(r.counter);

      r.ptr = std::move(temp_p);
      r.counter = std::move(temp_counter);
  }
  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  auto GetCount() const -> size_t {
      return (counter != nullptr) ? counter->GetCount(): 0;
  }

 private:
  void AddPoint(){
      if(counter) {
        counter->AddPointer();
      }
  }

  void Clear() {
    if (counter) {
      counter->Clear();
    }
  }

 private:
  T* ptr;
  s_ptr_counter<T>* counter;
};

#endif  // INCLUDE_SHAREDPTR_HPP_
