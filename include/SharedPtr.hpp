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
  {
    if ( std::is_move_constructible<T>::value ) {
      ptr = r.ptr;
      counter = r.counter;
      counter->AddPointer();
    } else {
      throw std::runtime_error("ERROR: Not copiable type!");
    }
  }

  SharedPtr(SharedPtr&& r) {
    if (std::is_move_assignable<T>::value) {
      std::swap(ptr, r.ptr);
      std::swap(counter, r.counter);
    }  else {
      throw std::runtime_error("ERROR: Not assignable type!");
    }
  }

  ~SharedPtr() noexcept{
    Clear();
  }

  auto operator=(const SharedPtr& r) -> SharedPtr&{
    if (std::is_move_constructible<T>::value && &r != this) {
      Clear();

      ptr = r.ptr;
      counter = r.counter;

      AddPoint();
    } else if ( &r == this ) {
      std::cout << "The object you want to copy is equal to this\n";
    } else {
      throw std::runtime_error("ERROR: Not copiable type!");
    }
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr&{
    if (std::is_move_assignable<T>::value && &r != this) {
      Clear();

      ptr = std::move(r.ptr);
      counter = std::move(r.counter);
    } else if (&r == this) {
      std::cout << "The object you want to assign is equal to this\n";
    } else {
      throw std::runtime_error("ERROR: Not assignable type!");
    }
    return *this;
  }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const{
    return (ptr != nullptr);
  }// ?? Указатель должен быть удалён сразу,
                         // как только счётчик становится равен 0

  auto operator*() const -> T&{
    return *(ptr);
  }

  auto operator->() const -> T*{
    return ptr;
  }

  inline auto Get() const -> T*{
    return ptr;
  }

  inline void Swap(SharedPtr& r){
    std::swap(ptr, r.ptr);
    std::swap(counter, r.counter);
  }

  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот же управляемый объект
  inline auto GetCount() const -> size_t{
    return (counter != nullptr) ? counter->GetCount(): 0;
  }

 private:
 inline void AddPoint(){
    if (counter) {
      counter->AddPointer();
    }
  }

 inline void Clear(){
    if (counter) {
      counter->Clear();
    }
  }

 private:
  T* ptr;
  SPtrCounter<T>* counter;
};

#endif  // INCLUDE_SHAREDPTR_HPP_
