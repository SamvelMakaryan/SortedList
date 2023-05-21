#ifndef LIST_HPP_
#define LIST_HPP_
#include <initializer_list>
#include <stdexcept>

template <typename T>
class List {
public:
    List();
    List(const T&);
    List(std::initializer_list<T>);
    List(const List&);
    List(List&&) noexcept;
	~List();
public:
    void print() const;
    void print_sorted() const;
    void push_back(const T&);
    void push_front(const T&);
    void insert(const T&, int);
    T pop_front();
    T pop_back();
    void erase(int);
    bool empty() const;
private:
    struct Node {
        Node() = default;
        Node(const T& val) : val(val) {}
        Node* next;
        Node* next_max;
        Node* prev_min;
        T val;
    };
private:
    void insert_sorted(Node*);
private:
    Node* m_head;    
    Node* m_sorted;
};

#include "List.tpp"

#endif //LIST_HPP_
