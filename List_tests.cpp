// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

TEST(compile) {
    List<int> my_list;

    int size = 0;
    my_list.empty();
    my_list.size();
    std::cout << (my_list.size() == size) << std::endl;

    my_list.push_front(42);
    my_list.push_back(42);

    my_list.front() = 73;
    my_list.back() = 73;

    my_list.pop_front();
    my_list.pop_back();

    List<int> list2(my_list);
    list2 = my_list;

    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 42);
    iter = my_list.begin();
    my_list.erase(iter);
    iter = my_list.begin();

    List<int>::Iterator iter2 = my_list.end();
    const List<int>::Iterator iter3 = iter2;

    bool b = iter == iter2;
    b = iter3 == my_list.end();
    b = my_list.end() == iter3;
    my_list.push_front(42);
    my_list.push_back(42);
    iter = my_list.begin();
    b = iter != iter2;
    b = iter3 != my_list.end();
    b = my_list.end() != iter3;
    std::cout << b << std::endl;
    ++iter;

    std::cout << *iter <<   std::endl;

    List<int>::Iterator iter_cpy(iter);
    iter_cpy = iter;

    std::cout << *++--iter <<  std::endl;
    std::cout << *--++my_list.begin() <<   std::endl;

    my_list.insert(my_list.begin(), 3);
    my_list.erase(my_list.begin());

    List<int> list3;
    list3.push_back(3);
    std::cout << *list3.begin() <<   std::endl;

    List<int> list4;
    list4.push_back(4);
    std::cout << list4.size() <<   std::endl;

    my_list.clear();

}

TEST(test_stub) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}
TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    ASSERT_EQUAL(0, empty_list.size());
}

TEST(test_list_default) {
    List<int> test;
    test.push_front(12);
    ASSERT_FALSE(test.empty());
}
TEST(test_constructor1){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    ASSERT_EQUAL(empty_list.size(),0);
    empty_list.push_front(1);
    ASSERT_EQUAL(empty_list.size(),1);
    
    List<char> empty_char_list;
    empty_char_list.push_front('c');
    ASSERT_EQUAL(empty_char_list.size(),1);
    empty_list.clear();
}
TEST(test_size){
    List<int> empty_list;
    ASSERT_EQUAL(empty_list.size(),0);
    
}
TEST(test_front){
        List<int> empty_list;
        ASSERT_TRUE(empty_list.empty());
        empty_list.push_front(1);
        empty_list.push_front(3);
        ASSERT_EQUAL(empty_list.front(),3);
        empty_list.clear();
}
TEST(test_back){
        List<int> empty_list;
        ASSERT_TRUE(empty_list.empty());
        empty_list.push_front(5);
        empty_list.push_front(3);
        empty_list.push_front(1);
        ASSERT_EQUAL(empty_list.back(),5);
        empty_list.clear();
}

TEST(test_pop_front){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_front(5);
    empty_list.push_front(3);
    empty_list.push_front(1);
    ASSERT_EQUAL(empty_list.back(),5);
    ASSERT_EQUAL(empty_list.front(),1);
    empty_list.pop_front();
    ASSERT_EQUAL(empty_list.back(),5);
    ASSERT_EQUAL(empty_list.front(),3);
    empty_list.pop_front();
    ASSERT_EQUAL(empty_list.back(),5);
    ASSERT_EQUAL(empty_list.front(),5);
    empty_list.pop_back();
    ASSERT_TRUE(empty_list.empty());
    empty_list.clear();
    ASSERT_TRUE(empty_list.empty());
}
TEST(test_pop_back){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_back(1);
    empty_list.push_back(3);
    empty_list.push_back(5);
    ASSERT_EQUAL(empty_list.back(),5);
    ASSERT_EQUAL(empty_list.front(),1);
    empty_list.pop_back();
    ASSERT_EQUAL(empty_list.back(),3);
    ASSERT_EQUAL(empty_list.front(),1);
    empty_list.pop_back();
    ASSERT_EQUAL(empty_list.back(),1);
    ASSERT_EQUAL(empty_list.front(),1);
    empty_list.pop_back();
    ASSERT_TRUE(empty_list.empty());
    empty_list.clear();
    ASSERT_TRUE(empty_list.empty());
}
TEST(test_clear){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_front(1);
    empty_list.push_front(3);
    empty_list.push_front(5);
    empty_list.clear();
    ASSERT_TRUE(empty_list.empty());
}
TEST(test_iterater){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_front(5);
    empty_list.push_front(3);
    empty_list.push_front(1);
    
    List<int>::Iterator iter = empty_list.begin();
    empty_list.insert(iter, 42);
    ASSERT_EQUAL(*iter, 1);
    
    List<int>::Iterator iter1 = empty_list.end();
    iter1 = empty_list.begin();
    ASSERT_EQUAL(*iter1, 42);
    iter1 = empty_list.end();
    empty_list.insert(iter1, 20);
    List<int>::Iterator iter2 = empty_list.begin();
    ++iter2;
    ++iter2;
    ++iter2;
    --iter2;
    ++iter2;
    ++iter2;
    ASSERT_EQUAL(*iter2, 20);
    ASSERT_EQUAL(*++--iter2, 20);
    ASSERT_EQUAL(*--++empty_list.begin(),42);
    --iter2;
    ASSERT_EQUAL(*iter2, 5);
    ++iter2;
    empty_list.erase(iter2);
    ASSERT_EQUAL(empty_list.back(),5);
    List<int>::Iterator iter3 = empty_list.begin();
    empty_list.erase(iter3);
    ASSERT_EQUAL(empty_list.front(),1);
    List<int>::Iterator iter7 = empty_list.begin();
    ++iter7;
    empty_list.erase(iter7);
    ASSERT_EQUAL(empty_list.front(),1);
    ASSERT_EQUAL(empty_list.back(),5);
    
    List<int>::Iterator iter4 = empty_list.end();
    ASSERT_TRUE(iter1==iter4);
    iter1 = empty_list.end();
    List<int> empty_list1;
    List<int>::Iterator iter5 = empty_list1.end();
    ASSERT_TRUE(iter1==iter5);
    List<int>::Iterator iter6 = empty_list.begin();
    ASSERT_TRUE(iter1!=iter6);
    List<int> empty_list3;
    empty_list3.push_front(5);
    empty_list3.push_front(3);
    empty_list3.push_front(1);
    List<int>::Iterator iter8 = empty_list3.begin();
    ++iter8;
    empty_list3.insert(iter8, 42);
    ASSERT_EQUAL(*iter8, 3);
    --iter8;
    ASSERT_EQUAL(*iter8, 42);
    ++iter8;
    ++iter8;
    ASSERT_EQUAL(*iter8, 5);
    
}
TEST(test_copy){
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_front(5);
    empty_list.push_front(3);
    empty_list.push_front(1);
    List<int> list2(empty_list);
    List<int>::Iterator j = list2.begin();
    for (List<int>::Iterator i= empty_list.begin(); i != empty_list.end(); ++i) {
        ASSERT_EQUAL(*i,*j);
        ++j;
    }
    List<int> list3;
    list3.push_front(6);
    list3.push_front(4);
    list3.push_front(2);
    list3 = empty_list;
    List<int>::Iterator h = list3.begin();
    for (List<int>::Iterator i= empty_list.begin(); i != empty_list.end(); ++i) {
        ASSERT_EQUAL(*i,*h);
        ++h;
    }
}

TEST_MAIN()
