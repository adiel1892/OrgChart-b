#include <string>
#include <vector>
// Each person in the organization is a node
// The person a has job title , vector of childrens , his height in the tree and a father.
class Node{
    public:
    std::string job;
    std::vector<Node*> subs;
    int high = -1;
    std::string father = "root";
    Node(const std::string & job) : job(job){};
};