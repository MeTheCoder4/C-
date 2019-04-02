
#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <string>
#include <iostream>

class Node {
public:
    Node(int, Node*, Node*, const char*);

    friend std::ostream& operator<<(std::ostream& outStream, Node& node) {
        return outStream << "Key: " << node.m_key << std::endl
                         << "Balance factor: " << node.getBalanceFactor() << std::endl
                         << "Key as char array: " << node.getCharacters() << std::endl;
    }

    void setKey(int key) { m_key = key; }
    int getKey() { return m_key; }
    void setLeftChild(Node* leftNode) { m_left = leftNode; }
    Node* getLeftChild();
    void setRightChild(Node* rightChild) { m_right = rightChild; }
    Node* getRightChild();
    void setCharacters(const char*);
    char* getCharacters();
    void setBalanceFactor(int);
    int getBalanceFactor();
    bool isLeftNull();
    bool isRightNull();

private:
    int m_key;
    Node* m_left, *m_right;
    char m_characters[10];
    int m_balanceFactor;

};


#endif //AVL_NODE_H
