#ifndef _multiset_h
#define _multiset_h

#include <memory>

namespace nonstd {

template <typename T>
class MultiSet {
public:
//========================================================================== 
  class Node {
    // Members
  private:
    T value_;
    std::unique_ptr<Node> left_, right_;

    // Constructor
  private:
    Node(const T& value) : value_(value) {}

    // Other shit
  public:
    Node *left() {
      return this->left_.get();
    }
    Node *right() {
      return this->right.get();
    }
    const T& value() const {
      return this->value_;
    }

// A friend who will only manipulate your data and use you for his structures
    friend class MultiSet<T>;
  };
//========================================================================== 
  // Members
private:
  std::unique_ptr<Node> root_;
  int size_;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Constructor
public:
  MultiSet(): size_(0) { }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // >Destructor in ${currentyear}
  ~MultiSet() { }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  void insert(const T& value) {
    /* Simple insertion into binary tree.  Less than goes left, greater than
    and equal go right.  If no root is defined it will set first insert */

    // Root
    if(!this->root_)
    {
      root_ = std::unique_ptr<Node>(new Node(value));
      this->size_++;
      return;
    }

    Node* current = root_.get();
    while(true)
    {
      // Left
      if(value < current->value_)
      {
        if(current->left_)
          current = current->left_.get();
        else
        {
          current->left_ = std::unique_ptr<Node>(new Node(value));
          this->size_++;
          return;;
        }
      }

      // Right
      else
      {
        if(current->right_)
          current = current->right_.get();
        else
        {
          current->right_=std::unique_ptr<Node>(new Node(value));
          this->size_++;
          return;
        }
      }
    } // end while

  } // end function
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int remove(const T& value){
    return this->remove(value, this->root_.get());
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
private:
  int remove(const T& value, Node* current ){
 
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int remove(Node* toDelete, bool deleteLeft){
    
  }
public:
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int count(const T& value) {
    /* offloads work onto coworker below */
    return count(value, this->root_.get());
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int count(const T& value, Node* localRoot) {
    /* Recursive function to count how many times a value is in a tree.
    Will be called by the count above with localRoot set to this->root_*/
    if(!localRoot) return 0;
    int count__ = (value == localRoot->value_) ? 1 : 0;
    if(value < localRoot->value_)
      return count(value, localRoot->left_.get()) + count__;
    else
      return count(value, localRoot->right_.get()) + count__;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  bool contains(const T& value, Node* localRoot = NULL) {
    /* defining localRoot will allow you to search subtrees and not just
    from this->root_ */
    Node* current = localRoot ? localRoot : this->root_.get();
    while(current)
    {
      if(value == current->value_)
        return true;
      else if(value < current->value_)
        current = current->left_.get();
      else
        current = current->right_.get();
    }
    return false;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int size() {
    // Both ways work.  I just forgot I had a member to track this
    return this->size_;
    // return size(this->root_.get());
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int size(Node* parent)
  {
    /* Recursive function to calculate size */
    if(!parent)
      return 0;

    int size__ = 0;
    size__ += size(parent->left_.get());
    size__ += size(parent->right_.get());
    return size__ + 1;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  Node *root() {
    /* If you can't understand this you should probably neck yourself */
    return this->root_.get();
  }
};
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
} // end namespace nonstd
#endif
