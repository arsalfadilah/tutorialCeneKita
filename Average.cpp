#include<iostream>
using namespace std;

int main(){
    int i, arr[]={10, 2, 1, 5, 4, 3, 7, 8, 9, 6};
    float average=0;

    //rata = jumlah nilai data / banyaknya data;

    for(i=0; i<10; i++){
        average = average + arr[i];
    }

    cout<<"Masukan Rata-rata : "<<average/10;

    return 0;
}
