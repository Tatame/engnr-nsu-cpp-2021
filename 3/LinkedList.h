#ifndef LAB3_LINKEDLISTS_H
#define LAB3_LINKEDLISTS_H

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
        T value;
        Node *early;
        Node *next;

        explicit Node(const T &val = T{}, Node *e = nullptr, Node *n = nullptr) {
            value = val;
            early = e;
            next = n;
        }

        explicit Node(T &val, Node *e = nullptr, Node *n = nullptr) {
            value = val;
            early = e;
            next = n;
        }
    };

public:

    class const_iterator {
    public:

        const_iterator() : current{nullptr} {}

        const T &operator*() const {
            return current->value;
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
            current = current->early;
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
        const_iterator(Node *p) : current{p} {}
        friend class LinkedList<T>;
    };

    class iterator : public const_iterator {

    public:

        iterator() = default;

        T &operator*() {
            return const_iterator::current->value;
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
            this->current = this->current->early;
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
            return current->value;
        }

        const_reverse_iterator &operator++() {
            current = current->early;
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
        const_reverse_iterator(Node *p) : current{p} {}
        friend class LinkedList<T>;
    };

    class reverse_iterator : public const_reverse_iterator {
    public:

        reverse_iterator() = default;

        T &operator*() {
            return const_reverse_iterator::current->value;
        }

        const T &operator*() const {
            return const_reverse_iterator::operator*();
        }

        reverse_iterator &operator++() {
            this->current = this->current->early;
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
        reverse_iterator(Node *p) : const_reverse_iterator{p} {};
        friend class LinkedList<T>;
    };

public: // конструкторы/деструкторы
    LinkedList() {
        create();
    }

    LinkedList(const LinkedList &other) {
        create();
        for (auto &x: other)
            push_back(x);
    }

    LinkedList(LinkedList&& other) noexcept {
        list_size = other.list_size;
        other.list_size = 0;
        head = other.head;
        other.head = nullptr;
        tail = other.tail;
        other.tail = nullptr;
    }

    LinkedList(size_type count, const T &value) {
        create();
        list_size = count;
        while (count) {
            push_back(value);
            --count;
        }
    }

    explicit LinkedList(size_type count) {
        create();
        while (count) {
            push_back(0);
            --count;
        }

    }

    template<typename InputIt>
    LinkedList(InputIt first, InputIt last) {
        create();
        for (auto i = first; i != last; i++) {
            push_back(*i);
        }
    }

    LinkedList(std::initializer_list<T> init) {
        create();
        for (const auto &value: init) {
            push_back(value);
        }
    }

    ~LinkedList() {
        clear();
        delete head;
        delete tail;
    }

public: // замена содержимого списка

    LinkedList &operator=(const LinkedList &other) {
        LinkedList copy = other;
        std::swap(*this, copy);
        return *this;
    }

    LinkedList &operator=(LinkedList &&other) {
        std::swap(list_size, other.list_size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        return *this;
    }

    LinkedList &operator=(std::initializer_list<T> ilist) {
        clear();
        create();
        for (const auto &value: ilist) {
            push_back(value);
        }
        return *this;
    }

    void assign(size_type count, const T &value) {
        clear();
        create();
        while (count) {
            push_back(value);
            --count;
        }
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last) {
        clear();
        create();
        for (auto i = first; i != last; i++) {
            push_back(*i);
        }
    }

    void assign(std::initializer_list<T> ilist) {
        clear();
        create();
        for (const auto &value: ilist) {
            push_back(value);
        }
    }

public: // доступ к элементам контейнера

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

public: // доступ к итераторам "натурального" порядка перебора элементов

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

public: // доступ к итераторам обратного порядка перебора элементов

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(tail->early);
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(tail->early);
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(tail->early);
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

public: // информация о количестве элементов в списке

    size_type size() const noexcept {
        return list_size;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }

public: // вставка элементов

    iterator insert(const_iterator pos, const T &value) {
        Node *p = pos.current;
        iterator itr = iterator(p->early = p->early->next = new Node{value, p->early, p});
        ++list_size;
        return itr;
    }

    iterator insert(const_iterator pos, T &&value) {
        Node *p = pos.current;
        iterator itr = iterator(p->early = p->early->next = new Node{std::move(value), p->early, p});
        ++list_size;
        return itr;
    }

    iterator insert(const_iterator pos, size_type count, const T &value) {
        if (pos == cend())
            throw std::runtime_error("No iterator");
        while (count) {
            pos = insert(pos, value);
            --count;
        }
        return iterator(pos.current);
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        last++;
        for (auto i = first; i != last; i++) {
            pos = insert(pos, *i);
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

public: // изъятие элементов

    iterator erase(const_iterator pos) {
        Node *p = pos.current;
        iterator retVal(p->next);
        p->early->next = p->next;
        p->next->early = p->early;
        delete p;
        --list_size;
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

public: // операции

    bool operator!=(const LinkedList<T> &rhs) const {
        return !(*this == rhs);
    }

    void sort() {
        sort(std::less_equal<T>());
    }

    template<typename Compare>
    void sort(Compare comp) {
        merge_sort(begin(), end(), comp);
    }

    size_type distance(iterator beg, iterator end) {
        size_type size = 0;
        for (auto i = beg; i != end; i++, size++);
        return size;
    }

    iterator next(iterator beg, size_type size) {
        auto i = beg;
        while (size--)
            i++;
        return i;
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
        for (auto i = beg; i != end; i++)
            temp.push_back(*i);
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
        return unique([](const auto &left, const auto &right) { return left == right; });
    }

    template<typename BinaryPredicate>
    size_type unique(BinaryPredicate p) {
        size_type init_cnt = size();
        auto first = cbegin();
        if (first == cend())
            return init_cnt;

        auto second = ++cbegin();
        for (; second != cend();) {
            if (p(*first, *second)) {
                erase(first);
                first = second;
                ++second;
            } else {
                ++first;
                ++second;
            }
        }
        return init_cnt - size();
    }

    void reverse() noexcept {
        auto it1 = begin();
        auto it2 = --end();
        while (it1 != it2) {
            swap(it1, it2);
            it1++;
            it2--;
        }
    }

    size_type remove(const T &value) {
        return remove_if([&value](auto &item) { return item == value; });
    }

    bool operator==(const LinkedList<T> &rhs) const {
        if (rhs.size() != size())
            return false;

        auto another = rhs.begin();

        for (auto i = begin(); i != end(); i++, another++)
            if (*i != *another)
                return false;

        return true;
    }

    template<typename UnaryPredicate>
    size_type remove_if(UnaryPredicate predicate) {
        auto i = begin();
        size_t cnt = 0;
        for (; i != end();) {
            if (predicate(*i)) {
                i = erase(i);
                cnt++;
            } else
                i++;
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
    }

    void resize(size_type count) {
        if (size() > count) {
            auto diff = size() - count;
            while (diff--) {
                pop_back();
            }
            return;
        }

        auto diff = count - size();
        while (diff--) {
            push_back(0);
        }
    }

    void swap(LinkedList &other) noexcept {
        std::swap(*this, other);
    }

    template<typename Iterator>
    void swap(Iterator first, Iterator second) {
        std::iter_swap(first, second);
    }

private:

    size_type list_size{};
    Node *head;
    Node *tail;

    void create() {
        list_size = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->early = head;
    }
};


#endif //LAB3_LINKEDLISTS_H
