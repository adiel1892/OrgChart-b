#include <string>
#include <vector>
class Node{
    public:
    std::string job;
    std::vector<Node*> subs;
    int high = -1;
    std::string father = "root";
    Node(const std::string & job) : job(job){};
};