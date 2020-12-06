//
// Created by lamp on 21.11.2020.
//
// Copyright 2020 mrmamongo
#include <gtest/gtest.h>

#include <utility>
#include "SharedPtr.hpp"


class MyClass {
 public:
    int value;
    string name;

    explicit MyClass(int value_ = 10, string name_ = "Typical Class") {
      value = value_;
      name = std::move(name_);
    }

    bool operator==(const MyClass& ref) const {
      bool out = false;
      out = value == ref.value;
      out = name == ref.name;
      return out;
    }
};

int Foo(int value){
  return value + 10;
}

int Foo_Link(int& value){
  return value += 20;
}

MyClass FooClass(MyClass object){
  object.name = "Foo";
  object.value = 10500;
  return object;
}

MyClass FooClass_Link(MyClass& object){
  object.name = "Foo_Link";
  object.value = 10500800;
  return object;
}



TEST(SharedPtrTest, TestNullptr) {
  SharedPtr<int> nullPointer;
  SharedPtr<MyClass> nullObjectPointer;
  SharedPtr<std::vector<int>> nullVectorIntPointer;
  SharedPtr<std::vector<MyClass>> nullVectorMyClassPointer;


  EXPECT_FALSE(nullPointer);
  EXPECT_FALSE(nullObjectPointer);
  EXPECT_FALSE(nullVectorIntPointer);
  EXPECT_FALSE(nullVectorMyClassPointer);
}

TEST(SharedPtrTest, TestTempType) {
  int value = 5;

  SharedPtr<int> pvalue1(&value);
  SharedPtr<int> pvalue2(pvalue1);

  EXPECT_EQ(pvalue1.GetCount(), 2);
  EXPECT_EQ(pvalue2.GetCount(), 2);

  EXPECT_EQ(*pvalue1, 5);
  EXPECT_EQ(*pvalue2, 5);

  EXPECT_EQ(*(pvalue1.Get()), 5);
  EXPECT_EQ(*(pvalue2.Get()), 5);

  EXPECT_TRUE(pvalue1);
  EXPECT_TRUE(pvalue2);

  EXPECT_EQ(Foo(*pvalue1), 15);
  EXPECT_EQ(Foo(*pvalue2), 15);

  EXPECT_EQ(Foo_Link(*pvalue1), 25);
  EXPECT_EQ(*pvalue2, 25);
}

TEST(SharedPtrTest, TestCustomType) {
  MyClass testObject;

  SharedPtr<MyClass> pobject1(&testObject);
  SharedPtr<MyClass> pobject2(pobject1);

  EXPECT_EQ(pobject1.GetCount(), 2);
  EXPECT_EQ(pobject2.GetCount(), 2);

  EXPECT_EQ(pobject1.Get()->name, "Typical Class");
  EXPECT_EQ(pobject2.Get()->name, "Typical Class");

  EXPECT_EQ(pobject1.Get()->value, 10);
  EXPECT_EQ(pobject2.Get()->value, 10);

  EXPECT_EQ(pobject1->value, 10);
  EXPECT_EQ(pobject2->value, 10);

  EXPECT_TRUE(pobject1);
  EXPECT_TRUE(pobject2);

  EXPECT_EQ(FooClass(*pobject1), MyClass(100500, "Foo"));
  EXPECT_EQ(FooClass(*pobject2), MyClass(100500, "Foo"));

  EXPECT_EQ(
      FooClass_Link(*pobject1),
      MyClass(100500800, "Foo_Link"));
  EXPECT_EQ(
      *pobject2,
      MyClass(100500800, "Foo_Link"));
}

TEST(SharedPtrTest, TestSTLContainer) {
  std::vector<int> values { 1, 2, 3, 4, 5};
  std::vector<MyClass> objects {
      MyClass
      (10, "First"),
      MyClass
      (5, "Second"),
      MyClass
      (0, "Last")
  };

  SharedPtr<std::vector<int>> pvalues(&values);
  SharedPtr<std::vector<int>> pvalues2(pvalues);
  SharedPtr<std::vector<int>> pvalues3(pvalues2);

  SharedPtr<std::vector<MyClass>> pobjects(&objects);
  SharedPtr<std::vector<MyClass>> pobjects2(pobjects);
  SharedPtr<std::vector<MyClass>> pobjects3(pobjects2);

  EXPECT_EQ((*pvalues)[0], 1);
  EXPECT_EQ((*pvalues2)[0], 1);
  EXPECT_EQ((*pvalues3)[0], 1);
  EXPECT_EQ((*pvalues)[4], 5);
  EXPECT_EQ((*pvalues2)[4], 5);
  EXPECT_EQ((*pvalues3)[4], 5);

  EXPECT_EQ((*pvalues).size(), 5);
  EXPECT_EQ((*pvalues2).size(), 5);
  EXPECT_EQ((*pvalues3).size(), 5);

  EXPECT_TRUE(pvalues);
  EXPECT_TRUE(pvalues2);
  EXPECT_TRUE(pvalues3);

  EXPECT_EQ(pvalues.GetCount(), 3);
  EXPECT_EQ(pvalues2.GetCount(), 3);
  EXPECT_EQ(pvalues3.GetCount(), 3);

  EXPECT_EQ((*pobjects)[0].name, "First");
  EXPECT_EQ((*pobjects)[0].value, 10);
  EXPECT_EQ((*pobjects2)[0].name, "First");
  EXPECT_EQ((*pobjects2)[0].value, 10);
  EXPECT_EQ((*pobjects3)[0].name, "First");
  EXPECT_EQ((*pobjects3)[0].value, 10);

  EXPECT_EQ((*pobjects)[2].name, "Last");
  EXPECT_EQ((*pobjects)[2].value, 0);
  EXPECT_EQ((*pobjects2)[2].name, "Last");
  EXPECT_EQ((*pobjects2)[2].value, 0);
  EXPECT_EQ((*pobjects3)[2].name, "Last");
  EXPECT_EQ((*pobjects3)[2].value, 0);

  EXPECT_EQ((*pobjects).size(), 3);
  EXPECT_EQ((*pobjects2).size(), 3);
  EXPECT_EQ((*pobjects3).size(), 3);

  EXPECT_TRUE(pobjects);
  EXPECT_TRUE(pobjects2);
  EXPECT_TRUE(pobjects3);
}

TEST(SharedPtrTest, SwapTestTempType) {
  int firstValue = 5;

  SharedPtr<int> pvalue1_1(&firstValue);
  SharedPtr<int> pvalue1_2(pvalue1_1);

  int secondValue = 10;

  SharedPtr<int> pvalue2_1(&secondValue);
  SharedPtr<int> pvalue2_2(pvalue2_1);
  SharedPtr<int> pvalue2_3(pvalue2_2);

  pvalue2_1.Swap(pvalue1_1);

  EXPECT_EQ(pvalue1_1.GetCount(), 3);
  EXPECT_EQ(pvalue2_1.GetCount(), 2);

  EXPECT_EQ(*pvalue1_1, 10);
  EXPECT_EQ(*pvalue2_1, 5);
}

TEST(SharedPtrTest, SwapTestCustomType) {
  MyClass firstObject {
      10, "First"
  };
  MyClass secondObject {
      5, "Second"
  };

  SharedPtr<MyClass> pobject1_1(&firstObject);
  SharedPtr<MyClass> pobject1_2(pobject1_1);

  SharedPtr<MyClass> pobject2_1(&secondObject);
  SharedPtr<MyClass> pobject2_2(pobject2_1);
  SharedPtr<MyClass> pobject2_3(pobject2_2);

  pobject1_1.Swap(pobject2_1);

  EXPECT_EQ(pobject1_1.GetCount(), 3);
  EXPECT_EQ(pobject2_1.GetCount(), 2);

  EXPECT_EQ(*pobject1_1, MyClass(5, "Second"));
  EXPECT_EQ(*pobject2_1, MyClass(10, "First"));
}

class NotCopiable {
 public:
  NotCopiable& operator= (NotCopiable&) = delete;
};

TEST(ErrorTest, TestCopiable) {
  try {
    NotCopiable notCopiableObject;
    SharedPtr<NotCopiable> pointer(&notCopiableObject);
    SharedPtr<NotCopiable> error(pointer);
  } catch (std::runtime_error& er) {
    string ref = "ERROR: Not copiable type!";
    EXPECT_EQ(ref, er.what());
  }
}

class NotAssignable {
 public:
  NotAssignable& operator= (NotAssignable&&) = delete;
};

TEST(ErrorTest, TestAssignable) {
  try{
    NotAssignable notAssignableObject;

    SharedPtr<NotAssignable> pointer(&notAssignableObject);
    SharedPtr<NotAssignable> error;
  } catch (std::runtime_error& er){
    string ref = "ERROR: Not assignable type!";
    EXPECT_EQ( ref, er.what());
  }
}

TEST(ErrorTest, TestCopiableOperator) {
  try {
    NotCopiable notCopiableObject;
    SharedPtr<NotCopiable> pointer(&notCopiableObject);
    SharedPtr<NotCopiable> error = pointer;
  } catch (std::runtime_error& er) {
    string ref = "ERROR: Not copiable type!";
    EXPECT_EQ(ref, er.what());
  }
}

TEST(ErrorTest, TestAssignableOperator) {
  try{
    NotAssignable notAssignableObject;

    SharedPtr<NotAssignable> pointer(&notAssignableObject);
    SharedPtr<NotAssignable> error = std::move(pointer);
  } catch (std::runtime_error& er){
    string ref = "ERROR: Not assignable type!";
    EXPECT_EQ( ref, er.what());
  }
}