//
// Created by lamp on 21.11.2020.
//
// Copyright 2020 mrmamongo
#include <gtest/gtest.h>
#include "SharedPtr.hpp"


TEST(SharedPtr_Test, Counter_Test) {
  int value = 5;

  SharedPtr<int> pvalue1(&value);
  SharedPtr<int> pvalue2(pvalue1);

  EXPECT_EQ(pvalue1.GetCount(), 2);
  EXPECT_EQ(pvalue2.GetCount(), 2);
}

TEST(SharedPtr_Test, Pointer_Test) {
  int value = 5;

  SharedPtr<int> pvalue1(&value);
  SharedPtr<int> pvalue2(pvalue1);

  EXPECT_EQ(*pvalue1, 5);
  EXPECT_EQ(*pvalue2, 5);

  struct Value{
    int value;
  };
  Value value1 { 10 };
  SharedPtr<Value> pvalue3(&value1);
  SharedPtr<Value> pvalue4(pvalue3);


  EXPECT_EQ(pvalue3->value, 10);
  EXPECT_EQ(pvalue4->value, 10);
}

TEST(SharedPtr_Test, Get_Test) {
  int value = 5;
  int* pvalue = &value;
  SharedPtr<int> pvalue1(&value);
  SharedPtr<int> pvalue2(pvalue1);

  EXPECT_EQ(pvalue1.Get(), pvalue);
  EXPECT_EQ(pvalue2.Get(), pvalue);
}

TEST(SharedPtr_Test, Swap_Test) {
  int firstValue = 5;

  SharedPtr<int> pvalue1(&firstValue);
  SharedPtr<int> pvalue2(pvalue1);

  int secondValue = 10;

  SharedPtr<int> pvalue3(&secondValue);
  SharedPtr<int> pvalue4(pvalue3);
  SharedPtr<int> pvalue5(pvalue4);

  pvalue3.Swap(pvalue1);

  EXPECT_EQ(pvalue1.GetCount(), 3);
  EXPECT_EQ(pvalue3.GetCount(), 2);

  EXPECT_EQ(*pvalue1 == 10);
  EXPECT_EQ(*pvalue3 == 5);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
