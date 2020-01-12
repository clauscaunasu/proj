#include "functions.h"
#include<iostream>
vector<int>adj[100]; //adjacency list for the graph
vector<int>adjTrans[100];   //adjacency list for the transposed graph
int main()
{
	vector<tuple<int, int, int>> node; //vector that will store three integers: source,destination and weight
	int no_vertices, k, mst = 0, i = 0, step = 0;
	bool erased = 0;
	cout << "Introduce the number of vertices:" << endl;
	cin >> no_vertices;
	srand(time(0));
	createGraph(no_vertices, node, adj, adjTrans);  //create the oriented graph with all vertices
	sort(node.begin(), node.end(), sortByWeight); //sort the vector of tripletes after weight
	cout << "The vertices of the directed graph in decreasing order are:" << endl;
	for (k = 0; k < node.size(); k++)
		cout << get<0>(node[k]) << " " << get<1>(node[k]) << " " << get<2>(node[k]) << "\n";  //print the source,destination and weight
	cout << "The vertices that contain the MST are:" << endl;                            //in decreasing order 
	while (i < node.size()) //while there are still elements in the vector of tripletes
	{
		step++;  //count the present step
		int u = get<0>(node[i]); //store the value of source in a variable
		int v = get<1>(node[i]);  //store the value of destination in a variable
		erased = 0; //use the variable to see if the current triplete will be erased or kept
		int position = -1;
		for (int j = 0; j < adj[u].size(); j++) { //search for the destination in the adjacency list of source and store its position
			position++;
			if (adj[u][j] == v)
				break;
		}
		adj[u].erase(adj[u].begin() + position); // delete the vertice by erasing the destination from the adjacency list of source

		int position1 = -1,position2=-1,found1=0,found2=0;
		for (int j = 0; j < adjTrans[v].size(); j++) { //search for the source in the adjacency list of destination and store its position
				position2++;
			if (adjTrans[v][j] == u)
				break;
			
		}
		for (int j = 0; j < adjTrans[u].size(); j++)       //search for the destination in the adjacency list of source and store its position
		{
			position1++;
			if (adjTrans[u][j] == v)
				break;
		}
		adjTrans[u].erase(adjTrans[u].begin() + position1);  //erase from the adjacency list of source the destination
		adjTrans[v].erase(adjTrans[v].begin() + position2);  //erase from the adjacency list of destination the source


		if (isConnected(no_vertices, adj, adjTrans, step) == false) //check if after the deletion the graph is still connected
		{                                                         //if not introduce again the destination stored previously in the adjacency list of source
			adjTrans[u].push_back(v);                             
			adjTrans[v].push_back(u);
			adj[u].push_back(v); 
								 //which was also stored in a variable before
			cout << "(" << u << ", " << v << ") \n"; //we print the source and destination
			mst += get<2>(node[i]); //we add the third element from the triplete (the weight) to the mst
		}
		else {

			node.erase(node.begin() + i); //if the graph is still connected, erase the triplete
			erased = 1;                   //store the change in the variable
		}
		if (erased == 0)  //if no triplete was erased, move to the next triplete
		{
			i++;
		}
	}
	cout << "The MST is: " << mst;
	return 0;
}