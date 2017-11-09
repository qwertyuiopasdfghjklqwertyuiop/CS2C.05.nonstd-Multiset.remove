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
      return this->right_.get();
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
      this->root_ = std::unique_ptr<Node>(new Node(value));
      this->size_++;
      return;
    }

    // Traverse through tree until you get to the bottom where the insert should go
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
          return;
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
   int numRemoved = this->remove( value, this->root_.get(), NULL );
   this->size_ -= numRemoved;
   return numRemoved;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
private:
  int remove(const T& value, Node* current, std::unique_ptr<Node>* parent = NULL){
    if(!current) return 0;
    int numRemoved = 0;

    // You found him, now search and kill all his children that look like him before finishing him off
    if( value == current->value_ ){
      numRemoved += this->remove( value, current->left_.get(), &current->left_ );
      numRemoved += this->remove( value, current->right_.get(), &current->right_ );
      numRemoved += this->remove( current, parent );
      return numRemoved;
    }
    if( value <= current->value_ )
      numRemoved += this->remove( value, current->left_.get(), &current->left_ );
    if(value >= current->value_)
      numRemoved += this->remove( value, current->right_.get(), &current->right_ );
    return numRemoved;

  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int remove( Node* toDelete, std::unique_ptr<Node>* parent ){
    /* Remove function that removes a single node.
       toDelete is a Node* to the Node you want to delete
       parent is a pointer to the unique_ptr that points to toDelete */

    int numRemoved = 0;

    // No children Case:
    // No orphans to worry about if we just kill him
    if(!toDelete->left_ && !toDelete->right_) {
      if(toDelete == this->root_.get())
        this->root_.reset();
      else
        parent->reset();
      numRemoved += 1;
    }

    // 2 Children Case:
    // 2 Children so we get the least most value on the right
    // and overwrite the value of toDelete with the value of 
    // that node, then send that node to be executed.
    else if(toDelete->left_ && toDelete->right_) {
      Node* lChild = toDelete->left_.release();
      Node* rChild = toDelete->right_.release();
      if(!rChild->left_)
      {
        rChild->left_.reset(lChild); // should be NULL anyways before we reset it
        parent->reset(rChild);
        numRemoved+=1;
      }
      else{
        Node* traversal = rChild;
        while(traversal->left_->left_)  // keep traversing left but keep your distance so you stop at parent of the node you want
          traversal = traversal->left_.get();
        parent->reset(traversal->left_.release());  // remove node and set it to least most on right side
        numRemoved += 1;
        
        // Now reattach rChild
        traversal = parent->get();
        while(traversal->right_)
          traversal = traversal->right_.get();
        traversal->right_.reset(rChild);
        
      }

//      if(!toDelete->right_->left_) {
//        toDelete->value_ = toDelete->right_->value_;
//        numRemoved += this->remove(toDelete->right_.get(), &toDelete->right_);
//      } 
//      else{
//        Node* traversal = toDelete->right_.get();
//        while(traversal->left_->left_)  // keep traversing left but keep your distance so you stop at parent of the node you want
//          traversal = traversal->left_.get();
//        toDelete->value_ = traversal->left_->value_;
//        numRemoved += this->remove(traversal->left_.get(), &traversal->left_);
//      }
    }

    // 1 Child Case:
    // toDelete's parent abandons him and adopts his only child
    else {
      std::unique_ptr<Node>* parentOfAnOnlyChild = &(toDelete->left_.get() ? toDelete->left_ : toDelete->right_);
      if( !parent ){  // if it has no parent it must always be root, if not, then I don't know how
        if( toDelete != this->root_.get() ) { std::cout << "Fucking how!?" << std::endl; exit(1); }

      	this->root_.reset( parentOfAnOnlyChild->release() ); // Take away custody and give it to state
      	numRemoved += 1;
      }
      else {
        parent->reset( parentOfAnOnlyChild->release() );   // Take away custody of their only child and give it to their parent
        numRemoved += 1;
      }
    }
    return numRemoved;
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
    /* search tree ( or subtree ) to see if it contains a T value */
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
