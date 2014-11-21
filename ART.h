template <class T>
struct Node
{
    pair<T, T> range;
    vector<int> shardID;
    set<Node> sub;
};

class RoutingTree
{
public:
    RoutingTree(){};
    Node *search(pair<T, T> range){};
private:
    Node *root;
    void insert(pair<T, T> range){};
};