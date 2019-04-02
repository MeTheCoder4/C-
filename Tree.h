
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Vector.h"
#include "Node.h"

class Tree {
public:
    Tree();
    ~Tree();
    bool insert(int);
    void insertRandom(int);
    Node* find(int);
    bool remove(int);
    void preorder(Node*);
    void inorder(Node*);
    void postorder(Node*);
    Node* getRoot() { return m_root; }
    int height(Node*);
    int calculateBalanceFactor(Node*);
    void zeroCounter() { m_entryCounter = 0; }
    int getEntryCounter() { return m_entryCounter; }

private:
    // Private methods
    Node* growLeaf(int);
    int max(int, int);
    void rotateRight(Node*, Node*, Node*);
    void rotateLeft(Node*, Node*, Node*);
    void setGrandparent(Node*, Node*, Node*);
    bool removal(int, Vector<Node*>&);
    void balance(Vector<Node*>&);
    // Private fields
    Node* m_root;
    int m_entryCounter;
};


#endif //AVL_TREE_H
