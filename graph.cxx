/**
 * Dynamic Programming & Nearest Neighbour Algorithm for TSP
 * File: graph.cxx
 * Author: iJab(Zhan Caibao) zhancaibaoATgmail.com
 * Date: 2013/02/20
 *
 */

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>

#include "graph.hxx"

using namespace std;

// Helper function to print time
void print_current_time()
{
		time_t rawtime;
		struct tm * timeinfo;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		printf ( "The current date/time is: %s", asctime (timeinfo) );
};

///////////////////////////////////////////////////////////////
/**
 * Graph base class implementation
 *
 */
graph::~graph()
{
}

/**
 * Calculate shortest path for TSP with Dynamic Programmings
 * @param int source : source vertex id
 * @return int : number of path from source to other nodes
 */
double graph::dp_tsp(int source)
{
	cout << "Dynamic Programming Calculating shortest path for TSP from vertex " << source << endl;
	print_current_time();
	cout << endl;

	int _v_size = this->get_size();
	
	if(source < 0 || source >= _v_size)
	{
		source = 0;		
	}
	this->source = source;

	// Do some clean
	this->tsp_s_path.unvisited.clear();
	this->tsp_s_path.type.clear();

	vector<STATUS> pre_v;
    vector<STATUS> cur_v;

    // Init current vertex array
	// Distance and shortest path from each vertex to source using empty vertices set. {Vi, {emtpy set}}
    for(int i = 0; i < _v_size; i++)   
    {   
		if(i == source)  continue;		// Ignore source vertex

        STATUS _v_status;
		_v_status.cur_v = i;
		_v_status.distance = this->get_cost(i, source);
		cur_v.push_back(_v_status);
    }

    // Loop on each vertex   
    for(int j = 0; j < _v_size - 2; j++)   
    {       
		// Set previous vertex to current vertex array
        pre_v = cur_v;   
        cur_v.clear();
        for(int i = 0; i < _v_size; i++)   
        {   
			if(i == source) continue;

            vector<STATUS>::iterator it;   
            for(it = pre_v.begin(); it != pre_v.end(); ++it)   
            {   
                STATUS temp = *it;   

				// Check if vertex i has been included in temp's path or not
				int b_exist = false;
				if(i == temp.cur_v)   
					b_exist = true;   
				else   
				{   
					vector<int>::iterator uv_it = temp.unvisited.begin();
					for(; uv_it != temp.unvisited.end(); ++uv_it)   
						if(i == *uv_it)
						{
							b_exist = true;
							break;
						}
				} 
				// If not exist
                if(!b_exist)   
                {   
                    STATUS _n_v_status = temp;   
                    vector<int>::iterator int_iter = _n_v_status.unvisited.begin();   
					_n_v_status.unvisited.insert(int_iter, _n_v_status.cur_v);   
					_n_v_status.type.insert(_n_v_status.cur_v);
					_n_v_status.distance += this->get_cost(i, _n_v_status.cur_v);
					_n_v_status.cur_v = i;
                    cur_v.push_back(_n_v_status);       
                }   
            }   
        } 
		
		// Calculae the shortest path in current vertex's paths
		this->tsp_paths.clear();
		vector<STATUS>::iterator iter;   
        STATUS temp;   
        while(cur_v.size() > 0)   
        {   
            iter = cur_v.begin();   
            temp = *iter;   
            iter = cur_v.erase(iter);

            for(; iter != cur_v.end(); )   
            {   
				bool need_inc = true;
				if((temp.cur_v == (*iter).cur_v) && (temp.type == (*iter).type))   
                {   
                    if((*iter).distance < temp.distance)   
                        temp = *iter;   
                    iter = cur_v.erase(iter);   
                    need_inc = false;   
                }

				if(need_inc) ++iter;
            }   
            this->tsp_paths.push_back(temp);   
        }

		// Check current minimum path array
		cur_v = this->tsp_paths;
    } 
  
    // Calculate the shortest path from source to every possible path   
    vector<STATUS>::iterator iter = this->tsp_paths.begin();   
    this->tsp_s_path = *iter;   
	this->m_dis = this->tsp_s_path.distance + this->get_cost(source, this->tsp_s_path.cur_v);
    iter++;   
    for(; iter != this->tsp_paths.end(); iter++)   
    {   
		double temp_dis = this->get_cost(source, (*iter).cur_v) + (*iter).distance;   
		if(temp_dis < this->m_dis)   
        {   
			this->m_dis = temp_dis;   
            this->tsp_s_path = *iter;   
        }       
    }   
    
	cout << "Dynamic Calculating shortest path for TSP from vertex " << source << endl;
	print_current_time();
	cout << endl;

	return this->m_dis;
}


/**
 * Shortest path for TSP with Nearest Neighbour Heuristic algorithm
 * @param source int
 * @return int : all paths
 */
double graph::nn_tsp(int source)
{
	if(this->is_empty_graph()) return 0;

	cout << "Nearest Neighbour Algorithm Calculating shortest path for TSP ... " << endl;
	print_current_time();
	cout << endl;

	int _v_size = this->get_size();
	if(source < 0 || source >= _v_size)
		source = 0;
	this->source = source;

	// Do some clean
	this->tsp_s_path.unvisited.clear();
	this->tsp_s_path.type.clear();

	set<int> visited_v;
	visited_v.insert(source);
	
	// Loop to find the nearest vertex for current vertex till all vertices are marked visted
	int current_v = source;
	this->m_dis = 0;
	while((int)visited_v.size() < _v_size)
	{
		pair<int, double> nearest_v = this->get_unvisited_nearest_neighbour(current_v, visited_v);
		this->m_dis += nearest_v.second;
		
		if(current_v == source)
		{
			this->tsp_s_path.cur_v = nearest_v.first;
			this->tsp_s_path.distance = nearest_v.second;
		}
		else
		{
			this->tsp_s_path.unvisited.insert(this->tsp_s_path.unvisited.begin(), nearest_v.first);
			this->tsp_s_path.distance += nearest_v.second;
		}

		// Set current vertex to the nearest neighbour and mark it as visited
		current_v = nearest_v.first;
		visited_v.insert(current_v);

		// If it's the last one, add the distance between it and the source vertex
		if(visited_v.size() == _v_size)
		{
			this->m_dis += this->get_cost(current_v, source);
		}
	}
	
	cout << "Nearest Neighbour Algorithm Completed Calculating shortest path for TSP." << endl;
	print_current_time();
	cout << endl;

	return this->m_dis;
}

/**
 * Print the shortest path cost result
 */
void graph::print_result()
{
	// Print Result   
    vector<int>::iterator iter_v;   
	cout << "Minimum distance is " << this->m_dis << endl;   
	cout << "The shortest path is " << this->source << "->" << this->tsp_s_path.cur_v;   
    for(iter_v = this->tsp_s_path.unvisited.begin(); iter_v != this->tsp_s_path.unvisited.end(); iter_v++)   
        cout<< "->"<< *iter_v;   
    cout << "->" << this->source << endl;  
}

///////////////////////////////////////////////////////////////////////////////////
/**
 * Implementation of 2-d array based graph
 *
 */

/**
 * Constructor of 2-d array based graph
 * @param num int: size of vertices in the graph
 * @return void
 */
twodarray_graph::twodarray_graph(int num) : graph(num)
{
	if(num < 1)
	{
		this->adj_matrix = NULL;
	}
	else
	{
		// Init and new memory for graph
		this->adj_matrix = new double*[num];

		for(int i = 0; i < num; ++i)
		{
			this->adj_matrix[i] = new double[num];
			// Set init value to INF_WEIGHT which means no path between vertices
			for( int j = 0; j < num; ++j)
			{
				this->adj_matrix[i][j] = INF_WEIGHT;
			}
		}
	}
}

/**
 * Desstructor of 2-d array based graph
 * @param num int: size of vertices in the graph
 * @return void
 */
twodarray_graph::~twodarray_graph()
{
	// Release resource
	if(this->adj_matrix != NULL)
	{
		int _size = this->get_size();
		for(int i = 0; i < _size; ++i)
		{
			delete []this->adj_matrix[i];
			this->adj_matrix[i] = NULL;
		}
		delete []this->adj_matrix;
		this->adj_matrix = NULL;
	}
}

/**
 * Add connected edge to graph
 * @param int source : source vertex id
 * @param int target : target vertex id
 * @param double w : weight between these two vertices
 * @return void
 */
void twodarray_graph::add_edge(int source, int target, double w)
{
	// Not allocated memory for graph
	if(this->adj_matrix == NULL)
		return;

	// Negative source or target
	if(source < 0 || target < 0)
		return;

	// source or target is greater than number of vertices predefined
	int _size = this->get_size();
	if(source >= _size || target >= _size)
		return;

	if(source == target)
		this->adj_matrix[source][target] = 0;
	else
		this->adj_matrix[source][target] = w < 1 ? INF_WEIGHT : w;
}

/**
 * Remove connected edge between vertices from graph
 * @param int source : source vertex id
 * @param int target : target vertex id
 * @return void
 */
void twodarray_graph::remove_edge(int source, int target)
{
	// Make the weight between vertices to be -1 to disconnect
	this->add_edge(source, target, INF_WEIGHT);
}

/**
 * Get cost between two vertices
 * @param int source : source vertex
 * @param int target : target vertex
 * @return double : cost between two vertices
 */
double twodarray_graph::get_cost(int source, int target)
{
	int _v_size = this->get_size();

	if(source < 0 || source >= _v_size 
		|| target < 0 || target >= _v_size)
		return 0;

	return this->adj_matrix[source][target];
}

/**
 * Get nearest neighbour to the vertex
 * @param int source : source vertex
 * @param set<int> : visited vertices
 * @return pair<int, double> : nearest vertex and the distance
 */
pair<int, double> twodarray_graph::get_unvisited_nearest_neighbour(int source, set<int> visited_v)
{
	int _v_size = this->get_size();

	double min_dist = INF_WEIGHT;
	int	nearest_v = source;

	for(int i = 0; i < _v_size; ++i)
	{
		if(i == source || visited_v.find(i) != visited_v.end())
			continue;

		double alt_dist = this->get_cost(source, i);
		if(min_dist > alt_dist)
		{
			min_dist = alt_dist;
			nearest_v = i;
		}
	}

	return pair<int, double>(nearest_v, min_dist);

}

/**
 * Print graph
 * @param void
 * @return void
 */
void twodarray_graph::print_graph()
{
	int _v_size = this->get_size();
	
	for(int i = 0; i < _v_size; ++i)
	{
		for(int j = 0; j < _v_size; ++j)
		{
			cout << this->adj_matrix[i][j] << "\t\t";
		}
		cout << endl;
	}
}