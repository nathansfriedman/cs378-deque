// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert> // assert
#include <iterator> // iterator, bidirectional_iterator_tag
#include <memory> // allocator
#include <stdexcept> // out_of_range
#include <utility> // !=, <=, >, >=
#include <iostream>
// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        std::cout << "UNINITIALIZED COOPY ERROR" << std::endl;
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -----
// MyDeque
// -----

template < typename T, typename A = std::allocator<T> >
class MyDeque {
    public:
        // --------
        // typedefs
        // --------

        typedef A allocator_type;
        typedef typename allocator_type::value_type value_type;

        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;

	typedef typename allocator_type::template rebind<T*>::other outer_allocator;
	typedef typename allocator_type::template rebind<T*>::other::pointer outer_pointer;

    public:
        // -----------
        // operator ==
        // -----------

        /**
	 * @param lhs MyDeque to compare to rhs
         * @param rhs MyDeque to test equality with lhs
         * @return True if MyDeques are the same size and have the same contents
	 */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
	 * @param lhs MyDeque to compare to rhs
         * @param rhs MyDeque to test order with lhs
         * @return True if lhs comes before rhs in the lexicographical compare
	 */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;

	pointer _f;
	pointer _b;
	pointer _e;
	pointer _l;

        size_type _size;

	outer_allocator _oa;
	outer_pointer _of;
	outer_pointer _ob;
	outer_pointer _oe;
	outer_pointer _ol;

	size_type _arraySize;
	

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return (!_b && !_e && !_of && !_ob && !_oe && !_ol) || (((_of <= _ob) && (_ob <= _oe) && (_oe <= _ol)) && ((*_ob <= _b) && (*_oe <= _e)));}

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename MyDeque::value_type value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::pointer pointer;
                typedef typename MyDeque::reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
	 	 * @return true if both iterators are indexing the same MyDeque and pointing to the same element
	 	 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return ((lhs.x == rhs.x) && (lhs.index == rhs.index));}

                /**
		 * @return true if operator == returns false
		 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
	 	 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
		 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
	 	 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	   	 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
		unsigned int index;
		MyDeque* x;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return true;}
                    //return (!x || index <= x->size());}

            public:
                // -----------
                // constructor
                // -----------

                /**
		 * Two-arg constructor for the read/write iterator
		 * @param p a pointer to the MyDeque this iterator is associated with
		 * @param i an int value which represents the zero-based index this iterator should point at in the MyDeque
		 */
                iterator (MyDeque* p, int i) : index(i), x(p) {
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
		 * @return a reference to the element this iterator is pointing at
		 */
                reference operator * () const {
                    return x->at(index);}

                // -----------
                // operator ->
                // -----------

                /**
		 * @return the address of the element this iterator is pointing at
 		 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
		 * @return the reference to this iterator after its index has been incremented
		 */
                iterator& operator ++ () {
			++index;
                    assert(valid());
                    return *this;}

                /**
		 * @return a copy of this iterator, the original having had its index incremented
		 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
		 * @return the reference to this iterator after its index has been decremented
		 */
                iterator& operator -- () {
			--index;
                    assert(valid());
                    return *this;}

                /**
		 * @return a copy of this iterator, the original having had its index decremented
		 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
		 * @param d a difference_type value which represents the change in the index of the iterator
		 * @return a reference to this iterator after it has had its index updated
		 */
                iterator& operator += (difference_type d) {
                    index += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
		 * @param d a difference_type value which represents the change in the index of the iterator
		 * @return a reference to this iterator after it has had its index updated
		 */
                iterator& operator -= (difference_type d) {
                    index -= d;
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename MyDeque::value_type value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::const_pointer pointer;
                typedef typename MyDeque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
		 * @return true if both const_iterators are associated with the same MyDeque and are both pointing to the same element
		 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return ((lhs.x == rhs.x) && (lhs.index == rhs.index));}

                /**
		 * @return true if the operator == returns false
		 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
		 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
		 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
		 * <NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
		 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
		const MyDeque* x;
		unsigned int index; 

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return true;}
                    //return (!x || index <= x->size());}

            public:
                // -----------
                // constructor
                // -----------

                /**
		 * Two-arg constructor for the const_iterator
		 * @param p read-only pointer to the MyDeque this iterator is associated
		 * @param i int value which represents the index of the element this iterator will point to initially
		 */
                const_iterator (const MyDeque* p, int i) : x(p), index(i) {
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
		 * @return a read-only reference to the element this iterator is pointing at
		 */
                reference operator * () const {
                    return x->at(index);}
		
                // -----------
                // operator ->
                // -----------

                /**
 		 * @return a read-only pointer to the element this iterator is pointing to
		 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
		 * @return the reference to this iterator after its index has been incremented
		 */
                const_iterator& operator ++ () {
                    ++index;
                    assert(valid());
                    return *this;}

                /**
		 * @return a copy of this iterator, the original having had its index incremented
		 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
		 * @return the reference to this iterator after its index has been decremented
		 */
                const_iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;}

                /**
		 * @return a copy of this iterator, the original having had its index decremented
		 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
		 * @param d a difference_type value which represents the change in the index of the iterator
		 * @return a reference to this iterator after it has had its index updated
		 */
                const_iterator& operator += (difference_type d) {
                    index += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
		 * @param d a difference_type value which represents the change in the index of the iterator
		 * @return a reference to this iterator after it has had its index updated
		 */
                const_iterator& operator -= (difference_type d) {
                    index -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
	 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	 */
        explicit MyDeque (const allocator_type& a = allocator_type()) : _a(a), _f(0), _b(0), _e(0), _l(0), _size(0), _oa(a), _of(0), _ob(0), _oe(0), _ol(0), _arraySize(0) {
            assert(valid());}

        /**
	 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	 */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : _a(a), _size(s), _oa(a) {
            _of = _oa.allocate(3);
	    _ob = _of + 1;
	    _oe = _of + 2;
	    _ol = _of + 3;

	    *_ob = _a.allocate(3 * s);
            _b = *_ob + s;
            _e = *_ob + 2*s;
            uninitialized_fill(_a, begin(), end(), v);

	    _arraySize = 3*s;
            assert(valid());}

        /**
	* NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	*/
        MyDeque (const MyDeque& that) : _a(that._a), _size(that._size), _oa(that._oa) {
            _f = _a.allocate(3 * _size);
            _b = _f + _size;
            _e = _f + 2*_size;
            _l = _f + 3*_size;
            uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
	* NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	* Resizes the array to zero, destroying all elements, then deallocates all memory assigned. 
	*/
        ~MyDeque () {
		if (_b) {
			clear();
			_a.deallocate(_f, _l - _f);
		}			
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
	* @return A reference to MyDeque for assignment
	* @param that a MyDeque to be assigned
	*/
        MyDeque& operator = (const MyDeque& that) {
	    if (this == &that)
                return *this;
            if (that.size() == size())
                std::copy(that.begin(), that.end(), begin());
            else if (that.size() < size()) {
                std::copy(that.begin(), that.end(), begin());
                resize(that.size());}
            else {
                clear();
		_size = that.size();
                iterator eIter = uninitialized_copy(_a, that.begin(), that.end(), begin());
		_e = &(*eIter);
	    }
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
	* NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	* @param size_type index The index in the deque to retrieve
        * @return value_type The ith value in the deque
	*/
        reference operator [] (size_type index) {
	    int row = (index + (_b - *_ob)) / _arraySize;
	    int col = (index + (_b - *_ob)) % _arraySize;
	
	    return *(_b + index);
	}

        /**
	* @param size_type index The index in the deque to retrieve
        * @return read-only reference to value_type The ith value in the deque
	*/
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
	* @param size_type index The index in the deque to retrieve
        * @return value_type The ith value in the deque
	* @throw out_of_range exception if the requested index does not exist
	*/
        reference at (size_type index) {
	    if ( index > _size || index < 0 ) {
                throw std::out_of_range("MyDeque::at(index)");
            }
            return (this)->operator[](index);}

        /**
	 * @param size_type index The index in the deque to retrieve
         * @return read-only reference to value_type The ith value in the deque
	 * @throw out_of_range exception if the requested index does not exist
	 */
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
	 * @return Reference to the last value in the MyDeque
	 */
        reference back () {
	    return at(_size-1);
        }

        /**
	 * @return read-only reference to the last value in the MyDeque
	 */
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * @return An iterator formed by a pointer to _b
         */
        iterator begin () {
            return iterator(this, 0);}

        /**
         * @return A const iterator formed by a pointer to _b
         */
        const_iterator begin () const {
            return const_iterator(this, 0);}

        // -----
        // clear
        // -----

        /**
	* Removes all elements by resizing the deque to 0
	*/
        void clear () {
            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
	* @return True if there are no elements in the deque
	*/
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * @return An iterator formed by a pointer to _e
         */
        iterator end () {
            return iterator(this, _size);}

        /**
         * @return An iterator formed by a const pointer to _e
         */
        const_iterator end () const {
            return const_iterator(this, _size);}

        // -----
        // erase
        // -----

        /**
	* removes one element from the MyDeque
	* @param i iterator pointing to the element to be removed
	* @return an iterator pointing to the space previously occupied by the removed element
	*/
        iterator erase (iterator i) {
            iterator i_copy(i);
	    std::copy(i +1, end(), i);
	    resize(_size - 1);
            assert(valid());
            return i_copy;}

        // -----
        // front
        // -----

        /**
	* @return reference to the first element in the MyDeque
	*/
        reference front () {
            return at(0);
        }

        /**
	* @return const_reference to the first element in the MyDeque
	*/
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
	 * insert one element into the MyDeque
	 * @param i iterator pointing to the space the inserted element will occupy
	 * @param v const_reference of the value to be inserted
	 * @return an iterator pointing to the inserted element
	 */
        iterator insert (iterator i, const_reference v) {
            if (i == begin()) {
		push_front(v);
		return begin();
	    }
	    else if (i == end()) {
		push_back(v);
		return --(end());
	    }
	    else {
		iterator i_copy(i);
		resize(_size + 1);
		std::copy(i, end(), i + 1);
		*i_copy = v;
		assert(valid());
		return i_copy;
	    }
	}

        // ---
        // pop
        // ---

        /**
	 * removes the last element in the MyDeque and destroys it
	 */
        void pop_back () {
            assert(!empty());
            resize(_size - 1);
            assert(valid());}

        /**
 	 * removes the first element in the MyDeque and destroys it
	 */
        void pop_front () {
            assert(!empty());
            _a.destroy(_b);
	    _b = &at(1);
            assert(valid());}

        // ----
        // push
        // ----

        /**
	 * adds a new element to the back of the MyDeque
	 * @param v const_reference of the value to be added
	 */
        void push_back (const_reference v) {
            resize(_size + 1, v);
            assert(valid());}

        /**
	 * NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	 */
        void push_front (const_reference) {
            //TODO write for multi-array
            assert(valid());}

        // ------
        // resize
        // ------

        /**
	* NEEDS UPDATING WITH ARRAY OF ARRAYS IMPLEMENTATION
	* @param size_type s To resize to
        * @param const_reference v Value to fill new positions with if size is greater than current size
	*/
        void resize (size_type s, const_reference v = value_type()) {
            iterator eIter(this, _size);
            if( s == size())
		return;
	    else if (s < size()) {
                eIter = destroy(_a, begin() + difference_type(s), end());
		_e = &*eIter;
	    } else 
		uninitialized_fill(_a, end(), begin() + difference_type(s), v);
            _size = s;
            assert(valid());}

        // ----
        // size
        // ----

        /**
	* @return size_type The current number of elements in the MyDeque
	*/
        size_type size () const {
            return _size;
	}

        // ----
        // swap
        // ----

        /**
	* swaps contents of two MyDeque containers
	*/
        void swap (MyDeque& that) {
            if (_a == that._a) {
                std::swap(_f, that._f);
                std::swap(_b, that._b);
                std::swap(_e, that._e);
                std::swap(_l, that._l);}
            else {
                MyDeque x(*this);
                *this = that;
                that = x;}
            assert(valid());}};

#endif // Deque_h
