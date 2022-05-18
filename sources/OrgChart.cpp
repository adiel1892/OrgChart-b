#include "OrgChart.hpp"
#include <stack>
using namespace ariel;
using namespace std;

OrgChart::OrgChart(){
    this->root = nullptr;
}
OrgChart & OrgChart::add_root(const string & job){
    if(this->root == nullptr){
        this->root = new Node(job);
        this->root->high = 0;
    }else{
        // there is already root so well make a new root and point the new root to the old root
        Node *newRoot = new Node(job);
        newRoot->subs.push_back(this->root);
        this->root = newRoot;
    }
    return *this;
}
vector<Node*> OrgChart::iterator::getNodes(){
    return this->nodes;
}

OrgChart & OrgChart::add_sub(const string &father, const string &son){
    Node* dad =  searchNode(father);
    if(dad == nullptr){
        throw invalid_argument("Can't add sub to Null");
    }
    dad->subs.push_back(new Node(son));
    for(unsigned int i = 0; i < dad->subs.size(); i++){
        if(dad->subs.at(i)->high == -1){
            dad->subs.at(i)->high = dad->high + 1;
        }
    }
    return *this;
}
Node* OrgChart::searchNode(const string & job){
    if(this->root == nullptr){
        throw invalid_argument("There is not a root for this organization");
    }
    std::queue<Node*> helper; 
    helper.push(this->root);
    while(!helper.empty()){
        int times = helper.size();
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

ostream& ariel::operator<<(ostream& out ,const OrgChart &org){
    if(!org.root){
        return out;
    }
    vector<Node*> iter = org.begin_level_order().getNodes();
    unsigned int high = 0;
    for(unsigned int i = 0; i < iter.size(); i++){
        if(high == iter.at(i)->high){
            out << iter.at(i)->job <<  "  ";
        }else{
            out << endl;
            high++;
            out << iter.at(i)->job <<  "  ";
        }
    }
    return out;
}

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
    }else{
        this->currNode = nullptr;
    }
}

void OrgChart::iterator::iter_begin_level_order(Node* node){
    std::queue<Node*> helper; 
    helper.push(node);
    this->nodes.push_back(node);
    while(!helper.empty()){
        int times = helper.size();
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
    // for(unsigned int i = 0; i < this->nodes.size(); i++){
    //     cout << this->nodes.at(i)->job << " ";
    // }
    // this->currNode = *this->nodes.begin();
    // cout << endl;
}

void OrgChart::iterator::iter_begin_reverse_order(Node* node){
    std::queue<Node*> helper; 
    std::stack<Node*> nodeStack;
    helper.push(node);
    nodeStack.push(node);
    while(!helper.empty()){
        int times = helper.size();
        while(times > 0){
            Node* tmp = helper.front();
            helper.pop();
            for(int i = tmp->subs.size() - 1; i >= 0; i--){
                if(tmp->subs.size() >= 0){
                    unsigned int ii = (unsigned int)(i);
                    helper.push(tmp->subs.at(ii));
                }
            }
            for(int i = tmp->subs.size() - 1; i >= 0; i--){
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
            // for(unsigned int i = 0; i < this->nodes.size(); i++){
            //     cout << this->nodes.at(i)->job << " ";
            // }
            // this->currNode = *this->nodes.begin();
            // cout << endl;
        
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
        for(int i = tmp->subs.size() - 1; i >= 0; i--){
            if(tmp->subs.size() >= 0){
                unsigned int ii = (unsigned int)(i);
                nodeStack.push(tmp->subs.at(ii));
            }
        }
    }
    //  for(unsigned int i = 0; i < this->nodes.size(); i++){
    //             cout << this->nodes.at(i)->job << " ";
    //         }
    //         this->currNode = *this->nodes.begin();
    //         cout << endl;
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
OrgChart::iterator OrgChart::iterator::operator++(int){
    OrgChart::iterator it = *this;
    ++*this;
    return it;
}
OrgChart::iterator OrgChart::begin_level_order()const{
    return OrgChart::iterator(root , "level");
}
OrgChart::iterator OrgChart::end_level_order()const{
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin_reverse_order(){
    return OrgChart::iterator(root , "reverse");
}
OrgChart::iterator OrgChart::reverse_order(){
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin_preorder(){
    return OrgChart::iterator(root , "preorder");
}
OrgChart::iterator OrgChart::end_preorder(){
    return OrgChart::iterator(nullptr , "null");
}
OrgChart::iterator OrgChart::begin(){
    return OrgChart::iterator(root , "level");
}
OrgChart::iterator OrgChart::end(){
    return OrgChart::iterator(nullptr , "null");
}
