// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_stub) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_bst) {
    int size = 0;
    BinarySearchTree<int> b;
    ASSERT_TRUE(b.empty());
    std::cout << (b.size() == size) << std::endl;
    BinarySearchTree<int>::Iterator iter = b.begin();
    BinarySearchTree<int>::Iterator iter3 = b.end();
    ASSERT_EQUAL(iter, iter3);
    BinarySearchTree<char> c;
    c.insert('a');
    size = 1;
    std::cout << (c.size() == size) << std::endl;
    BinarySearchTree<char>::Iterator iter1 = c.begin();
    ASSERT_TRUE(*iter1=='a');
    
}
TEST(test_bst_other) {
    BinarySearchTree<int> other1;
    other1.insert(1);
    other1.insert(0);
    BinarySearchTree<int> c(other1);
    ASSERT_FALSE(c.empty());
    ASSERT_TRUE(*c.begin()==*other1.begin());
    ASSERT_TRUE(*c.begin()++==*other1.begin()++);
}
TEST(test_bst_assignment) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
    BinarySearchTree<int> c;
    c.insert(3);
    c.insert(4);
    c.insert(1);
    // change first datum to 2, resulting in the first broken tree above
    *c.begin() = 2;
    ASSERT_TRUE(c.check_sorting_invariant());
    BinarySearchTree<int> d;
    d.insert(1);
    d.insert(3);
    d.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *d.begin() = 0;
    ASSERT_TRUE(d.check_sorting_invariant());
    
}

//check tree is good or not
//TEST(test_distructor) ?
//test cout?

TEST(test_height) {
    BinarySearchTree<int> b;
    int height = 0;
    ASSERT_TRUE(height==b.height());
    b.insert(1);
    b.insert(0);
    height = 2;
    ASSERT_TRUE(height==b.height());
    b.insert(2);
    ASSERT_TRUE(height==b.height());
    height = 3;
    ASSERT_FALSE(height==b.height())
    // change first datum to 2, resulting in the first broken tree above
}
TEST(test_size) {
    BinarySearchTree<int> b;
    int size = 0;
    ASSERT_TRUE(size==b.size());
    b.insert(1);
    b.insert(0);
    size = 2;
    ASSERT_TRUE(size==b.size());
    b.insert(2);
    ASSERT_FALSE(size==b.size());
    size = 3;
    ASSERT_TRUE(size==b.size())
}
TEST(test_check_sorting_invarian) {
    BinarySearchTree<int> d;
    ASSERT_TRUE(d.check_sorting_invariant());
    d.insert(4);
    d.insert(2);
    d.insert(6);
    d.insert(1);
    d.insert(3);
    d.insert(5);
    d.insert(7);
    ASSERT_TRUE(d.check_sorting_invariant());
    BinarySearchTree<int>::Iterator iter = d.find(2);
    *iter=8;
    ASSERT_FALSE(d.check_sorting_invariant());
    *iter=2;
    BinarySearchTree<int>::Iterator iter1 = d.find(6);
    *iter1=1;
    ASSERT_FALSE(d.check_sorting_invariant());
    *iter1=6;
    BinarySearchTree<int>::Iterator iter2 = d.find(3);
    *iter2 = 8;
    ASSERT_FALSE(d.check_sorting_invariant());
    *iter2 = 3;
    BinarySearchTree<int>::Iterator iter3 = d.find(5);
    *iter3 = 5;
    ASSERT_TRUE(d.check_sorting_invariant());
}
TEST(test_traverse_inorder) {
    BinarySearchTree<int> e;
    std::ostringstream oss_inorder1;
    e.traverse_inorder(oss_inorder1);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder1.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder1.str() == "");
    e.insert(4);
    e.insert(2);
    e.insert(6);
    e.insert(1);
    e.insert(3);
    e.insert(5);
    e.insert(7);
    std::ostringstream oss_inorder;
    e.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 4 5 6 7 ");
}
TEST(test_traverse_preorder) {
    BinarySearchTree<int> f;
    std::ostringstream oss_preorder1;
    f.traverse_preorder(oss_preorder1);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder1.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder1.str() == "");
    f.insert(4);
    f.insert(2);
    f.insert(6);
    f.insert(1);
    f.insert(3);
    f.insert(5);
    f.insert(7);
    std::ostringstream oss_preorder;
    f.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
    ASSERT_TRUE(oss_preorder.str() == "4 2 1 3 6 5 7 ");
}
TEST(test_calculate) {
   BinarySearchTree<int> g;
    BinarySearchTree<int>::Iterator iter1 = g.begin();
    BinarySearchTree<int>::Iterator iter5 = g.end();
    ASSERT_EQUAL(iter1, iter5);
    g.insert(4);
    g.insert(2);
    g.insert(6);
    g.insert(1);
    g.insert(3);
    g.insert(5);
    g.insert(7);
    BinarySearchTree<int>::Iterator iter = g.find(4);
    ASSERT_TRUE(*iter++==4);
    ASSERT_TRUE(*++iter==6);
    ASSERT_TRUE(*++iter==7);
    ASSERT_EQUAL(++iter, iter5);
    BinarySearchTree<int>::Iterator iter2 = g.find(5);
    ++iter2;
    ASSERT_TRUE(*iter2==6);
    BinarySearchTree<int>::Iterator iter3 = g.find(1);
    ++iter3;
    ASSERT_TRUE(*iter3==2);
}
TEST(test_iterator_begin) {
    BinarySearchTree<int> h;
    BinarySearchTree<int>::Iterator iter1 = h.begin();
    BinarySearchTree<int>::Iterator iter5 = h.end();
    ASSERT_EQUAL(iter1, iter5);
    h.insert(4);
    h.insert(2);
    h.insert(6);
    h.insert(1);
    h.insert(3);
    h.insert(5);
    h.insert(7);
    BinarySearchTree<int>::Iterator iter = h.begin();
    ASSERT_TRUE(*iter==1);
}

TEST(test_iterator_end) {
    BinarySearchTree<int> i;
    BinarySearchTree<int>::Iterator iter1 = i.end();
    BinarySearchTree<int>::Iterator iter5 = i.end();
    ASSERT_EQUAL(iter1, iter5);
    i.insert(4);
    i.insert(2);
    i.insert(6);
    i.insert(1);
    i.insert(3);
    i.insert(5);
    i.insert(7);
    BinarySearchTree<int>::Iterator iter = i.end();
    ASSERT_EQUAL(iter, iter5);
}
TEST(test__iterator_min) {
    BinarySearchTree<int> b;
    BinarySearchTree<int>::Iterator iter1 = b.min_element();
    BinarySearchTree<int>::Iterator iter5 = b.end();
    ASSERT_EQUAL(iter1, iter5);
    b.insert(4);
    b.insert(2);
    b.insert(6);
    b.insert(1);
    b.insert(3);
    b.insert(5);
    b.insert(7);
    BinarySearchTree<int>::Iterator iter = b.min_element();
    BinarySearchTree<int>::Iterator iter4 = b.max_element();
    ASSERT_TRUE(*iter==1);
    ASSERT_TRUE(*iter4==7);
}

TEST(test__iterator_find) {
    BinarySearchTree<int> j;
    BinarySearchTree<int>::Iterator iter1 = j.find(0);
    BinarySearchTree<int>::Iterator iter5 = j.end();
    ASSERT_EQUAL(iter1, iter5);
    j.insert(4);
    j.insert(2);
    j.insert(6);
    j.insert(1);
    j.insert(3);
    j.insert(5);
    j.insert(7);
    BinarySearchTree<int>::Iterator iter = j.find(0);
    ASSERT_EQUAL(iter, iter5);
    BinarySearchTree<int>::Iterator iter2 = j.find(7);
    ASSERT_TRUE(*iter2==7);
}

TEST(test__iterator_insert) {
    BinarySearchTree<int> k;
    BinarySearchTree<int>::Iterator iter1 = k.max_element();
    BinarySearchTree<int>::Iterator iter5 = k.end();
    ASSERT_EQUAL(iter1, iter5);
    k.insert(4);
    k.insert(2);
    k.insert(6);
    k.insert(1);
    k.insert(3);
    k.insert(5);
    k.insert(7);
    BinarySearchTree<int>::Iterator iter = k.max_element();
    ASSERT_TRUE(*iter==7);
}

TEST(test__iterator_mingreaterthan) {
    BinarySearchTree<int> l;
    BinarySearchTree<int>::Iterator iter1 = l.min_greater_than(0);
    BinarySearchTree<int>::Iterator iter5 = l.end();
    ASSERT_EQUAL(iter1, iter5);
    l.insert(4);
    l.insert(2);
    l.insert(6);
    l.insert(1);
    l.insert(3);
    l.insert(5);
    l.insert(7);
    BinarySearchTree<int>::Iterator iter = l.min_greater_than(0);
    ASSERT_TRUE(*iter==1);
    BinarySearchTree<int>::Iterator iter2 = l.min_greater_than(1);
    ASSERT_TRUE(*iter2==2);
    BinarySearchTree<int>::Iterator iter3 = l.min_greater_than(7);
    BinarySearchTree<int>::Iterator iter4 = l.min_greater_than(4);
    ASSERT_TRUE(*iter4==5);
    ASSERT_EQUAL(iter3, iter5);
}
TEST(test_it){
    BinarySearchTree<std::pair<int, double>> tree;
    auto it = tree.insert({ 3, 4.1 });
    ASSERT_TRUE (it->first==3);  // prints 3
    ASSERT_TRUE (it->second==4.1); // prints 4.1
}

TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  std::cout << "cout << tree.to_string()" << std::endl;
    std::cout << tree.to_string() << std::endl << std::endl;

  std::cout << "cout << tree" << std::endl << "(uses iterators)" << std::endl;
    std::cout << tree << std::endl << std::endl;

    std::ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
    std::cout << "preorder" << std::endl;
    std::cout << oss_preorder.str() << std::endl << std::endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

    std::ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
    std::cout << "inorder" << std::endl;
    std::cout << oss_inorder.str() << std::endl << std::endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}





TEST_MAIN()
