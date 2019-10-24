//
// Created by Илья on 018 18.10.19.
//

#ifndef SKIP_LIST_IMPLEMENTATION_NODE_H
#define SKIP_LIST_IMPLEMENTATION_NODE_H
#include <bits/stdc++.h>

class Node
{
public:
    int key;

    Node **forward;  // Pointers to different levels
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;
    forward = new Node*[level+1];
    memset(forward, 0, sizeof(Node*)*(level+1));
};

#endif //SKIP_LIST_IMPLEMENTATION_NODE_H
