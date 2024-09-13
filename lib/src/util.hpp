#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <concepts>
#include <stdexcept>

// concept to check if the type is printable
template <typename CustomType>
concept printable = requires(CustomType a) {
  std::cout << a;
};

// concept to check if the type is considered to be
// a number atleast within a ring
template <typename CustomType>
concept comparable_and_addible = requires(CustomType a, CustomType b) {
    a + b;
    a - b;
    a += b;
    a -= b;
    a < b;
    a <= b;
    a == b;
    a >= b;
    a > b;
    a != b;
};

template<printable CustomType>
struct Edge {
    CustomType from;
    CustomType to;
};

template <printable CustomType>
std::istream& operator>>(istream& is, Edge& edge) {
    std::cin >> edge.from >> edge.to;
    return is;
}

template<printable CustomType, comparable_and_addible CustomWeight>
struct WeightedEdge : public Edge<CustomType> {
    CustomWeight weight;
};

template <printable CustomType>
std::istream& operator>>(istream& is, WeightedEdge& weighted_edge) {
    std::cin >> weighted_edge.from >> weighted_edge.to >> weighted_edge.weight;
    return is;
}

// this graph uses unordered_map as a container, which allows to be
// both adjacency matrix graph and adjacency list graph,
// therefore it's called "Combined Graph"
class CombinedGraph {
    protected:
        long long vertices_amount_;
        long long edges_amount_;
};

template <printable CustomType, comparable_and_addible CustomWeight>
class WeightedUnorientedGraph : public CombinedGraph {
    public:
        WeightedUnorientedGraph(
            std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector);
        WeightedUnorientedGraph(long long vertices_amount,
            std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector);
    protected:
        virtual void add_to_adjacency_map(WeightedEdge<CustomType, CustomWeight>& wedge,
            std::unordered_map<CustomType>& vertices_set);
        void initialize(
            std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector);
        std::unordered_map<CustomType, std::unordered_map<CustomType, CustomWeight>> adjacency_map;
};

template <printable CustomType, comparable_and_addible CustomWeight>
class WeightedOrientedGraph : public WeightedUnorientedGraph<CustomType, CustomWeight> {
    protected:
        void add_to_adjacency_map(WeightedEdge<CustomType, CustomWeight>& wedge,
            std::unordered_map<CustomType>& vertices_set) override;
};

template <printable CustomType>
class UnweightedUnorientedGraph : public CombinedGraph {
    public:
        UnweightedUnorientedGraph(std::vector<Edge<CustomType>>& edge_initialization_vector);
        UnweightedUnorientedGraph(long long vertices_amount,
            std::vector<Edge<CustomType>>& edge_initialization_vector);
    protected:
        virtual void add_to_adjacency_map(
            Edge<CustomType>& edge, std::unordered_map<CustomType>& vertices_set);
        void initialize(
            std::vector<Edge<CustomType>>& edge_initialization_vector);
        std::unordered_map<CustomType, std::unordered_map<CustomType, bool>> adjacency_map;
};

template <printable CustomType>
class UnweightedOrientedGraph : public UnweightedUnorientedGraph<CustomType> {
    protected:
        void add_to_adjacency_map(Edge<CustomType>& edge,
            std::unordered_map<CustomType>& vertices_set) override;
};

void WeightedUnorientedGraph<CustomType, CustomWeight>::add_to_adjacency_map(
    WeightedEdge<CustomType, CustomWeight>& wedge, std::unordered_map<CustomType>& vertices_set
) {
    vertices_set.insert(wedge.from);
    vertices_set.insert(wedge.to); // vertices_set.insert(from, to);
    adjacency_map[wedge.from][wedge.to] = weight;
    adjacency_map[wedge.to][wedge.from] = weight;
}

template <printable CustomType, comparable_and_addible CustomWeight>
void WeightedUnorientedGraph<CustomType, CustomWeight>::initialize(
    std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector
) {
    edges_amount_ = wedge_initialization_vector.size();
    std::unordered_set<CustomType> vertices_set;
    for (const auto& wedge : wedge_initialization_vector) {
        add_to_adjacency_map(wedge, vertices_set);
    }
    vertices_amount_ = vertices_set.size();
}

template <printable CustomType, comparable_and_addible CustomWeight>
WeightedUnorientedGraph<CustomType, CustomWeight>::WeightedUnorientedGraph(
    std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector
) {
    initialize(wedge_initialization_vector);
}

template <printable CustomType, comparable_and_addible CustomWeight>
WeightedUnorientedGraph<CustomType, CustomWeight>::WeightedUnorientedGraph(
    long long vertices_amount,
    std::vector<WeightedEdge<CustomType, CustomWeight>>& wedge_initialization_vector
) {
    initialize(vertices_amount);
    if (vertices_amount < vertices_amount_) {
        throw std::logic_error("vertices_amount doesn't allign with given edges");
    } else {
        vertices_amount_ = vertices_amount;
    }
}

template <printable CustomType, comparable_and_addible CustomWeight>
void WeightedOrientedGraph<CustomType, CustomWeight>::add_to_adjacency_map(
    WeightedEdge<CustomType, CustomWeight>& wedge, unordered_set<CustomType>& vertices_set
) {
    vertices_set.insert(wedge.from);
    vertices_set.insert(wedge.to); // vertices_set.insert(from, to);
    adjacency_map[wedge.from][wedge.to] = weight;
}

template <printable CustomType>
void UnweightedUnorientedGraph<CustomType>::add_to_adjacency_map(
    Edge<CustomType>& edge, std::unordered_map<CustomType>& vertices_set) {
    vertices_set.insert(edge.from);
    vertices_set.insert(edge.to); // vertices_set.insert(from, to);
    adjacency_map[edge.from][edge.to] = true;
    adjacency_map[edge.to][edge.from] = true;
}

template <printable CustomType>
void UnweightedUnorientedGraph<CustomType>::initialize(
    std::vector<Edge<CustomType>>& edge_initialization_vector) {
    edges_amount_ = edge_initialization_vector.size();
    std::unordered_set<CustomType> vertices_set;
    for (const auto& edge : edge_initialization_vector) {
        add_to_adjacency_map(edge, vertices_set);
    }
    vertices_amount_ = vertices_set.size();
}

template <printable CustomType>
UnweightedUnorientedGraph<CustomType>::UnweightedUnorientedGraph(
    std::vector<Edge<CustomType>>& edge_initialization_vector) {
    initialize(edge_initialization_vector);
}

template <printable CustomType>
UnweightedUnorientedGraph<CustomType>::UnweightedUnorientedGraph(
    long long vertices_amount, std::vector<Edge<CustomType>>& edge_initialization_vector) {
    initialize(edge_initialization_vector);
    if (vertices_amount < vertices_amount_) {
        throw std::logic_error("vertices_amount doesn't allign with given edges");
    } else {
        vertices_amount_ = vertices_amount;
    }
}

template <printable CustomType>
void UnweightedOrientedGraph<CustomType>::add_to_adjacency_map(
    Edge<CustomType>& edge, std::unordered_map<CustomType>& vertices_set) {
    vertices_set.insert(edge.from);
    vertices_set.insert(edge.to); // vertices_set.insert(from, to);
    adjacency_map[edge.from][edge.to] = true;
}