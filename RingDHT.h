#pragma once
#include<cstdlib>
#include<ctime>
#include<string>
#include<cmath>
#include"FingerTable.h"
#include"AVLtree.h"
#include"FunctionUtil.h"
using namespace std;

// Dht Node where you have to change the data members
template <typename T>
struct dhtNode
{
    T id;
    RoutingTable<T>FingerTable;
    AVL<T> avlTree;
    dhtNode* next;
    dhtNode()
    {
        next = NULL;
    }
    dhtNode(T i)
    {
        id = i;
        next = NULL;
    }
};

// DHT Class Implemenation
// A circular Linklist holding Each of the Machine.
template <typename T>
class DHT {
public:
    dhtNode<T>* head, * tail;
    int machines;
    int BitSpace;
    DHT()
    {
        head = NULL;
    }
    DHT(int Machine, int Space, bool IDAssignment)
    {
        machines = Machine;
        BitSpace = Space;
        head = tail = NULL;
        assign_ids(IDAssignment);
        buildRoutingdtable();
    }
    // This function make a machine in the Ring 
    void Insert(T val)
    {
        dhtNode<T>* temp = new dhtNode<T>(val);
        if (head == NULL)
        {
            head = tail = temp;
            tail->next = head;
        }
        //Insertion at the Head Position
        else if (head->id > temp->id)
        {
            tail->next = temp;
            temp->next = head;
            head = temp;
        }
        // Insertion At the End 
        else if (tail->id < temp->id)
        {
            temp->next = head;
            tail->next = temp;
            tail = temp;
        }
        // Insertion in the Middle 
        else
        {
            dhtNode<T>* ptr = head;
            while (ptr != tail)
            {
                if (ptr->next->id > temp->id)
                    break;
                ptr = ptr->next;
            }
            temp->next = ptr->next;
            ptr->next = temp;
        }
    }

    // This function Build a Routing table for each Node
    void buildRoutingdtable()
    {
        dhtNode<T>* ptr = head, * temp, * flag;
        do
        {
            for (int i = 1; i <= BitSpace; i++)
            {
                temp = ptr;
                T str = ResolveID(ptr->id, i, BitSpace);
                bool con = false;
                dhtNode<T>* temporary = head;
                do {
                    if (str <= temporary->id) {
                        temp->FingerTable.insert(temporary);
                        con = true;
                        break;
                    }
                    temporary = temporary->next;
                } while (temporary != head);
                if (con == false)
                    temp->FingerTable.insert(head);
            }
            ptr = ptr->next;

        } while (ptr != head);
    }

    T ResolveID(T a, int Number, int Bits)
    {
        string res = "";
        int s = 0;
        string b = To_Binary_String(pow(2, Number - 1), Bits);
        int i = a.size() - 1, j = b.size() - 1;
        while (i >= 0 || j >= 0 || s == 1)
        {
            s += ((i >= 0) ? a[i] - '0' : 0);
            s += ((j >= 0) ? b[j] - '0' : 0);
            res = char(s % 2 + '0') + res;
            s /= 2;
            i--; j--;
        }
        if (a.size() != res.size())
        {
            string final = "";
            int res_len = res.size();
            for (int i = res.size() - a.size(); i < res.size(); i++)
            {
                final = final + res[i];
            }
            res = final;
        }
        return res;

    }
    dhtNode<T>* findThroughRountingTable(int MachineNo, string key)
    {
        string binary = To_Binary_String(MachineNo, BitSpace);
        SinglyListNode<T>* ptr = head->FingerTable.head;
        cout << "Machine ID form where Insertion Takes:: " << MachineNo << endl;
        dhtNode<T>* tail, * temp = head;
        do {
            tail = temp;
            temp = temp->next;
        } while (temp != head);
        // Implementation of Arriving on that machine Using FingerTable
        if (head->id != binary)
        {
            cout << "Path to Reach on the Entered Machine :: ";
            do {
                cout << To_Integer(temp->id) << "->";
                if (ptr->Pointer->id == binary)
                    break;
                while (ptr != NULL)
                {
                    if (ptr->Pointer == head || binary <= ptr->Pointer->id)
                        break;
                    temp = ptr->Pointer;
                    ptr = ptr->next;
                }
                ptr = temp->FingerTable.head;
            } while (true);

            cout << To_Integer(ptr->Pointer->id) << endl;
            temp = ptr->Pointer;
        }
        // Finding the Machine number on Which Data is to be Inserted
        binary = Gethashedvalue<T>(key, BitSpace);
        cout << "Hashed Value  of  the  key  to Reach :: " << To_Integer(binary) << endl;
        if (temp == head && binary < temp->id)
        {
            cout << "Path to Reach on machine Responsible for Hashed Key" << endl;
            cout << To_Integer(temp->id) << endl;
        }
        else
        {
            if (temp->id != binary)
            {
                ptr = temp->FingerTable.head;
                bool con, con2, con3;
                binary == tail->id ? con2 = true : con2 = false;
                binary > tail->id ? con3 = true : con3 = false;
                temp->id > binary ? con = false : con = true;
                cout << "Path to Reach on machine Responsible for Hashed Key" << endl;
                do {
                    cout << To_Integer(temp->id) << "->";
                    if (binary <= ptr->Pointer->id && con)
                        break;
                    if (con3 && ptr->Pointer == head)
                    {
                        break;
                    }
                    while (ptr != NULL)
                    {
                        if (ptr->Pointer->id <= head->next->id)
                            con = true;
                        if ((binary <= ptr->Pointer->id && con))
                            break;
                        if (con2 && ptr->Pointer->id < temp->id)
                            break;
                        if (ptr->Pointer == head && con3)
                            break;
                        temp = ptr->Pointer;
                        ptr = ptr->next;
                    }
                    ptr = temp->FingerTable.head;
                } while (true);
                cout << To_Integer(ptr->Pointer->id) << endl;
                temp = ptr->Pointer;
            }
        }
        return temp;
    }

    void InsertKeyValuePair(int MachineNo, string key, string Value)
    {
        string binary = Gethashedvalue<T>(key, BitSpace);
        dhtNode<T>* temp = findThroughRountingTable(MachineNo, key);
        // Inserting the Data on the Required 
        string c = "./textFiles/" + temp->id + ".txt";
        temp->avlTree.root = temp->avlTree.insert(binary, c, Value, temp->avlTree.root);
    }

    void deleteValue(int MachineID, string key)
    {
        T binary = Gethashedvalue<T>(key, BitSpace);
        dhtNode<T>* temp = findThroughRountingTable(MachineID, key);
        temp->avlTree.removeAVLNodeAndBalance(binary, temp->avlTree.root);
    }


    // Assigning ids and it takes a  boolean as a parameter 
    // as we want to automatically assign ids or enter from user
    void assign_ids(bool takeInput)
    {
        if (takeInput == false)
        {
            string s = "a";
            T ID;
            for (int i = 1; i <= machines; i++)
            {
                bool Con = false;
                ID = Gethashedvalue<T>(s, BitSpace);
                // Check for a Duplicate Value While Assigning Number ID
                // Regenerating the Automatic Hash in Case of Duplicate
                dhtNode<T>* flag = head;
                if (flag != NULL)
                {
                    do {
                        if (flag->id == ID)
                            Con = true;
                        flag = flag->next;
                    } while (flag != head);
                }
                if (Con)
                {
                    i--;
                }
                else {
                    Insert(ID);
                }
                string fileID = "./textFiles/" + ID + "_0.txt";
                ofstream openFile;
                openFile.open(fileID);
                openFile.close();
                s += "f";
            }
        }
        else {
            int choice;
            for (int i = 1; i <= machines; i++)
            {
                cout << "Assign ID to Machine " << i << " :: ";
                cin >> choice;
                T ID = To_Binary_String(choice, BitSpace);
                Insert(ID);
                string fileID = "./textFiles/" + ID + "_0.txt";
                ofstream openFile(fileID);
                openFile.close();
            }
        }
    }

    // Inserting A new machine to the System
    void InsertMachine(int ID)
    {
        T MachineID = To_Binary_String(ID, BitSpace);
        dhtNode<T>* temp, * ptr = head;
        bool check = true;
        //Checking if such Machine Already Exit
        do {
            if (ptr->id == MachineID)
                check = false;
            ptr = ptr->next;
        } while (ptr != head);
        // Insertion Take Place if machine doesn't already Exit
        if (check)
        {
            Insert(MachineID);
            ptr = head;
            do
            {
                if (ptr->id == MachineID)
                    break;
                ptr = ptr->next;
            } while (ptr != head);
            ofstream openFile("./textFiles/" + MachineID + "_0.txt");

            bool con = true;
            while (con)
                con = InsertAndUpdateAVL(ptr->id, ptr->next->id, (ptr->avlTree), (ptr->next->avlTree), ptr->next->avlTree.root);
            cout << "The Updated AVl of the inserted Machine ::" << To_Integer(ptr->id) << endl;
            ptr->avlTree.Display(ptr->avlTree.root);
            temp = head;
            do
            {
                temp->FingerTable.clear();
                temp = temp->next;
            } while (temp != head);
            buildRoutingdtable();
        }
        else
            cout << "Duplicate Machine are not allowed in the Ring DHT" << endl;
    }

    bool InsertAndUpdateAVL(T id1, T id2, AVL<T>& AVLtree1, AVL<T>& AVLtree2, AVLNode<T>* RootNode)
    {
        if (RootNode != NULL)
        {
            if (RootNode->key > id2 || RootNode->key <= id1)
            {
                string c = "./textFiles/" + id1 + ".txt";
                string fileName = RootNode->fileName;
                int fileNo = RootNode->lineNumber;
                string data;
                ifstream p(fileName);
                getline(p, data);
                for (int i = 1; i <= fileNo; i++)
                    getline(p, data);
                AVLtree1.root = AVLtree1.insert(RootNode->key, c, data, AVLtree1.root);
                AVLtree2.removeAVLNodeAndBalance(RootNode->key, AVLtree2.root);
                return true;
            }

            if (RootNode->right)
            {
                if (RootNode->right->key <= id1 || RootNode->right->key > id2)
                {
                    string c = "./textFiles/" + id1 + ".txt";
                    string fileName = RootNode->right->fileName;
                    int fileNo = RootNode->right->lineNumber;
                    string data;
                    ifstream p(fileName);
                    getline(p, data);
                    for (int i = 1; i <= fileNo; i++)
                        getline(p, data);
                    AVLtree1.root = AVLtree1.insert(RootNode->right->key, c, data, AVLtree1.root);
                    AVLtree2.removeAVLNodeAndBalance(RootNode->right->key, AVLtree2.root);
                    return true;
                }
            }
            if (RootNode->left)
            {
                if (RootNode->left->key > id2 || RootNode->left->key <= id1)
                {
                    string c = "./textFiles/" + id1 + ".txt";
                    string fileName = RootNode->left->fileName;
                    int fileNo = RootNode->left->lineNumber;
                    string data;
                    ifstream p(fileName);
                    getline(p, data);
                    for (int i = 1; i <= fileNo; i++)
                        getline(p, data);
                    AVLtree1.root = AVLtree1.insert(RootNode->left->key, c, data, AVLtree1.root);
                    AVLtree2.removeAVLNodeAndBalance(RootNode->left->key, AVLtree2.root);
                    return true;
                }
            }
            return false;
        }
        return false;
    }
    // Deletion of a node from the Circular list 
    void deleteCircularNode(T ID)
    {
        if (head == NULL)
            return;
        if (head->id == ID && head->next == head)
        {
            delete head;
            head = NULL;
            return;
        }
        dhtNode<T>* flag, * temp = head;
        if (head->id == ID)
        {
            while (temp->next != head)
                temp = temp->next;
            temp->next = head->next;
            delete head;
            head = temp->next;
            return;
        }

        while (temp->next != head && temp->next->id != ID)
        {
            temp = temp->next;
        }
        if (temp->next->id == ID)
        {
            flag = temp->next;
            temp->next = flag->next;
            delete flag;
        }
        else
            cout << "no such Machine found in the DHT";

    }
    // Insert a Machine to the System and Updating files Accordingly   
    bool DeleteMachine(int ID)
    {
        string MachineID = To_Binary_String(ID, BitSpace);
        bool check;
        dhtNode<T>* ptr = head;
        do
        {
            if (ptr->id == MachineID)
            {
                check = true;
                break;
            }
            ptr = ptr->next;
        } while (ptr != head);
        if (check)
        {
            bool con = true;
            //for Removal of files of that machines
            string c = "./textFiles/" + ptr->id + "_0.txt";
            char* file = new char[c.size()];
            for (int i = 0; i < c.size(); i++)
                file[i] = c[i];
            // AVL Removal and insertin in the next c
            if (ptr->avlTree.root)
            {
                while (con)
                    con = DeleteMAchineAndUpdateAvl(ptr->id, ptr->next->id, (ptr->avlTree), (ptr->next->avlTree), ptr->avlTree.root);
            }
            // Removal of the file 
            remove(file);
            delete[]file;
            T flag1 = ptr->id;
            // Clearance of the finger table.
            ptr = head;
            do {
                ptr->FingerTable.clear();
                ptr = ptr->next;

            } while (ptr != head);
            // Deletion of the Node from DHT circular link.
            deleteCircularNode(flag1);
            //Rebuilding of the Routing tables
            buildRoutingdtable();
            return true;
        }
        return false;
    }
    // Deleting a machine from the System and Updating files accordingly
    bool DeleteMAchineAndUpdateAvl(T id1, T id2, AVL<T>& AVLtree1, AVL<T>& AVLtree2, AVLNode<T>* RootNode)
    {
        if (RootNode)
        {
            string c = "./textFiles/" + id2 + ".txt";
            string fileName = RootNode->fileName;
            int fileNo = RootNode->lineNumber;
            string data;
            ifstream p(fileName);
            getline(p, data);
            for (int i = 1; i <= fileNo; i++)
                getline(p, data);
            AVLtree2.root = AVLtree2.insert(RootNode->key, c, data, AVLtree2.root);
            AVLtree1.removeAVLNodeAndBalance(RootNode->key, AVLtree1.root);
            return true;
        }
        return false;
    }
    // Searching the value Using it Key and Machine Number
    void searchNode(string key, int MachineID)
    {
        dhtNode<T>* temp = findThroughRountingTable(MachineID, key);
        T binary = Gethashedvalue<T>(key, BitSpace);
        // Searching the Value in the Reached Machine
        cout << "Value: ";
        temp->avlTree.Search(temp->avlTree.root, binary);
        cout << endl;
    }
    // Displays the Each Machine in the Ring DHT with their Machine ID.
    void Display()
    {
        if (head == NULL)
            return;
        dhtNode<T>* temp = head;
        do
        {
            cout << "Machine ID ::" << To_Integer(temp->id) << endl;
            temp = temp->next;
        } while (temp != head);
    }
    void displayRoutingTable(int machineNumber)
    {
        string machineBinary = To_Binary_String(machineNumber, BitSpace);
        dhtNode<T>* temp = head;
        do {
            if (machineBinary == temp->id)
            {
                cout << "Routing table of entered Machine ID :: ";
                temp->FingerTable.display();
                break;
            }
            temp = temp->next;
        } while (temp != head);
    }

    // This function Printing the Avl Matained on any Key
    void displayAVLTree(int machineNumber)
    {
        string machineBinary = To_Binary_String(machineNumber, BitSpace);
        dhtNode<T>* temp = head;
        do {
            if (temp->id == machineBinary)
            {
                cout << "The Machine data stored on Tree is: \n";
                temp->avlTree.Display(temp->avlTree.getRoot());
                cout << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Machine Not Found!\n";
    }
};