#include <iostream>
#include<stdexcept>
using namespace std;
int findMinimumNumberInRotateArray(int* numbers, int length)
{
    if(numbers == nullptr || length <= 0){
        //Error when using "throw new std::exception("Invalid parameters");"
        std::logic_error ex("Invalid parameters");
        throw new std::exception(ex);
        cout<<"something error"<<endl;
        return -1;
    }
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    cout<<"Start search"<<"\n";
    while(index1 < index2){
        cout<<"index1 = "<<index1<<"\tindexMid = "<<indexMid<<"\tindex2 = "<<index2<<"\n";
        if(index2 - index1 == 1){
            indexMid = index2;
            break;
        }

        indexMid = (index1 + index2)/2;
        if(numbers[indexMid] > numbers[index1]){
            index1 = indexMid;
            cout<<"index1<-indexMid = "<<indexMid<<"\n";
        }else if(numbers[indexMid] < numbers[index2]){
            index2 = indexMid;
            cout<<"index2<-indexMid = "<<indexMid<<"\n";
        }
    }

    return numbers[indexMid];
}

int main()
{
    int SIZE = 5;
    int numbers[SIZE] = {3,4,5,1,2};
    cout<<"Origin array: "<<endl;
    for(int i=0;i<SIZE;i++){
        cout<<numbers[i]<<" ";
    }
    cout<<endl;
    int minNumber = findMinimumNumberInRotateArray(numbers, SIZE);
    cout<<"The minimum number is "<<minNumber<<endl;
    return 0;
}


