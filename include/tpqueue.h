// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T DATA;
        Item* NEXT;
        Item* LAST;
    };
    Item* HEAD;
    Item* TAIL;
    TPQueue::Item* create(const T&);

 public:
    TPQueue() : HEAD(nullptr), TAIL(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

struct SYM {
    char ch;
    int prior;
};

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data){
    Item* item = new Item;
    item->DATA = DATA;
    item->NEXT = nullptr;
    item->LAST = nullptr;
    return item;
}

template <typename T>
T TPQueue<T>::pop(){
    if (!HEAD) {
        throw std::string("TPQueue - empty");
    } else {
        Item* temp = HEAD->NEXT;
        T DATA = HEAD->DATA;
        delete HEAD;
        HEAD = temp;
        return DATA;
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (HEAD) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* uk = HEAD;
    while (uk) {
        std::cout << uk->DATA << " ";
        uk = uk->NEXT;
    }
    std::cout << std::endl;
}

template <typename T>
void TPQueue<T>::push(const T& value) {
    if (HEAD == nullptr) {
        HEAD = create(value);
        TAIL = HEAD;
    } else if (TAIL->DATA.prior >= value.prior) {
        if (TAIL->DATA.ch == value.ch) {
            TAIL->DATA = value;
        } else {
            TAIL->NEXT = create(value);
            TAIL->NEXT->LAST = TAIL;
            TAIL = TAIL->NEXT;
        }
    } else if (HEAD == TAIL) {
        TAIL->LAST = create(value);
        HEAD = TAIL->LAST;
        HEAD->NEXT = TAIL;
    } else {
        Item* tmp = TAIL;
        while (tmp != HEAD && tmp->DATA.prior < value.prior) {
            tmp = tmp->LAST;
        }
        if (tmp->DATA.prior > value.prior) {
            Item* cell = new Item;
            cell->NEXT = tmp->NEXT;
            cell->LAST = tmp;
            cell->DATA = value;
            tmp->NEXT->LAST = cell;
            tmp->NEXT = cell;
        }
        if (tmp == HEAD && tmp->DATA.prior < value.prior) {
            HEAD->LAST = create(value);
            HEAD = HEAD->LAST;
            HEAD->NEXT = tmp;
        }
    }
}
#endif  // INCLUDE_TPQUEUE_H_
