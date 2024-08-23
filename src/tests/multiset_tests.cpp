#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(Constructors, Default_multiset) {
  s21::multiset<int> s21;
  std::multiset<int> stl;
  ASSERT_TRUE(s21.empty() == stl.empty());
}

TEST(Constructors, Parametres_multiset) {
  s21::multiset<int> s21{1, 5, 6, 8, -15, 21};
  std::multiset<int> stl{1, 5, 6, 8, -15, 21};
  s21::multiset<int>::iterator s21It = s21.begin();
  std::multiset<int>::iterator stlIt = stl.begin();
  bool equal = true;
  for (; (s21It != s21.end()) && (stlIt != stl.end()); ++s21It, ++stlIt) {
    if (*s21It != *stlIt) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Copy_multiset) {
  s21::multiset<int> st1{76, -68, 15, 0, 8, -15, 21};
  s21::multiset<int> st2(st1);
  s21::multiset<int>::iterator it1 = st1.begin();
  s21::multiset<int>::iterator it2 = st2.begin();
  bool equal = true;
  for (; (it1 != st1.end()) && (it2 != st2.end()); ++it1, ++it2) {
    if (*it1 != *it2) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Move_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2((s21::multiset<int> &&) st1);
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Constructors, Destructor_multiset) {
  s21::multiset<int> s21{1, 5, 6, 8, -15, 21};
  s21.~multiset<int>();
  ASSERT_TRUE(s21.empty());
}

TEST(Overloads, Dereferencing_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  ASSERT_TRUE(*it1 == 135);
}

TEST(Overloads, PreIncrement_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.begin();
  s21::multiset<int>::iterator it2 = ++it1;
  ASSERT_TRUE(*it1 == -4 && *it2 == -4);
}

TEST(Overloads, PreDecrement_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = --it1;
  ASSERT_TRUE(*it1 == 67 && *it2 == 67);
}

TEST(Overloads, Equal_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = --it1;
  ASSERT_TRUE(it1 == it2);
}

TEST(Overloads, NotEqual_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  s21::multiset<int>::iterator it2 = it1;
  --it1;
  ASSERT_TRUE(it1 != it2);
}

TEST(Overloads, MoveAssign_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2;
  st2 = (s21::multiset<int> &&) st1;
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Iterators, Begin_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.begin();
  ASSERT_TRUE(*it1 == -15);
}

TEST(Iterators, End_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(135);
  ++it1;
  ASSERT_TRUE(it1 == st1.end());
}

TEST(Capacity, Empty_multiset) {
  s21::multiset<int> st1;
  ASSERT_TRUE(st1.empty());
}

TEST(Capacity, Size_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.size() == 7);
}

TEST(Capacity, MaxSize_multiset) {
  s21::multiset<int> st1;
  std::multiset<int> st2;
  std::cout << "std1: " << st1.max_size() << std::endl;
  std::cout << "std2: " << st2.max_size() << std::endl;
  ASSERT_TRUE(true);
}

TEST(LookUp, Find_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(67);
  ASSERT_TRUE(*it1 == 67);
}

TEST(LookUp, Contains_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.contains(67));
}

TEST(Modifieres, Clear_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.clear();
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Insert_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.insert(-200);
  ASSERT_TRUE(*st1.begin() == -200);
}

TEST(Modifieres, Erase_multiset_1) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int>::iterator it1 = st1.find(8);
  st1.erase(it1);
  ASSERT_FALSE(st1.contains(8));
}

TEST(Modifieres, Erase_multiset_2) {
  s21::multiset<int> st1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 1; i <= 10; i++) {
    s21::multiset<int>::iterator it1 = st1.find(i);
    st1.erase(it1);
  }
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Erase_multiset_3) {
  s21::multiset<int> st1;
  s21::multiset<int>::iterator it1;
  int arr_in_1[10]{50, 30, 20, 40, 70, 60, 80, 55, 65, 67};
  int arr_out_1[10]{65, 70, 60, 30, 67, 40, 80, 50, 55, 20};
  for (int x : arr_in_1) {
    st1.insert(x);
  }
  for (int x : arr_out_1) {
    it1 = st1.find(x);
    st1.erase(it1);
  }
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Erase_multiset_4) {
  s21::multiset<int> st1;
  s21::multiset<int>::iterator it1;
  int arr_in_2[10]{50, 70, 80, 60, 40, 45, 35, 48, 42, 41};
  int arr_out_2[10]{35, 48, 41, 42, 70, 80, 45, 50, 60, 40};
  for (int x : arr_in_2) {
    st1.insert(x);
  }
  for (int x : arr_out_2) {
    it1 = st1.find(x);
    st1.erase(it1);
  }
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Swap_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2{1, 3, 6, 7, -12, 21};
  st1.swap(st2);
  ASSERT_TRUE(*st1.find(21) && *st2.find(135));
}

TEST(Modifieres, Merge_multiset) {
  s21::multiset<int> st1{-4, 8, 135, 67, 5, -15, 1};
  s21::multiset<int> st2{1, 3, 6, 7, -12, 21};
  st1.merge(st2);
  ASSERT_TRUE(*st1.find(21) && *st1.find(135));
}

// count
TEST(OnlyForMultiset, count_multiset) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  // std::cout << s21.count(4) << " " << stl.count(4);
  ASSERT_TRUE(s21.count(4) == stl.count(4));
}
// equal_range
TEST(OnlyForMultiset, equal_multiset_1) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> eq_std =
      stl.equal_range(4);
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> eq_s21 =
      s21.equal_range(4);
  ASSERT_TRUE((*eq_std.first == *eq_s21.first) &&
              (*eq_std.second == *eq_s21.second));
}

TEST(OnlyForMultiset, equal_multiset_2) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> eq_std =
      stl.equal_range(-1);
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> eq_s21 =
      s21.equal_range(-1);
  ASSERT_TRUE((*eq_std.first == *eq_s21.first) &&
              (*eq_std.second == *eq_s21.second));
}
// lower_bound
TEST(OnlyForMultiset, lower_bound_multiset_1) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.lower_bound(4) == *stl.lower_bound(4));
}

TEST(OnlyForMultiset, lower_bound_multiset_2) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.lower_bound(1) == *stl.lower_bound(1));
}

TEST(OnlyForMultiset, lower_bound_multiset_3) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.lower_bound(6) == *stl.lower_bound(6));
}

TEST(OnlyForMultiset, lower_bound_multiset_4) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.lower_bound(-1) == *stl.lower_bound(-1));
}

TEST(OnlyForMultiset, upper_bound_multiset_1) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.upper_bound(-1) == *stl.upper_bound(-1));
}

TEST(OnlyForMultiset, upper_bound_multiset_2) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.upper_bound(1) == *stl.upper_bound(1));
}

TEST(OnlyForMultiset, upper_bound_multiset_3) {
  s21::multiset<int> s21{1, 2, 3, 4, 4, 4, 5, 6};
  std::multiset<int> stl{1, 2, 3, 4, 4, 4, 5, 6};
  ASSERT_TRUE(*s21.upper_bound(4) == *stl.upper_bound(4));
}

TEST(Modifieres, Insert_many_multiset) {
  s21::multiset<int> st1;
  st1.insert_many(1, 2, 3, 4, 5, 6, 7, 8);
  ASSERT_TRUE((*st1.begin() == 1) && (*(--st1.end()) == 8));
}

TEST(Const, Iterator_multiset_1) {
  s21::multiset<int> st1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::multiset<int>::iterator it_begin = st1.begin();
  s21::multiset<int>::iterator it_end = st1.end();
  --it_end;
  do {
    --it_end;
  } while (*it_end != *it_begin);

  ASSERT_TRUE(*it_end == 1);
}

TEST(Const, Iterator_multiset_2) {
  s21::multiset<int> st{-1, 23, 5, -19};
  s21::multiset<int>::iterator it = st.find(5);
  s21::multiset<int>::const_iterator it_const(it);
  ASSERT_TRUE(*it_const == 5);
}
