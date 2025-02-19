//
// Created by Lenya on 25.06.2024.
//
#include <iostream>
#include <vector>
#include <string>
#include "tree_realization.cpp"

using namespace std;

double multiply_by_two_interface(double value){
    return value * 2;
}

bool is_more_than_4(double value){
    return value > 4;
}

vector<Tree<double>*> array_trees;
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
        double* arr = new double[n];
        cout << "write elements:\n";
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        Tree<double>* new_tree = new Tree<double>(arr, n);
        array_trees.push_back(new_tree);
        string name;
        cout << "name:\n";
        cin >> name;
        array_trees_names.push_back(name);
        delete[] arr;
    }
    else if(number == 2){
        number = 0;
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
        Tree<double>* now_tree = array_trees[number - 1];
        number = 0;
        while(number < 1 || number > 13) {
            cout << "choose operation:\n1 - Get Size\n2 - Get Root\n3 - Find\n4 - Append\n5 - Delete\n6 - Custom Print Array Of Tree\n7 - Get Min\n8 - Get Max\n9 - Merge\n10 - Print by Level\n11 - Sub Tree\n12 - Map(multiply by 2)\n13 - Where(is more than 4)\n";
            cin >> number;
        }
        if(number == 1){
            cout << now_tree->Get_Size() << '\n';
        }
        else if(number == 2) {
            cout << now_tree->Get_Root()->Get_value() << "\n";
        }
        else if(number == 3){
            cout << "write value:";
            double value;
            cin >> value;
            if(now_tree->Find(value) == nullptr){
                cout << "such value does not exist in the tree\n";
                start_interface();
            }
            else cout << now_tree->Find(value)->Get_value() <<'\n';
        }
        else if(number == 4){
            cout << "write value:";
            double value;
            cin >> value;
            now_tree->Append(value);
            cout << '\n';
        }
        else if(number == 5){
            cout << "write value of delete node:";
            double value;
            cin >> value;
            if(now_tree->Find(value) == nullptr){
                cout << "such value does not exist in the tree\n";
                start_interface();
            }
            now_tree->Delete(now_tree->Find(value));
        }
        else if(number == 6){
            cout << "write instructions(example 'KLP', 'LPK'):\n";
            char* instructions = new char[3];
            cin >> instructions;
            now_tree->Custom_Print_Array_Of_Tree(cout, instructions);
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
            double * array = new double[n];
            for(int i = 0; i < n; i++){
                cin >> array[i];
            }
            Tree<double> second_tree(array, n);
            now_tree->Merge(second_tree);
            delete[] array;
        }
        else if(number == 10){
            now_tree->Print_Tree_By_Level(cout);
        }
        else if(number == 11){
            cout << "write value of root node:";
            cin >> number;
            Tree<double>* new_tree = now_tree->Sub_Tree(now_tree->Find(number));
            string name;
            cout << "name of new tree:\n";
            cin >> name;
            array_trees_names.push_back(name);
            array_trees.push_back(new_tree);
        }
        else if(number == 12){
            Tree<double>* new_tree = now_tree->Map(multiply_by_two_interface);
            string name;
            cout << "name of new tree:\n";
            cin >> name;
            array_trees_names.push_back(name);
            array_trees.push_back(new_tree);
        }
        else if(number == 13){
            Tree<double>* new_tree = now_tree->Where(is_more_than_4);
            string name;
            cout << "name of new tree:\n";
            cin >> name;
            array_trees_names.push_back(name);
            array_trees.push_back(new_tree);
        }
        number = 0;
    }
    else{
        exit(0);
    }
    start_interface();
}