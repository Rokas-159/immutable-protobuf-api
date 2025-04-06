#include <iostream>
#include <benchmark/benchmark.h>
#include "Tester/graph.pb.h"

void printGraph(Graph& graph) {
    for (int i = 0; i < graph.nodes_size(); i++) {
        const Node& node = graph.nodes(i);
        std::cout << "Node " << node.id() << ": " << node.value() << "; Adj: ";
        for (size_t j = 0; j < node.adj_size(); j++) {
            std::cout << node.adj(j) << " ";
        }
        std::cout << ";" << std::endl;
    }
}

class GraphTester {
private:
    int buildBinaryNode(int v, int n, Graph& graph) {
        Node* node = graph.add_nodes();
        node->set_id(v);
        node->set_value(0);

        if (v < n) {
            node->add_adj(buildBinaryNode(2*v, n, graph));
            node->add_adj(buildBinaryNode(2*v+1, n, graph));
        }

        return graph.nodes_size();
    }
public:
    void binaryGraphTest(int size, int copies) {
        Graph graph;

        buildBinaryNode(1, size, graph);
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
