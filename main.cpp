#include<iostream>

#include"vector.hpp"

int main()
{
    std::cout << "For Integer data_type" << std::endl;
 
    Lib::Vector<int> v(6);
    v.push(5);
    v.push(6);
    v.push(7);
    v.push(8);
    v.push(9);
    v.push(10);
    v.push(11);
    v.push(12);
 
    // Function called to display element in
    // vector in v
    std::cout << "Element in vector v : < ";
    for (auto e = v.begin(); e < v.end(); e++) std::cout << *e << ' ';
    std::cout << '>' << std::endl;
 
    // Print the size of vector v
    std::cout << "size: " << v.size() << std::endl;
 
    // Print Element at index 2
    std::cout << "v[2]: " << v[2] << '\n';
    std::cout << "v.at(2): " << v.at(2) << '\n';
 
    // Pop an element and print it
    std::cout << "Popped Element: " << v.pop() << '\n';
    std::cout << "< ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '>' << std::endl;
 
    std::cout << std::endl;
 
    std::cout << "For Char data_type" << std::endl;
 
    Lib::Vector<char> c;
    c.push('a');
    c.push('b');
    c.push('c');
    c.push('d');
    c.push('e');
    c.push('f');
    c.push('g');
    c.push('h');
 
    // Function called to display element in
    // vector in c
    std::cout << "Element in vector c : < ";
    for (auto e = c.begin(); e < c.end(); e++) std::cout << *e << ' ';
    std::cout << '>' << std::endl;
 
    // Print the size of vector c
    std::cout << "size: " << c.size() << '\n';
 
    // Print Element at index 2
    std::cout << "c[2]: " << c[2] << '\n';
    std::cout << "c.at(2): " << c.at(2) << '\n';
 
    // Pop an element and print it
    std::cout << "pop: " << c.pop(2) << '\n';
    std::cout << "push: z" << c.push('z', 3) << '\n';
    // Function called to display element in
    // vector in c
    std::cout << "Element in vector c : < ";
    for (auto e = c.begin(); e < c.end(); e++) std::cout << *e << ' ';
    std::cout << '>' << std::endl;
    return 0;
}