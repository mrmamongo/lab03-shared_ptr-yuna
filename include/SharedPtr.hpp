//
// Created by lamp on 20.11.2020.
//
// Copyright 2020 mrmamongo

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SPtrCounter.hpp"

using std::string;

template <typename T>
class SharedPtr {
 public:
  SharedPtr() noexcept
      : ptr(nullptr), counter(nullptr) {}

  explicit SharedPtr(T* p){
    std::unique_ptr<T> temp(p);

    counter = new SPtrCounter<T>(temp.get());

    ptr = temp.release();
  }

  SharedPtr(const SharedPtr& r)
      : ptr(r.ptr), counter(r.counter) {
    AddPoint();
  }

  SharedPtr(SharedPtr&& r)  noexcept{
    ptr = std::move(r.ptr);
    counter = std::move(r.counter);
  }

  ~SharedPtr() noexcept{
    Clear();
  }

  auto operator=(const SharedPtr& r) noexcept -> SharedPtr&{
    if (r != this) {
      Clear();

      ptr = r.ptr;
      counter = r.counter;

      AddPoint();

      return *this;
    }
  }

  auto operator=(SharedPtr&& r)   noexcept -> SharedPtr&{
    if (r != this) {
      Clear();

      ptr = std::move(r.ptr);
      counter = std::move(r.counter);

      return *this;
    }
  }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const{
    return (ptr!= nullptr);
  }// ?? Указатель должен быть удалён сразу,
                         // как только счётчик становится равен 0

  auto operator*() const -> T&{
    return *(ptr);
  }

  auto operator->() const -> T*{
    return ptr;
  }

  auto Get() const -> T*{
    return ptr;
  }

  void Swap(SharedPtr& r){
    T* temp_p = std::move(ptr);
    SPtrCounter<T>* temp_counter = std::move(counter);

    ptr = std::move(r.ptr);
    counter = std::move(r.counter);

    r.ptr = std::move(temp_p);
    r.counter = std::move(temp_counter);
  }

  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  auto GetCount() const -> size_t{
    return (counter != nullptr) ? counter->GetCount(): 0;
  }

 private:
  void AddPoint(){
    if (counter) {
      counter->AddPointer();
    }
  }

  void Clear(){
    if (counter) {
      counter->Clear();
    }
  }

 private:
  T* ptr;
  SPtrCounter<T>* counter;
};

#endif  // INCLUDE_SHAREDPTR_HPP_
