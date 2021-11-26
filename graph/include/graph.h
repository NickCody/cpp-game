#pragma once

#include <memory>
#include <array>
#include <string>
#include <algorithm>
#include <iomanip>
#include <optional>

using namespace std;

namespace cody {
namespace graph {

template <typename D>
struct Vertex {
  private:
    using adj_t = std::vector<int>;

    std::optional<D> data = {};
    int vertex_num = 0; // range(1..N)
    adj_t adj;
    
  public:

    size_t getAdjSize() const { return adj.size(); }
    int getVertexNum() const { return vertex_num; }
    
    void setVertexNum(int v) { vertex_num = v; }
    void addAdj(int v) { adj.push_back(v); }
    void clearAdj() { adj.clear(); }
    int getAdj(int v) { return adj[v]; }

    using iterator = adj_t::iterator;
    using const_iterator = adj_t::const_iterator;

    iterator begin() { return adj.begin(); }
    iterator end() { return adj.end(); }
    const_iterator begin() const { return adj.begin(); }
    const_iterator end() const { return adj.end(); }
    const_iterator cbegin() const { return adj.cbegin(); }
    const_iterator cend() const { return adj.cend(); }

    friend ostream& operator<<(ostream& output, Vertex const& vertex) {
      output << vertex.data.value_or(vertex.vertex_num);
      return output;
    }

};

template <typename VertexType = Vertex<int>>
class Graph
{
private:
  using vertices_t = vector<VertexType>;

  vertices_t vertices;
  int V;
  bool directed;

public:
  Graph(int V, bool directed) : V(V), directed(directed) {
    vertices.resize(V);
    for(int u=0; u < V; u++) {
      vertices[u].setVertexNum(u+1);
    }
  }

  Graph(const Graph& rhs) {
    V = rhs.V;
    directed = rhs.directed;
    vertices.resize(V);
    for(int u=0; u < V; u++) {
      vertices[u].setVertexNum(u+1);
    }

    for (auto const& x: rhs) {
        for (int y: x) {
            addDirectedEdge(x.getVertexNum()-1, y);
        }
    }

  }

  Graph& operator=(Graph&& other) {
    cout << "std::move() called" << endl;
      vertices = std::move(other.vertices);
      directed = other.directed;
      V = other.V;
      return *this;
  }

  using iterator = vertices_t::iterator;
  using const_iterator = vertices_t::const_iterator;

  iterator begin() { return vertices.begin(); }
  iterator end() { return vertices.end(); }
  const_iterator begin() const { return vertices.begin(); }
  const_iterator end() const { return vertices.end(); }
  const_iterator cbegin() const { return vertices.cbegin(); }
  const_iterator cend() const { return vertices.cend(); }

  int getNumVertices() {
    return V;
  }

  void addDirectedEdge(int u, int v)
  {
    auto& x = vertices[u];

    if (find(x.begin(), x.end(), v) == x.end())
      x.addAdj(v);
  }

  void addEdge(int u, int v)
  {
    addDirectedEdge(u,v);

    if (!directed)
      addDirectedEdge(v, u);
  }

  VertexType& getVertex(int u) {
    return vertices[u];
  }

  vector<int>& getAdjancency(int u ) {
    return vertices[u].adj;  
  }

  bool isDirected() { return directed; }

  Graph transpose() {

    Graph _temp(*this);

    if (!directed)
      return _temp;

    for (VertexType& x : _temp.vertices) {
      x.clearAdj();
    }

    for (auto const& x : vertices) {
      for (int y : x) {
        _temp.addDirectedEdge(y, x.getVertexNum()-1);
      }
    }

    return _temp;
  }



}; // Graph

} // namespace graph
} // namespace cody