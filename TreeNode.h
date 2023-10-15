/// @file TreeNode.h
/// @brief Allows for creation of a tree node for implementation within ScapegoatST. (header)
/// @author Tyler Edwards - tk.edwards2003@gmail.com

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();

  template <typename S>
  friend class ScapegoatST;
  void setNodeSize(int i);
  int getNodeSize();
  int getNodeDepth();

private:
  T m_data;
  int m_depth;
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
  TreeNode<T>* m_parent;
  int nodeSize;

};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_data = d;
  m_left = NULL;
  m_right = NULL;
  m_parent = NULL;
  int m_depth = 0;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL){
    delete m_left;
  }
  if(m_right != NULL){
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}


//-------------------------my inclusions----------------------------
template <typename T>
void TreeNode<T>::setNodeSize(int i){
  nodeSize += i;
}

template<typename T>
int TreeNode<T>::getNodeSize(){
  return nodeSize;
}

//--------------------------end of my inclusions-----------------------------

#endif
