/// @file ScapegoatST.h
/// @brief creates the scapegoat tree and rebuilds it when needed (header)
/// @author Tyler Edwards - tk.edwards2003@gmail.com
#ifndef SCAPEGOATST_H
#define SCAPEGOATST_H

#include "TreeNode.h"
#include <cmath>
#include "Student.h"


template <typename T>
class ScapegoatST{
public:
  ScapegoatST();
  virtual ~ScapegoatST();
  int getTotalSize();
  void insert(T d);
  void remove(T d);
  void removeInt(int id); //added
  bool contains(int id); //chnaged
  void printTreeInOrder();
  void printTreePostOrder();
  void testPrint();
  T* getPerson(int n);
  T getMin();
  T getMax();
  T getMedian();
  bool isScapeGoat(TreeNode<T>* subTreeRoot);
  int nodeTreeSize(TreeNode<T>* currRoot, TreeNode<T>* searchRoot);
  TreeNode<T>* getRoot();
  int getSizeAtNode(TreeNode<T>* subTreeRoot);
  double log32;
  int getNodeDepth(TreeNode<T>* subTreeRoot);
  bool rebuildCheck(TreeNode<T>* subTreeRoot);
  void rebuildTree(TreeNode<T>* subTreeRoot, int size);
  int treeToArray(TreeNode<T> *ptr, TreeNode<T> *arr[], int i);
  void rebuildTree(TreeNode<T> *u);
  TreeNode<T> *arrayToTree(TreeNode<T> **a, int i ,int n);
  void ascArray(TreeNode<T>* subTreeRoot);

private:
  int m_size;

  TreeNode<T>* m_root;
  T getMinHelper(TreeNode<T>* subTreeRoot);
  T getMaxHelper(TreeNode<T>* subTreeRoot);
  void insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode);
  bool containsHelper(TreeNode<T>* subTreeRoot, int id); //changed
  void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
  void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
  void findTargetInt(int key, TreeNode<T>*& target, TreeNode<T>*& parent); //added
  void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
  TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
  T* personHelper(TreeNode<T>* subTreeRoot, int n);

};

//constructor
template <typename T>
ScapegoatST<T>::ScapegoatST(){
  m_root = NULL;
  m_size = 0;
  log32 = 2.4663034623764317;
}

//destructor
template <typename T>
ScapegoatST<T>::~ScapegoatST(){
  if(m_root != NULL){
    delete m_root;
  }
}


//returns total size of the tree
template <typename T>
int ScapegoatST<T>::getTotalSize(){
  return m_size;
}


//returns the size of the subtree
template <typename T>
int ScapegoatST<T>::getSizeAtNode(TreeNode<T>* subTreeRoot){
  if (subTreeRoot == NULL){
    return 0;
  }
  return 1 + getSizeAtNode(subTreeRoot->m_left) + getSizeAtNode(subTreeRoot->m_right);
}

//inserts an item into the tree
template <typename T>
void ScapegoatST<T>::insert(T d){
  //adds the node and adds to the size
  TreeNode<T>* newNode = new TreeNode<T>(d);
  if (m_size == 0){
  m_root = newNode;
  }else{
  insertHelper(m_root, newNode);
  }
  ++m_size;
}

template <typename T>
void ScapegoatST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){//inserts when the node is empty
    subTreeRoot = newNode;
    rebuildCheck(subTreeRoot);//checks if we need to rebuild after an insert
  } else if(newNode->m_data < subTreeRoot->m_data){
    newNode->m_parent = subTreeRoot;
    insertHelper(subTreeRoot->m_left,newNode);//moves left if the value is less than
  } else{
    newNode->m_parent = subTreeRoot;
    insertHelper(subTreeRoot->m_right,newNode);//moves right if the value is greater than
  }
}

//checks if we need to rebuild and will be called after every deletion and insertion
template<typename T>
bool ScapegoatST<T>::rebuildCheck(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != m_root){
    //cout << ((double)(log(getTotalSize())) / (double)(log(1.5))) << endl;
    if (getNodeDepth(subTreeRoot) > ((double)(log(getTotalSize())) / (double)(log(1.5))) || getNodeDepth(subTreeRoot) < (getTotalSize()/2)){//includes the upper and lower bound conditions
      isScapeGoat(subTreeRoot);// if we must rebuild we will find the scapegoat
    }else{
      if(subTreeRoot != m_root){
      rebuildCheck(subTreeRoot->m_parent);//will continue to check up the path until it reaches the root
      }
    }
  }
}

//checks if it exists in the tree
template <typename T>
bool ScapegoatST<T>::contains(int id){
  return containsHelper(m_root, id);

}

template <typename T>
bool ScapegoatST<T>::containsHelper(TreeNode<T>* subTreeRoot, int id){
  if(subTreeRoot == NULL){
    return false;
  } else if(id == subTreeRoot->m_data.getId()){
    return true;
  } else if(id < subTreeRoot->m_data.getId()){
    return containsHelper(subTreeRoot->m_left,id);
  } else{
    return containsHelper(subTreeRoot->m_right,id);
  }
}

template <typename T>
void ScapegoatST<T>::printTreeInOrder(){
  printTreeInOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    cout << subTreeRoot->m_data.getId() << endl;
    printTreeInOrderHelper(subTreeRoot->m_right);
  }

}

template <typename T>
void ScapegoatST<T>::printTreePostOrder(){
  printTreePostOrderHelper(m_root);
}

template <typename T>
void ScapegoatST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    printTreeInOrderHelper(subTreeRoot->m_right);
    cout << subTreeRoot->m_data.getId() << endl;
  }
}

//finds the depth of the node by incrementing each time it travels until it reaches the value
template <typename T>
int ScapegoatST<T>::getNodeDepth(TreeNode<T>* subTreeRoot){
  TreeNode<T>* newNode = m_root;
  int depth = 0;

  while (newNode->m_data != subTreeRoot->m_data){

    if (subTreeRoot->m_data == newNode->m_data){
      return depth;
    }
    else if (subTreeRoot->m_data < newNode->m_data){

      depth++;
      newNode = newNode->m_left;
    }else if (subTreeRoot->m_data > newNode->m_data){

      depth++;
      newNode = newNode->m_right;
    }else if (newNode == NULL){//if it never finds it then it doesn't exist
      return -1;
    }
  }
  return depth;
}



//will check if the node is a scapegoat
template<typename T>
bool ScapegoatST<T>::isScapeGoat(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != m_root){
    if (((double)getSizeAtNode(subTreeRoot) / (double)getSizeAtNode(subTreeRoot->m_parent)) > 2.0/3.0){
      rebuildTree(subTreeRoot);//will rebuild the tree if it meets the conditions
      return true;
    }else{
      if (subTreeRoot->m_parent != NULL){
      return isScapeGoat(subTreeRoot->m_parent);//continues to check up the path until it finds the scapegoat
      }else{false;}
      }
  }
}


template <typename T>
T ScapegoatST<T>::getMin(){
  //check if empty
  return getMinHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_left==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T>
T ScapegoatST<T>::getMax(){
  //check if empty
  return getMaxHelper(m_root);
}

template <typename T>
T ScapegoatST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_right==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMaxHelper(subTreeRoot->m_right);
  }

}


//returns root of the tree
template <typename T>
TreeNode<T>* ScapegoatST<T>::getRoot(){
    return m_root;
}


template <typename T>
T ScapegoatST<T>::getMedian(){
  //check if empty
  return m_root->m_data;
}

template <typename T>
void ScapegoatST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && target->m_data != key){
    parent = target;
    if(key < target->m_data){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}

template <typename T>
void ScapegoatST<T>::findTargetInt(int key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && target->m_data.getId() != key){
    parent = target;
    if(key < target->m_data.getId()){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}

//returns the furtherest left node of the right subtree
template <typename T>
TreeNode<T>* ScapegoatST<T>::getSuccessor(TreeNode<T>* rightChild){
  while(rightChild->m_left != NULL){
    rightChild = rightChild->m_left;
  }
  return rightChild;
}

//removes a node from the tree
template <typename T>
void ScapegoatST<T>::remove(T d){
  //check if empty
  TreeNode<T>* target = NULL;
  TreeNode<T>* parent = NULL;
  target = m_root;
  findTarget(d,target,parent);
  if(target == NULL){ //if it doesn't exist do nothing
    return;
  }
  //check if leaf (including the root)
  if(target->m_left == NULL && target->m_right == NULL){ //if the target is a leaf
    if(target == m_root){ //we are removing the root
      m_root = NULL;
    } else{ //it's not the root
      if(target ==  parent->m_left){
        parent->m_left = NULL;
      } else{
        parent->m_right = NULL;
      }
      rebuildCheck(parent);//after deletion we will check if we must rebuild
    }
    //delete target; //free the memory

  } else if(target->m_left != NULL && target->m_right != NULL){ //2 child case
    TreeNode<T>* suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); //remove successor treenode
    target->m_data = value;
    rebuildCheck(target); // call rebuildCheck on the replacement node and it's path

  } else{ //1 child
    TreeNode<T>* child;
    if(target->m_left != NULL){
      child = target->m_left;
    } else{
      child = target->m_right;
    }
    rebuildCheck(child);//calls rebuildCheck on the replacement node and it's path
    if(target ==  m_root){
      m_root = child;
    } else{
      if(target == parent->m_left){
        //cout << "I'm here!" << endl;
        parent->m_left = child;
      } else{
        parent->m_right = child;
      }
    }
      //delete target;
  }
  --m_size;


}


template <typename T>
void ScapegoatST<T>::removeInt(int id){//given the ID we will remove the corresponding node
  //check if empty
  TreeNode<T>* target = NULL;
  TreeNode<T>* parent = NULL;
  target = m_root;
  findTargetInt(id,target,parent);
  if(target == NULL){ //value wasn't in tree, nothing to do
    return;
  }
  if(target->m_left == NULL && target->m_right == NULL){ //checks if it's the leaf
    if(target == m_root){ //leaf is the root of tree
      m_root = NULL;
    } else{ //it's not the root
      if(target ==  parent->m_left){
        parent->m_left = NULL;
      } else{
        parent->m_right = NULL;
      }
      rebuildCheck(parent);//calls rebuildCheck on the parent of the leaf
    }
    //delete target; //free the memory

  } else if(target->m_left != NULL && target->m_right != NULL){ //2 child case
    TreeNode<T>* suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); //remove successor treenode
    target->m_data = value;
    rebuildCheck(target); // calls rebuildCheck on its' replacement and path

  } else{ //1 child
    TreeNode<T>* child;
    if(target->m_left != NULL){
      child = target->m_left;
    } else{
      child = target->m_right;
    }
    rebuildCheck(child);//calls rebuildCheck on its' replacement and path
    if(target ==  m_root){
      m_root = child;
    } else{
      if(target == parent->m_left){
        //cout << "I'm here!" << endl;
        parent->m_left = child;
      } else{
        parent->m_right = child;
      }
    }
      //delete target;
  }
  --m_size;


}

//returns the person(either student or faculty) given their ID
template <typename T>
T* ScapegoatST<T>::getPerson(int n){
  return personHelper(m_root, n);
}

//helps locate the person given the ID
template <typename T>
T* ScapegoatST<T>::personHelper(TreeNode<T>* subTreeRoot, int n){
  if (subTreeRoot == NULL){}
  else if(n == subTreeRoot->m_data.getId())
  {
    return &subTreeRoot->m_data;
  }
  else if(n < subTreeRoot->m_data.getId())
  {
    return personHelper(subTreeRoot->m_left,n);
  }
  else
  {
    return personHelper(subTreeRoot->m_right,n);
  }
}

//prints the array of the values in the tree in ascending order
template <typename T>
void ScapegoatST<T>::ascArray(TreeNode<T>* subTreeRoot){
  int size = getSizeAtNode(subTreeRoot);
  TreeNode<T> **arr = new TreeNode<T>* [size];//creates
    treeToArray(subTreeRoot, arr, 0);//populates
    cout << "array" << endl;
    for (int i = 0; i < size; i++){
      arr[i]->m_data.printInfo();

    }
}

//converts the values from the tree and puts them into an array
template <typename T>
int ScapegoatST<T>::treeToArray(TreeNode<T> *subTreeRoot, TreeNode<T> *arr[], int i)
{
  if (subTreeRoot == NULL){
    cout << i << endl;
    return i;
  }
  i = treeToArray(subTreeRoot->m_left, arr, i);
  arr[i++] = subTreeRoot;
  return treeToArray(subTreeRoot->m_right, arr, i);
}


//rebuilds the subtree
template <typename T>
void ScapegoatST<T>::rebuildTree(TreeNode<T> *subTreeRoot)
{
  TreeNode<T> *parentRoot = subTreeRoot->m_parent;
  int size = getSizeAtNode(subTreeRoot);
  TreeNode<T> **arr = new TreeNode<T>* [size];

  treeToArray(subTreeRoot, arr, 0);//takes the array version of the tree and puts them back into the tree

  if (parentRoot == NULL){
    m_root = arrayToTree(arr, 0, size);
    m_root->m_parent = NULL;
  }
  else if (parentRoot->m_left == subTreeRoot){//builds left
    parentRoot->m_left = arrayToTree(arr, 0, size);
    parentRoot->m_left->m_parent = parentRoot;
  }
  else{//builds right
    parentRoot->m_right = arrayToTree(arr, 0, size);
    parentRoot->m_right->m_parent = parentRoot;
  }
}

//converts the array back into a tree
template <typename T>
TreeNode<T> * ScapegoatST<T>::arrayToTree(TreeNode<T> **arr, int i, int size)
{
  int median = size / 2;
  if (size== 0)
    return NULL;

  arr[i+median]->m_right = arrayToTree(arr, i+median+1, size-median-1);//fills right side
  if (arr[i+median]->m_right != NULL){
    arr[i+median]->m_right->m_parent = arr[i+median];
  }

  arr[i+median]->m_left = arrayToTree(arr, i, median);//fills left side
  if (arr[i+median]->m_left != NULL){
    arr[i+median]->m_left->m_parent = arr[i+median];
  }

  return arr[i+median];
}



#endif
