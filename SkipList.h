//
// Created by Илья on 018 18.10.19.
//
#include "Node.h"
#include <iostream>
using std::cout;
using std::endl;
#ifndef SKIP_LIST_IMPLEMENTATION_SKIPLIST_H
#define SKIP_LIST_IMPLEMENTATION_SKIPLIST_H

class SkipList
{
private:
    int MAXLVL;  // max level
    float P;  //  Probability of each level existence
    int level;  // current existing max level
    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    void insertElement(int);
    void displayList();
    bool Search(int);
    void Remove(int);
};

SkipList::SkipList(int MAXLVL, float P)
{
    level = 0;
    this->MAXLVL = MAXLVL;
    this->P = P;
    header = new Node(-1, MAXLVL);
}

// Return random level
int SkipList::randomLevel()
{
    int lvl = 0;
    float r = (float)rand()/RAND_MAX;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
}


void SkipList::insertElement(int key)
{
    Node *current = header;

    // create update array and initialize it
    // elements in update array will be changed
    // they will obtain new pointers
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    /* reached level 0 and forward pointer to
       right, which is desired position to
       insert key.
    */
    current = current->forward[0];

    /* current == NULL   means we reached the end of level
       current->key != key   because we don't support repeating values */
    if (current == NULL || current->key != key)
    {
        // Generate a random level for node
        int rlevel = randomLevel();

        /* If rLevel is greater than current level, initialize (rLevels - level) upper levels with header pointer */
        if (rlevel > level)
        {
            for (int i = level + 1; i < rlevel + 1;i++)
                update[i] = header;

            level = rlevel;  // change current level
        }

        Node* n = new Node(key, rlevel);  // Create node for inserting

        /* Set the right pointers in different levels */
        for (int i = 0; i <= rlevel; i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }
}

// Display skip list level wise
void SkipList::displayList()
{
    cout<<"\nSkip List"<<"\n";
    for (int i = 0; i <= level; i++)
    {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key<<" ";
            node = node->forward[i];
        }
        cout << endl;
    }
}


bool SkipList::Search(int value)
{
    Node* current = header;
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] && current->forward[i]->key < value)
            current = current->forward[i];
    }
    current = current->forward[0];
    return current && current->key == value;
}

void SkipList::Remove(int key)
{
    Node *current = header;
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];

    /* if the element is found and if it equal to given value*/
    if (current != NULL && current->key == key)
    {
        /* Set the right pointers in different levels */
        for (int i=0;i<=level;i++)
        {
            if(update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }
        /* If deleted node had the greatest level in list, decrease level */
        while(level > 0 && header->forward[level] == 0)
            level--;
    }
}

#endif //SKIP_LIST_IMPLEMENTATION_SKIPLIST_H
