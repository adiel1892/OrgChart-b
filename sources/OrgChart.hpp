
#include <string>
#include <iterator>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include <queue>
using namespace std;
namespace ariel{
    class OrgChart{
    public:
    Node *root;
    OrgChart();
    OrgChart &add_root(const string & job);
    OrgChart &add_sub(const string &father, const string &son);
    Node* searchNode(const string & job);
    friend ostream & operator<<(ostream& out , const OrgChart &org);
    class iterator{
        private:
        vector<Node*> nodes;
        Node* currNode;
        public:
        iterator(Node* node , const string &way);
        void iter_begin_level_order(Node *node);
        void iter_begin_reverse_order(Node *node);
        void iter_begin_preorder(Node* node);
        vector<Node*> getNodes();
        string* operator->();
        // bool operator==(const iterator &other);
        bool operator!=(const iterator &other);
        string operator*();
        iterator &operator++();
        iterator operator++(int);
    };
    iterator begin_level_order()const;
    iterator end_level_order()const;
    iterator begin_reverse_order();
    iterator reverse_order();
    iterator begin_preorder();
    iterator end_preorder();
    iterator begin();
    iterator end();
    };
}
