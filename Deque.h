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

    public:
        // -----------
        // operator ==
        // -----------

        /**
* <your documentation>
*/
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::equal()
            return true;}

        // ----------
        // operator <
        // ----------

        /**
* <your documentation>
*/
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return true;}

    private:
        // ----
        // data
        // ----

        allocator_type _a;

        // <your data>
	pointer _f;
	pointer _b;
	pointer _e;
	pointer _l;

        size_type _size;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return (!_f && !_b && !_e && !_l) || ((_f <= _b) && (_b <= _e) && (_e <= _l));}

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
* <your documentation>
*/
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return (lhs._p == rhs._p);}

                /**
* <your documentation>
*/
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
		pointer _p;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return (_p);}

            public:
                // -----------
                // constructor
                // -----------

                /**
* <your documentation>
*/
                iterator (pointer p) : _p(p) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
* <your documentation>
*/
                reference operator * () const {
                    // <your code>
                    return *_p;}

                // -----------
                // operator ->
                // -----------

                /**
* <your documentation>
*/
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
* <your documentation>
*/
                iterator& operator ++ () {
                    // <your code>
			++_p;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
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
* <your documentation>
*/
                iterator& operator -- () {
                    // <your code>
			--_p;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
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
* <your documentation>
*/
                iterator& operator += (difference_type d) {
                    _p += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
* <your documentation>
*/
                iterator& operator -= (difference_type d) {
                    _p -= d;
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
* <your documentation>
*/
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return (lhs._p == rhs._p);}

                /**
* <your documentation>
*/
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
* <your documentation>
*/
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
* <your documentation>
*/
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
		pointer _p; 

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return (_p);}

            public:
                // -----------
                // constructor
                // -----------

                /**
* <your documentation>
*/
                const_iterator (pointer p) : _p(p) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
* <your documentation>
*/
                reference operator * () const {
                    return *_p;}

                // -----------
                // operator ->
                // -----------

                /**
* <your documentation>
*/
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator ++ () {
                    ++_p;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
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
* <your documentation>
*/
                const_iterator& operator -- () {
                    --_p;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
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
* <your documentation>
*/
                const_iterator& operator += (difference_type d) {
                    _p += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator -= (difference_type d) {
                    _p -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
* <your documentation>
*/
        explicit MyDeque (const allocator_type& a = allocator_type()) : _a(a), _f(0), _b(0), _e(0), _l(0), _size(0) {
            assert(valid());}

        /**
* <your documentation>
*/
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : _a(a), _size(s) {
            _f = _a.allocate(3 * s);
            _b = _f + s;
            _e = _f + 2*s;
            _l = _f + 3*s;
            uninitialized_fill(_a, begin(), end(), v);
            assert(valid());}

        /**
	* <your documentation>
	*/
        MyDeque (const MyDeque& that) : _a(that._a), _size(that._size) {
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
                iterator eIter(_e);
                clear();
                eIter = uninitialized_copy(_a, that.begin(), that.end(), begin());
		_size = that.size();
		_e = &*eIter;
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
		
            return *(_b + index);
	}

        /**
	* <your documentation>
	*/
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
	* <your documentation>
	*/
        reference at (size_type index) {
	    if ( index >= _size ) {
                throw std::out_of_range("MyDeque::at(index)");
            }
            return (this)->operator[](index);}

        /**
* <your documentation>
*/
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
* <your documentation>
*/
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
* <your documentation>
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
            return iterator(_b);}

        /**
         * @return A const iterator formed by a pointer to _b
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(_b);}

        // -----
        // clear
        // -----

        /**
	* Removes all elements by resizing the deque to 0. s
	*/
        void clear () {
            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
	* @return True if there are no elements in the deque. 
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
            return iterator(_e);}

        /**
         * @return An iterator formed by a const pointer to _e
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(_e);}

        // -----
        // erase
        // -----

        /**
	* <your documentation>
	*/
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
	* <your documentation>
	*/
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
	* <your documentation>
	*/
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
* <your documentation>
*/
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
* <your documentation>
*/
        void pop_back () {
            // <your code>
            assert(valid());}

        /**
* <your documentation>
*/
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
* <your documentation>
*/
        void push_back (const_reference) {
            // <your code>
            assert(valid());}

        /**
* <your documentation>
*/
        void push_front (const_reference) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

        /**
	* @param size_type s To resize to
        * @param const_reference v Value to fill new positions with if size is greater than current size
	*/
        void resize (size_type s, const_reference v = value_type()) {
            iterator eIter(_e);
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
	* <your documentation>
	*/
        void swap (MyDeque&) {
            // <your code>
            assert(valid());}};

#endif // Deque_h
