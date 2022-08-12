//Square Shaped Phantom Concept!.

#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <string>
#define OFFSET 50
#define v 11
#define total_packet_sending 5
#include <set>
#include <random>
#include <ostream>
using namespace std;

struct package_data{
    int k =  2048;
    long double e_elec = 50 * pow(10,-9);
    long double e_amp = 100 * pow(10,-12);
    string data = NULL;
    
};


class packs{
public:
    
        int k =  2048;
        long double e_elec = 50 * pow(10,-9);
        long double e_amp = 100 * pow(10,-12);
        string data = NULL;
    
    
};
typedef struct package_data pack;
struct node{
    int x;
    int y;
    int ID;
    long double power;
    struct package_data *package;
    packs packages;
    int im_attacker = 0;
    int index_1,index_2;
    vector<int> neighbours;
    vector<node> phantom_sqaure,closure_neighbour,equal_neighbour,forther_neighbour;
    
    bool operator<(const node& t) const
    {
        return (this->ID < t.ID);
    }

};

void set_packdata(struct node *Node){
    Node->package->k = 2048;
    Node->package->data = "\0";
    Node->package->e_elec = 50 * pow(10,-9);
    Node->package->e_amp = 100 * pow(10,-12);
}
void power_reduce(node *current){
    if(current->package == NULL){
        current->package = (pack *)malloc(sizeof(pack));
        set_packdata(current);
    }
    long double consumption = (current->package->e_elec * current->package->k) + (current->package->e_amp * current->package->k * 50);
    current->power = current->power - consumption;
}
void power_reduction(node *current,node *current2){
    if(current->package == NULL){
        current->package = (pack *)malloc(sizeof(pack));
        set_packdata(current);
    }
    if(current2->package == NULL){
        current2->package = (pack *)malloc(sizeof(pack));
        set_packdata(current2);
    }
    cout << "Initially...."<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    cout << "The power of node "<<current2->ID<<" is "<< current->power<<endl;
    cout << "Working" << endl;
    if(current2->package == NULL) cout << "There is no package!" << endl;
    else cout << "The package exist" << endl;
    if(current->package == NULL) cout << "Node1 has 0 package"<<endl;
    else cout << "Node1 package exist" << endl;
    long double consumption = (current->package->e_elec * current->package->k) + (current->package->e_amp * current->package->k * 50);
    
    cout << "Elec is:"<< current->package->e_elec << endl;
    cout << "S1:"<<(current->package->e_elec * current->package->k)<<endl;
    cout << "S2:"<<(current->package->e_amp * current->package->k * 50)<<endl;
    cout << (current->package->e_elec * current->package->k) + (current->package->e_amp * current->package->k * pow(50,2)) << endl;
    if(current2->ID == -1){
        current->power = current->power - consumption;
        cout << "After......."<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    return;
    }
    current->power = current->power - consumption;
    current2->power = current2->power - consumption;
    cout << "After......"<<endl;
    cout << "The power of node "<<current->ID<<" is "<< current->power<<endl;
    cout << "The power of node "<<current2->ID<<" is "<< current->power<<endl;
}


class board{
    public:
        int offset = 50;
        struct node *array[11][11];
        int m = 10;
        int source_x,source_y,source_id;//To get the equal,forther,closer neighbours.
        int Packets_received_counts = 0;
        int Packets_cancelled_counts = 0;
        int attacker_id = -1;
        vector<int> attacker_paths;
        std::set<node> phantom1,phantom2;
        fstream data_file;
        int tot_inter_nodes = 0;
        int won_packs = 0,lost_packs = 0;

    board(){
        cout << "Constructor working..." << m << endl;
        
    if(m%2 == 0){
        m = m+1;
        }
        int max_val = offset * (m/2);
        int cnt = 1;
        for(int i = 0;i<m;i++){
        int col = offset * (m/2);
        //setting co-ordinates
        for(int j = 0;j<m;j++){
            array[i][j] = (struct node *)malloc(sizeof(struct node));
            array[i][j]->ID = cnt;
            cnt++;
            if(i < (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = max_val;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = max_val;
                    col = col - offset;
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = max_val;
                    col = col + offset;
                }
                
            }else if(i == (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = 0;
                    array[i][j]->ID = -1;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = 0;
                    col = col - offset;
                    
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = 0;
                    col = col + offset;
                    
                }
            }else if(i > (m/2)){
                if(j == (m/2)){
                    array[i][j]->x = 0;
                    array[i][j]->y = -1 * max_val;
                    col = offset;
                }else if(j < (m/2)){
                    array[i][j]->x = -1 * col;
                    array[i][j]->y = -1 * max_val;
                    col = col - offset;
                }else if(j > (m/2)){
                    array[i][j]->x = col;
                    array[i][j]->y = -1 * max_val;
                    col = col + offset;
                }
                
            }
        }
        if(i == (m/2)){
            max_val = offset;
        }else if(i < (m/2)){
            max_val = max_val - offset;
        }
        else if(i > (m/2)){
            max_val = max_val + offset;
        }

    }
    }
    
    void initialize_attacker_in_board(){
        if(array[5][5] != NULL){
            array[5][5]->im_attacker = 1;
        }
        else{
            array[5][5] = (struct node *)malloc(sizeof(struct node));
            array[5][5]->im_attacker = 1;
            
        }
    }
    void get_neighbours(){
        
        //Getting neighbours
    int max_val = offset *(m/2);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            array[i][j]->index_1 = i;
            array[i][j]->index_2 = j;
            array[i][j]->power = 0.5;
            cout << array[i][j]->ID << "'s power is:"<<array[i][j]->power<<endl;
            if((array[i][j]->y == max_val) && (array[i][j]->x == -1 * max_val)){
                
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->y == max_val) && (array[i][j]->x == max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
            }else if((array[i][j]->y == max_val) && (array[i][j]->x != max_val)){
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x == -1 * max_val)){
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x == max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
            }
            else if((array[i][j]->y == -1 * max_val) && (array[i][j]->x != max_val)){
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
            }
            else if((array[i][j]->x == -1 * max_val) && (array[i][j]->y != max_val)){
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
            else if((array[i][j]->x == max_val) && (array[i][j]->y != max_val)){
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
            }
            else{
                array[i][j]->neighbours.push_back(array[i][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i-1][j+1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j-1]->ID);
                array[i][j]->neighbours.push_back(array[i+1][j+1]->ID);
            }
        }
    }
    }
    void print_node_with_neighbours(){
        //printing the neighbours
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            printf("%d : {",array[i][j]->ID);
            for(int k = 0;k< array[i][j]->neighbours.size();k++){
                if(k == array[i][j]->neighbours.size()-1){
                    cout<<array[i][j]->neighbours[k]<<"";
                    
                }
                else{
                    cout<<array[i][j]->neighbours[k]<<",";
                }
            }cout<<"} ";
        }cout<<endl;
    }
    }

    void get_3N(int id){
        cout << "The id:"<<id<<endl;
        long double cal = (v/2)/4;
        int h_max = ceil(cal);
        int max_val = offset *(m/2);
        int found = 0;
        for(int i = 0;i<11;i++){
            for(int j = 0;j<11;j++){
                if(array[i][j]->ID == id){
                    found = 1;
                    source_x = i;
                    source_y = j;
                    
                    //north
                    if(array[i][j]->x == 0 && array[i][j]->y > 0 && array[i][j]->y != max_val){
                        cout << "A1" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == 0 && array[i][j]->y == max_val){
                        cout << "A2" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                    }
                    //south
                    else if(array[i][j]->x == 0 && array[i][j]->y < 0 && array[i][j]->y != -1 * max_val){
                        cout << "A3" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == 0 && array[i][j]->y == -1 * max_val){
                        cout << "A4" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->equal_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    //west
                    else if(array[i][j]->x > 0 && array[i][j]->y == 0 && array[i][j]->x != max_val){
                        cout << "A5" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                    }
                    else if(array[i][j]->x == max_val && array[i][j]->y == 0){
                        cout << "A6" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                       array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                    }
                    //east
                    else if(array[i][j]->x < 0 && array[i][j]->y == 0 && array[i][j]->x != -1 * max_val){
                        cout << "A7" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                       array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y == 0){
                        cout << "A8" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                    //top
                    else if(array[i][j]->y == max_val && array[i][j]->x == -1 * max_val){
                        cout << "A9" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        
                       array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                         }
                    else if(array[i][j]->y == max_val && array[i][j]->x == max_val){
                        cout << "A10" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        
                    }
                    else if(array[i][j]->y == max_val && array[i][j]->x != -1*max_val && array[i][j]->x != max_val){
                        if(array[i][j]->x < 0){
                        cout << "A11" << endl;

                            array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        }
                        else if(array[i][j]->x > 0){
                            cout << "A12" << endl;
                           array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                      array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        }
                        
                    }
                    //bottom
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y == -1 * max_val){
                        cout << "A13" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                       array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                    else if(array[i][j]->x == max_val && array[i][j]->y == -1 * max_val){
                        cout << "A14" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                       array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                    }
                    else if(array[i][j]->y == -1 * max_val && array[i][j]->x != max_val && array[i][j]->x != -1 * max_val){
                        cout << "A15" << endl;
                        if(array[i][j]->x < 0){
                            array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                        }
                        else if(array[i][j]->x > 0){
                            cout << "A16" << endl;
                            array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                        }
                    }
                    //left
                    else if(array[i][j]->x == -1 * max_val && array[i][j]->y != -1 * max_val && array[i][j]->y != max_val){
                        cout << "A17" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                       array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                    }
                    //right
                    else if(array[i][j]->x == max_val && array[i][j]->y != -1 * max_val && array[i][j]->y != max_val){
                        cout << "A18" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                    }
                    //side-1
                    else if(array[i][j]->x > 0 && array[i][j]->y != max_val && array[i][j]->y != -1*max_val && array[i][j]->x != max_val){
                        cout << "A19" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j+1]);
                    }
                    //side2
                    else if(array[i][j]->x < 0 && array[i][j]->x != -1*max_val && array[i][j]->y != max_val && array[i][j]->y != -1 * max_val){
                        cout << "A20" << endl;
                        array[i][j]->equal_neighbour.push_back(*array[i-1][j]);
                        array[i][j]->equal_neighbour.push_back(*array[i+1][j]);
                        array[i][j]->forther_neighbour.push_back(*array[i][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i-1][j-1]);
                        array[i][j]->forther_neighbour.push_back(*array[i+1][j-1]);
                        array[i][j]->closure_neighbour.push_back(*array[i][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i+1][j+1]);
                        array[i][j]->closure_neighbour.push_back(*array[i-1][j+1]);
                    }
                   cout << "Done" << endl;
                   cout << array[i][j]->equal_neighbour.size() << " "<<array[i][j]->closure_neighbour.size()<<endl;
                   
                }
            }
        }
        if(found == 0){
            cout << "The id not found!"<<endl;
        }
        cout << "Exited"<<endl;
    }
    void print_all_powers(){
    cout << "Let's see all the powers of the nodes..."<<endl;
    if(!data_file)
        data_file.open("data.csv",ios::out);
    else
        data_file.open("data.csv",ios::app);
    data_file << endl << endl << "Nodes" << ":" "Power" << endl <<endl;
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            cout << array[i][j]->ID<<":"<<array[i][j]->power << "\t" ;
            data_file << array[i][j]->ID << ":" << array[i][j]->power << endl;
        }
        
        cout << endl<<endl;

    }
    data_file.close();
}
    void set_package(node *source,string data){
        cout<<"in-process"<<endl;
        cout << "The given data :" << data << endl;
        source->package = (struct package_data *)malloc(sizeof(struct package_data));
        set_packdata(source);
        source->package->data = data;
        cout << "Test:"<<source->package->data<<endl;
        cout << "Package fixed!"<<endl;
    }
    int get_square2(int source_x,int source_y){
        int h_max = ceil((v/2)/4);
        int s1 = source_x - (h_max+2);
        int e1 = source_y +(h_max+2);
        int s2 = source_x + (h_max+2);
        int e2 = source_y + (h_max + 2);
        int s3 = source_x + (h_max+2);
        int e3 = source_y - (h_max+2);
        int s4 = source_x - (h_max+2);
        int e4 = source_y -(h_max+2);
        int start1,end1,start2,end2,start3,end3,start4,end4;
        start1 = s1;start2 = s2;start3 = s3;start4 = s4;end1 = e1;end2 = e2;end3 = e3;end4= e4;
        /*
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        cout << "Size:" << phantom1.size() << endl;
        */
        if(start1 > -1 && start1 < 11&& end1 > -1 && end1 < 11){
            phantom2.insert(*array[start1][end1]);
        }
        if(start2 < 11 && end2 > -1 && end2 < 11){
            phantom2.insert(*array[start2][end2]);
        }
        if(start3 < 11 && start3 > -1 && end3 > -1 && end3 < 11){
            phantom2.insert(*array[start3][end3]);
        }
        if(start4 < 11 && start4 > -1 && end4 > -1 && end4 < 11){
            phantom2.insert(*array[start4][end4]);
            
        }
        if(start1 < 0 || start4 < 0){
            start1 = 0;
            start4 = 0;
        }
        if(start3 > 10 || start2 > 10){
            start3 = 10;
            start2 = 10;
        }
        if(start2 )
        if(end1 > 10 || end2 > 10){
            end1 = 10;
            end2 = 10;
        }
        if(end4 < 0 || end3 < 0){
            end4 = 0;
            end3 = 0;
        }
       for(auto it : phantom2){
        if(it.im_attacker == 1){
            this->Packets_cancelled_counts++;
            this->attacker_id = it.ID;
            cout << "The attacker is :" << it.ID << endl;
            this->attacker_paths.push_back(it.ID);
            cout << "ATTACKER CAUGHT" << endl;
            return 1;
        }
       }
       /*
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        */
        for(int i = start4;i<=start3;i++){
            for(int j = end4;j<=end1;j++){
                /*
                if(array[i][j]->im_attacker == 1){
                    this->Packets_cancelled_counts++;
                    this->attacker_id = array[i][j]->ID;
                    cout << "The ATTACKER is :" << array[i][j]->ID << endl;
                    cout << "ATTACKER CAUGHT" << endl;
                    return 1;
                }
                */
                cout << "Power reduction for the node :"<<array[i][j]->ID<<endl;
                power_reduce(array[i][j]);
                power_reduce(array[i][j]);
            }
        }
        return 0;
    }
    int get_square(int source_x,int source_y){
        int h_max = ceil((v/2)/4);
        cout << "Hmax:"<<h_max<<endl;
        int s1 = source_x - (h_max+2);
        int e1 = source_y +(h_max+2);
        int s2 = source_x + (h_max+2);
        int e2 = source_y + (h_max + 2);
        int s3 = source_x + (h_max+2);
        int e3 = source_y - (h_max+2);
        int s4 = source_x - (h_max+2);
        int e4 = source_y -(h_max+2);
        int start1,end1,start2,end2,start3,end3,start4,end4;
        start1 = s1;start2 = s2;start3 = s3;start4 = s4;end1 = e1;end2=e2;end3=e3;end4=e4;
        /*
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        */
        if(start1 < 0 || start4 < 0){
            start1 = 0;
            start4 = 0;
        }
        if(start3 > 10 || start2 > 10){
            start3 = 10;
            start2 = 10;
        }
        if(start2 )
        if(end1 > 10 || end2 > 10){
            end1 = 10;
            end2 = 10;
        }
        if(end4 < 0 || end3 < 0){
            end4 = 0;
            end3 = 0;
        }
        /*
        cout << "Start1:"<<start1 << "end1:"<<end1<<endl<<" start2:"<< start2<<" end2:"<< end2<<endl;
        cout << "start3:"<<start3 << " end3:"<<end3<<endl<<" start4:" << start4<<" end4:"<<end4<<endl;
        */
        if(s4 > -1 && s1 > -1 && s4 == s1){
            for(int i = end4;i<=end1;i++){
                phantom1.insert(*array[s4][i]);
                
            }
        }
        if(e4 > -1 && e3 > -1 && e4 == e3){
            for(int i = start4;i<=start3;i++){
                phantom1.insert(*array[i][e4]);
            }
        }
        if(e1 < 11 && e2 < 11 && e1 == e2){
            for(int i = start1;i<=start2;i++){
                phantom1.insert(*array[i][end1]);
            }
        }
        if(s3 < 11 && s2 < 11 && s3 == s2){
            for(int i = end3;i<=end2;i++){
                phantom1.insert(*array[s3][i]);
            }
        }
        
        for(auto it : phantom2){
            if(it.im_attacker == 1){
                this->Packets_cancelled_counts++;
                this->attacker_id = it.ID;
                cout << "The ATTACKER is :" << it.ID << endl;
                this->attacker_paths.push_back(it.ID);
            cout << "ATTACKER CAUGHT" << endl;
            return 1;
            }
        }
        cout << "The size of the Phantom square is:"<<phantom1.size()<<endl;
        cout << "The elements are..."<<endl;
        set<node>::iterator it = phantom1.begin();
        for(auto iter = it;iter!=phantom1.end();iter++){
            cout <<iter->ID<<endl;
        }
        for(int i = start4;i<=start3;i++){
            for(int j = end4;j<=end1;j++){
                /*
                if(array[i][j]->im_attacker == 1){
                    this->Packets_cancelled_counts++;
                    this->attacker_id = array[i][j]->ID;
                    cout << "ATTACKER CAUGHT" << endl;
                    return 1;
                }
                */
                cout << "Power reduction for the node :"<<array[i][j]->ID<<endl;
                power_reduce(array[i][j]);
                power_reduce(array[i][j]);
            }
        }
        return 0;
    }
    
    
   
    void print_all_nodes(){
        cout << "Working..." << endl;
        printf("\nPrinting all nodes\n");
        cout << m << endl;
    for(int i = 0;i<m;i++){
        for(int j = 0;j<m;j++){
            cout << array[i][j]->ID << "\t";
        }cout << endl;
    }
    cout << "Done" << endl;
    } 
    
    void packing(node *source,string new_data){
        source->package = (pack *)malloc(sizeof(pack));
        set_packdata(source);
        source->package->data = new_data;
        cout << source->package->data<<endl;
        cout << "Packet packed successfully!" << endl;
    }
    
    int SP(int src_ii,int src_jj,int des_ii,int des_jj){
        cout << "SHORTEST PATH ALGORITHM EXECUTION STARTS.." << endl;
        int src_i = src_ii;
        int src_j = src_jj;
        int des_i = des_ii;
        int des_j = des_jj;
        cout << "The source node details:"<<endl;
        cout<<"ID:"<<array[src_i][src_j]->ID<<endl;
        cout << "The destination node details:"<<endl;
        cout << "ID:"<<array[des_i][des_j]->ID<<endl;
    
        struct node *iter = array[src_i][src_j],*dest = array[des_i][des_j];
       
        
        while(src_i != des_i && src_j != des_j){
            
            if(src_i > des_i && src_j == des_j){
                cout << "A1"<<endl;
                iter = array[src_i-1][src_j];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
                if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->Packets_cancelled_counts++;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                power_reduction(iter,array[src_i][src_j]);
               array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_i = src_i - 1;
                
            }
            else if(src_i < des_i && src_j == des_j){
                cout << "A2"<<endl;
                iter = array[src_i+1][src_j];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                power_reduction(iter,array[src_i][src_j]);
                iter->package->data = array[src_i][src_j]->package->data;
                if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->Packets_cancelled_counts++;
                   this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_i = src_i + 1;
                
            }
            
            if(src_j > des_j && src_i == des_i){
                cout << "A3"<<endl;
                iter = array[src_i][src_j+1];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
                if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                power_reduction(iter,array[src_i][src_j]);
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_j = src_j + 1;
            }else if(src_j < des_j && src_i == des_i){
                cout << "A4"<<endl;
                iter = array[src_i][src_j - 1];
                iter->package = (pack *)malloc(sizeof(pack));
                set_packdata(iter);
                iter->package->data = array[src_i][src_j]->package->data;
               if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                power_reduction(iter,array[src_i][src_j]);
                array[src_i][src_j]->package = NULL;
                cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                
                src_j = src_j - 1;
            }
            
            if(src_j != des_j && src_i != des_i){
                if(des_j > src_j && des_i > src_i){
                    cout << "A5"<<endl;
                    iter = array[src_i+1][src_j+1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                   this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    
                    src_i = src_i + 1;
                    src_j = src_j + 1;
                }else if(des_j < src_j && des_i < src_i){
                    cout << "A6"<<endl;
                    iter = array[src_i-1][src_j-1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                    if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                   this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    
                    src_i = src_i - 1;
                    src_j = src_j - 1;
                }
                else if(des_j < src_j && des_i > src_i){
                    cout << "A7"<<endl;
                    iter = array[src_i + 1][src_j - 1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                   if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                   this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    src_i = src_i + 1;
                    src_j = src_j - 1;
                }
                else if(des_j > src_j && des_i < src_i){
                    cout << "A8"<<endl;
                    iter = array[src_i - 1][src_j + 1];
                    iter->package = (pack *)malloc(sizeof(pack));
                    set_packdata(iter);
                    iter->package->data = array[src_i][src_j]->package->data;
                   if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                   this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            
                    power_reduction(iter,array[src_i][src_j]);
                    array[src_i][src_j]->package = NULL;
                    
                    cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
                    src_i = src_i - 1;
                    src_j = src_j + 1;
                }
            }
        }
        
        while(src_i < des_i && src_j == des_j){
            cout << "A9"<<endl;
            iter = array[src_i+1][src_j];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
           if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL; 
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_i = src_i + 1;
        }
        while(src_i > des_i && src_j == des_j){
            cout << "A10"<<endl;
            iter = array[src_i-1][src_j];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                     this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_i = src_i - 1;
        }
        while(src_j > des_j && src_i == des_i){
            cout << "A11"<<endl;
            iter = array[src_i][src_j - 1];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
           if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            power_reduction(iter,array[src_i][src_j]);
            array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_j = src_j - 1;
        }
        while(src_j < des_j && src_i == des_i){
            cout << "A12"<<endl;
            iter = array[src_i][src_j + 1];
            iter->package = (pack *)malloc(sizeof(pack));
            set_packdata(iter);
            iter->package->data = array[src_i][src_j]->package->data;
            if(iter->im_attacker == 1){
                    iter->im_attacker = 0;
                    array[src_i][src_j]->im_attacker = 1;
                    cout << "The old attacker is :" << iter->ID << endl;
                    cout << "The new attacker is :" << array[src_i][src_j]->ID << endl;
                    this->attacker_paths.push_back(array[src_i][src_j]->ID);
                    this->Packets_cancelled_counts++;
                    this->attacker_id = iter->ID;
                    return 1;
                }
            power_reduction(iter,array[src_i][src_j]);
           array[src_i][src_j]->package = NULL;
            cout << "The Transfer status: "<< array[src_i][src_j]->ID << " -> "<<iter->ID<<endl;
            src_j = src_j + 1;
        }
        if(src_i == des_i && src_j == des_j){
            cout << "transfer done" << endl;
            cout << "Mission Success" << endl;
            cout << array[des_i][des_j]->package->data<<endl;
        }
        return 0;
    }
    void check_pack(node *source){
        cout << source->package->data<<endl;
        cout << "Passed" << endl;
    }
    int forward_random_walk(node &source){
        cout << "Source id:"<<source.ID<<endl;
        cout << "Source's package:"<<source.package->data<<endl;
        
            for(int i = 0;i<array[source_x][source_y]->closure_neighbour.size();i++){
            if(array[source_x][source_y]->closure_neighbour[i].ID == -1){
                
                cout << "working" << endl;
                
                array[5][5]->package = (pack *)malloc(sizeof(pack));
                set_packdata(array[5][5]);
                cout << "alloted"<<endl;
                array[5][5]->package->data = source.package->data;
                if(array[5][5]->im_attacker == 1){
                    cout << "The old attacker is :" << array[5][5]->ID << endl;
                    cout << "The new attacker is :" << source.ID << endl;
                    array[5][5]->im_attacker = 0;
                    source.im_attacker = 1;
                    this->Packets_cancelled_counts++;
                    attacker_id = source.ID;
                     this->attacker_paths.push_back(source.ID);
                    return 1;
                }
                power_reduction(array[source_x][source_y],array[5][5]);
                cout << "alloted and shifted"<<endl;
                array[source_x][source_y]->package = NULL;
                this->get_3N(array[source_x][source_y]->closure_neighbour[i].ID); 
                this->Packets_received_counts++;
                cout << "Package shifted to base station"<<endl;
                return 0;
            }
        }
        
        
        this->get_3N(source.ID);
        int new_ind = rand()%array[source_x][source_y]->closure_neighbour.size();
        cout << "New_ind:"<<new_ind<<endl;
        cout << "New_source:"<<array[source_x][source_y]->closure_neighbour[new_ind].ID<<endl;
        
        array[source_x][source_y]->closure_neighbour[new_ind].package = (pack *)malloc(sizeof(pack));
        cout << "Memeory alloted"<<endl;
        cout << "The package data:"<<source.package->data<<endl;
        struct node *iter;
        iter = &array[source_x][source_y]->closure_neighbour[new_ind];
        set_packdata(iter);
        array[source_x][source_y]->closure_neighbour[new_ind].package->data = source.package->data;
        struct node getter = array[source_x][source_y]->closure_neighbour[new_ind];
        //source_x = source.index_1;
        //source_y = source.index_2;
        if(getter.im_attacker == 1){
            cout << "The old attacker is:"<<getter.ID << endl;
            cout << "The new attacker is:"<< source.ID << endl;
            getter.im_attacker = 0;
            source.im_attacker = 1;
            this->attacker_paths.push_back(source.ID);
            this->attacker_id = source.ID;
            this->Packets_cancelled_counts++;
            return 1;
        }
        cout << "Package shifted" << endl;
        power_reduction(iter,array[source_x][source_y]);
        
        array[source_x][source_y]->package = NULL;
        forward_random_walk(array[source_x][source_y]->closure_neighbour[new_ind]);
        return 0;
    }
    
           
    void mission1(){
        
        int id;
        cout << "Enter the source id:"<<endl;
        cin>>id;
        if(id == -1){
            this->get_3N(id);
            cout << "The SOURCE impersonating as BASE STATION"<<endl;
            return;
        }
        int src_i,src_j;
        int found = 0;
        for(int i = 0;i<11;i++){
            for(int j = 0;j<11;j++){
                
                if(array[i][j]->ID == id){
                    src_i = i;
                    src_j = j;
                    found = 1;
                    //total packets sending...
                    if(!data_file)
        data_file.open("data.csv",ios::out);
    else
        data_file.open("data.csv",ios::app);
                    for(int i = 0;i<total_packet_sending;i++){
                        
                        cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout << endl<< endl <<endl<<endl<<endl;
                        cout << "\t\t\t\t\t\t\tPACKAGE NO :"<<i<<endl;
                        cout << endl<< endl <<endl<<endl<<endl;
                         cout<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout << "ATTACKER ID :" << this->attacker_id << endl;
                        data_file<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                        data_file << endl<< endl;
                        data_file << "\t\t\t\t\t\t\tPACKAGE NO :"<<i<<endl;
                        data_file << endl<< endl;
                         data_file<<"----------------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout << "ATTACKER ID :" << this->attacker_id << endl;
                        cout << "Initial power of the source......"<<endl;
                        cout << "The power of the source node is:"<<array[src_i][src_j]->power<<endl;
                        long double initial_power = array[src_i][src_j]->power;
                    this->get_3N(id);
                    cout << endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                    this->print_all_powers();
                    int cond1 = this->get_square(source_x,source_y);
                    if(cond1 == 1){
                        lost_packs++;
                        continue;
                    }
        
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                    this->print_all_powers();
                    srand(time(0));
        int ind = rand()%phantom1.size();
        cout << "The random picked node is:";
        set<node>::iterator iter = phantom1.begin();
        advance(iter,ind);
        cout << iter->ID << endl;
        string new_data = "Secret Mission 001";
        this->packing(array[source_x][source_y],new_data);
        int des_x = 0,des_y = 0;
        int found = 0;
        for(int i = 0;i<11;i++){
            if(found == 1) break;
            for(int j = 0;j< 11 ;j++){
                if(array[i][j]->ID == iter->ID){
                    des_x = i;
                    des_y = j;
                    found = 1;
                    break;
                }
            }
        }
        
        //cout << "Des i:"<<des_x<<" j:"<<des_y<<endl;
        int sp1 = this->SP(source_x,source_y,des_x,des_y);
        if(sp1){
            lost_packs++;
            continue;
        }
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                    
        //cout << "Package sent successfully!" << endl;
        cout << "GET SQUARE 2 IS EXECUTING..." << endl;
        int cond2 = this->get_square2(des_x,des_y);
        if(cond2 == 1){
            lost_packs++;
            continue;
        }
       
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        this->tot_inter_nodes += phantom2.size();
        int number = 1;
        for(auto it : phantom2){
            int short_path_cond = 0,frw1 = 0;
            
            cout << "INTERMEDIATE NODE NO " << number << endl;
            number++;
                short_path_cond = this->SP(des_x,des_y,it.index_1,it.index_2);
                cout << "Packet sent to the intermediate node " << number << " id is :" << it.ID << endl;
                cout << "Packet is :" << this->array[it.index_1][it.index_2]->package->data;
                if(this->array[des_x][des_y]->package == NULL){
                    cout << "Pack is empty" << endl;
                    this->array[des_x][des_y]->package = (pack *)malloc(sizeof(pack));
                    cout << "Alloted" << endl;
                    this->array[des_x][des_y]->package->data = this->array[it.index_1][it.index_2]->package->data;
                    cout << "Pack is filled" << endl;
                }
                if(short_path_cond == 1){
                    this->lost_packs++;
                    continue;
                }
                cout << "Forward Random walk " << number << " starting......."<< endl<<endl<<endl<<endl;
        
             frw1 = this->forward_random_walk(*array[it.index_1][it.index_2]);
        
            cout << "Caught:" << frw1 << endl;
            if(frw1 == 1) this->lost_packs++;cout << "ATTACKER DETECTED in FRW" << endl;continue;
               
                //this->array[des_x][des_y]->package->data = array[it.index_1][it.index_2]->package->data;
               
                if(phantom2.size() == 4){
                it.package->k = 512;
            }else if (phantom2.size() == 3){
                it.package->k = 2048/3;
            }
            else if(phantom2.size() == 2){
                it.package->k = 2048/2;
            }else{
                it.package->k = 2048;
            }
           
            
        }
        this->won_packs++;
        this->array[des_x][des_y]->package = NULL;
        // if(short_path_cond == 1) continue;
        // if(frw1 == 1) continue;
        
        /*          
        int ind2 = rand()%phantom2.size();
        // UNDER CHANGES FOR INTERMEDIATE NODE SPLITTING AND SENDING THE PACKETS.
        set<node>::iterator inter_iter = phantom2.begin();
        advance(inter_iter,ind2);
        cout << inter_iter->ID << endl;
        int inter_des_x = 0,inter_des_y = 0;
        cout << "The Current node id is :"<< array[des_x][des_y]->ID<<endl;
        int new_sp = 0;
        for(int i = 0;i<11;i++){
            for(int j = 0;j< 11 ;j++){
                if(array[i][j]->ID == inter_iter->ID){
                    new_sp = this->SP(des_x,des_y,i,j);
                    inter_des_x = i;
                    inter_des_y = j;
                 
                    break;
                }
            }
        }
        if(new_sp == 1) continue;
        
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                    
        cout << "Inter_Pack_data:"<<array[inter_des_x][inter_des_y]->package->data<<endl;
        cout<<"Inter id:"<<array[inter_des_x][inter_des_y]->ID<<endl;
        this->get_3N(array[inter_des_x][inter_des_y]->ID); 
        cout << "The source id :"<<array[source_x][source_y]->ID<<endl;
        cout<<"Inter id:"<<array[inter_des_x][inter_des_y]->ID<<endl;
        cout << "Forward Random walk starting......."<< endl<<endl<<endl<<endl;
        int frw1 = this->forward_random_walk(*array[inter_des_x][inter_des_y]);
        
        cout << "Caught:" << frw1 << endl;
        if(frw1) continue;
        */
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;  
        cout << "The Source id atlast is:"<<array[source_x][source_y]->ID<<endl;
        cout << "The source id :" << array[source_x][source_y]->ID << endl;
        if(array[source_x][source_y]->package == NULL){
            cout << "The source id doesn't have package" << endl;
        }
        //cout << "The source id pack is:"<<array[source_x][source_y]->package->data<<endl;
        array[source_x][source_y]->power = 0.5;
        cout << "The power of the source is:"<<array[source_x][source_y]->power<<endl;
        if(array[src_i][src_j]->package == NULL) cout << "Yes, source doesn't have a package." << endl;
    cout << "Power reduction status:"<< initial_power << "-->" << array[src_i][src_j]->power<<endl;
    cout << "Power reduced:";
    if(initial_power > array[src_i][src_j]->power) cout << "True" << endl;
    else cout << "False" << endl;
    cout << "The power of the source node is:"<<array[src_i][src_j]->power<<endl;
    
    }
                }
            }
            if(found == 0){
                cout << "ID not found"<<endl;
            }

    

        }
        
        }
    
    
};


int main(){
    freopen("input.txt", "r", stdin);
    board circuit;

    circuit.print_all_nodes();
    
    circuit.get_neighbours();
    circuit.print_node_with_neighbours();
    circuit.initialize_attacker_in_board();
    circuit.mission1();
    circuit.print_all_powers();
    cout<<circuit.Packets_received_counts<<endl;
    cout << circuit.Packets_cancelled_counts<<endl;
    cout << "The paths travelled by attacker are .." << endl;
    cout << "Total moves by attacker:" <<  circuit.attacker_paths.size() << endl;
    for(auto it : circuit.attacker_paths){
        cout << it << endl;
    }
    cout << "Total inter_nodes are ..." << circuit.tot_inter_nodes << endl;
    cout << "format : {won:lost} --> " << circuit.won_packs << ":" << circuit.lost_packs << endl;
    return 0;
}
