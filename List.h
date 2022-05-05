#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
    
    ~List() {
    clear();
    }
    
    List(const List &other) {
      first = nullptr;
      last = nullptr;
      copy_all(other);
    }
    
    List & operator=
    (const List &rhs) {
    if (this == &rhs) return *this;
      clear();
      copy_all(rhs);
      return *this;
    }
    
    List(){
        first = nullptr;
        last = nullptr;
    }
    
  //EFFECTS:  returns true if the list is empty
    bool empty() const{
        return (first == nullptr||last == nullptr);
    }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
    int size() const{
        return count;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front(){
        assert(!empty());
        return first->datum;
    }
  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
   
    T & back(){
        assert(!empty());
        return last->datum;
    }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum){
        count++;
        Node *p = new Node;
        p->datum = datum;
        p->next = first;
        first = p;
        if(size() == 1){
            last = first;
            last->next = nullptr;
            last->prev = nullptr;
            first->next = nullptr;
        }
        else if(size() == 2){
            last->prev = first;
            first->next = last;
        }
        else{
        first->next->prev = first;
        }
        first->prev = nullptr;
    }
  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum){
        count++;
        Node *p = new Node;
        p->datum = datum;
        p->prev = last;
        last = p;
        if(size() == 1){
            first = last;
            first->prev = nullptr;
            last->prev = nullptr;
            first->next = nullptr;
        }
        else if(size() == 2){
            first->next = last;
            last->prev = first;
        }
        else{
        last->prev->next = last;
        }
        last->next = nullptr;
    }
  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front(){
        assert(!empty());
        count--;
        if(size()!=0){
        Node *victim = first;
        first = first->next;
        first->prev = nullptr;
        delete victim;
        }
        else{
            first = nullptr;
            last = nullptr;
        }

    }
  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    void pop_back(){
        assert(!empty());
        count--;
        if(size()!=0){
        Node *victim = last;
        last = last->prev;
        last->next = nullptr;
        delete victim;
        }
        else{
            first = nullptr;
            last = nullptr;
        }

    }
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
    void clear(){
        while (!empty()) {
        pop_front();
        }
    }
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
    int count = 0;
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };
    Node *first;
    Node *last;

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other){
        Node *last = nullptr;
        for (Node *p=other.first; p!=nullptr; p=p->next) {
          Node *q = new Node;
          q->datum = p->datum;
          q->next = nullptr;
        if(last == nullptr) {
          first = last = q;
        }
        else{
          last->next = q;
          last = q;
        }// points to last Node in list, or nullptr if list is empty
      }
    }

public:

  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
      Iterator() : node_ptr(nullptr) {
          node_ptr = nullptr;
      }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
          assert(node_ptr);
          node_ptr = node_ptr->prev;
          return *this;
    }
      T & operator* () const {
      assert(node_ptr != nullptr);
      return node_ptr->datum;
      }
      
      Iterator & operator++ () {
          assert(node_ptr != nullptr);
          node_ptr = node_ptr->next;
          return *this;
      }
      
      bool operator!= (Iterator rhs) const {
          return node_ptr != rhs.node_ptr;
      }
      bool operator == (Iterator rhs) const {
          return node_ptr == rhs.node_ptr;
      }
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    // add any friend declarations here
      friend class List;
    // construct an Iterator at a specific position
      Iterator(Node *p) : node_ptr(p) {
         node_ptr = p;
      }
  };//List::Iterator
  ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const {
      return Iterator(first);
    }

  // return an Iterator pointing to "past the end"
    Iterator end() const{
     return Iterator();
    }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
    void erase(Iterator i){
        assert(i.node_ptr != nullptr);
        if (i.node_ptr == first){
            pop_front();
            }
        else if (i.node_ptr == last){
            pop_back();
        }
        else{
        Node *victim = i.node_ptr;
        i.node_ptr->prev->next = i.node_ptr->next;
        i.node_ptr->next->prev = i.node_ptr->prev;
        delete victim;
            count--;
        }
    }
  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum){
        if (i.node_ptr == first){
            push_front(datum);
            }
        else if (i.node_ptr == nullptr){
            push_back(datum);
        }
        else {
                Node *p = new Node;
                p->datum = datum;
                i.node_ptr->prev->next = p;
                p->prev = i.node_ptr->prev;
                p->next = i.node_ptr;
                i.node_ptr->prev = p;
                count++;
            }
        }
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
