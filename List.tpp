#ifndef LIST_TPP_
#define LIST_TPP_
#include "List.hpp"

template <typename T>
List<T>::List()
    : m_head(nullptr),
    m_sorted(nullptr) {}

template <typename T>
List<T>::List(const T& val)
    : m_head(new Node(val)),
    m_sorted(m_head) {}

template <typename T>
List<T>::List(std::initializer_list<T> init) 
 : m_head(nullptr),
   m_sorted(nullptr)
{
    for (auto i : init) {
        push_back(i);
    }
}

template <typename T>
List<T>::List(const List& oth) {
    Node* tmp = oth.m_head;
    while (tmp) {
        push_back(tmp->val);
        tmp = tmp->next;
    } 
}

template <typename T>
List<T>::List(List&& oth) noexcept
    : m_head(oth.m_head),
    m_sorted(oth.m_sorted) 
{
    oth.m_head = nullptr;
    oth.m_sorted = nullptr;
}

template <typename T>
void List<T>::print() const {
Node* tmp = m_head;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::print_sorted() const {
    Node* tmp = m_sorted;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->next_max;
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::push_back(const T& val) {
    Node* new_node = new Node(val);
    if (m_head == nullptr) {
        m_head = new_node;
        m_head->next = nullptr;
    }
    else {
        Node* tmp = m_head;
        while (tmp->next) {
            tmp = tmp -> next;
        }
        tmp->next = new_node;
        tmp->next->next = nullptr;
    }
    insert_sorted(new_node);
}

template <typename T>
void List<T>::push_front(const T& val) {
    Node* new_node = new Node(val);
    if (m_head == nullptr) {
        m_head = new_node;
        m_head->next = nullptr;
    }
    else {
        new_node->next = m_head;
        m_head = new_node;
    }
    insert_sorted(new_node);
}

template <typename T>
void List<T>::insert(const T& val, int n) {
    if (n < 0) {
        return;
    }
    Node* new_node = new Node(val);
    if (n == 0) {
        push_front(val);
        return;
    }
    if (m_head == nullptr) {
        m_head = new_node;
        m_head->next = nullptr;
    }
    else {
        Node* tmp = m_head;
        for (int i = 0; i < n - 1; ++i) {
            tmp = tmp->next;
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
    }
    insert_sorted(new_node);
}

template <typename T>
T List<T>::pop_front() {
    if (!m_head) {
        std::runtime_error("List is empty");
    }
    if (!m_head->next) {
        T val = m_head->val;
        delete m_head;
        m_head = nullptr;
        m_sorted = nullptr;
        return val;
    }
    Node* tmp = m_head;
    m_head = tmp->next;
    if (tmp->next_max) {
        tmp->next_max->prev_min = tmp->prev_min;
    }
    if (tmp->prev_min) {
        tmp->prev_min->next_max = tmp->next_max;
    }
    T val = tmp->val;
    delete tmp;
    return val;
}

template <typename T>
T List<T>::pop_back() {
    if (!m_head) {
        throw std::runtime_error("List is empty");
    }
    Node* tmp = m_head;
    Node* old;
    while (tmp->next) {
        old = tmp;
        tmp = tmp->next;
    }
    tmp->next_max->prev_min = tmp->prev_min;
    tmp->prev_min->next_max = tmp->next_max;
    old->next = nullptr;
    T val = tmp->val;
    delete tmp;
    return val;
}

template <typename T>
void List<T>::erase(int n) {
    if (n < 0) {
        throw std::invalid_argument("Given index is out of bounds");
    }
    if (!m_head) {
        throw std::runtime_error("List is empty");
    }
    if (n == 0) {
        pop_front();
        return;
    }
    Node* tmp = m_head;
    while (tmp && n >= 2) {
        tmp = tmp->next;
        --n;
    }
    if (!tmp) {
        throw std::invalid_argument("Given index is out of bounds");
    }
    if (!tmp->next) {
        pop_back();
        return;
    }
    Node* old = tmp->next;
    tmp->next = old->next;
    old->prev_min->next_max = old->next_max;
    old->next_max->prev_min = old->prev_min;
    delete old;
}

template <typename T>
bool List<T>::empty() const {
    return !m_head;
}

template <typename T>
void List<T>::insert_sorted(Node* new_node) {
if (m_sorted == nullptr) {
    m_sorted = m_head;
    m_sorted->next_max = m_sorted->prev_min = nullptr;
}
else {
    Node* tmp = m_sorted;
    while (tmp->next_max && tmp->val < new_node->val) {
        tmp = tmp->next_max;
    }
    if (!tmp->next_max) {
        if (tmp->val < new_node->val) {
            tmp->next_max = new_node;
            new_node->next_max = nullptr;
            new_node->prev_min = tmp;
        }
        else {
            new_node->prev_min = tmp->prev_min;
            new_node->next_max = tmp;
            tmp->prev_min->next_max = new_node;
            tmp->prev_min = new_node;
        }
    }
    else {
        if (tmp->prev_min) {
            tmp->prev_min->next_max = new_node;
        }
        else {
            m_sorted = new_node;
        }
        new_node->prev_min = tmp->prev_min;
        new_node->next_max = tmp;
        tmp->prev_min = new_node;
    }
    }
}

#endif //LIST_TPP_