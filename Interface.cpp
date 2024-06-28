//
// Created by Lenya on 25.06.2024.
//
#include <iostream>
#include <vector>
#include <string>
#include "tree_realization.cpp"

using namespace std;

vector<Tree<int>*> array_trees;
vector<string> array_trees_names;
bool first = 1;
int number = 0;
void start_interface(){
    number = 0;
    if(first) {
        cout << "Welcome to tree realization\n";
        first = 0;
    }
    while(number < 1 || number > 3) {
        cout << "1 - create tree\n2 - do operation with tree\n3 - exit\n";
        cin >> number;
    }
    if(number == 1){
        int n;
        cout << "write size:\n";
        cin >> n;
        int* arr = new int[n];
        cout << "write elements:\n";
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        Tree<int>* new_tree = new Tree<int>(arr, n);
        array_trees.push_back(new_tree);
        string name;
        cout << "name:\n";
        cin >> name;
        array_trees_names.push_back(name);
        delete[] arr;
    }
    else if(number == 2){
        if(array_trees_names.size() == 0){
            cout << "no trees\n";
            start_interface();
        }
        while(number < 1 || number > array_trees_names.size()) {
            cout << "choose tree:\n";
            for (int i = 0; i < array_trees_names.size(); i++) {
                cout << i + 1<< " - " << array_trees_names[i] << "\n";
            }
            cin >> number;
        }
        Tree<int>* now_tree = array_trees[number - 1];
        cout << *now_tree << "\n";
        number = 0;
        while(number < 1 || number > 9) {
            cout << "choose operation:\n1 - Get Size\n2 - Get Root\n3 - Find\n4 - Append\n5 - Delete\n6 - Custom Print\n7 - Get Min\n8 - Get Max\n9 - Merge\n";
            cin >> number;
        }
        if(number == 1){
            cout << now_tree->Get_Size() << '\n';
        }
        else if(number == 2) {
            cout << now_tree->Get_Root()->value << "\n";
        }
        else if(number == 3){
            cout << "write value:";
            cin >> number;
            if(now_tree->Find(number) == nullptr){
                cout << "such value does not exist in the tree\n";
                start_interface();
            }
            else cout << now_tree->Find(number)->value <<'\n';
        }
        else if(number == 4){
            cout << "write value:";
            cin >> number;
            now_tree->Append(number);
            cout << '\n';
        }
        else if(number == 5){
            cout << "write value of delete node:";
            cin >> number;
            if(now_tree->Find(number) == nullptr){
                cout << "such value does not exist in the tree\n";
                start_interface();
            }
            now_tree->Delete(number);
        }
        else if(number == 6){
            cout << "write instructions(example 'KLP', 'LPK'):\n";
            char* instructions = new char[3];
            cin >> instructions;
            now_tree->Custom_Print(cout, instructions);
            cout << '\n';
        }
        else if(number == 7){
            cout << now_tree->Get_Min();
        }
        else if(number == 8){
            cout << now_tree->Get_Max();
        }
        else if(number == 9){
            int n;
            cin >> n;
            int* array = new int[n];
            for(int i = 0; i < n; i++){
                cin >> array[i];
            }
            Tree<int> second_tree(array, n);
            now_tree->Merge(second_tree);
            delete[] array;
        }
        number = 0;
    }
    else{
        exit(0);
    }
    start_interface();
}