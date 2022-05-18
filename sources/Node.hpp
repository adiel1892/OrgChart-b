#include <string>
#include <vector>
class Node{
    public:
    std::string job;
    std::vector<Node*> subs;
    int high = -1;
    Node(const std::string & job){
        this->job = job;
    }
    ~Node(){

    }
};