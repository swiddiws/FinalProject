/*
    Graph Implementation
    
    After reviewing, might not fit what we needed.


*/
#ifndef CUSTOM_GRAPH_H
#define CUSTOM_GRAPH_H

#include <set>
#include <cassert>

typedef struct {
    int x, y;
} Vertex;

template <class T>
class custom_graph {
public:
    custom_graph(const int width, const int height);
    ~custom_graph();
    void addVertex(const T& value);
    void addEdge(int source, int target);
    T& operator [](int vertex);
    T operator [](int vertex) const;
    bool isEdge(int source, int target) const;
    std::set<int> neighbors(int vertex) const;
private:
    static const int MAXIMUM = 200;
    bool adjacencyMatrix[MAXIMUM][MAXIMUM];
    T labels[MAXIMUM];
    int manyVertices;
    int h;
    int w;
};

template <class T>
const int custom_graph<T>::MAXIMUM;

template <class T>
custom_graph<T>::custom_graph(const int width, const int height) {
    h = height;
    w = width;
}

template <class T>
custom_graph<T>::~custom_graph() {

}

template <class T>
void custom_graph<T>::addVertex(const T& value) {
    assert(manyVertices < h);
    int newVertexNumber = manyVertices;
    manyVertices++;
    for (int otherVertexNumber = 0; otherVertexNumber < manyVertices; otherVertexNumber++) {
        adjacencyMatrix[otherVertexNumber][newVertexNumber] = false;
        adjacencyMatrix[newVertexNumber][otherVertexNumber] = false;
    }
    labels[newVertexNumber] = value;
}

template <class T>
void custom_graph<T>::addEdge(int source, int target) {
    assert(source < h && target < w);
    adjacencyMatrix[source][target] = true;
}

template <class T>
T& custom_graph<T>::operator [](int vertex) {
    assert(vertex < h);
    return labels[vertex];
}

template <class T>
T custom_graph<T>::operator [](int vertex) const {
    assert(vertex < h);
    return labels[vertex];
}

template <class T>
bool custom_graph<T>::isEdge(int source, int target) const {
    assert(source < h && target < w);
    bool isAnEdge = false;
    isAnEdge = adjacencyMatrix[source][target];
    return isEdge;
}

template <class T>
std::set<int> custom_graph<T>::neighbors(int vertex) const {
    assert(vertex < h);
    std::set<int> vertexNeighbors;

    for (int i = 0; i < w; i++) {
        if (adjacencyMatrix[vertex][i]) {
            vertexNeighbors.insert(i);
        }
    }
    return vertexNeighbors;
}

#endif
