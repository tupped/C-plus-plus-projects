#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


const int listLength = 100;


std::vector<int> initialList;

std::vector<int> secondaryList;

int randIntRange = 100;


int main(){

    std::cout << "HELLO" << '\n';
    std::cout.flush();

    srand(time(0));

    

    for (int i = 0; i < listLength; i++){
        int randomInt = rand() % (randIntRange + 1);
        initialList.push_back(randomInt);
        std::cout << initialList[i] << '\n';

    }

    for(auto& number : initialList){
        if (secondaryList.empty()){
            secondaryList.push_back(number);
            continue;
        }
        size_t i = 0;
        for (; i < secondaryList.size(); i++){
            if (number < secondaryList[i]){
                secondaryList.insert(secondaryList.begin() + i, number);    
                break;
            } 
        }
        if (i == secondaryList.size()){
                secondaryList.push_back(number);
            }


    }

    for (auto& element : secondaryList){
        std::cout << element << '\n';
    }

 
    return 0;
}

