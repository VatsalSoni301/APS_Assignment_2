#include <bits/stdc++.h>
#define ll long long
#define maxkey 2
using namespace std;

ll minkey, searchflag;

struct BNode
{
    ll keys[maxkey + 1], count;      // count=no of keys present in node , keys array
    struct BNode *child[maxkey + 1]; // child pointer array
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
    newNode->count = 1;
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
    node->count = mid;
    (*newNode)->count = maxkey - mid;
    //cout << "inside split new node count" << (maxkey - mid) << endl;
    if (nodepos <= minkey) // if cond. true insert new key to current node.
    {
        insertvalue(nodepos, val, child, node);
    }
    else // else insert new key to newly created node.
    {
        insertvalue(nodepos - mid, val, child, *newNode);
    }
    *previous = node->keys[node->count];             // mid value store in prev. that will be there in new root node.
    (*newNode)->child[0] = node->child[node->count]; // right link of root copy to left link of its right child.
    node->count--;
    //cout << "inside split node->count" << node->count << endl;
}

// add value to the node in appropriate position and do right shift if require.
void insertvalue(ll nodepos, ll key, struct BNode *child, struct BNode *tmp)
{
    ll k = tmp->count;
    //cout << "inside insertvalue key" << key << endl;
    //cout << "inside insertvalue key count" << tmp->count << endl;
    while (k > nodepos) //right shift
    {
        tmp->keys[k + 1] = tmp->keys[k];
        tmp->child[k + 1] = tmp->child[k];
        k--;
    }
    //cout << "inside insertvalue right shift " << k << endl;
    tmp->keys[k + 1] = key;
    tmp->child[k + 1] = child;
    tmp->count++;
    //cout << "inside insertvalue tmp->count" << tmp->count << endl;
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
        nodepos = tmp->count;
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
        //cout << "inside inserthelper" << tmp->count << endl;
        if (tmp->count < maxkey) // checking whether new key can accomodate into current node.
        {                        // if yes we will insert new key to current node.
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
        for (i = 0; i < tmp->count; i++)
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
        nodepos = tmp->count;
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
        // If root node count is zero then delete root node and first child will become root.
        if (tmp->count == 0)
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
            nodepos = tmp->count;
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
        if (tmp->child[nodepos])
        {
            if (tmp->child[nodepos]->count < minkey)
                balanceNode(nodepos, tmp);
        }
    }
    return flag;
}

void deletevalue(ll nodepos, struct BNode *tmp)
{
    ll i = nodepos + 1;
    while (i <= tmp->count) // left shift of all keys which are present after key which is going to delete.
    {
        tmp->keys[i - 1] = tmp->keys[i];
        tmp->child[i - 1] = tmp->child[i];
        i++;
    }
    tmp->count--; //deletion key done, now decrement count of that node.
}

void balanceNode(ll nodepos, struct BNode *tmp)
{
    if (!nodepos)
    {
        if (tmp->child[1]->count > minkey)
        {
            leftrotate(1, tmp);
        }
        else
        {
            merge(1, tmp);
        }
    }
    else
    {
        if (tmp->count != nodepos)
        {
            if (tmp->child[nodepos - 1]->count > minkey)
            {
                rightRotate(nodepos, tmp);
            }
            else
            {
                if (tmp->child[nodepos + 1]->count > minkey)
                {
                    leftrotate(nodepos + 1, tmp);
                }
                else
                {
                    merge(nodepos, tmp);
                }
            }
        }
        else
        {
            if (tmp->child[nodepos - 1]->count > minkey)
                rightRotate(nodepos, tmp);
            else
                merge(nodepos, tmp);
        }
    }
}

void merge(ll nodepos, struct BNode *tmp)
{
    ll j = 1;
    struct BNode *right = tmp->child[nodepos];
    struct BNode *left = tmp->child[nodepos - 1];

    left->count++;
    left->keys[left->count] = tmp->keys[nodepos];
    //left->child[left->count] = tmp->child[0];

    while (j <= right->count)
    {
        left->count++;
        left->keys[left->count] = right->keys[j];
        left->child[left->count] = right->child[j];
        j++;
    }

    j = nodepos;
    while (j < tmp->count)
    {
        tmp->keys[j] = tmp->keys[j + 1];
        tmp->child[j] = tmp->child[j + 1];
        j++;
    }
    tmp->count--;
    free(right);
}

void rightRotate(ll nodepos, struct BNode *tmp)
{
    struct BNode *next = tmp->child[nodepos];
    ll j = next->count;

    while (j > 0)
    {
        next->keys[j + 1] = next->keys[j];
        next->child[j + 1] = next->child[j];
    }

    next->keys[1] = tmp->keys[nodepos];
    next->child[1] = next->child[0];
    next->count++;
    next = tmp->child[nodepos - 1];
    tmp->keys[nodepos] = next->keys[next->count];
    tmp->child[nodepos] = next->child[next->count];
    next->count--;
    return;
}

void leftrotate(ll nodepos, struct BNode *tmp)
{
    ll j = 1;
    struct BNode *preceder = tmp->child[nodepos - 1];

    preceder->count++;
    preceder->keys[preceder->count] = tmp->keys[nodepos];
    preceder->child[preceder->count] = tmp->child[nodepos]->child[0];

    preceder = tmp->child[nodepos];
    tmp->keys[nodepos] = preceder->keys[1];
    preceder->child[0] = preceder->child[1];
    preceder->count--;

    while (j <= preceder->count)
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

    for (succ = tmp->child[nodepos]; succ->child[0] != NULL;)
        succ = succ->child[0];
    tmp->keys[nodepos] = succ->keys[1];
}

int main()
{
    ios_base::sync_with_stdio(false);
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