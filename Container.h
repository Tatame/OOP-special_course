#include <iostream>

#pragma once

template<class T>
class Container{

public:
    struct Node {
        T value;
        Node *early;
        Node *next;

        explicit Node(const T& val, Node* e = nullptr, Node* n = nullptr) {
            value = val;
            early = e;
            next = n;
        }
    };

    class Iterator{
    public:
        Iterator() : current{nullptr} {}

        T& operator*(){
            return current->value;
        }

        Iterator& operator++(){
            current = current->next;
            return *this;
        }

        Iterator& operator--(){
            current = current->early;
            return *this;
        }

        bool operator==(const Iterator &other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }

    public:
        explicit Iterator(Node *p) : current{p} {}

    protected:
        Node* current;
    };

public:
    Iterator begin() noexcept{
        return Iterator(head);
    }

    Iterator end() noexcept{
        return Iterator(tail->next);
    }

public:
    Container(){
        create();
    }

    ~Container(){
        clear();
    }

public:
    uint32_t size(){
        return container_size;
    }

    bool is_empty() const {
        return container_size == 0;
    }

    void push_front(const T& val){
        if (is_empty()) create_first(val);
        else {
            Node* tmp = new Node(val);
            tmp->next = head;
            head->early = tmp;
            head = tmp;
            ++container_size;
        }
    }

    void push_back(const T& val){
        if (is_empty()) create_first(val);
        else {
            Node* tmp = new Node(val);
            tmp->early = tail;
            tail->next = tmp;
            tail = tmp;
            ++container_size;
        }
    }

    void pop_front(){
        if (!is_empty()){
            Node* tmp = head;
            head = head->next;
            if (head) head->early = nullptr;
            free(tmp);
            --container_size;
        }
        else throw std::out_of_range("Container is empty");
    }

    void pop_back(int i) {
        if (!is_empty()){
            Node* tmp = tail;
            tail = tail->early;
            if (tail) tail->next = nullptr;
            delete tmp;
            --container_size;
        }
        else throw std::out_of_range("Container is empty");
    }

    void clear(){
        while (!is_empty()){
            pop_front();
        }
    }

    const T& get_first_element() const{
        if (!is_empty()){
            return head->value;
        }
        else throw std::out_of_range("Container is empty");
    }

    const T& get_last_element() const{
        if (!is_empty()){
            return tail->value;
        }
        else throw std::out_of_range("Container is empty");
    }

    void swap(Container& other){
        Node* tmp = head;
        head = other.head;
        other.head = tmp;
        tmp = tail;
        tail = other.tail;
        other.tail = tmp;
        auto len = container_size;
        container_size = other.container_size;
        other.container_size = len;
    }

    void swap(Iterator& it1, Iterator& it2){
        std::iter_swap(it1, it2);
    }

    void reverse() noexcept {
        auto it1 = begin();
        auto it2 = Iterator(tail);
        uint32_t count = container_size/2;
        while (count--) {
            swap(it1, it2);
            ++it1;
            --it2;
        }
    }

public:


private:
    void create() {
        container_size = 0;
        head = nullptr;
        tail = nullptr;
    }

    void create_first(const T& val){
        head = new Node(val, nullptr, nullptr);
        tail = head;
        container_size = 1;
    }

private:
    Node* head;
    Node* tail;
    uint32_t container_size{};
};

