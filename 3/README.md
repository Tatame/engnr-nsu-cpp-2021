# Doubly linked list

## Api:
template <class T>
class LinkedList {
public: 
   using value_type = T;
 
   using size_type = size_t;
   using difference_type = std::ptrdiff_t;
 
   using reference = T&;
   using const_reference = const reference;
 
   using pointer = T*;
   using const_pointer = const pointer;
 
public: 
   class iterator;
   class const_iterator;
   class reverse_iterator;     
   class const_reverse_iterator;
 
public:
   LinkedList();

   LinkedList(const LinkedList& other);

   LinkedList(LinkedList&& other);
 
   LinkedList(size_type count, const T& value);

   explicit LinkedList(size_type count);
 
   template<typename InputIt>
   LinkedList(InputIt first, InputIt last);
 
   LinkedList(std::initializer_list<T> init);
 
   ~LinkedList();
 
public:

   LinkedList& operator=(const LinkedList& other);

   LinkedList& operator=(LinkedList&& other);
 
   LinkedList& operator=(std::initializer_list<T> ilist);
 
   void assign(size_type count, const T& value);

   template<typename InputIt>
   void assign(InputIt first, InputIt last);

   void assign(std::initializer_list<T> ilist);
 
public: // доступ к элементам контейнера
   reference front();

   const_reference front() const;

   reference back();

   const_reference back() const;
 
public:
   iterator begin() noexcept;
 
   const_iterator begin() const noexcept;

   const_iterator cbegin() const noexcept;
 
   iterator end() noexcept;
 
   const_iterator end() const noexcept;

   const_iterator cend() const noexcept;
 
public:
   reverse_iterator rbegin() noexcept;
 
   const_reverse_iterator rbegin() const noexcept;
   const_reverse_iterator crbegin() const noexcept;
 
   reverse_iterator rend() noexcept;
 
   const_reverse_iterator rend() const noexcept;
   const_reverse_iterator crend() const noexcept;
 
public:
   size_type size() const noexcept;

   [[nodiscard]] bool empty() const noexcept;
 
public:
   iterator insert(const_iterator pos, const T& value);

   iterator insert(const_iterator pos, T&& value);

   iterator insert(const_iterator pos, size_type count, const T& value);

   template<typename InputIt>
   iterator insert(const_iterator pos, InputIt first, InputIt last);

   iterator insert(const_iterator pos, std::initializer_list<T> ilist);
 
   void push_front(const T& value);

   void push_front(T&& value);
 
   void push_back(const T& value);

   void push_back(T&& value);
 
public:
   iterator erase(const_iterator pos);

   iterator erase(const_iterator first, const_iterator last);
 
   void pop_back();

   void pop_front();
 
public:
   void sort();

   template<typename Compare>
   void sort(Compare comp);
 
   size_type unique();

   template<typename BinaryPredicate>
   size_type unique(BinaryPredicate p);
 
   void reverse() noexcept;
 
   size_type remove(const T& value);

   template<typename UnaryPredicate>
   size_type remove_if(UnaryPredicate p);
 
public:
   void clear() noexcept;
 
   void resize(size_type count, const value_type& value);
   void resize(size_type count);
 
   void swap(LinkedList& other) noexcept;
};
