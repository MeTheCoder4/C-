
#ifndef AVL_VECTOR_H
#define AVL_VECTOR_H

#include <cstring>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector();
    ~Vector();
    void push(T value);
    T& operator[](int index);
    T pop();
    int getSize() {return size;}
    bool empty() {return size == 0;}
private:
    T* data;
    int size;
};

template<typename T>
Vector<T>::Vector() {
    data = nullptr;
    size = 0;
}

template<typename T>
Vector<T>::~Vector() {
    if(size == 1)
        delete data;
    else if(size > 1)
        delete[] data;

    data = nullptr;
}

template<typename T>
void Vector<T>::push(T value) {
    if(!size) {
        data = new T(value);
        size++;
    }
    else {
        T* temp = new T[++size];
        memcpy(temp, data, sizeof(T)*(size-1));
        temp[size-1] = value;

        if((size-1) == 1)
            delete data;
        else
            delete[] data;

        data = temp;
    }
}

template<typename T>
T Vector<T>::pop() {
    if(!size)
        throw std::out_of_range("Trying to pop an element from an empty Vector!");

    size--;
    T* temp = nullptr;

    if(size == 1)
        temp = new T;
    else if(size > 1)
        temp = new T[size];

    memcpy(temp, data, sizeof(T)*size);
    T value = data[size];

    if((size + 1) == 1)
        delete data;
    else if((size + 1) > 1)
        delete[] data;

    data = temp;
    return value;
}

template<typename T>
T& Vector<T>::operator[](const int index) {
    return data[index];
}

#endif //AVL_VECTOR_H
