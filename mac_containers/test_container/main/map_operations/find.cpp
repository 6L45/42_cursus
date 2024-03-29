#include "../main.hpp"

int main()
{
    // create a map
    // std::map<int, int> myMap;
    map<int, int> myMap2;
    
    // create a Tree
    // pair<int, int> p1(1, 1);
    // test size
    // std::cout << "size: " << myMap2.size() << std::endl;
    // std::cout << "max_size: " << myMap2.max_size() << std::endl;

    // myMap2._tree.print2D();

    // unsigned int i = 0;

    // test find function
    pair<int, int> p2(1, 3);
    myMap2.insert(p2);
    // myMap2.print();
    pair<int, int> p3(2, 4);
    myMap2.insert(p3);
    std::cout << "---------------" << std::endl;
    // myMap2.print();
    std::cout << "---------------" << std::endl;
    // create a iterator

    // test find function
    unsigned int v = 1;
    std::cout << "find " << v << " : " <<  (*(myMap2.find(v))).second << std::endl;

    // test iterator
    // map<int, int>::iterator it = myMap2.begin();
    // std::cout << (*(it)).first << " " << (*it).second << std::endl;

    v = 2;
    std::cout << "find " << v << " : " <<  (*(myMap2.find(v))).second << std::endl;

    std::cout << "---------------" << std::endl;
    // std::cout << "end-node : " <<  (*(myMap2.end())).second << std::endl;

    // ft::map<int, int>::iterator it = myMap2.find(2);
    // std::cout << "find : 2,4  " << std::endl;
    // std::cout << "it->first = " << (*(it)).first << "  it->second = " << (*(it)).second << std::endl;
    // ft::map<int,int>::iterator d = myMap2.begin();
    // ft::Tree<ft::pair<int, int> >::Node *node = myTree._tree.find(p2.first, myTree._tree._root);

    // myMap.insert(std::pair<int, int>(1, 10));
    // myMap.insert(std::pair<int, int>(2, 20));
    // myMap.insert(std::pair<int, int>(2, 30));
}

// int main()
// {
//     std::string *str;
//     new (str) std::string("hello");
//     for (int i = 0; i < 9; i++)
//         std::cout << str[i] << std::endl;
// }