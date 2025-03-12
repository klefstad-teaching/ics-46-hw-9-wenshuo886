#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int currVertex = pq.top().second;
        pq.pop();

        if (currDist > distances[currVertex])
            continue;

        for (const Edge& edge : G[currVertex]) {
            int nextVertex = edge.dst;
            int newDist = currDist + edge.weight;

            if (newDist < distances[nextVertex]) {
                distances[nextVertex] = newDist;
                previous[nextVertex] = currVertex;
                pq.emplace(newDist, nextVertex);
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " ";
        }
    }
    cout << " \nTotal cost is " << total << "\n";
}
