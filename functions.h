#pragma once
#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<time.h>
using namespace std;

void createGraph(int no_vertices, vector<tuple<int, int, int>>& node, vector<int>adj[100], vector<int>adjTrans[100]);
bool sortByWeight(const tuple<int, int, int>& a, const tuple<int, int, int>& b);
void DFS(int source, vector<int>adj[100], bool visited[]);
bool isConnected(int no_vertices, vector<int>adj[100], vector<int>adjTrans[100], int step);
