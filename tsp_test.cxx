/**
 * TSP solution implementation using Dynamic Programming & Nearest Neighbour Algorithm
 * This is the Unit Test for the implementation
 * All the test cases would be run in this Unit Test file
 *
 * File: tsp_test.cxx
 * Author: iJab(Zhan Caibao) zhancaibaoATgmail.com
 * Date: 2013/02/20
 *
 */

#include <UnitTest++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "graph.hxx"

using namespace std;

double d_rand(double d_min, double d_max)
{
    double f = (double)rand() / RAND_MAX;
    return d_min + f * (d_max - d_min);
}

void add_edges(graph *g, int n)
{
	int r_edges = n - 1; //rand() % n;  // random number 0 to n-1, try to add edges to this number

	// Random edges to add
	/*
	for(int i = 0; i <= r_edges; ++i)
	{
		int src = rand() % n;
		int dst = rand() % (src+1);
		double w = d_rand(1.0, 100.0);
		g->add_edge(src, dst, w);
		g->add_edge(dst, src, w);
	}
	*/
	for(int i = 0; i < r_edges; ++i)
	{
		for(int j = i+1; j <= r_edges; ++j)
		{
			if(i != j && i < j)
			{
				double cost = d_rand(1.0, 100.0);
				g->add_edge(i, j, cost);
				g->add_edge(j, i, cost);
			}
		}
	}
}


// Test Case 1: 5 nodes for two-dimension array based TSP dynamic algorithm
// 5
TEST(TwoArrayDP_TSP5)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 12;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp(0);
	CHECK(m_dist + 1);

	_aTest.print_result();
}
/*
// Test Case 2: 5 nodes for two-dimension array based Nearest Neighbour algorithm
// 5 
TEST(TwoArrayNN_TSP5)
{
	int n = 5;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 1: 6 nodes for two-dimension array based TSP dynamic algorithm
// 6
TEST(TwoArrayDP_TSP6)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 6;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 2: 30 nodes for two-dimension array based Nearest Neighbour algorithm
// 30 
TEST(TwoArrayNN_TSP30)
{
	int n = 30;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 3: 7 nodes for two-dimension array based TSP dynamic algorithm
// 7
TEST(TwoArrayDP_TSP7)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 7;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 3: 50 nodes for two-dimension array based Nearest Neighbour algorithm
// 50 
TEST(TwoArrayNN_TSP50)
{
	int n = 50;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 8 nodes for two-dimension array based TSP dynamic algorithm
// 8
TEST(TwoArrayDP_TSP8)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 8;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 80 nodes for two-dimension array based Nearest Neighbour algorithm
// 80 
TEST(TwoArrayNN_TSP80)
{
	int n = 80;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 5: 9 nodes for two-dimension array based TSP dynamic algorithm
// 9
TEST(TwoArrayDP_TSP9)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 9;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 5: 100 nodes for two-dimension array based Nearest Neighbour algorithm
// 100 
TEST(TwoArrayNN_TSP100)
{
	int n = 100;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 6: 10 nodes for two-dimension array based TSP dynamic algorithm
// 10
TEST(TwoArrayDP_TSP10)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 10;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 6: 120 nodes for two-dimension array based Nearest Neighbour algorithm
// 120 
TEST(TwoArrayNN_TSP120)
{
	int n = 120;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 7: 11 nodes for two-dimension array based TSP dynamic algorithm
// 11
TEST(TwoArrayDP_TSP11)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 11;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 7: 35 nodes for two-dimension array based Nearest Neighbour algorithm
// 35 
TEST(TwoArrayNN_TS3P5)
{
	int n = 35;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 8: 12 nodes for two-dimension array based TSP dynamic algorithm
// 12
TEST(TwoArrayDP_TSP12)
{
	cout << "Init Two-dimension array based graph ...";
	print_current_time();
	cout << endl;

	int n = 12;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);

	cout << "Init  Two-dimension array based graph completed.";
	print_current_time();
	cout << endl;

	double m_dist = _aTest.dp_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 7: 150 nodes for two-dimension array based Nearest Neighbour algorithm
// 150 
TEST(TwoArrayNN_TSP150)
{
	int n = 150;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 200 nodes for two-dimension array based Nearest Neighbour algorithm
// 200 
TEST(TwoArrayNN_TSP200)
{
	int n = 200;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 250 nodes for two-dimension array based Nearest Neighbour algorithm
// 250 
TEST(TwoArrayNN_TSP250)
{
	int n = 250;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 300 nodes for two-dimension array based Nearest Neighbour algorithm
// 300 
TEST(TwoArrayNN_TSP300)
{
	int n = 300;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 500 nodes for two-dimension array based Nearest Neighbour algorithm
// 500 
TEST(TwoArrayNN_TSP500)
{
	int n = 500;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 800 nodes for two-dimension array based Nearest Neighbour algorithm
// 800 
TEST(TwoArrayNN_TSP800)
{
	int n = 800;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 1000 nodes for two-dimension array based Nearest Neighbour algorithm
// 1000 
TEST(TwoArrayNN_TSP1000)
{
	int n = 1000;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 2000 nodes for two-dimension array based Nearest Neighbour algorithm
// 2000 
TEST(TwoArrayNN_TSP2000)
{
	int n = 2000;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 5000 nodes for two-dimension array based Nearest Neighbour algorithm
// 5000 
TEST(TwoArrayNN_TSP5000)
{
	int n = 5000;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}

// Test Case 4: 7000 nodes for two-dimension array based Nearest Neighbour algorithm
// 7000 
TEST(TwoArrayNN_TSP7000)
{
	int n = 7000;
	twodarray_graph _aTest(n);
	add_edges(&_aTest, n);
	double m_dist = _aTest.nn_tsp();
	CHECK(m_dist + 1);

	_aTest.print_result();
}
*/

int main(int argc, char* argv[])
{
	int rv = 0;
	rv = UnitTest::RunAllTests();

	getchar();

	return rv;
}