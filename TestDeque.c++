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
        CPPUNIT_ASSERT(i == 1000);
    }

    void test_end_2() { 
        C a(10, 2);
        typename C::iterator iter = a.end();
	--iter;
        CPPUNIT_ASSERT(*iter == 2);
        CPPUNIT_ASSERT(*iter == a.back());}



    /*
    void test_equals_1() {
    }

    void test_lessthan_1() {
    }

    void test_iterator_equals_1() {

    void test_const_iterator_equals_1() {
    }

    void test_front_1() {
    }
    
    void test_erase_1() {
    }
    
    void test_insert_1() {
    }
    
    void test_swap_1() { 
    }
  
    TODO test push/pop back/front
    */

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
    //CPPUNIT_TEST(test_assignment_2);
    CPPUNIT_TEST(test_assignment_3);

    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);

    CPPUNIT_TEST(test_begin_1);
    CPPUNIT_TEST(test_begin_2);
    CPPUNIT_TEST(test_begin_3);

    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);


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
