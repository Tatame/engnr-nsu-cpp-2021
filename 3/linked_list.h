#pragma once

#include <set>
#include <algorithm>
#include <iostream>
#include <exception>
#include <vector>

template<class T>
class LinkedList {

public:

    using value_type = T;

    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    using reference = T &;
    using const_reference = const reference;

    using pointer = T *;
    using const_pointer = const pointer;

public:

    struct Node {
        T data;
        Node *prev;
        Node *next;

        Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
                : data{d}, prev{p}, next{n} {}

        Node(T &&d, Node *p = nullptr, Node *n = nullptr)
                : data{std::move(d)}, prev{p}, next{n} {}
    };

public:

    class const_iterator {
    public:

        using difference_type = ptrdiff_t;

        const_iterator() : current{nullptr} {}

        const T &operator*() const {
            return retrieve();
        }

        const_iterator &operator++() {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator old = *this;

            ++(*this);

            return old;
        }

        const_iterator &operator--() {
            current = current->prev;

            return *this;
        }

        const_iterator operator--(int) {
            const_iterator old = *this;

            --(*this);

            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node *current;

        T &retrieve() const {
            return current->data;
        }

        const_iterator(Node *p) : current{p} {}

        friend class LinkedList<T>;
    };

    class iterator : public const_iterator {

    public:

        iterator() {}

        T &operator*() {
            return const_iterator::retrieve();
        }

        const T &operator*() const {
            return const_iterator::operator*();
        }

        iterator &operator++() {
            this->current = this->current->next;

            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;

            ++(*this);

            return old;
        }

        iterator &operator--() {
            this->current = this->current->prev;

            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;

            --(*this);

            return old;
        }

    protected:

        iterator(Node *p) : const_iterator{p} {}

        friend class LinkedList<T>;
    };

    class const_reverse_iterator {
    public:

        const_reverse_iterator() : current{nullptr} {}

        const T &operator*() const {
            return retrieve();
        }

        const_reverse_iterator &operator++() {
            current = current->prev;

            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator old = *this;

            ++(*this);

            return old;
        }

        const_reverse_iterator &operator--() {
            current = current->next;

            return *this;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator old = *this;

            --(*this);

            return old;
        }

        bool operator==(const const_reverse_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_reverse_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node *current;

        T &retrieve() const { return current->data; }

        const_reverse_iterator(Node *p) : current{p} {}

        friend class LinkedList<T>;
    };

    class reverse_iterator : public const_reverse_iterator {
    public:

        reverse_iterator() {}

        T &operator*() {
            return const_reverse_iterator::retrieve();
        }

        const T &operator*() const {
            return const_reverse_iterator::operator*();
        }

        reverse_iterator &operator++() {
            this->current = this->current->prev;

            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator old = *this;

            ++(*this);

            return old;
        }

        reverse_iterator &operator--() {
            this->current = this->current->next;

            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator old = *this;

            --(*this);

            return old;
        }

    protected:

        reverse_iterator(Node *p) : const_reverse_iterator{p} {}

        friend class LinkedList<T>;
    };

public:
    LinkedList() {
        init();
        //work
    }

    LinkedList(const LinkedList &other) {
        init();

        for (auto &x: other)
            push_back(x);
    }

    LinkedList(LinkedList &&other) : _size{other._size}, head{other.head}, tail{other.tail} {
        other._size = 0;

        other.head = nullptr;
        other.tail = nullptr;
    }

    LinkedList(size_type count, const T &value) {
        init();

        _size = count;

        while (count--) {
            push_back(value);
        }
    }

    explicit LinkedList(size_type count) {
        init();

        Node *h = head;
        Node *t = tail;

        while (count--) {
            Node *temp = tail;
            tail->next = new Node;
            tail = tail->next;
            temp->prev->next = tail;
            tail->prev = temp;
            tail->next = nullptr;
        }

        head = h;
        tail = t;
    }

    template<typename InputIt>
    LinkedList(InputIt first, InputIt last) {
        init();

        for (auto it = first; it != last; it++) {
            push_back(*it);
        }
    }

    LinkedList(std::initializer_list<T> init_) {
        init();

        for (const auto &value: init_) {
            push_back(value);
        }
    }

    ~LinkedList() {
        clear();

        delete head;
        delete tail;
    }

public:

    LinkedList &operator=(const LinkedList &other) {
        LinkedList copy = other;

        std::swap(*this, copy);

        return *this;
    }

    LinkedList &operator=(LinkedList &&other) {
        std::swap(_size, other._size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);

        return *this;
    }

    LinkedList &operator=(std::initializer_list<T> ilist) {
        clear();
        init();

        for (const auto &value: ilist) {
            push_back(value);
        }

        return *this;
    }

    void assign(size_type count, const T &value) {
        clear();
        init();

        while (count--) {
            push_back(value);
        }
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last) {
        clear();
        init();

        for (auto it = first; it != last; it++) {
            push_back(*it);
        }
    }

    void assign(std::initializer_list<T> ilist) {
        clear();
        init();

        for (const auto &value: ilist) {
            push_back(value);
        }
    }

public:

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        return *--end();
    }

    const_reference back() const {
        return *--end();
    }

public:

    iterator begin() noexcept {
        return iterator(head->next);
    }

    const_iterator begin() const noexcept {
        return const_iterator(head->next);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(head->next);
    }

    iterator end() noexcept {
        return iterator(tail);
    }

    const_iterator end() const noexcept {
        return const_iterator(tail);
    }

    const_iterator cend() const noexcept {
        return const_iterator(tail);
    }

public:

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(tail->prev);
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(tail->prev);
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(tail->prev);
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(head);
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(head);
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(head);
    }

public:

    [[nodiscard]] size_type size() const noexcept {
        return _size;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }

public:

    iterator insert(const_iterator pos, const T &value) {
        Node *p = pos.current;

        ++_size;

        return iterator(p->prev = p->prev->next = new Node{value, p->prev, p});
    }

    iterator insert(const_iterator pos, T &&value) {
        Node *p = pos.current;

        ++_size;

        return iterator(p->prev = p->prev->next = new Node{std::move(value), p->prev, p});
    }

    iterator insert(const_iterator pos, size_type count, const T &value) {
        if (pos == cend())
            throw std::runtime_error("No iterator");

        while (count--) {
            pos = insert(pos, value);
        }

        return iterator(pos.current);
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        last++;

        for (auto it = first; it != last; it++) {
            pos = insert(pos, *it);
            pos++;
        }

        return iterator(pos.current);
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        for (const auto &value: ilist) {
            pos = insert(pos, value);
            pos++;
        }

        return iterator(pos.current);
    }

    void push_front(const T &value) {
        insert(begin(), value);
    }

    void push_front(T &&value) {
        insert(begin(), std::move(value));
    }

    void push_back(const T &value) {
        insert(end(), value);
    }

    void push_back(T &&value) {
        insert(end(), std::move(value));
    }

public:

    iterator erase(const_iterator pos) {
        Node *p = pos.current;
        iterator retVal(p->next);

        p->prev->next = p->next;
        p->next->prev = p->prev;

        delete p;
        --_size;

        return retVal;
    }

    iterator erase(const_iterator first, const_iterator last) {
        auto itr = first;

        for (; itr != last;) {
            itr = erase(itr);
        }

        return iterator(itr.current);
    }

    void pop_back() {
        erase(--end());
    }

    void pop_front() {
        erase(begin());
    }

public:

    void sort() {
        sort(std::less_equal<T>());
    }

    template<typename Compare>
    void sort(Compare comp) {
        merge_sort(begin(), end(), comp);
    }

    size_type distance(iterator beg, iterator end) {
        size_type size = 0;
        for (auto it = beg; it != end; it++, size++);
        return size;
    }

    iterator next(iterator beg, size_type size) {
        auto it = beg;
        while (size--)
            it++;
        return it;
    }

    template<typename Compare>
    void merge_sort(iterator beg, iterator end, Compare comp) {
        size_type size = distance(beg, end);
        if (size <= 1)
            return;

        auto mid = next(beg, size / 2);
        merge_sort(beg, mid, comp);
        merge_sort(mid, end, comp);
        merge(beg, mid, end, comp);
    }

    void _insert(std::vector<value_type> &temp, iterator beg, iterator end) {
        for (auto it = beg; it != end; it++)
            temp.push_back(*it);
    }

    template<typename Compare>
    void merge(iterator beg, iterator mid, iterator end, Compare comp) {
        std::vector<value_type> temp;

        temp.reserve(distance(beg, end));

        iterator left = beg;
        iterator right = mid;

        while (left != mid && right != end) {
            if (comp(*right, *left))
                temp.emplace_back(*right++);
            else
                temp.emplace_back(*left++);
        }

        _insert(temp, left, mid);
        _insert(temp, right, end);

        for (const auto &value: temp) {
            *beg = std::move(value);
            beg++;
        }
    }

    size_type unique() {
        Node *p = head->next;
        std::set<T> unique_values;

        while (p != tail) {
            if (unique_values.find(p->data) == unique_values.end()) {
                unique_values.insert(p->data);
            } else {
                erase(iterator(p));
            }
            p = p->next;
        }

        _size == unique_values.size();
        return unique_values.size();
    }

    template<typename BinaryPredicate>
    size_type unique(BinaryPredicate p) {
        auto first = begin();
        auto last = end();

        if (first == last)
            return last;

        size_t count = 0;
        auto result = first;

        while (++first != last) {
            if (!p(*result, *first) && ++result != first) {
                *result = std::move(*first);
                count++;
            }
        }

        return count;
    }

    void reverse() noexcept {
        Node *p = head->next;
        Node *h = head;

        head = tail;

        while (p != nullptr) {
            Node *d = p->prev;
            p->prev = p->next;
            p->next = d;

            p = p->prev;
        }

        tail = h;
    }

    size_type remove(const T &value) {
        Node *p = head->next;

        while (p != tail) {
            if (p->data == value) {
                erase(iterator(p));
            }
            p = p->next;
        }

        return size();
    }

    bool operator==(const LinkedList<T> &rhs) {
        if (rhs.size() != (*this).size())
            return false;

        auto this_ll = this->begin();
        auto another = rhs.begin();

        for (; this_ll != this->end(); this_ll++, another++)
            if (*this_ll != *another)
                return false;

        return true;
    }

    bool operator!=(const LinkedList<T> &rhs) {
        return !(*this == rhs);
    }

    template<typename UnaryPredicate>
    size_type remove_if(UnaryPredicate predicate) {
        auto it = begin();
        size_t cnt = 0;
        for (; it != end();) {
            if (predicate(*it)) {
                it = erase(it);
                cnt++;
            } else
                it++;
        }
        return cnt;
    }

public:

    void clear() noexcept {
        while (!empty())
            pop_front();
    }

    void resize(size_type count, const value_type &value) {
        if (size() >= count)
            return;
        auto diff = count - size();
        while (diff--) {
            push_back(value);
        }
        _size = count;
    }

    void resize(size_type count) {
        if (size() >= count)
            return;
        auto diff = count - size();
        Node *t = tail;
        while (diff--) {
            tail = new Node;
            Node *t = tail;
            tail->next = new Node;
            tail = tail->next;
            tail->prev = t;
            tail->prev->next = tail;
            tail->next = nullptr;
        }
        _size += count;
    }

    void swap(LinkedList &other) noexcept {
        std::swap(*this, other);
    }

    template<typename Iterator>
    void swap(Iterator first, Iterator second) {
        insert(first, *second);
        insert(second, *first);
        erase(first);
        erase(second);
    }

private:

    size_type _size{};
    Node *head;
    Node *tail;

    void init() {
        _size = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};
