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
            return (lhs.size() == 0 && rhs.size() == 0) || ((lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin()));}

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

	pointer _b;
	pointer _e;

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


        MyDeque (const MyDeque& that, int rows) : _a(that._a), _size(that._size), _oa(that._oa), _arraySize(that._arraySize) {
            _of = _oa.allocate(rows);
            _ob = _of + (that._ob - that._of);
            _oe = _of + (that._oe - that._of);
            _ol = _of + rows;
/*
            uninitialized_copy(_oa, that._ob, (that._oe) + 1, _ob);
	    _b = that._b;
            _e = that._e;
	    //_b = *_ob + (that._b - *(that._ob));
       	    //_e = *_oe + (that._e - *(that._oe));
            assert(valid());}*/


	    for(int i = 0; i <= (_oe - _ob); ++i) {
	            *(_ob+i) = _a.allocate(_arraySize);	
	    }
	    _b = *_ob + (that._b - *(that._ob));
       	    _e = *_oe + (that._e - *(that._oe));

            uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

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
	 * @param allocator_type a The allocator to use
         * Default constructor
	 */
        explicit MyDeque (const allocator_type& a = allocator_type()) : _a(a),  _b(0), _e(0),  _size(0), _oa(a), _of(0), _ob(0), _oe(0), _ol(0), _arraySize(0) {
            assert(valid());}

        /**
	 * @param size_type s size of Deque
         * @param const_reference v a value to fill the deque with
         * @param allocator_type a The allocator to use
	 */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : _a(a), _size(s), _oa(a) {
            _of = _oa.allocate(3);
	    _ob = _of + 1;
	    _oe = _ob;
	    _ol = _of + 3;

	    *_ob = _a.allocate(3 * s);
            _b = *_ob + s;
            _e = *_ob + 2*s;
	   
            _arraySize = 3*s;
            
	    uninitialized_fill(_a, begin(), end(), v);

	    
            assert(valid());}

        /**
	* @param MyDeque that
        * Copy constructor - copy all data from that into a new MyDeque
	*/
        MyDeque (const MyDeque& that) : _a(that._a), _size(that._size), _oa(that._oa), _arraySize(that._arraySize) {
            _of = _oa.allocate(that._ol - that._of);
            _ob = _of + (that._ob - that._of);
            _oe = _of + (that._oe - that._of);
            _ol = _of + (that._ol - that._of);

	    for(int i = 0; i <= (_oe - _ob); ++i) {
	            *(_ob+i) = _a.allocate(_arraySize);	
	    }
	    _b = *_ob + (that._b - *(that._ob));
       	    _e = *_oe + (that._e - *(that._oe));


            uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
	* Resizes the array to zero, destroying all elements, then deallocates all memory assigned. 
	*/
        ~MyDeque () {
		if (_b) {
			clear();
			int rowsDeall = _ob - _oe + 1;
                        for (int i = 0; i < rowsDeall; ++i) {
				_a.deallocate(*_ob, _arraySize);
				++_ob;
			}
			_oa.deallocate(_of, _ol - _of);
		}			
	           //insert(valid());
	}

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
		resize(that.size());
                iterator eIter = std::copy(that.begin(), that.end(), begin());
		_e = &(*eIter);
	    }
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
	* @param size_type index The index in the deque to retrieve
        * @return value_type The ith value in the deque
	*/
        reference operator [] (size_type index) {
	    int row = (index + (_b - *_ob)) / _arraySize;
	    int col = (index + (_b - *_ob)) % _arraySize;
	    return *(*(_ob+row)+col);

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
	    assert(_b == _e); 
	    assert(_ob == _oe);
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
		std::copy_backward(i, end() -1, end());
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
	    --_size;
            assert(valid());}

        // ----
        // push
        // ----

        /**
	 * adds a new element to the back of the MyDeque
	 * @param v const_reference of the value to be added
	 */
        void push_back (const_reference v) {
            //resize(_size + 1, v);
		resize(_size + 1);
		*(end() - 1) = v;
            assert(valid());}

        /**
	 * @param const_reference value to push front
         * Push to front of deque
	 */
        void push_front (const_reference v) {
		using namespace std;
	    if (*_ob != _b) {
		//space available on this row
		--_b;
		*begin() = v;
		++_size;
	    }
	    else if (_ob != _of) {
		//space available for a new row
		--_ob;
		*_ob = _a.allocate(_arraySize);
		_b = *_ob + _arraySize - 1;
		*begin() = v;
		++_size;
	    }
	    else {
		//need to resize outer array
		MyDeque x(*this, _ol - _of + 2);
		swap(x);
		std::copy_backward(_ob, _ol - 2, _ol);
		_oe += 2;
		++_ob;
		*_ob = _a.allocate(_arraySize);
		_b = *_ob + _arraySize - 1;
		*begin() = v;
		++_size;
	    }
            assert(valid());}

        // ------
        // resize
        // ------

        /**
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
		_oe = _ob + ((s + (_b - *_ob)) / _arraySize);
	    } else {

                // get hypothetical row number of bigger size's back element
                int endRowNum = (s + (_b - *_ob)) / _arraySize;

                if(endRowNum == (_oe - _ob)) {
			_size = s;
			eIter = uninitialized_fill(_a, end(), begin() + difference_type(s), v);
			_e = &*eIter;
                        // _oe stays the same
		} else if (endRowNum < (_ol - _ob)) {
			_size = s;			
			int moreRows = endRowNum - (_oe - _ob);
			for (int i = 0; i < moreRows; ++i) {
				++_oe;
				*_oe = _a.allocate(_arraySize);
				
			}
			eIter = uninitialized_fill(_a, end(), begin() + difference_type(s), v);
			_e = &*eIter;
		} else {
			int moreRows = endRowNum - (_ol - _ob) + 1;
			int totalRows = _ol-_of + moreRows;
			MyDeque x(*this, totalRows);
			swap(x);
			resize(s, v);
		}
            }
	    
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

                std::swap(_b, that._b);
                std::swap(_e, that._e);
                std::swap(_of, that._of);
                std::swap(_ob, that._ob);
                std::swap(_oe, that._oe);
                std::swap(_ol, that._ol);
		std::swap(_arraySize, that._arraySize);
                std::swap(_size, that._size);
	    } else {
                MyDeque x(*this);
                *this = that;
                that = x;}
            assert(valid());}};

#endif // Deque_h
