#include <iostream>
#include <benchmark/benchmark.h>
#include "Tester/graph.mypb.h"

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
    Graph::Builder graph_builder;
    Graph graph;
    int root;
    bool built = false;

    long long sumDFS(Graph graph, Node v, const long long MOD) {
        long long sum = v.get_value() % MOD;

        for (int i = 0; i < v.adj_size(); i++) {
            sum += sumDFS(graph, graph.get_nodes(v.get_adj(i)), MOD);
            sum %= MOD;
        }

        return sum;
    }

    int buildBinaryNode(int v, int n, Graph::Builder& graph_builder) {
        Node::Builder node_builder;
        node_builder.set_id(v);
        node_builder.set_value(v);

        if (v < n) {
            node_builder.add_adj(buildBinaryNode(2*v, n, graph_builder));
            node_builder.add_adj(buildBinaryNode(2*v+1, n, graph_builder));
        }

        int index = graph_builder.nodes_size();

        graph_builder.add_nodes(std::move(node_builder).Build());

        return index;
    }
public:
    void binaryGraphTestBuild(int size) {
        root = buildBinaryNode(1, size, graph_builder);

        graph = std::move(graph_builder).Build();

        built = true;
    }

    void binaryGraphTestBFS() {
        assert(built);

        long long sum = sumDFS(graph, graph.get_nodes(root), 1e9+7);

        //std::cout << sum << std::endl;
    }
};

GraphTester tester;

static void MY_PB_BUILD(benchmark::State& state) {
    for (auto _ : state) {
        tester.binaryGraphTestBuild(1000000);
    }
}

static void MY_PB_BFS(benchmark::State& state) {
    for (auto _ : state) {
        tester.binaryGraphTestBFS();
    }
}

BENCHMARK(MY_PB_BUILD);

BENCHMARK(MY_PB_BFS);

BENCHMARK_MAIN();