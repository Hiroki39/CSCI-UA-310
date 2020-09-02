#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    Node() : distance(-1), neighbors() {}
    int distance;
    vector<pair<int, int>> neighbors;
};

class Graph {
public:
    // Node comparison functor
    class CompNode {
    public:
        bool operator()(Node* a, Node* b) { return a->distance > b->distance; }
    };

    // Construct a vector of pointers to nodes
    Graph(int num_of_node) : node_list() {
        for (int i = 0; i < num_of_node; ++i) {
            node_list.push_back(new Node());
        }
    };

    // Add a neighbor to a node
    void add_edge(int start, int end, int weight) {
        node_list[start - 1]->neighbors.push_back(make_pair(end, weight));
    }

    int dijkstra() const {
        priority_queue<Node*, vector<Node*>, CompNode> min_heap;
        node_list[0]->distance = 0;
        min_heap.push(node_list[0]);
        while (!min_heap.empty()) {
            Node* curr_nodep = min_heap.top();
            if (curr_nodep == node_list.back()) return curr_nodep->distance;
            min_heap.pop();
            for (const pair<int, int>& nbr_pair : curr_nodep->neighbors) {
                Node* nbrp = node_list[nbr_pair.first - 1];
                if (nbrp->distance == -1 ||
                    nbrp->distance > curr_nodep->distance + nbr_pair.second) {
                    nbrp->distance = curr_nodep->distance + nbr_pair.second;
                    min_heap.push(nbrp);
                }
            }
        }
        return -1;
    }

    // Destructor
    ~Graph() {
        for (Node* nodep : node_list) {
            delete nodep;
        }
    }

private:
    vector<Node*> node_list;
};

int main() {
    int num_of_node, num_of_passage;
    cin >> num_of_node >> num_of_passage;

    Graph graph(num_of_node * 2);
    int start, end, weight;

    // add a neighbor to a node after reading each line
    for (int i = 0; i < num_of_passage; ++i) {
        cin >> start >> end >> weight;
        graph.add_edge(start, end, weight - 1);
        graph.add_edge(start + num_of_node, end + num_of_node, weight - 1);
        if (weight == 1) graph.add_edge(start, end + num_of_node, weight - 1);
    }

    cout << graph.dijkstra() << endl;
}
