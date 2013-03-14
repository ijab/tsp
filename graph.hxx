/**
 * Travel Salesman Problem implementation
 * File: graph.hxx
 * Author: iJab(Zhan Caibao) zhancaibaoATgmail.com
 * Date: 2013/03/12
 *
 */

#ifndef __TRAVEL_SALESMAN_PROBLEM_GRAPH__
#define __TRAVEL_SALESMAN_PROBLEM_GRAPH__

#include <vector>
#include <map>
#include <set>
#include <list>
#include <limits>
#include <ctime>

using namespace std;

const bool VERBOSE_DEBUG = false;
const double INF_WEIGHT = numeric_limits<double>::infinity();

// Helper function to print time
void print_current_time(); 


struct STATUS   
{   
    int cur_v;				// current vertex   
    vector<int> unvisited;	// unvisited vertices   
    set<int> type;			// set of vertic with the same status   
    double distance;		// The distance from current vertex visiting all vertices and return to source   
};

/**
 * Graph class
 *
 */
class graph
{
public:
	graph(int num){this->size = num; this->m_dis = INF_WEIGHT;};

	virtual ~graph();

	virtual void add_edge(int source, int target, double w) = 0;
	virtual void remove_edge(int source, int target) = 0;
	int get_size() {return this->size;};

	// Dynamic Programming exact algorithm for TSP
	virtual double dp_tsp(int source = 0);

	// Nearest Neighbour Heuristic Algorithm for TSP
	virtual double nn_tsp(int source = 0);

	virtual double get_cost(int source, int target) = 0;
	virtual pair<int, double> get_unvisited_nearest_neighbour(int source, set<int> visited_v) = 0;
	
	virtual bool is_empty_graph() = 0;
	virtual void print_graph() = 0;
	void print_result();
	void print_path(int source, int target);

protected:
	int size;
	vector<STATUS> tsp_paths;			// Store result of cost results on each iterat
	STATUS tsp_s_path;					// TSP shortest path
	int source;							// Current source vertex
	double m_dis;						// minimum distance
};

/**
 * Two dimensions based Graph implementation
 */
class twodarray_graph : public graph
{
public:
	twodarray_graph(int num);
	
	virtual ~twodarray_graph();

public:
	virtual void add_edge(int source, int target, double w);
	virtual void remove_edge(int source, int target);

	virtual double get_cost(int source, int target);
	virtual pair<int, double> get_unvisited_nearest_neighbour(int source, set<int> visited_v);
	
	virtual bool is_empty_graph() {return this->adj_matrix == NULL;};
	virtual void print_graph();
private:
	double **adj_matrix;
};

#endif