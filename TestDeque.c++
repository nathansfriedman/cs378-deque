// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -ansi -pedantic -lcppunit -ldl -Wall TestDeque.c++ -o TestDeque.c++.app
% valgrind TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring> // strcmp
#include <deque> // deque
#include <sstream> // ostringstream
#include <stdexcept> // invalid_argument
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TestSuite.h" // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {
	// -----------
	// constructor
	// -----------

	void test_constructor_1() {
		C x;
		CPPUNIT_ASSERT(true);
	}

	void test_constructor_2() {
		C x(10);
		CPPUNIT_ASSERT(true);
	}

	void test_constructor_3() {
		C x(10, 5);
		CPPUNIT_ASSERT(true);
	}

	void test_constructor_4() {
		C x(10);
		C y(x);
		CPPUNIT_ASSERT(&x != &y);
	}


    // ------
    // index
    // ------
    void test_index_1() {
        const C x(5000, 1);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[4000] == 1);
    }
    
    // ---
    // at
    // ---
    
    void test_at_1() {
        try {
            C x(100, 100); 
            CPPUNIT_ASSERT(x.at(50) == 100);
        } catch (std::out_of_range& e) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_at_2() {
        try {
            C x(10, 2);
            int q = x.at(100);
            CPPUNIT_ASSERT(false);
        } catch (std::out_of_range& e) {
            CPPUNIT_ASSERT(true);
        }
    }

    void test_at_3() { 
        try {
	    const C x(10, 10);
	    CPPUNIT_ASSERT(x.at(5) == 10);
        } catch (std::out_of_range& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    // ----
    // size
    // ----

    void test_size_1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}
   
    void test_size_2 () {
        C x(10);
        x.resize(0);
	CPPUNIT_ASSERT(x.size() == 0); }
    
    void test_size_3 () {
        C x(12, 1);
        CPPUNIT_ASSERT(x.size() == 12); }
 
    void test_size_4 () {
        C x(6, 1);
        C y(5, 2);
        y = x;
        CPPUNIT_ASSERT(y[0] == 1);
	CPPUNIT_ASSERT(y.at(5) == 1);
	CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(y.size() == 6); 
    }

    void test_size_5 () {
        C x(10, 2);
        C y(5, 2);
        x = y;
        CPPUNIT_ASSERT(x.size() == 5);}

    // ----------
    // assignment
    // ----------
    void test_assignment_1() { 
	C a(10, 1);
	C b(10, 2);
	b = a;
	CPPUNIT_ASSERT(b[1] == 1);
        CPPUNIT_ASSERT(b == a);}

    void test_assignment_2() { 
	C a(1000, 1);
 	C b(5, 1);
	b = a;
	CPPUNIT_ASSERT(b[98] == 1);
	CPPUNIT_ASSERT(b.size() == 1000);}
	
    void test_assignment_3() { 
	C a(4, 1);
	C b(100, 3);
	b = a;
	CPPUNIT_ASSERT(b.at(1) == 1);
	CPPUNIT_ASSERT(b.size() == 4);}
    
    // --------
    // back
    // --------
 
    void test_back_1() { 
	C a(12, 1);
        CPPUNIT_ASSERT(a.back() == 1);}
    
    void test_back_2() { 
	C a(10, 2);
	C b(15, 5);
	a = b;
	CPPUNIT_ASSERT(a.back() == 5);}

    void test_back_3() { 
	C a(100, 100); 
	CPPUNIT_ASSERT(a.back() == a[99]);}

    // ----
    // begin
    // ----
    
    void test_begin_1() { 
        C a(100, 2);
        typename C::iterator iter = a.begin();
        CPPUNIT_ASSERT(*iter == 2);
	++iter;
	CPPUNIT_ASSERT(*iter == 2);}

    void test_begin_2() { 
        C a(10, 2);
	typename C::iterator iter = a.begin();
	++*iter;
 	CPPUNIT_ASSERT(*iter == 3);}

    void test_begin_3() { 
        C a(10, 2);
	CPPUNIT_ASSERT(*a.begin() == a[0]);
    }

    // -----
    // end
    // -----
    void test_end_1() { 
	C a(1000, 2);
        typename C::iterator iter = a.begin();
        int i = 0;
        while(iter != a.end()) {
	    ++i;
            ++iter;
        }
        CPPUNIT_ASSERT(iter == a.end());
        CPPUNIT_ASSERT(i == 1000);}

    void test_end_2() { 
        C a(10, 2);
        typename C::iterator iter = a.end();
	--iter;
        CPPUNIT_ASSERT(*iter == 2);
        CPPUNIT_ASSERT(*iter == a.back());}

    void test_end_3() { 
        C a(12, 1);
        typename C::iterator iter = a.end();
        --iter;
	CPPUNIT_ASSERT(*iter == 1);}

    // ----
    // equals
    // ----
    
    void test_equals_1() {
        C a(110, 1);
        C b(110, 1);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(&a != &b);}

    void test_equals_2() {
        C a(50, 1);
        C b(10, 1);
        a.resize(10);
        CPPUNIT_ASSERT(a == b);}

    void test_equals_3() { 
        C a(100, 12);
        C b(a);
        CPPUNIT_ASSERT(a == b);}

    
    // -------
    // lessthan
    // -------


    void test_lessthan_1() {
        C a(10, 2);
        C b(10, 1);
        CPPUNIT_ASSERT(a > b);
    }

    void test_lessthan_2() {
        C a(10, 2);
        C b(a);
        CPPUNIT_ASSERT( a <= b);}

    void test_lessthan_3() {
        C a(10, 1);
        C b(10, 1);
        b[9] = 0;
        CPPUNIT_ASSERT( b < a );}

    // ---------------
    // iterator equals
    // ----------------

    void test_iterator_equals_1() {
        C a(1000, 1);
        typename C::iterator iter1 = a.begin();
        typename C::iterator iter2 = a.begin();
        iter1 += 500;
        iter2 += 500;
        CPPUNIT_ASSERT(iter1 == iter2);
    }    

    void test_iterator_equals_2() {
        const C a(1000, 1);
        typename C::const_iterator iter1 = a.begin();
        typename C::const_iterator iter2 = a.begin();
        iter1 += 500;
        iter2 += 500;
        CPPUNIT_ASSERT(iter1 == iter2);
    }

    void test_iterator_equals_3() {
        C a(100, 1);
        C b(100, 1);
        typename C::iterator iter1 = a.begin();
        typename C::iterator iter2 = b.begin();
        ++iter1;
        ++iter2;
        CPPUNIT_ASSERT(iter1 != iter2);}

 
    // ------
    // front
    // ------

    void test_front_1() {
        C a(100, 1);
        CPPUNIT_ASSERT(a.front() == 1);
    }

    void test_front_2() {
        C a(100, 1);
        C b(a);
        CPPUNIT_ASSERT(b.front() == 1);
    }

    void test_front_3() {
        C a(100, 1);
        C b = a;
        CPPUNIT_ASSERT(b.front() == 1);
    }
    

    // -------
    // erase
    // -------

    void test_erase_1() {
        C a(10, 1);
        a[2] = 2;
        typename C::iterator iter = a.begin();
        ++iter;
        a.erase(iter);
        CPPUNIT_ASSERT(a.size() == 9);
        CPPUNIT_ASSERT(a[1] == 2);
    }
    
    void test_erase_2() { 
        C a(10, 1);
        typename C::iterator result = a.erase(a.begin());
        CPPUNIT_ASSERT(result == a.begin());
        CPPUNIT_ASSERT(a.size() == 9);
    }

    void test_erase_3() { 
        C a(10, 1);
        a[8] = 2;
        typename C::iterator iter = a.end();
        --iter;
        a.erase(iter);
        CPPUNIT_ASSERT(a.size() == 9);
        CPPUNIT_ASSERT(a.back() == 2);
    }       

    // ------
    // insert
    // ------ 

    void test_insert_1() {
       using namespace std;
       C a(5, 1);
       int i = 0;
       typename C::iterator iter = a.begin();
       while (i < 40) {
           iter = a.begin();
           ++iter;
           a.insert(iter, 10);
           ++i;
       }
       
       CPPUNIT_ASSERT(a.size() > 40);


       CPPUNIT_ASSERT(a.back() == 1);
       CPPUNIT_ASSERT(a[10] == 10);           
    }

    void test_insert_2() {
        C a(100, 1);
        typename C::iterator iter = a.begin();
        iter += 50;
        typename C::iterator result = a.insert(iter, 4);
        
        CPPUNIT_ASSERT(a.size() == 101);
        CPPUNIT_ASSERT(*result == 4);
    }


    void test_insert_3() { 
        C a(10, 1);
        a.insert(a.begin(), 2);
        CPPUNIT_ASSERT(a.front() == 2);
    }

    void test_insert_4() {
       using namespace std;
       C a(5, 1);
       typename C::iterator iter = a.begin();
       
       ++iter;
       a.insert(iter, 10);

       CPPUNIT_ASSERT(a.back() == 1);
       CPPUNIT_ASSERT(a[1] == 10);           
       CPPUNIT_ASSERT(a[2] == 1);
    }


    // -----
    // swap
    // -----
    
    void test_swap_1() { 
        C a(10, 1);
        C b(1000, 2);
        C c(1000, 2);
        
        a.swap(b);
        CPPUNIT_ASSERT(a == c);
        CPPUNIT_ASSERT(b.size() == 10);
        CPPUNIT_ASSERT(a.at(10) == 2);
    }

    void test_swap_2() {
        C a(10, 1);
        C b(10, 1);
        a.swap(b);
        CPPUNIT_ASSERT(a == b);
    }

    void test_swap_3() { 
       C a(10, 1);
       C b(10, 2);
       b.swap(a);
       CPPUNIT_ASSERT(a.front() == 2);
       CPPUNIT_ASSERT(b.front() == 1);
    }


    // -----------
    // push_front
    // -----------
 
    void test_push_front_1() { 
        C a(5, 1);
        a.push_front(100);
        CPPUNIT_ASSERT(a.front() == 100);
        CPPUNIT_ASSERT(a.size() == 6);
    }

    void test_push_front_2() {
        C a(1, 1);
        a.push_front(1);
        CPPUNIT_ASSERT(a.front() == 1);
        CPPUNIT_ASSERT(a.back() == 1);
    }

    void test_push_front_3() {
        C a(10, 1);
        int i = 0;
        while (i < 100){
            ++i;
            a.push_front(2);
        }
	CPPUNIT_ASSERT(true);
        CPPUNIT_ASSERT(a.back() == 1);
        CPPUNIT_ASSERT(a[10] == 2);
    }


    void test_push_front_4() {
        C a(1, 1);
        a.push_front(2);
        CPPUNIT_ASSERT(a.back() == 1);
        CPPUNIT_ASSERT(a[0] == 2);
    }

    void test_push_front_5() {
        C a(1, 1);
        a.push_front(2);
	a.push_front(3);
        CPPUNIT_ASSERT(a.back() == 1);
        CPPUNIT_ASSERT(a[0] == 3);
    }

    void test_push_front_6() {
        C a(1, 1);
	int* x = &a[0];
        a.push_front(2);
        a.push_front(3);
        a.push_front(4);
        a.push_front(5);
        a.push_front(6);
        CPPUNIT_ASSERT(a.back() == 1);
        CPPUNIT_ASSERT(a[0] == 6);
	CPPUNIT_ASSERT(x == &a[5]);
    }


    // -----------
    // push_back
    // -----------

    void test_push_back_1() {
        using namespace std;
        C a(10, 1); 
	const int i = 2;
        a.push_back(i);
        a.push_back(i);
        CPPUNIT_ASSERT(a.size() == 12);
        CPPUNIT_ASSERT(a.front() == 1);
        CPPUNIT_ASSERT(a.back() == 2);
    }

    void test_push_back_2() {
        C a(10, 1);
        int i = 0;
        while (i < 100){
            ++i;
            a.push_back(2);
        }
        CPPUNIT_ASSERT(a.front() == 1);
        CPPUNIT_ASSERT(a.size() == 110);
        CPPUNIT_ASSERT(a[100] == 2);
    }

    void test_push_back_3() {
        C a(100, 1);
        //C b = a;
        a.push_back(2);
        CPPUNIT_ASSERT(a.back() == 2);
        //CPPUNIT_ASSERT(a != b);
    }
        
    // ----------------
    // pop_front
    // ----------------

    void test_pop_front_1() {
        C a(100, 1);
        a.push_front(2);        
        CPPUNIT_ASSERT(a.front() == 2);
        a.pop_front();
        CPPUNIT_ASSERT(a.front() == 1);
    }

    void test_pop_front_2() { 
        C a(100, 1);
        int i = 0;
        while (i < 50) {
            ++i;
            a.pop_front();
        }
        CPPUNIT_ASSERT(a.size() == 50);
        CPPUNIT_ASSERT(a.front() == 1);
    }

    void test_pop_front_3() {
        C a(10, 1);
        a.push_front(2);
        C b(a);
        b.pop_front();

        CPPUNIT_ASSERT(a.front() == 2);
        CPPUNIT_ASSERT(b.front() == 1);

    }

    void test_pop_front_4() {
        C a (10, 1);
        a.pop_front();

	CPPUNIT_ASSERT(a.size() == 9);
	CPPUNIT_ASSERT(a.front() == 1);}

    // ----------------
    // pop_backj
    // ----------------

    void test_pop_back_1() {
        C a(100, 1);
        a.push_back(2);
        CPPUNIT_ASSERT(a.back() == 2);
        a.pop_back();
        CPPUNIT_ASSERT(a.back() == 1);
    }

    void test_pop_back_2() {
        C a(100, 1);
        int i = 0;
        while (i < 50) {
            ++i;
            a.pop_back();
        }
        CPPUNIT_ASSERT(a.size() == 50);
        CPPUNIT_ASSERT(a.back() == 1);
    }

    void test_pop_back_3() {
        C a(10, 1);
        a.push_back(2);
        C b(a);
        b.pop_back();

        CPPUNIT_ASSERT(a.back() == 2);
        CPPUNIT_ASSERT(b.back() == 1);

    }


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);

    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    CPPUNIT_TEST(test_size_4);
    CPPUNIT_TEST(test_size_5);
    
    CPPUNIT_TEST(test_index_1);

    CPPUNIT_TEST(test_at_1);
    CPPUNIT_TEST(test_at_2);
    CPPUNIT_TEST(test_at_3);

    CPPUNIT_TEST(test_assignment_1);
    CPPUNIT_TEST(test_assignment_2);
    CPPUNIT_TEST(test_assignment_3);

    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);

    CPPUNIT_TEST(test_begin_1);
    CPPUNIT_TEST(test_begin_2);
    CPPUNIT_TEST(test_begin_3);

    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);
    CPPUNIT_TEST(test_end_3);
 
    CPPUNIT_TEST(test_equals_1);
    CPPUNIT_TEST(test_equals_2);
    CPPUNIT_TEST(test_equals_3);

    CPPUNIT_TEST(test_lessthan_1);
    CPPUNIT_TEST(test_lessthan_2);
    CPPUNIT_TEST(test_lessthan_3);

    CPPUNIT_TEST(test_iterator_equals_1);
    CPPUNIT_TEST(test_iterator_equals_2);
    CPPUNIT_TEST(test_iterator_equals_3);

    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);

    CPPUNIT_TEST(test_erase_1);
    CPPUNIT_TEST(test_erase_2);
    CPPUNIT_TEST(test_erase_3);


    CPPUNIT_TEST(test_insert_1);
    CPPUNIT_TEST(test_insert_2);
    CPPUNIT_TEST(test_insert_3);
    CPPUNIT_TEST(test_insert_4);

    CPPUNIT_TEST(test_swap_1);
    CPPUNIT_TEST(test_swap_2);
    CPPUNIT_TEST(test_swap_3);
 
    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);
    CPPUNIT_TEST(test_push_front_4);
    CPPUNIT_TEST(test_push_front_5);
    CPPUNIT_TEST(test_push_front_6);

// there are problems with the resize and the iterator valid() here
    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);

    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);
    CPPUNIT_TEST(test_pop_front_4);

    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);


  

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque< deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
