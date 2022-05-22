#pragma once
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
    OrgChart(){
        this->root = nullptr;
    }
    OrgChart(const OrgChart & other);
    OrgChart &operator=(const OrgChart & other);
    OrgChart(OrgChart && other)noexcept;
    OrgChart &operator=(OrgChart && other)noexcept;
    ~OrgChart();
    OrgChart &add_root(const string & job);
    OrgChart &add_sub(const string &father, const string &son);
    Node* searchNode(const string & job)const;
    bool in_the_org(const string & job)const;
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
        bool operator!=(const iterator &other);
        string operator*();
        iterator &operator++();
    };
    iterator begin_level_order()const;
    iterator end_level_order()const;
    iterator begin_reverse_order()const;
    iterator reverse_order()const;
    iterator begin_preorder()const;
    iterator end_preorder()const;
    iterator begin()const;
    static iterator end();
    };
}
