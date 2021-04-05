#include<iostream>
using namespace std;

int main(){
    int i, arr[10] = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10};//idx arr dimulai dari 0
    int tempMax = arr[0];
    int tempMin = arr[0];

    for(i=0; i<10; i++){
        if(tempMax < arr [i]){
            tempMax = arr[i];
        }
        if(tempMin > arr[i]){
            tempMin = arr[i];
        }
    }

    cout<<"Nilai max : "<<tempMax<<endl;
    cout<<"Nilai min : "<<tempMin<<endl;

    return 0;
}
