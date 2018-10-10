#include <bits/stdc++.h>
#define ll long long
#define degree 4
using namespace std;

// B-tree visualization
// https://www.cs.usfca.edu/~galles/visualization/BTree.html

// B-tree code
// http://see-programming.blogspot.com/2013/05/insertion-deletion-and-traversal-in-b.html

ll maxkey, minkey, searchflag;

struct BNode
{
    ll keys[degree], len;        // len=no of keys present in node , keys array
    struct BNode *child[degree]; // child pointer array
};

struct BNode *root;

//insertion functions
struct BNode *createNode(ll key, struct BNode *child);
void insertkey(ll key);
void split(ll *previous, ll val, ll nodepos, struct BNode *child, struct BNode **newNode, struct BNode *node);
void insertvalue(ll nodepos, ll key, struct BNode *child, struct BNode *tmp);
ll inserthelper(ll val, ll *previous, struct BNode **child, struct BNode *tmp);

// search functions
ll searchkey(ll key, struct BNode *tmp);

//traversal functions
void printElements(struct BNode *tmp);

//deletion functions
void deletion(ll key, struct BNode *tmp);
ll deletehelper(ll key, struct BNode *tmp);
void balanceNode(ll nodepos, struct BNode *tmp);
void findsuccessor(ll nodepos, struct BNode *tmp);
void deletevalue(ll nodepos, struct BNode *tmp);
void rightRotate(ll nodepos, struct BNode *tmp);
void leftrotate(ll nodepos, struct BNode *tmp);
void merge(ll nodepos, struct BNode *tmp);

//creation of node
struct BNode *createNode(ll key, struct BNode *child)
{
    struct BNode *newNode;
    newNode = new BNode;
    //cout << "Inside creation key=" << key << endl;
    newNode->child[0] = root;
    newNode->child[1] = child;
    newNode->keys[1] = key;
    newNode->len = 1;
    return newNode;
}

// insert value into B-tree
void insertkey(ll key)
{
    ll chk, i;
    struct BNode *child;
    //cout << "Inside insertion key=" << key << endl;
    chk = inserthelper(key, &i, &child, root);
    //cout << "inside insertkey chk=" << chk << endl;
    // if chk is "1" it will create new node.
    if (chk)
    { // new node creation.
        root = createNode(i, child);
    }
}

// split the node from mid.
void split(ll *previous, ll val, ll nodepos, struct BNode *child, struct BNode **newNode, struct BNode *node)
{
    //cout << "inside split" << endl;
    ll mid, k;
    // find mid element which will become root node of that sub-tree.
    if (minkey < nodepos)
    {
        mid = minkey + 1;
    }
    else
    {
        mid = minkey;
    }
    //cout << "inside split median - break point" << mid << endl;
    *newNode = new BNode;
    k = mid + 1;
    while (k <= maxkey) // copy all keys which are present after mid pos to newly created node.
    {
        (*newNode)->keys[k - mid] = node->keys[k];
        (*newNode)->child[k - mid] = node->child[k];
        k++;
    }
    node->len = mid;
    (*newNode)->len = maxkey - mid;
    //cout << "inside split new node len" << (maxkey - mid) << endl;
    if (nodepos <= minkey) // if cond. true insert new key to current node.
    {
        insertvalue(nodepos, val, child, node);
    }
    else // else insert new key to newly created node.
    {
        insertvalue(nodepos - mid, val, child, *newNode);
    }
    *previous = node->keys[node->len];             // mid value store in prev. that will be there in new root node.
    (*newNode)->child[0] = node->child[node->len]; // right link of root copy to left link of its right child.
    node->len--;
    //cout << "inside split node->len" << node->len << endl;
}

// add value to the node in appropriate position and do right shift if require.
void insertvalue(ll nodepos, ll key, struct BNode *child, struct BNode *tmp)
{
    ll k = tmp->len;
    //cout << "inside insertvalue key" << key << endl;
    //cout << "inside insertvalue key len" << tmp->len << endl;
    while (k > nodepos) //right shift
    {
        tmp->keys[k + 1] = tmp->keys[k];
        tmp->child[k + 1] = tmp->child[k];
        k--;
    }
    //cout << "inside insertvalue right shift " << k << endl;
    tmp->keys[k + 1] = key;
    tmp->child[k + 1] = child;
    tmp->len++;
    //cout << "inside insertvalue tmp->len" << tmp->len << endl;
}

// goto correct node (in depth find respected node then add/split node)
ll inserthelper(ll key, ll *previous, struct BNode **child, struct BNode *tmp)
{
    ll nodepos;
    if (!tmp) // If empty.
    {
        *previous = key;
        *child = NULL;
        return 1;
    }
    //cout << "inside inserthelper key=" << key << " tmp->keys[1]=" << tmp->keys[1] << endl;
    if (key < tmp->keys[1])
    { // newkey is lesser than the first key of node..
        nodepos = 0;
    }
    else
    { //find position of new key (where can it seat?--we find it from right side.)
        nodepos = tmp->len;
        //cout << "inside inserthelper" << nodepos << endl;
        while (key < tmp->keys[nodepos] && nodepos > 1)
        {
            nodepos--;
        }
        if (key == tmp->keys[nodepos])
        {
            cout << "Duplicate found" << endl;
            return 0;
        }
    }
    if (inserthelper(key, previous, child, tmp->child[nodepos]))
    {
        //cout << "inside inserthelper" << tmp->len << endl;
        if (tmp->len < maxkey) // checking whether new key can accomodate into current node.
        {                      // if yes we will insert new key to current node.
            insertvalue(nodepos, *previous, *child, tmp);
        }
        else
        { // if not ..we are required to split the node.
            split(previous, *previous, nodepos, *child, child, tmp);
            return 1;
        }
    }
    return 0;
}

// B-Tree traversal
void printElements(struct BNode *tmp)
{
    if (tmp)
    {
        ll i; // call for all childrean.
        for (i = 0; i < tmp->len; i++)
        {
            printElements(tmp->child[i]);
            cout << tmp->keys[i + 1] << " ";
        }
        printElements(tmp->child[i]); // call right child.
    }
}

// searching in B-Tree
ll searchkey(ll key, struct BNode *tmp)
{
    ll nodepos;
    if (!tmp)
    {
        return 0;
    }
    //cout<<"Inside search key="<<key<<"tmp->keys[1]="<<tmp->keys[1]<<endl;
    // find position of key.
    if (key < tmp->keys[1])
    {
        // if first position.
        nodepos = 0;
    }
    else
    {
        // find it position from right side.
        nodepos = tmp->len;
        while (nodepos > 1 && key < tmp->keys[nodepos])
        {
            nodepos--;
        }
        //cout<<"Inside search nodepos"<<nodepos<<endl;
        // if found then return else recur with its link.
        if (key == tmp->keys[nodepos])
        {
            searchflag = 1;
            return 1;
        }
    }
    searchkey(key, tmp->child[nodepos]);
    return 0;
}

void deletekey(ll key, struct BNode *tmp)
{
    struct BNode *freenode;
    if (!deletehelper(key, tmp)) // if value found then func. will return 1 else return 0
    {                            // if above function return 0 print below statement.
        cout << "Element not found" << endl;
        return;
    }
    else
    {
        // If root node len is zero then delete root node and first child will become root.
        if (tmp->len == 0)
        {
            freenode = tmp;
            tmp = tmp->child[0];
            free(freenode);
        }
    }
    root = tmp;
    return;
}

ll deletehelper(ll key, struct BNode *tmp)
{
    ll flag = 0, nodepos;
    if (tmp)
    {
        // find possible position of the key to be deleted.
        if (key < tmp->keys[1]) // If it is smaller than first key, goto left side.
        {
            nodepos = 0;
            flag = 0;
        }
        else
        {
            // else find position in the node.
            nodepos = tmp->len;
            while (nodepos > 1 && key < tmp->keys[nodepos])
            {
                nodepos--;
            }
            if (key == tmp->keys[nodepos]) // if found.
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag)
        {                                // flag=1 means element found .
            if (tmp->child[nodepos - 1]) // check whether node is internal or leaf.
            {
                findsuccessor(nodepos, tmp);
                flag = deletehelper(tmp->keys[nodepos], tmp->child[nodepos]);
                if (flag == 0)
                {
                    cout << "Element not found" << endl;
                }
            }
            else
            {
                // delete key from tmp node.(current node).
                deletevalue(nodepos, tmp);
            }
        }
        else
        { // flag=0 do recursion to go to next level to find node.
            flag = deletehelper(key, tmp->child[nodepos]);
        }
        if (tmp->child[nodepos]) // check whether child exist or not
        {                        // If exist then check its degree, if it is lower then minkey then need to balance node.
            if (tmp->child[nodepos]->len < minkey)
                balanceNode(nodepos, tmp);
        }
    }
    return flag;
}

void deletevalue(ll nodepos, struct BNode *tmp)
{
    ll i = nodepos + 1;
    while (i <= tmp->len) // left shift of all keys which are present after key which is going to delete.
    {
        tmp->keys[i - 1] = tmp->keys[i];
        tmp->child[i - 1] = tmp->child[i];
        i++;
    }
    tmp->len--; //deletion key done, now decrement len of that node.
}

void balanceNode(ll nodepos, struct BNode *tmp)
{
    if (!nodepos) // check whether delete key is on first position(nodepos=0)
    {
        if (tmp->child[1]->len > minkey) // child has enaugh keys then left rotate to balance
        {
            leftrotate(1, tmp);
        }
        else // If not then merge.
        {
            merge(1, tmp);
        }
    }
    else
    {
        if (tmp->len != nodepos) // check whether delete key is on last position
        {
            if (tmp->child[nodepos - 1]->len > minkey) // left child has enaugh keys then right rotate.
            {
                rightRotate(nodepos, tmp);
            }
            else
            {
                if (tmp->child[nodepos + 1]->len > minkey) // check same for right child.
                {
                    leftrotate(nodepos + 1, tmp);
                }
                else // if both do not have.. merge them.
                {
                    merge(nodepos, tmp);
                }
            }
        }
        else
        {
            if (tmp->child[nodepos - 1]->len > minkey)
                rightRotate(nodepos, tmp);
            else
                merge(nodepos, tmp);
        }
    }
}

void merge(ll nodepos, struct BNode *tmp)
{
    ll j = 1;
    struct BNode *right = tmp->child[nodepos];    // get right child
    struct BNode *left = tmp->child[nodepos - 1]; // get left child.

    left->len++;
    left->keys[left->len] = tmp->keys[nodepos]; // copy key from root node to left child.
    //left->child[left->len] = tmp->child[0];

    // copy all the keys from right node to left node and then delete right node.
    while (j <= right->len)
    {
        left->len++;
        left->keys[left->len] = right->keys[j];
        left->child[left->len] = right->child[j];
        j++;
    }

    j = nodepos;
    // ex-- if key deleted from first pos then need to do left shift of all keys which
    //are present after the key which is going to delete.
    while (j < tmp->len)
    {
        tmp->keys[j] = tmp->keys[j + 1];
        tmp->child[j] = tmp->child[j + 1];
        j++;
    }
    tmp->len--;
    free(right);
}

void rightRotate(ll nodepos, struct BNode *tmp)
{
    struct BNode *right = tmp->child[nodepos];    // right child
    struct BNode *left = tmp->child[nodepos - 1]; // left child
    ll j = right->len;

    // right shift all the keys of that node , then copy root node key to the fist
    // empty slot(just created because if right shift).

    while (j > 0)
    {
        right->keys[j + 1] = right->keys[j];
        right->child[j + 1] = right->child[j];
        j--;
    }
    // copy root node key to right child.
    right->keys[1] = tmp->keys[nodepos];
    right->child[1] = right->child[0];

    right->len++;
    // copy leftchild key to root node. and delete it from left child.
    tmp->keys[nodepos] = left->keys[left->len];
    right->child[0] = tmp->child[nodepos - 1]->child[left->len];
    left->len--;
    return;
}

void leftrotate(ll nodepos, struct BNode *tmp)
{
    ll j = 1;
    struct BNode *preceder = tmp->child[nodepos - 1]; // left child
    // increase length of left child and copy root key and its link to left child.

    preceder->len++;
    preceder->keys[preceder->len] = tmp->keys[nodepos];
    preceder->child[preceder->len] = tmp->child[nodepos]->child[0];

    // make right child as precedor and then copy first element and link of right child
    // to root node. then one key deleted from right child so decrease length.

    preceder = tmp->child[nodepos]; // right child
    tmp->keys[nodepos] = preceder->keys[1];
    preceder->child[0] = preceder->child[1];
    preceder->len--;

    // then left shift all keys and childs of right child of root node(new precedor).
    while (j <= preceder->len)
    {
        preceder->keys[j] = preceder->keys[j + 1];
        preceder->child[j] = preceder->child[j + 1];
        j++;
    }
    return;
}

void findsuccessor(ll nodepos, struct BNode *tmp)
{
    struct BNode *succ;
    // find successor of a key and copy it in root. then go to that successor and delete it.
    for (succ = tmp->child[nodepos]; succ->child[0] != NULL;)
        succ = succ->child[0];
    tmp->keys[nodepos] = succ->keys[1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    maxkey = degree - 1;
    minkey = maxkey / 2;

    //cout << "minKey=" << minkey << endl;
    //cout << "maxKey=" << maxkey << endl;

    ll value, choice;
    do
    {
        cout << "Press 1 to insert" << endl;
        cout << "Press 2 to search" << endl;
        cout << "Press 3 to delete" << endl;
        cout << "Press 4 to print" << endl;
        cout << "Press 0 to quit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter Value" << endl;
            cin >> value;
            insertkey(value);
        }
        else if (choice == 2)
        {
            cout << "Enter Value" << endl;
            cin >> value;
            searchflag = 0;
            searchkey(value, root);
            if (searchflag == 0)
                cout << "Element not found" << endl;
            else
                cout << "Element found" << endl;
        }
        else if (choice == 3)
        {
            cout << "Enter Value" << endl;
            cin >> value;
            deletekey(value, root);
        }
        else if (choice == 4)
        {
            printElements(root);
            cout << endl;
        }
        else if (choice != 0)
        {
            cout << "Wrong choice" << endl;
        }
    } while (choice != 0);
    cout << "Thank You!!!" << endl;
    return 0;
}