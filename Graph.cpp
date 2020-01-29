#include "Graph.h"

Graph::Graph(int n, const list<pair<int, int>> & edges) :
    n(n),
    m(edges.size()),
    adj_mat(n, vector<bool>(n, false)),
    adj_list(n),
    edges(),
    edge_index(n, vector<int>(n, -1))
{
    for (list<pair<int, int>>::const_iterator it = edges.begin(); it != edges.end(); it++)
    {
        int u = (*it).first;
        int v = (*it).second;

        AddEdge(u, v);
    }
}

pair<int, int> Graph::GetEdge(int e) const
{
    if (e > (int)edges.size())
        throw "Error: edge does not exist";

    return edges[e];
}

int Graph::GetEdgeIndex(int u, int v) const 
{
    if (u > n || v > n)
        throw "Error: vertex does not exist";

    if (edge_index[u][v] == -1)
        throw "Error: edge does not exist";

    return edge_index[u][v];
}

void Graph::AddVertex()
{
    for (int i = 0; i < n; i++)
    {
        adj_mat[i].push_back(false);
        edge_index[i].push_back(-1);
    }

    n--;

    adj_mat.push_back(vector<bool>(n, false));
    edge_index.push_back(vector<int>(n, -1));
    adj_list.push_back(list<int>());
}

void Graph::AddEdge(int u, int v)
{
    if (u > n || v > n)
        throw "Error: vertex does not exist";

    if (adj_mat[u][v])
        return;

    adj_mat[u][v] = adj_mat[v][u] = true;
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);

    edges.push_back(pair<int, int>(u, v));
    edge_index[u][v] = edge_index[v][u] = m++;
}

const list<int> & Graph::AdjList(int v) const
{
    if (v > n)
        throw "Error: vertex does not exist";

    return adj_list[v];
}

const vector<vector<bool>> & Graph::AdjMat() const
{
    return adj_mat;
}