#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef std::pair<int, int> termpair;
bool comparator_term( const termpair& l, const termpair& r); 

bool comparator_term(const termpair& l, const termpair& r)
{
    return l.second > r.second;
}
/**
 * 打印一个vector
 */
template<typename T>
void printVector(vector<T> &arr)
{
    size_t length = arr.size();
    for (size_t i = 0; i != length; ++i) {
        std::cout << arr.at(i) << '\n';
    }
}

/*
 * 将字符串打散到数组中
 */
template<typename T>
int explode(const std::string &str, const std::string delimiter, std::vector<T> &store)
{
    int strlen = str.length();
    int dellen = delimiter.length();
    if (dellen==0 || strlen == 0) {
        return -1;//no change
    }
    int i=0; 
    int k=0;
    T t;
    while( i<strlen ) {
        int j=0;
        while (i+j<strlen && j<dellen && str[i+j]==delimiter[j])
            j++;
        if (j==dellen){ //found delimiter 
            stringstream stream;
            stream << str.substr(k, i-k);
            stream >> t;
            store.push_back(t);
            i+=dellen;
            k=i;
        } else {
            i++;
        }
    }
    stringstream stream;
    stream<<str.substr(k, i-k);
    stream>>t;
    store.push_back(t);
    return store.size(); 
}

template<typename T>
int explode(const std::string& str, const char& ch, std::vector<T> &result)
{
    string next = "";
    T t;
    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (next.length() > 0) {
                // Add them to the result vector
                stringstream stream;
                stream << next;
                stream >> t;
                result.push_back(t);
                next = "";
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (next.size() > 0) {
        stringstream stream;
        stream << next;
        stream >> t;
        result.push_back(t);
    }
    return result.size();
}



#endif //UTIL_H

/**
 ＊  将字符串打散到vector中,分隔符是另一个字符串
 */
/*template<typename T>
int explode(std::string& str, std::string delimiter, std::vector<T> &store)
{
    int strlen = str.length();
    int dellen = delimiter.length();
    if (dellen==0 || strlen == 0) {
        return -1;//no change
    }
    int i=0; 
    int k=0;
    T t;
    while( i<strlen ) {
        int j=0;
        while (i+j<strlen && j<dellen && str[i+j]==delimiter[j])
            j++;
        if (j==dellen){ //found delimiter 
            std::stringstream stream;
            stream<<str.substr(k, i-k);
            stream>>t;
            store.push_back(t);
            i+=dellen;
            k=i;
        } else {
            i++;
        }
    }
    std::stringstream stream;
    stream<<str.substr(k, i-k);
    stream>>t;
    store.push_back(t);
    return store.size(); 
}
*/
/**
 ＊  将字符串打散到vector中,分隔符是一个字符
 */
/*
template<typename T>
int explode(const std::string& str, const char ch, std::vector<T> &result) 
{
    string next = "";
    T t;
    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (next.length() > 0) {
                // Add them to the result vector
                stringstream stream;
                stream << next;
                stream >> t;
                result.push_back(t);
                next = "";
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    return result.size();
}
*/
