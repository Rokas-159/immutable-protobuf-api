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
    long long sumDFS(const Graph& graph, const Node& v, const long long MOD) {
        long long sum = v.value() % MOD;

        for (int i = 0; i < v.adj_size(); i++) {
            sum += sumDFS(graph, graph.nodes(v.adj(i)), MOD);
            sum %= MOD;
        }

        return sum;
    }

    int buildBinaryNode(int v, int n, Graph& graph) {
        int index = graph.nodes_size();

        Node* node = graph.add_nodes();
        node->set_id(v);
        node->set_value(v);

        if (v < n) {
            node->add_adj(buildBinaryNode(2*v, n, graph));
            node->add_adj(buildBinaryNode(2*v+1, n, graph));
        }

        return index;
    }
public:
    void binaryGraphTest(int size, int copies) {
        Graph graph;

        int root = buildBinaryNode(1, size, graph);

        long long sum = sumDFS(graph, graph.nodes(root), 1e9+7);

        //std::cout << sum << std::endl;
    }
};

static void test() {
    GraphTester tester;
    tester.binaryGraphTest(1000000, 0);
}

static void OFFICIAL_PB(benchmark::State& state) {
    for (auto _ : state) {
        test();
    }
}

BENCHMARK(OFFICIAL_PB);

BENCHMARK_MAIN();
