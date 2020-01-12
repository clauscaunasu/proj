#include "functions.h"
void createGraph(int no_vertices, vector<tuple<int, int, int>>& node, vector<int>adj[100], vector<int>adjTrans[100])
{
	//create all the edges of an oriented graph with some random weights
	for (int i = 1; i <= no_vertices; i++)
	{

		for (int j = 1; j <= no_vertices; j++)
			if (i != j) {
				int weight = rand() % 20 + 1;
				node.push_back(make_tuple(i, j, weight)); //introduce in a vector the tripletes
				adj[i].push_back(j);          //introduce in the adjacency list of source the destination
				adjTrans[i].push_back(j);     //introduce in another adjacency list the existence of an edge as if we wouldn't be interested
				adjTrans[j].push_back(i);     //in the sense of the edge, so there is an edge from i to j and also from j to i
				


			}

	}
}
bool sortByWeight(const tuple<int, int, int>& a, const tuple<int, int, int>& b) //function that helps us to sort the tripletes by weight
{
	return (get<2>(a) > get<2>(b));
}
void DFS(int source, vector<int>adj[100], bool visited[]) //DFS, it visits the source and then goes through the adjacency list of source
{                                                          //and visits all of them
	vector<int>::iterator i;
	visited[source] = true;
	for (i = adj[source].begin(); i != adj[source].end(); ++i)
		if (!visited[*i])
			DFS(*i, adj, visited);
}
bool isConnected(int no_vertices, vector<int>adj[100], vector<int>adjTrans[100], int step)
{
	bool visited[100];
	memset(visited, false, sizeof(visited)); //mark as not visited for all nodes
	DFS(1, adj, visited);
	for (int i = 2; i <= no_vertices; i++) //go through the visited vector of all vertices
		if (visited[i] == false/*&&(no_vertices*(no_vertices-1)-step+1)>=(no_vertices-1)*/) //if it finds a vertice that is not visited
		{
			memset(visited, false, sizeof(visited)); //resets all the visited vector
			DFS(1, adjTrans, visited); //with the help of the other adjacency list we try again the dfs
			break;                    //the result will change because in this dfs we are only interested in the existence of an edge between nodes
		}
	for (int i = 2; i <= no_vertices; i++)//we will use only this for if the sene of the edge counts
		if (visited[i] == false)
			return false;

	return true;
}