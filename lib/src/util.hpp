#include <iostream>
#include <vector>
#include <concepts>

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

template<printable CustomType, comparable_and_addible CustomWeight>
struct WeightedEdge : public Edge<CustomType> {
    CustomWeight weight;
};

// this graph uses unordered_map as a container, which allows to be
// both adjacency matrix graph and adjacency list graph,
// therefore it's called "Combined Graph"
template <printable CustomType>
class CombinedGraph {
    public:
        virtual CombinedGraph(std::vector)
};