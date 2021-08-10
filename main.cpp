#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"RingDHT.h"
using namespace std;

int main()
{
    int IdentifierSpaceBit, Machine, chioce;
    bool Con1 = true;
    char Con2;
    cout << "___________________________________________________" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "###################################################" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%          Distributed Hash Table Search          %" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "###################################################" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "___________________________________________________" << endl;
    cout << "Specify the number of Bit in Identifer Space ::";
    cin >> IdentifierSpaceBit;
    cout << "Enter the number of machine in   the   Space ::";
    cin >> Machine;
    cout << "___________________________________________________" << endl;
    cout << "Press(Any-Key) to Assign ID Manually to Machines\n";
    cout << "Press(0) to Assign ID for Automically Assignment\n";
    cout << "___________________________________________________" << endl;
    cin >> Con2;
    cout << "___________________________________________________" << endl;
    bool valid;
    Con2 == '0' ? valid = false : valid = true;
    DHT<string> obj(Machine, IdentifierSpaceBit, valid);
    do
    {
        cout << "___________________________________________________" << endl;
        cout << "  Choice the desired Option from the Manu   Given  " << endl;
        cout << "___________________________________________________" << endl;
        cout << "1- Press Option(1) to Add the    key    Value  Pair" << endl;
        cout << "2- Press Option(2) to Delete a value from a Machine" << endl;
        cout << "3- Press Option(3) to  Display  the  IDS in the DHT" << endl;
        cout << "4- Press Option(4) to Print the Rounting     table " << endl;
        cout << "5- Press Option(5) to Print the AVL tree Maintained" << endl;
        cout << "6- Press Option(6) to Add new machine to the System" << endl;
        cout << "7- Press Option(7) to delete a machine from  System" << endl;
        cout << "8- Press Option(8) to Search a   Value  Using   Key" << endl;
        cout << "9- Press Option(9) to delete machines and terminate" << endl;
        cout << "___________________________________________________" << endl;
        cin >> chioce;
        cout << "___________________________________________________" << endl;
        switch (chioce)
        {
        case 1:
        {
            int ID;
            string key;
            string value;
            cout << "###################################################" << endl;
            cout << "Enter the Machine ID form insertion take place::";
            cin >> ID;
            cout << "Enter the Key   to Insert  on     the  Machine::";
            cin >> key;
            cout << "Enter the Value to Insert  on     the  Machine::";
            cin >> value;
            cout << "###################################################" << endl;
            obj.InsertKeyValuePair(ID, key, value);
            cout << "###################################################" << endl;
            break;
        }
        case 2:
        {
            int MId;
            string key;
            cout << "###################################################" << endl;
            cout << "Enter Machine-ID from where Deletion Takes Place ::";
            cin >> MId;
            cout << "Enter the key  to  be  removed  from  the System ::";
            cin >> key;
            obj.deleteValue(MId, key);
            cout << "###################################################" << endl;

            break;
        }
        case 3:
        {
            cout << "###################################################" << endl;
            obj.Display();
            cout << "###################################################" << endl;
            break;
        }
        case 4:
        {
            int mn;
            cout << "###################################################" << endl;
            cout << "Enter machine ID whose Routing table to be Printed :: ";
            cin >> mn;
            obj.displayRoutingTable(mn);
            cout << "###################################################" << endl;
            break;
        }
        case 5:
        {
            int mn;
            cout << "###################################################" << endl;
            cout << "Enter Machine-ID whose AVL you want to Printed::";
            cin >> mn;
            obj.displayAVLTree(mn);
            cout << "###################################################" << endl;
            break;
        }
        case 6:
        {
            int mId;
            cout << "###################################################" << endl;
            cout << "Enter Machine ID, which you want to Insert :: ";
            cin >> mId;
            obj.InsertMachine(mId);
            cout << "###################################################" << endl;
            break;
        }
        case 7:
        {
            int mn;
            cout << "###################################################" << endl;
            cout << "Enter Machine ID, Which you want to delete :: ";
            cin >> mn;
            obj.DeleteMachine(mn);
            cout << "###################################################" << endl;
            break;
        }
        case 8:
        {
            string k;
            int mID;
            cout << "###################################################" << endl;
            cout << "Enter Key you  wanted  to  search  in DHT Ring ::";
            cin >> k;
            cout << "Enter the machine ID from where you want Search::";
            cin >> mID;
            obj.searchNode(k, mID);
            cout << "###################################################" << endl;
            break;
        }
        case 9:
        {
            //The destructor will be atumatically called on return 0 call
            return 0;
        }

        default:
        {
            cout << "Enter the   Correct  Choice   from   the Given Manu" << endl;
            cout << "___________________________________________________" << endl;
        }
        }
    } while (true);
    return 0;
}