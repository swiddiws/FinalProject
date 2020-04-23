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
    Vertex& operator [](int vertex);
    Vertex operator [](int vertex) const;
    void add_vertex(int x, int y);
    void add_edge(int x1, int y1, int x2, int y2, float weight);
    int find_vertex_index(int x, int y);
private:
    int h;
    int w;
    Vertex* labels;
    float** connections;
    int row_counter;
};

template <class T>
custom_graph<T>::custom_graph(const int width, const int height) {
    h = height;
    w = width;
    row_counter = 0;
    labels = new Vertex[h*w];
    connections = new float*[h*w];
    for (int x = 0; x < h*w; ++x) {
        connections[x] = new float[h*w];
    }
}

template <class T>
custom_graph<T>::~custom_graph() {
    delete[] labels;
    delete[] connections;

}

template <class T>
void custom_graph<T>::add_vertex(int x, int y) {
    Vertex v = { x, y };
    int row_index = row_counter;
    row_counter++;
    for (int column_index = 0; column_index < h*w; column_index++) {
        connections[column_index][row_index] = NULL;
        connections[row_index][column_index] = NULL;
    }
    labels[row_index] = v;
}

template <class T>
Vertex& custom_graph<T>::operator [](int vertex) {
    return labels[vertex];
}

template <class T>
Vertex custom_graph<T>::operator [](int vertex) const {
    return labels[vertex];
}

template <class T>
void custom_graph<T>::add_edge(int x1, int y1, int x2, int y2, float weight) {
    int source = find_vertex_index(x1, y1);
    int target = find_vertex_index(x2, y2);
    //printf("(%d, %d) index: %d  --  (%d, %d) index: %d\n", x1, y1, source, x2, y2, target);
    connections[source][target] = weight;
}

template <class T>
int custom_graph<T>::find_vertex_index(int x, int y) {
    for (int i = 0; i < h * w; i++) {
        Vertex tmp = labels[i];
        if (tmp.x == x && tmp.y == y) {
            return i;
        }
    }
}


#endif
