#include "conepts.hpp"


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