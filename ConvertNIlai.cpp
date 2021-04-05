#include<iostream>
using namespace std;

/*Persyaratan*/
// 1. 0-50 = E
// 2. 51-60 = D
// 3. 61-75 = C
// 4. 76-90 = B
// 4. 91-100 = A

int main(){
    int nilaiAngka;
    char huruf;

    cout<<"Masukan Nilai : ";cin>>nilaiAngka;

    if(nilaiAngka>=0 && nilaiAngka<=50){
        cout<<"Convert nilainya adalah : E";
        //block code
    }else if (nilaiAngka>=51 && nilaiAngka<=60){
        cout<<"Convert nilainya adalah : D";
    }else if (nilaiAngka>=61 && nilaiAngka<=75){
        cout<<"Convert nilainya adalah : C";
    }else if (nilaiAngka>=76&&nilaiAngka<=90){
        cout<<"Convert nilainya adalah : B";
    }else if (nilaiAngka>=91&&nilaiAngka<=100){
        cout<<"Convert nilainya adalah : A";
    }else {
        cout<<"Wrong Input !!!";
    }

    return 0;
}
