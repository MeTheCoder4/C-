
#include "Node.h"
#include <cstring>
#include <cassert>

Node::Node(int key, Node *leftChild, Node *rightChild, const char *characters)
        : m_key(key), m_left(leftChild), m_right(rightChild) {
    setCharacters(characters);
}

void Node::setCharacters(const char *characters) {
    const int8_t maxLength = 10;
    assert(strlen(characters) < maxLength);
    strcpy(m_characters, characters);
}

char *Node::getCharacters() {
    return m_characters;
}

void Node::setBalanceFactor(int balanceFactor) {
    m_balanceFactor = balanceFactor;
}

int Node::getBalanceFactor() {
    return m_balanceFactor;
}

bool Node::isLeftNull() {
    return m_left == nullptr;
}

bool Node::isRightNull() {
    return m_right == nullptr;
}

Node *Node::getRightChild() {
    if(m_right)
        return m_right;

    return nullptr;
}

Node *Node::getLeftChild() {
    if(m_left)
        return m_left;

    return nullptr;
}
