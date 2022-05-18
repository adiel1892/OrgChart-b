#include <string>
#include <vector>
class Node{
    public:
    std::string job;
    std::vector<Node*> subs;
    int high = -1;
    std::string father = "root";
    Node(const std::string & job) : job(job){};
    Node(const Node & other) : job(other.job) , father(other.father) , high(other.high) , subs(other.subs){};
    ~Node(){

    }
};