//
// Created by Lenya on 26.06.2024.
//
#include <assert.h>
#include <sstream>

double multiply_by_two(double value){
    return value*2;
}

bool is_less_than_six(double value){
    return value<6;
}

void test(){
    double* arr = new double[7]{1, 5, 6, 1, 24, 5, 3};
    double* sort_arr = new double[7]{1, 1, 3, 5, 5, 6, 24};
    Tree<double> tree(arr, 7);

    for(int i = 0; i < 7; i++){
        tree.Delete(tree.Find(arr[i]));
    }
    for(int i = 0; i < 7; i++){
        tree.Append(arr[i]);
    }

    assert(tree.Get_Root()->Get_value() == 1);
    assert(tree.Get_Root()->Get_left()->Get_value() == 1);
    assert(tree.Get_Root()->Get_right()->Get_value() == 5);
    assert(tree.Get_Root()->Get_right()->Get_parent()->Get_value() == 1);
    assert(tree.Find(5)->Get_right()->Get_value() == 6);
    assert(tree.Get_Max() == 24);
    assert(tree.Get_Min() == 1);

    tree.Delete(tree.Find(1));

    assert(tree.Get_Size() == 6);

    std::ostringstream out;
    tree.Custom_Print(out, "LKP");

    assert(out.str() == "1 3 5 5 6 24 ");

    tree.Append(1);
    double* tree_arr = tree.Get_Array();

    for(int i = 0; i < 7; i++){
        assert(tree_arr[i] == sort_arr[i]);
    }

    Tree<double>* sub_tree = tree.Sub_Tree(tree.Get_Root()->Get_left());

    for(int i = 0; i < 2; i++){
        assert(sort_arr[i] == sub_tree->Get_Array()[i]);
    }

    sub_tree->Merge(tree);
    double* sub_tree_arr = sub_tree->Get_Array();

    for(int i = 0; i < 2; i++){
        assert(sub_tree_arr[i] == 1);
    }
    for(int i = 2; i < 9; i++){
        assert(sub_tree_arr[i] == sort_arr[i - 2]);
    }

    Tree<double>* map_tree = tree.Map(multiply_by_two);
    double* map_tree_arr = map_tree->Get_Array();

    for(int i = 0; i < 7; i++){
        assert(map_tree_arr[i] == 2 * sort_arr[i]);
    }

    Tree<double>* where_tree = tree.Where(is_less_than_six);
    double* where_tree_arr = where_tree->Get_Array();
    for(int i = 0; i < 7; i++){
        if(sort_arr[i] >= 6){
            break;
        }
        assert(where_tree_arr[i] == sort_arr[i]);
    }

    delete sub_tree;
    delete map_tree;
    delete where_tree;
    delete[] where_tree_arr;
    delete[] map_tree_arr;
    delete[] sub_tree_arr;
    delete[] tree_arr;
    delete[] arr;
}
