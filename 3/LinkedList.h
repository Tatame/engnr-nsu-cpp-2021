#ifndef LAB3_LINKEDLIST_H
#define LAB3_LINKEDLIST_H

#include <cstdint>
#include <set>
#include <algorithm>
#include <iostream>
#include <exception>
#include <vector>

template <class T>
class LinkedList {
public:
    using value_type = T;

    using size_type = std::int64_t;
    using difference_type = std::ptrdiff_t;

    using reference = T&;
    using const_reference = const T&;

    using pointer = T*;
    using const_pointer = const T*;

public: // итераторы LegacyBidirectionalIterator (en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

    struct Node{
        T value;
        Node *early;
        Node *next;

        explicit Node(const T &val = T{}, Node *e = nullptr, Node *n = nullptr ){
            value = val;
            early = e;
            next = n;
        }

        explicit Node(T &val, Node *e = nullptr, Node *n = nullptr){
            value = val;
            early = e;
            next = n;
        }


    };

    class iterator{
    public:

        iterator() = default;

        explicit iterator(Node *p) : cur_node{p} {};

        T &operator*(){
            return cur_node->value;
        }

        const T &operator*() const{
            return cur_node->value;
        }

        iterator &operator++(){
            cur_node = cur_node->next;
            return *this;
        }

        iterator operator++(int){
            iterator p = *this;
            ++(*this);
            return p;
        }

        iterator &operator--(){
            cur_node = cur_node->early;
            return *this;
        }

        iterator operator--(int){
            iterator p = *this;
            --(*this);
            return p;
        }

    protected:
        Node *cur_node;
        friend class LinkedList<T>;
    };

    class const_iterator{
    public:

        const_iterator() : cur_node{nullptr} {};

        explicit const_iterator(Node *p) : cur_node{p} {};

        const T &operator*() const {
            return cur_node->value;
        }

        const_iterator &operator++() {
            cur_node = cur_node->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator p = *this;
            ++(*this);
            return p;
        }

        const_iterator &operator--() {
            cur_node = cur_node->early;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator p = *this;
            --(*this);
            return p;
        }

        bool operator==(const const_iterator &p) const {
            return cur_node == p.cur_node;
        }

        bool operator!=(const const_iterator &p) const {
            return !(*this == p);
        }

    protected:
        Node *cur_node;
        friend class LinkedList<T>;
    };

    class reverse_iterator{
    public:
        reverse_iterator() = default;;

        explicit reverse_iterator(Node *p) : cur_node{p} {};

        T &operator*(){
            return cur_node->value;
        }

        const T &operator*() const{
            return cur_node->value;
        }

        reverse_iterator &operator++(){
            cur_node = cur_node->early;
            return *this;
        }

        reverse_iterator operator++(int){
            reverse_iterator p = *this;
            ++(*this);
            return p;
        }

        reverse_iterator &operator--(){
            cur_node = cur_node->next;
            return *this;
        }

        reverse_iterator operator--(int){
            reverse_iterator p = *this;
            --(*this);
            return p;
        }

    protected:
        Node *cur_node;
        friend class LinkedList<T>;
    };

    class const_reverse_iterator{
    public:
        const_reverse_iterator() = default;

        const_reverse_iterator(Node *p) : cur_node{p} {};

        const T &operator*() const{
            return cur_node->value;
        }

        const_reverse_iterator &operator++(){
            cur_node = cur_node->early;
            return *this;
        }

        const_reverse_iterator operator++(int){
            const_reverse_iterator p = *this;
            ++(*this);
            return p;
        }

        const_reverse_iterator &operator--(){
            cur_node = cur_node->next;
            return *this;
        }

        const_reverse_iterator operator--(int){
            const_reverse_iterator p = *this;
            --(*this);
            return p;
        }

        bool operator==(const const_reverse_iterator &dif) const{
            return cur_node == dif.cur_node;
        }

        bool operator!=(const const_reverse_iterator &dif) const{
            return !(*this == dif);
        }

    protected:
        Node *cur_node;
        friend class LinkedList<T>;
    };

public: // конструкторы/деструкторы
    LinkedList(){
        create();
    };

    LinkedList(const LinkedList& other){
        create();
        for (auto &elem: other) push_back(elem);
    };

    LinkedList(LinkedList&& other) noexcept {
        list_size = other.list_size;
        other.list_size = 0;
        head = other.head;
        head = nullptr;
        tail = other.tail;
        tail = nullptr;
    };

    LinkedList(size_type count, const T& value){
        create();
        list_size = count;
        while (count){
            push_back(value);
            count--;
        }
    };

    explicit LinkedList(size_type count){
        create();
        list_size = count;
        while (count){
            push_back(0);
            count--;
        }
    };

    template<typename InputIt>
    LinkedList(InputIt first, InputIt last){
        create();
        for (auto i = first; i != last; i++){
            push_back(*i);
        }
    };

    LinkedList(std::initializer_list<T> init){
        create();
        for (auto &v : init){
            push_back(v);
        }
    };



    ~LinkedList(){
        clear();
        delete head;
        delete tail;
    };

public: // замена содержимого списка

    LinkedList& operator=(const LinkedList& other){
        LinkedList copy = other;
        std::swap(*this, copy);
        return *this;
    };

    LinkedList& operator=(LinkedList&& other){
        std::swap(this->list_size, other.list_size);
        std::swap(this->head, other.head);
        std::swap(this->tail, other.tail);
        return *this;
    };

    LinkedList& operator=(std::initializer_list<T> ilist){
        clear();
        create();
        for (auto &v: ilist){
            push_back(v);
        }
        return *this;
    };

    void assign(size_type count, const T& value ){
        clear();
        create();
        while (count){
            push_back(value);
            count--;
        }
    };

    template<typename InputIt>
    void assign(InputIt first, InputIt last){
        clear();
        create();
        for (auto i = first; i != last; i++) {
            push_back(*i);
        }
    };

    void assign(std::initializer_list<T> ilist){
        clear();
        create();
        for (auto &v: ilist){
            push_back(v);
        }
    };

public:  // доступ к элементам контейнера

    reference front(){
        return *begin();
    };

    const_reference front() const{
        return *begin();
    };

    reference back(){
        return *--end();
    };

    const_reference back() const{
        return *--end();
    };

public: // доступ к итераторам "натурального" порядка перебора элементов

    iterator begin() noexcept{
        return iterator(head->next);
    };

    const_iterator begin() const noexcept{
        return const_iterator(head->next);
    };

    const_iterator cbegin() const noexcept{
        return const_iterator(head->next);
    };

    iterator end() noexcept{
        return iterator(tail);
    };

    const_iterator end() const noexcept{
        return const_iterator(tail);
    };

    const_iterator cend() const noexcept{
        return const_iterator(tail);
    };

public: // доступ к итераторам обратного порядка перебора элементо

    reverse_iterator rbegin() noexcept{
        reverse_iterator(tail->early);
    };

    const_reverse_iterator rbegin() const noexcept{
        return const_reverse_iterator(tail->early);
    };

    const_reverse_iterator crbegin() const noexcept{
        return const_reverse_iterator(tail->early);
    };

    reverse_iterator rend() noexcept{
        return reverse_iterator(head);
    };

    const_reverse_iterator rend() const noexcept{
        return const_reverse_iterator(head);
    };

    const_reverse_iterator crend() const noexcept{
        return const_reverse_iterator(head);
    };

public: // информация о количестве элементов в списке

    size_type size() const noexcept{
        return list_size;
    };
    [[nodiscard]] bool empty() const noexcept{
        return list_size == 0;
    };

public: // вставка элементов

    iterator insert(const_iterator pos, const T& value){
        Node *p = pos.cur_node;
        iterator itr = iterator(p->early = p->early->next = new Node{value, p->early, p});
        ++list_size;
        return itr;
    };

    iterator insert(const_iterator pos, T&& value){
        Node *p = pos.cur_node;
        iterator itr = iterator(p->early = p->early->next = new Node{std::move(value), p->early, p});
        ++list_size;
        return itr;
    };

    iterator insert(const_iterator pos, size_type count, const T& value){
        if (pos == cend()) throw std::runtime_error("No iterator");
        else{
            while (count){
                pos = insert(pos,value);
                count--;
            }
        }
        return iterator(pos.cur_node);
    };

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last){
        last++;
        for (auto i = first; i != last; i++){
            pos = insert(pos, *i);
            pos++;
        }

        return iterator(pos.cur_node);
    };

    iterator insert(const_iterator pos, std::initializer_list<T> ilist){
        for (const auto &v: ilist){
            pos = insert(pos, v);
            pos++;
        }
        return iterator(pos.cur_node);
    };

    void push_front(const T& value){
        insert(begin(), value);
    };

    void push_front(T&& value){
        insert(begin(), std::move(value));
    };

    void push_back(const T& value){
        insert(end(), value);
    };

    void push_back(T&& value){
        insert(end(), std::move(value));
    };

public: // изъятие элементов

    iterator erase(const_iterator pos){
        Node *p = pos.cur_node;
        p->next->early = p->early;
        p->early->next = p->next;
        iterator current = iterator(p->next);
        delete p;
        list_size--;
        return current;
    };

    iterator erase(const_iterator first, const_iterator last){
        for(auto i = first; i != last;){
            i = erase(i);
        }
        return iterator(last.cur_node);
    };

    void pop_back(){
        erase(--end());
    };

    void pop_front(){
        erase(begin());
    };

public: // операции

    void sort(){
        sort(std::less_equal<T>());
    };

    template<typename Compare>
    void sort(Compare comp){
        merge_sort(begin(), end(), comp);
    };

    template<typename Compare>
    void merge_sort(iterator begin, iterator end, Compare comp){
        size_type size = 0;
        for (auto i = begin; i != end; i++, size++);
        if (size <= 1)
            return;
        else{
            auto middle = begin;
            size_type mid_size = size/2;
            while (mid_size){
                middle++;
                mid_size--;
            }
            merge_sort(begin, middle, comp);
            merge_sort(middle, end, comp);
            merge(begin, middle, end, comp);
        }
    }

    void insert_vec(std::vector<value_type> &temp, iterator begin, iterator end) {
        for (auto i = begin; i != end; i++)
            temp.push_back(*i);
    }

    template<typename Compare>
    void merge(iterator begin, iterator middle, iterator end, Compare comp) {
        std::vector<value_type> temp;
        size_type size = 0;
        for (auto i = begin; i != end; i++, size++);
        temp.reserve(size);
        iterator left = begin;
        iterator right = middle;
        while (left != middle && right != end) {
            if (comp(*right, *left))
                temp.emplace_back(*right++);
            else
                temp.emplace_back(*left++);
        }

        insert_vec(temp, left, middle);
        insert_vec(temp, right, end);

        for (const auto &value: temp) {
            *begin = std::move(value);
            begin++;
        }
    }

    size_type unique(){
        return unique([](const auto &left, const auto &right) { return left == right; });
    };

    template<typename BinaryPredicate>
    size_type unique(BinaryPredicate p){
        size_type count = list_size;
        auto left = cbegin();
        if (left == cend())
            return count;

        auto right = ++cbegin();
        for (; right != cend();) {
            if (p(*left, *right)) {
                erase(left);
                left = right;
                ++right;
            } else {
                ++left;
                ++right;
            }
        }
        return count - list_size;
    };

    void reverse() noexcept{
        auto i_one = begin();
        auto i_two = --end();
        while(i_one != i_two) {
            swap(i_one, i_two);
            i_one++;
            i_two--;
        }
    };

    size_type remove(const T& value){
        return remove_if([&value](auto &item) { return item == value; });
    };

    template<typename UnaryPredicate>
    size_type remove_if(UnaryPredicate p){
        auto i = begin();
        size_t count = 0;
        for (; i != end();) {
            if (p(*i)) {
                i = erase(i);
                count++;
            } else
                i++;
        }
        return count;
    };

    bool operator==(const LinkedList<T> &el) const {
        if (el.size() != size())
            return false;
        auto another = el.begin();
        for (auto i = begin(); i != end(); i++, another++)
            if (*i != *another)
                return false;
        return true;
    }

    bool operator!=(const LinkedList<T> &el) const {
        return !(*this == el);
    }

public: // прочие модификаторы

    void resize(size_type count, const value_type& value){
        if (list_size >= count)
            return;
        auto diff = count - list_size;
        while (diff) {
            push_back(value);
            diff--;
        }
    };

    void resize(size_type count){
        if (list_size > count) {
            auto diff = list_size - count;
            while (diff) {
                pop_back();
                diff--;
            }
            return;
        }
        else{
            auto diff = count - list_size;
            while (diff){
                push_back(0);
                diff--;
            }
        }
    };

    void swap(LinkedList& other) noexcept {
        std::swap(*this, other);
    };

private:

    size_type list_size{};
    Node *head;
    Node *tail;

    void create(){
        list_size = 0;
        head = new Node;
        tail = new Node;
        tail->early = head;
        head->next = tail;
    }

    void clear() noexcept {
        while (!empty()) pop_front();
    }
};


#endif //LAB3_LINKEDLIST_H
