#include "OrgChart.hpp"
using namespace std;
using namespace ariel;
#include "doctest.h"


TEST_CASE("test_1"){
    OrgChart org;
    CHECK(org.root == nullptr);
    org.add_root("ONE");
    CHECK(org.root->job == "ONE");
    org.add_sub("ONE" , "TWO");
    CHECK(org.root->job == "ONE");
    org.add_sub("ONE" , "THREE");
    org.add_sub("ONE" , "FOUR");
    org.add_sub("TWO" , "FIVE");
    org.add_sub("TWO" , "SIX");
    org.add_sub("FOUR" , "SEVEN");
    org.add_sub("FOUR" , "EIGHT");
    org.add_sub("EIGHT" , "NINE");
    org.add_sub("FIVE" , "TEN");
    CHECK(org.root->job == "ONE");
    //          ONE
    //           |
    //          TWO - THREE - FOUR
    //           |              |
    //          FIVE - SIX    SEVEN - EIGHT
    //           |                      |
    //          TEN                    NINE
    CHECK(org.begin_level_order().getNodes().size() == 10);
    CHECK(org.begin_preorder().getNodes().size() == 10);
    CHECK(org.begin_reverse_order().getNodes().size() == 10);

    vector<string> BEGIN_LEVEL_ORDER = {"ONE" , "TWO" , "THREE" , "FOUR" , "FIVE" , "SIX" , "SEVEN" , "EIGHT" , "TEN" , "NINE"};
    unsigned int i = 0;
    for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
        CHECK(*it == BEGIN_LEVEL_ORDER.at(i++));
    }
    unsigned int j = 0;
    vector<string> REVERSE_LEVEL_ORDER = {"TEN" , "NINE" , "FIVE" , "SIX" , "SEVEN" , "EIGHT" , "TWO" , "THREE" , "FOUR" , "ONE"};
    for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
        CHECK(*it == BEGIN_LEVEL_ORDER.at(j++));
    }
    unsigned int k = 0;
    vector<string> PRE_ORDER = {"ONE" , "TWO" , "FIVE" , "TEN" , "SIX" , "THREE" , "FOUR" , "SEVEN" , "EIGHT" , "NINE"};
    for (auto it=org.begin_preorder(); it!=org.end_preorder(); ++it) {
        CHECK(*it == PRE_ORDER.at(k++));
    }
    // check not printing node twice
    vector<Node*> vec_begin = org.begin_level_order().getNodes();
    for(unsigned int i = 0; i < vec_begin.size() - 1; i++){
        cout << vec_begin.at(i)->job << " -- ";
        CHECK(vec_begin.at(i) != vec_begin.at(i + 1));
    }

    vector<Node*> vec_reverse = org.begin_reverse_order().getNodes();
    for(unsigned int i = 0; i < vec_reverse.size() - 1; i++){
        cout << vec_reverse.at(i)->job << " -- ";
        CHECK(vec_reverse.at(i) != vec_reverse.at(i + 1));
    }

    vector<Node*> vec_pre = org.begin_preorder().getNodes();
    for(unsigned int i = 0; i < vec_pre.size() - 1; i++){
        cout << vec_pre.at(i)->job << " -- ";
        CHECK(vec_pre.at(i) != vec_pre.at(i + 1));
    }
    
}