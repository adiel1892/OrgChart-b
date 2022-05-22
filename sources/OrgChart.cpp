#include "OrgChart.hpp"
#include <stack>
using namespace ariel;
using namespace std;

// destructor
OrgChart::~OrgChart(){
    if(this->root != nullptr){
        std::queue<Node*> helper; 
        helper.push(this->root);
        while(!helper.empty()){
            unsigned int times = helper.size();
            while(times > 0){
                Node* tmp = helper.front();
                helper.pop();
                for(unsigned int i = 0; i < tmp->subs.size(); i++){
                    helper.push(tmp->subs.at(i));
                }
                times--;
                delete tmp;
            }
        }
    }
}

// add root to the organization
OrgChart & OrgChart::add_root(const string & job){
    // The organization is empty
    if(this->root == nullptr){
        this->root = new Node(job);
    }else{
        for(unsigned int i = 0; i < this->root->subs.size(); i++){
            this->root->subs.at(i)->father = job;
        }
        this->root->job = job;
    }
    this->root->high = 0;
    return *this;
}
vector<Node*> OrgChart::iterator::getNodes(){
    return this->nodes;
}

// add child to the father
OrgChart & OrgChart::add_sub(const string &father, const string &son){
    if(!in_the_org(father)){
        throw invalid_argument("Can't add sub to Null");
    }
    Node* dad =  searchNode(father);
    dad->subs.push_back(new Node(son));
    for(unsigned int i = 0; i < dad->subs.size(); i++){
        if(dad->subs.at(i)->high == -1){
            dad->subs.at(i)->high = dad->high + 1;
        }
        dad->subs.at(i)->father = dad->job;
    }
    return *this;
}
// searching a node by level order run.
// if we found the node we will return it, if we didn't found the node well return null.
Node* OrgChart::searchNode(const string & job)const{
    if(this->root == nullptr){
        throw invalid_argument("There is not a root for this organization");
    }
    std::queue<Node*> helper; 
    helper.push(this->root);
    while(!helper.empty()){
        unsigned int times = helper.size();
        while(times > 0){
            Node* tmp = helper.front();
            // we found our node
            if(tmp->job == job){
                return tmp;
            }
            helper.pop();
            for(unsigned int i = 0; i < tmp->subs.size(); i++){
                helper.push(tmp->subs.at(i));
            }
        }
    }
    return nullptr;
}

// check if worker is part of organization
bool OrgChart::in_the_org(const string & job)const{
    if(this->root == nullptr){
        return false;
    }
    std::queue<Node*> helper; 
    helper.push(this->root);
    while(!helper.empty()){
        unsigned int times = helper.size();
        while(times > 0){
            Node* tmp = helper.front();
            if(tmp->job == job){
                return true;
            }
            helper.pop();
            for(unsigned int i = 0; i < tmp->subs.size(); i++){
                helper.push(tmp->subs.at(i));
            }
            times--;
        }
    }
    return false;
}

// printing the organization by level order. each node have in brackets next to him his dad
ostream& ariel::operator<<(ostream& out ,const OrgChart &org){
    if(org.root == nullptr){
        return out;
    }
    vector<Node*> iter = org.begin_level_order().getNodes();
    unsigned int high = 0;
    for(unsigned int i = 0; i < iter.size(); i++){
        if(high == iter.at(i)->high){
            out << iter.at(i)->job <<  "(dad:" << iter.at(i)->father << ")" << " ";
        }else{
            out << endl;
            high++;
            out << iter.at(i)->job <<  "(dad:" << iter.at(i)->father << ")" << " ";
        }
    }
    return out;
}

// There are 3 different iterators.
// The iterator gets string of the way (level || reverse || preorder) and the root.
OrgChart::iterator::iterator(Node* node , const string &way){
    this->currNode = node;
    if(node != nullptr){
        if(way == "level"){
            iter_begin_level_order(node);
            this->currNode = this->getNodes().at(0);
        }
        if(way == "reverse"){
            iter_begin_reverse_order(node);
            this->currNode = this->getNodes().at(0);
        }
        if(way == "preorder"){
            iter_begin_preorder(node);
            this->currNode = this->getNodes().at(0);
        }
        if(way == "begin"){
            iter_begin_level_order(node);
            this->currNode = this->getNodes().at(0);
        }
    }else{
        if(way == "end"){
            this->currNode = nullptr;
        }
    }
}

void OrgChart::iterator::iter_begin_level_order(Node* node){
    std::queue<Node*> helper; 
    helper.push(node);
    this->nodes.push_back(node);
    while(!helper.empty()){
        unsigned int times = helper.size();
        while(times > 0){
            Node* tmp = helper.front();
            helper.pop();
            for(unsigned int i = 0; i < tmp->subs.size(); i++){
                helper.push(tmp->subs.at(i));
                this->nodes.push_back(tmp->subs.at(i));
            }
            times--;
        }
    }
}

void OrgChart::iterator::iter_begin_reverse_order(Node* node){
    std::queue<Node*> helper; 
    std::stack<Node*> nodeStack;
    helper.push(node);
    nodeStack.push(node);
    while(!helper.empty()){
        unsigned int times = helper.size();
        while(times > 0){
            Node* tmp = helper.front();
            helper.pop();
            for(int i = (int)tmp->subs.size() - 1; i >= 0; i--){
                if(tmp->subs.size() >= 0){
                    unsigned int ii = (unsigned int)(i);
                    helper.push(tmp->subs.at(ii));
                }
            }
            for(int i = (int)tmp->subs.size() - 1; i >= 0; i--){
                if(tmp->subs.size() >= 0){
                    unsigned int ii = (unsigned int)(i);
                    nodeStack.push(tmp->subs.at(ii));
                }
            }
            times--;
        }
    }
    while(!nodeStack.empty()){
        Node *top = nodeStack.top();
        nodeStack.pop();
        this->nodes.push_back(top);
    }
}

void OrgChart::iterator::iter_begin_preorder(Node* node){
    if(node == nullptr){
        return;
    }
    std::stack<Node*> nodeStack;
    nodeStack.push(node);
    while(!nodeStack.empty()){
        Node* tmp = nodeStack.top();
        this->nodes.push_back(tmp);
        nodeStack.pop();
        for(int i = (int)tmp->subs.size() - 1; i >= 0; i--){
            if(tmp->subs.size() >= 0){
                unsigned int ii = (unsigned int)(i);
                nodeStack.push(tmp->subs.at(ii));
            }
        }
    }
}

string* OrgChart::iterator::operator->(){
    return &this->currNode->job;
}

bool OrgChart::iterator::operator!=(const iterator &other){
    return this->currNode != other.currNode;
}

string OrgChart::iterator::operator*(){
    return currNode->job;
}
OrgChart::iterator & OrgChart::iterator::operator++(){
    if(this->nodes.size() > 1){
        this->nodes.erase(this->nodes.begin());
        this->currNode = nodes.at(0);
    }else{
        this->currNode = nullptr;
    }
    return *this;
}



OrgChart::iterator OrgChart::begin_level_order()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(root , "level");
}
OrgChart::iterator OrgChart::end_level_order()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin_reverse_order()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(root , "reverse");
}
OrgChart::iterator OrgChart::reverse_order()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin_preorder()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(root , "preorder");
}
OrgChart::iterator OrgChart::end_preorder()const{
    if(this->root == nullptr){
        throw invalid_argument("Organization is empty!");
    }
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin()const{
    return OrgChart::iterator(root , "begin");
}
OrgChart::iterator OrgChart::end(){
    return OrgChart::iterator(nullptr , "end");
}
