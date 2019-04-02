
#include "Tree.h"
#include <cassert>
#include <cstring>

using namespace std;

Tree::Tree()
    : m_root(nullptr), m_entryCounter(0) {}

Tree::~Tree() {
    while(m_root != nullptr)
        remove(m_root->getKey());
}

bool Tree::insert(int key) {
    Node* temp = m_root, *parent = nullptr;
    Vector<Node*> pathToLeaf;
    pathToLeaf.push(nullptr);

    while(temp != nullptr) {
        if(temp->getKey() == key)
            return false;

        parent = temp;

        if(key > temp->getKey())
            temp = temp->getRightChild();
        else if(key < temp->getKey())
            temp = temp->getLeftChild();

        pathToLeaf.push(parent);
    }

    if(m_root == nullptr) {
        m_root = growLeaf(key);
        pathToLeaf.push(m_root);
    }
    else if(key > parent->getKey()) {
        parent->setRightChild(growLeaf(key));
        pathToLeaf.push(parent->getRightChild());
    }
    else if(key < parent->getKey()) {
        parent->setLeftChild(growLeaf(key));
        pathToLeaf.push(parent->getLeftChild());
    }

    balance(pathToLeaf);

    return true;
}

Node *Tree::growLeaf(int key) {
    string keyAsString = to_string(key);

    try {
        return new Node(key, nullptr, nullptr, keyAsString.c_str());
    }
    catch(bad_alloc& badAlloc) {
        throw badAlloc;
    }
}

void Tree::insertRandom(int amount) {
    assert(amount >= 0);
    const int max = 20000;
    const int min = -10000;

    for(int i = 0; i < amount; i++) {
        int value = (rand() % max) + min;

        while (find(value) != nullptr)
            value = (rand() % max) + min;

        insert(value);
    }
}

Node* Tree::find(int key) {
    if(m_root == nullptr)
        return nullptr;

    Node* temp = m_root;
    while(temp != nullptr) {
        if(temp->getKey() == key)
            return temp;
        else if(key > temp->getKey())
            temp = temp->getRightChild();
        else if(key < temp->getKey())
            temp = temp->getLeftChild();
    }

    return nullptr;
}

bool Tree::removal(int key, Vector<Node*>& pathToNode) {
    Node* temp = m_root, *parent = nullptr;
    Vector<Node*> helper;

    if((m_root == nullptr) || (find(key) == nullptr))
        return false;

    while(temp != nullptr) {
        parent = temp;

        if(parent->getKey() != key)
            pathToNode.push(parent);

        if(key > temp->getKey())
            temp = temp->getRightChild();
        else if(key < temp->getKey())
            temp = temp->getLeftChild();

        if(temp->getKey() == key && temp->isLeftNull() && temp->isRightNull()) {
            if(temp == m_root)
                m_root = nullptr;

            if(parent->getRightChild() == temp)
                parent->setRightChild(nullptr);
            else
                parent->setLeftChild(nullptr);

            delete temp;
            temp = nullptr;
            return true;
        }
        else if(!temp->isLeftNull() && !temp->isRightNull() && temp->getKey() == key) {
            // Parent of the successor
            Node* preparent = temp;
            // Successor
            Node* child = temp->getRightChild();

            while(!child->isLeftNull()) {
                preparent = child;
                helper.push(child);
                child = child->getLeftChild();
            }

            pathToNode.push(child);

            for(int i = 0; i < helper.getSize(); i++)
                pathToNode.push(helper[i]);

            if(preparent->getLeftChild() == child)
                preparent->setLeftChild(child->getRightChild());
            else
                preparent->setRightChild(child->getRightChild());

            child->setLeftChild(temp->getLeftChild());
            child->setRightChild(temp->getRightChild());

            if(temp == m_root)
                m_root = child;
            else if(parent->getLeftChild() == temp)
                parent->setLeftChild(child);
            else
                parent->setRightChild(child);

            delete temp;
            temp = nullptr;
            return true;
        }
        else if(temp->isRightNull()) {
            if(parent->getRightChild() == temp && temp->getKey() == key) {
                parent->setRightChild(temp->getLeftChild());
                delete temp;
                temp = nullptr;
                return true;
            }
            else if(parent->getLeftChild() == temp && temp->getKey() == key){
                parent->setLeftChild(temp->getLeftChild());
                delete temp;
                temp = nullptr;
                return true;
            }
            else if(parent == temp && temp->getKey() == key) {
                Node* temp2 = temp->getLeftChild();
                delete m_root;
                m_root = temp2;
                return true;
            }
        }
        else if(temp->isLeftNull()) {
            if(parent->getRightChild() == temp && temp->getKey() == key) {
                parent->setRightChild(temp->getRightChild());
                delete temp;
                temp = nullptr;
                return true;
            }
            else if(parent->getLeftChild() == temp && temp->getKey() == key){
                parent->setLeftChild(temp->getRightChild());
                delete temp;
                temp = nullptr;
                return true;
            }
            else if(parent == temp && temp->getKey() == key) {
                Node* temp2 = temp->getRightChild();
                delete m_root;
                m_root = temp2;
                return true;
            }
        }
    }

    return false;
}

void Tree::preorder(Node *root) {
    if(root == nullptr)
        return;

    cout << *root << endl;
    m_entryCounter++;
    preorder(root->getLeftChild());
    preorder(root->getRightChild());
}

void Tree::inorder(Node *root) {
    if(root == nullptr)
        return;

    inorder(root->getLeftChild());
//    cout << *root << endl;
    m_entryCounter++;

    root->setBalanceFactor(calculateBalanceFactor(root));
    if(root->getBalanceFactor() > 1 || root->getBalanceFactor() < -1)
        cout << root->getBalanceFactor() << endl;

    inorder(root->getRightChild());
}

void Tree::postorder(Node *root) {
    if(root == nullptr)
        return;

    postorder(root->getLeftChild());
    postorder(root->getRightChild());
    cout << *root << endl;
    m_entryCounter++;
}

int Tree::height(Node *currentRoot) {
    if(!currentRoot)
        return 0;

    return max(height(currentRoot->getLeftChild()),
                   height(currentRoot->getRightChild())) + 1;

}

int Tree::max(int val1, int val2) {
    return (val1 < val2) ? val2 : val1;
}

int Tree::calculateBalanceFactor(Node* currentRoot) {
    if(currentRoot != nullptr)
        return height(currentRoot->getRightChild()) - height(currentRoot->getLeftChild());

    return 0;
}

void Tree::rotateRight(Node *grandparent, Node *parent, Node *child) {
    setGrandparent(grandparent, parent, child);

    Node* temp = child->getRightChild();
    child->setRightChild(parent);
    parent->setLeftChild(temp);

    if(grandparent != nullptr)
        grandparent->setBalanceFactor(calculateBalanceFactor(grandparent));

    parent->setBalanceFactor(calculateBalanceFactor(parent));
    child->setBalanceFactor(calculateBalanceFactor(child));
}

void Tree::rotateLeft(Node *grandparent, Node *parent, Node *child) {
    setGrandparent(grandparent, parent, child);

    Node* temp = child->getLeftChild();
    child->setLeftChild(parent);
    parent->setRightChild(temp);

    if(grandparent != nullptr)
        grandparent->setBalanceFactor(calculateBalanceFactor(grandparent));

    parent->setBalanceFactor(calculateBalanceFactor(parent));
    child->setBalanceFactor(calculateBalanceFactor(child));
}

void Tree::setGrandparent(Node *grandparent, Node *parent, Node *child) {
    if(grandparent != nullptr) {
        if(grandparent->getRightChild() == parent)
            grandparent->setRightChild(child);
        else
            grandparent->setLeftChild(child);
    }
    else
        m_root = child;
}

bool Tree::remove(int key) {
    Vector<Node*> pathToLeaf;
    pathToLeaf.push(nullptr);

    if(!removal(key, pathToLeaf))
        return false;

    balance(pathToLeaf);

    return true;
}

void Tree::balance(Vector<Node*>& pathToLeaf) {
    if(pathToLeaf.getSize() <= 1)
        return;

    for(int i = pathToLeaf.getSize() - 1; i > 0; i--) {
        Node* currentNode = pathToLeaf[i];
        // Update balance factor of each node
        currentNode->setBalanceFactor(calculateBalanceFactor(currentNode));

        if(currentNode->getBalanceFactor() > 1) {
            if(currentNode->getRightChild()->getBalanceFactor() <= -1) {
                rotateRight(pathToLeaf[i], pathToLeaf[i]->getRightChild(), pathToLeaf[i]->getRightChild()->getLeftChild());
                rotateLeft(pathToLeaf[i - 1], pathToLeaf[i], pathToLeaf[i]->getRightChild());
            }
            else
                rotateLeft(pathToLeaf[i - 1], currentNode, currentNode->getRightChild());
        }
        else if(currentNode->getBalanceFactor() < -1) {
            if(currentNode->getLeftChild()->getBalanceFactor() >= 1) {
                rotateLeft(pathToLeaf[i], pathToLeaf[i]->getLeftChild(), pathToLeaf[i]->getLeftChild()->getRightChild());
                rotateRight(pathToLeaf[i - 1], pathToLeaf[i], pathToLeaf[i]->getLeftChild());
            }
            else
                rotateRight(pathToLeaf[i - 1], currentNode, currentNode->getLeftChild());
        }
    }
}
