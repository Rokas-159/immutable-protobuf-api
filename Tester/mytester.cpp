#include <iostream>
#include <benchmark/benchmark.h>
#include "graph.mypb.h"

void printGraph(const Graph& graph) {
    for (int i = 0; i < graph.nodes_size(); i++) {
        const Node& node = graph.get_nodes(i);
        std::cout << "Node " << node.get_id() << ": " << node.get_value() << "; Adj: ";
        for (size_t j = 0; j < node.adj_size(); j++) {
            std::cout << node.get_adj(j) << " ";
        }
        std::cout << ";" << std::endl;
    }
}

class GraphTester {
private:
    int buildBinaryNode(int v, int n, Graph::Builder& graph_builder) {
        Node::Builder node_builder;
        node_builder.set_id(v);
        node_builder.set_value(0);

        if (v < n) {
            node_builder.add_adj(buildBinaryNode(2*v, n, graph_builder));
            node_builder.add_adj(buildBinaryNode(2*v+1, n, graph_builder));
        }

        graph_builder.add_nodes(std::move(node_builder).Build());

        return graph_builder.nodes_size();
    }
public:
    void binaryGraphTest(int size, int copies) {
        Graph::Builder graph_builder;

        buildBinaryNode(1, size, graph_builder);

        Graph graph = std::move(graph_builder).Build();
    }
};

static void test() {
    GraphTester tester;
    tester.binaryGraphTest(1000000, 0);
}

static void BM_test(benchmark::State& state) {
    for (auto _ : state) {
        test();
    }
}

BENCHMARK(BM_test);

BENCHMARK_MAIN();