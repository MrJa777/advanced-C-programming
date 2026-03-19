#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int main()
{
    // note: there are many clever usages of this set/map
    // that you can learn by looking at top coder's codes
    // note, we don't have to use .clear() if we have just initialized the set/map
    set<int> used_values;    // used_values.clear();
    map<string, int> mapper; // mapper.clear();

    // suppose we enter these 7 name-score pairs below
    /*
    john 78
    billy 69
    andy 80
    steven 77
    felix 82
    grace 75
    martin 81
    */
    mapper["john"] = 78;
    used_values.insert(78);
    mapper["billy"] = 69;
    used_values.insert(69);
    mapper["andy"] = 80;
    used_values.insert(80);
    mapper["steven"] = 77;
    used_values.insert(77);
    mapper["felix"] = 82;
    used_values.insert(82);
    mapper["grace"] = 75;
    used_values.insert(75);
    mapper["martin"] = 81;
    used_values.insert(81);

    // then the internal content of mapper MAY be something like this:
    // re-read balanced BST concept if you do not understand this diagram
    // the keys are names (string)!
    //                        (grace,75)
    //           (billy,69)               (martin,81)
    //     (andy,80)   (felix,82)    (john,78)  (steven,77)

    // iterating through the content of mapper will give a sorted output
    // based on keys (names)
    for (auto &[key, value] : mapper) // C++17 style
        cout << key << " " << value << "\n";

    // map can also be used like this
    cout << "steven's score is " << mapper["steven"] 
         << ", grace's score is " << mapper["grace"] << "\n";
    cout << "==================\n";

    // interesting usage of lower_bound and upper_bound
    // display data between ["f".."m") ('felix' is included, 'martin' is excluded)
    for (auto it = mapper.lower_bound("f"); it != mapper.lower_bound("m"); it++)
        cout << it->first << " " << it->second << "\n";

    // the internal content of used_values MAY be something like this
    // the keys are values (integers)!
    //                 (78)
    //         (75)            (81)
    //     (69)    (77)    (80)    (82)

    // O(log n) search, found
    cout << *used_values.find(77) << "\n";
    // returns [69, 75] (these two are before 77 in the inorder traversal of this BST)
    for (auto it = used_values.begin(); it != used_values.lower_bound(77); it++)
        cout << *it << ",";
    cout << "\n";
    // returns [77, 78, 80, 81, 82] (these five are equal or after 77 in the inorder traversal of this BST)
    for (auto it = used_values.lower_bound(77); it != used_values.end(); it++)
        cout << *it << ",";
    cout << "\n";
    // O(log n) search, not found
    if (used_values.find(79) == used_values.end())
        cout << "79 not found\n";

    return 0;
}
