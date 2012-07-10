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

	// ----------
	// destructor
	// ----------

	void test_destructor_1() {
		C x;
		x.~C();
		CPPUNIT_ASSERT(true);
	}

	void test_destructor_2() {
		C x(10);
		x.~C();
		CPPUNIT_ASSERT(true);
	}

	void test_destructor_3() {
		C x(10, 5);
		x.~C();
		CPPUNIT_ASSERT(true);
	}

	void test_destructor_4() {
		C x(10);
		C y(x);
		x.~C();
		y.~C();
		CPPUNIT_ASSERT(true);
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
        C x(10, 2);
        C y(5, 2);
        y = x;
        CPPUNIT_ASSERT(y.size() == 10); 
    }

    void test_size_5 () {
        C x(10, 2);
        C y(5, 2);
        x = y;
        CPPUNIT_ASSERT(x.size() == 5);}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);/*
    CPPUNIT_TEST(test_destructor_1);
    CPPUNIT_TEST(test_destructor_2);
    CPPUNIT_TEST(test_destructor_3);
    CPPUNIT_TEST(test_destructor_4);*/

    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    CPPUNIT_TEST(test_size_4);
    CPPUNIT_TEST(test_size_5);
    
    CPPUNIT_TEST(test_index_1);

    CPPUNIT_TEST(test_at_1);
    CPPUNIT_TEST(test_at_2);

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
