//Nama Program : ATM Virtual
//Authors : Arsal Fadilah

//Library
#include<iostream> //cin, cout
#include<fstream> //ifstream, ofstream, fstream
#include<windows.h> //system, Sleep
#include<limits> //bit
#include<cstdlib> //srand, rand
#include<time.h> //time
using namespace std;

//Modul Main Menu
void menuAwal();
void CreateAccount();
void login(string* user, string* pass);
//Modul Menu Customer
void menuCstmr(string UserName);
void InfoSaldo(string UserName);
void Transfer(string UserName);
void Nabung(string UserName);
//Modul Menu Admin
void menuAdmn();
void infoAccountCstmr();
void setAccountCstmr();
bool searchInFile(string user);
void ChangePass(string UserName);
void DelAccount(string UserName);
//Modul Pendukung
int pilihMenu();
void pauseAndClear();
void ToUserName(string* ctgrs);
void tambahSaldo(string UserName, int nominal);
void kurangSaldo(string UserName, int nominal);

//variabel global
struct cstmr{
    string UserName;
    string Password;
    int saldo;
    int NoRek;
}data;

//driver code
int main(){
    //kebutuhan data :
    string UserName, Password;

    //Algoritma :
    menuAwal();

    switch(pilihMenu()){
        case 1: CreateAccount(); break;
        case 2: login(&UserName, &Password);
                if(UserName == "admin" && Password=="admin"){
                    menuAdmn();
                } else {
                    menuCstmr(UserName);
                } break;
        case 3: exit(0); break;
        default: cout<<"Ops Your Choose isn't Right"<<endl;
                 pauseAndClear();
                 main();
    }
    return 0;
}

void menuAwal(){
    cout<<"|     /| --- --------|"<<endl;
    cout<<"|   /|  |   |--|  |--|"<<endl;
    cout<<"| /|    |   |  |  |"<<endl;
    cout<<"||      |   |  |  |"<<endl;
    cout<<"||\\     |   |  |  |"<<endl;
    cout<<"|  |\\   |   |  |  |"<<endl;
    cout<<"|    |\\_|___|  |__|"<<endl;
    cout<<"<------------------->"<<endl;
    cout<<"|       Menu        |"<<endl;
    cout<<"| 1. Create Account |"<<endl;
    cout<<"| 2. Login          |"<<endl;
    cout<<"| 3. Exit           |"<<endl;
    cout<<"<------------------->"<<endl;
}

int pilihMenu(){
    int pilih;

    cout<<"Choose : ";
    while(!(cin >> pilih)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Only Integers !!!.  Try again: ";
    }
    system("cls");

    return pilih;
}

void CreateAccount(){
    //Inisialisasi
    cstmr temp;
    string tmpPassword, UserName;
    int jmlhData=0;
    bool succes=true;
    char c;
    FILE *ftp;
    ofstream addData;
    ftp = fopen("data.dat", "rb"); // a --> write appending, r-->read, w-->write
    addData.open("data.dat", ios::binary | ios::app);

    //Algoritrma :

            cout<<"     Create Account"<<endl;
    while(succes){
            cout<<"Username : ";cin>>UserName;
        if(!searchInFile(UserName)){
            data.UserName = UserName;
            cout<<"Password : ";cin>>data.Password;
            cout<<"Konfirmasi Password : ";cin>>tmpPassword;
            cout<<"Saldo Awal : ";cin>>data.saldo;
            succes=false;
        } else {
            cout<<"Username has been ready to login, please choose another or login !";
        }
    }

    //Membuat No. Rekening berdasar jumlah account
    //yang telah terdaftar
    while(fread(&temp, sizeof(cstmr), 1, ftp)){
        jmlhData++;
    }

    data.NoRek = 100000 + jmlhData;
    cout<<"No. Rekening : "<<data.NoRek;

    fclose(ftp);

    if(data.Password==tmpPassword){
        addData.write((char*) &data, sizeof(cstmr));
        cout<<"\n\nCongratulation Your Account Has Been Created !\n"<<endl;
        addData.close();
        system("pause");
        system("cls");
        main();
    } else {
        cout<<"\nOh I'M Sorry, Your Account Hasnt Save\n";
        addData.close();
    }
}

void login(string* user, string* pass){
    bool success=true;
    string UserName;
    string Password;

    FILE *flogin;
    flogin=fopen("data.dat", "rb");

    //Algoritma :
        cout<<"      Login"<<endl;
    while(success){
        cout<<"Username : ";cin>>UserName;
        cout<<"Password : ";cin>>Password;
        fseek(flogin, 0, SEEK_SET);
        while(fread(&data, sizeof(cstmr), 1, flogin) && success){
            if((data.UserName==UserName && data.Password==Password) || (UserName=="admin" && Password=="admin")){
                *user = UserName;
                *pass = Password;
                cout<<"Login Success !!!"<<endl;
                fclose(flogin);
                success = false;
            }
        }
        if(UserName=="admin" && Password=="admin"){
            *user = UserName;
            *pass = Password;
            success = false;
        }
        if(success){
           cout<<"Your Username/Password is Wrong"<<endl;
           pauseAndClear();
        }
    }
    pauseAndClear();
}

void menuAdmn(){
    int pilih;
    cout<<"-------------------------------"<<endl;
    cout<<"|         Menu Admin          |"<<endl;
    cout<<"| 1. Info Account Customer    |"<<endl;
    cout<<"| 2. Setting Account Customer |"<<endl;
    cout<<"| 3. Back Main Menu           |"<<endl;
    cout<<"-------------------------------"<<endl;

    do{
        pilih = pilihMenu();
        switch(pilih){
            case 1: infoAccountCstmr();break;
            case 2: setAccountCstmr();break;
            case 3: break;
            default:
                cout<<"Wrong Input !";
        }
    }while(pilih != 3);

    main();
}

void infoAccountCstmr(){
    bool success=true;
    int pilih=0, no=1;
    FILE *infoFile;
    string UserName;

    cout<<"--------------------------"<<endl;
    cout<<"|  Info Account Customer |"<<endl;
    cout<<"| 1. Search By UserName  |"<<endl;
    cout<<"| 2. See All             |"<<endl;
    cout<<"| 3. Back To Menu Admin  |"<<endl;
    cout<<"--------------------------"<<endl;

    infoFile=fopen("data.dat", "rb");

    do{
        pilih = pilihMenu();
        switch(pilih){
            case 1:
                cout<<"Username : ";cin>>UserName;
                if(searchInFile(UserName)){
                    while(fread(&data, sizeof(cstmr), 1, infoFile)){
                        if(data.UserName==UserName){
                            cout<<"Password : "<<data.Password<<"\n";
                            cout<<"No. Rek  : "<<data.NoRek<<"\n";
                            cout<<"Saldo    : Rp. "<<data.saldo<<"\n\n";
                        }
                    }
                } else {
                    cout<<"Ops, Your Username Not In File !"<<endl;
                }
                 success=false; break;
            case 2:
                while(fread(&data, sizeof(cstmr), 1, infoFile)){
                    cout<<no<<endl;
                    cout<<"Username : "<<data.UserName<<"\n";
                    cout<<"Password : "<<data.Password<<"\n";
                    cout<<"No.Rek   : "<<data.NoRek<<"\n";
                    cout<<"Saldo    : Rp. "<<data.saldo<<"\n\n";
                    no++;
                }success=false; break;
            case 3: break;
            default:
                cout<<"Wrong Input Try Again !";
        }
    }while(pilih!=3 && success);

    fclose(infoFile);
    system("pause");
    pauseAndClear();
    menuAdmn();
}

void setAccountCstmr(){
    bool succes = true;
    string UserName, Password;

    cout<<"   Setting Account Customer"<<endl;
    cout<<"Username : ";cin>>UserName;
    if(searchInFile(UserName)){
        cout<<"Do u want to :"<<endl;
        cout<<"1. Change Password"<<endl;
        cout<<"2. Delete Account"<<endl;
        cout<<"3. Cancel Action"<<endl;

        while(succes){
            switch(pilihMenu()){
                case 1:ChangePass(UserName);succes=false;break;
                case 2:DelAccount(UserName);succes=false;break;
                case 3:menuAdmn();succes=false;break;
                default:cout<<"Wrong Input"<<endl;
            }
        }
    } else {
        cout<<"Ops Username Not In File !"<<endl;
        cout<<"Back To Menu Admin..."<<endl;
        pauseAndClear();
    }

    menuAdmn();

}

bool searchInFile(string user){
    //inisialisasi
    FILE *searchFile;
    searchFile = fopen("data.dat", "rb");

    //algoritma
    while(fread(&data, sizeof(cstmr), 1, searchFile)){
        if(user==data.UserName){
            fclose(searchFile);
            return true;
        }
    }

    fclose(searchFile);

    return false;;

}

void ChangePass(string UserName){
    //inisialisasi
    fstream fs;
    string Password;
    int pos, flag;
    fs.open("data.dat", ios::in | ios::binary | ios::out);

    //algoritma
    while(!fs.eof()){
        pos = fs.tellg();
        fs.read((char*) &data, sizeof(cstmr));
        if(fs){
            if(data.UserName==UserName){
                flag=1;
                cout<<"New Password : ";cin>>Password;
                data.Password=Password;
                fs.seekg(pos);
                fs.write((char*) &data, sizeof(cstmr));
            }
        }
    }
    fs.close();
    if (flag == 1)
        cout << "\nrecord successfully modified \n";
    else
        cout << "\nrecord not found \n";

    pauseAndClear();
}

void DelAccount(string UserName){
    //inisialisasi
    FILE *jmlhFile;
    jmlhFile = fopen("data.dat", "rb");
    ifstream rFile;
    ofstream wFile;
    int i, pos, flag, no=0;
    rFile.open("data.dat", ios::in | ios::binary);
    wFile.open("temp.dat");

    //Algoritma
    while(fread(&data, sizeof(data), 1, jmlhFile)){
        no++;
    }

    fclose(jmlhFile);

    for(i=0; i<no; i++){
        rFile.read((char*) &data, sizeof(cstmr));
        cout<<data.UserName;
        cout<<UserName;
        if(UserName!=data.UserName){
            wFile.write((char*) &data, sizeof(cstmr));
        }
    }

    rFile.close();
    wFile.close();

    remove("data.dat");
    if(rename("temp.dat", "data.dat") != 0)
        cout<<"Oh, Sorry something wrong"<<endl;
    else
        cout<<"Succees Delete Account"<<endl;

    pauseAndClear();

}

void menuCstmr(string UserName){
    //inisiaslisasi
    int pilih=0;

    //algoritma

    while(pilih!=4){
        cout<<"     Welcome "<<UserName<<endl;
        cout<<"1. Info Saldo"<<endl;
        cout<<"2. Transfer"<<endl;
        cout<<"3. Nabung"<<endl;
        cout<<"4. Back Main Menu"<<endl;

    pilih = pilihMenu();
        switch(pilih){
            case 1: InfoSaldo(UserName);break;
            case 2: Transfer(UserName);break;
            case 3: Nabung(UserName);break;
            case 4:break;
            default: cout<<"Wrong Input"<<endl;
        }
    }

    pauseAndClear();
    main();

}

void InfoSaldo(string UserName){
    //insialisasi
    FILE *RFile = fopen("data.dat", "rb");

    //Algoritma
            cout<<"     INFO SALDO"<<endl;
    while(fread(&data, sizeof(data), 1, RFile)){
        if(data.UserName==UserName){
            cout<<"Username : "<<data.UserName<<endl;
            cout<<"No. Rek  : "<<data.NoRek<<endl;
            cout<<"Saldo    : Rp. "<<data.saldo<<"\n\n";
        }
    }
    fclose(RFile);
    system("pause");
    pauseAndClear();

}

void Transfer(string UserName){
    //inisialisasi
    string rek;
    int nominal;

    //Algortima
    cout<<" TRANSFER"<<endl;
    ToUserName(&rek);
    cout<<"Nominal       : ";cin>>nominal;

    if(searchInFile(rek)){
        //Isi Nominal Untuk No. Rek Tujuan
        tambahSaldo(rek, nominal);

        //Isi Nominal Untuk User
        kurangSaldo(UserName, nominal);

        cout<<"   Succes Transfer"<<endl;
        cout<<"From : "<<UserName<<endl;
        cout<<"To   : "<<rek<<endl;

    } else {
        cout<<"Sorry Your No. Rek Isn't Ready In This Bank"<<endl;
    }

    pauseAndClear();

}

void tambahSaldo(string UserName, int nominal){
        //inisialisasi
        fstream fs;
        int pos, flag;
        //Isi Nominal Untuk No. Rek Tujuan
        fs.open("data.dat", ios::in | ios::binary | ios::out);

        //algoritma
        while(!fs.eof()){
            pos = fs.tellg();
            fs.read((char*) &data, sizeof(cstmr));
            if(fs){
                if(data.UserName==UserName){
                    data.saldo=data.saldo+nominal;
                    fs.seekg(pos);
                    fs.write((char*) &data, sizeof(cstmr));
                }
            }
        }
        fs.close();
}

void kurangSaldo(string UserName, int nominal){
    //inisialisasi
    fstream fs;
    int pos, flag;
    fs.open("data.dat", ios::in | ios::binary | ios::out);

        //algoritma
        while(!fs.eof()){
            pos = fs.tellg();
            fs.read((char*) &data, sizeof(cstmr));
            if(fs){
                if(data.UserName==UserName){
                    data.saldo=data.saldo-nominal;
                    fs.seekg(pos);
                    fs.write((char*) &data, sizeof(cstmr));
                }
            }
        }
        fs.close();
}

void Nabung(string UserName){
    int i, pilih, kode, InKode;
    int nominal;
    bool succes=true;
    string metode[5]={
        "Shopee Pay",
        "Indomaret",
        "Alfamart",
        "Ovo",
        "Langsung Ke Bank"
    };
    cout<<"          NABUNG"<<endl;
    cout<<"Metode Nabung :"<<endl;
    for(i=0; i<5; i++){
        cout<<i+1<<". "<<metode[i]<<endl;
    }

    pilih = pilihMenu()-1;
    pauseAndClear();
    cout<<"       Pembayaran"<<endl;
    cout<<"Tempat  : "<<metode[pilih]<<endl;
    cout<<"Nominal : ";cin>>nominal;
    cout<<"Kode Pembayaran :"<<endl;
    srand (time(NULL));
    kode = rand()%999999+1;
    cout<<kode<<endl;
    cout<<"Attention This Code Expired, When Your Closing Program !!!"<<endl;
    pauseAndClear();

    //misalkan kita menabung sesuai dengan metode
    //yang telah dipilih
    while(succes){
        cout<<"Misal anda menjadi petugas pembayarannya"<<endl;
        cout<<"Kode Pembayaran : ";cin>>InKode;

        if(kode==InKode){
            tambahSaldo(UserName, nominal);
            cout<<"Succes Nabung !!!"<<endl;
            succes = false;
        } else {
            cout<<"Wrong Code Payment !!!"<<endl;
        }
    }

    pauseAndClear();

}

void ToUserName(string* ctgrs){
    //insialisasi
    FILE *RFile = fopen("data.dat", "rb");
    int tempKalimat;

    cout<<"NO.Rek Tujuan : ";cin>>tempKalimat;

    while(fread(&data, sizeof(data), 1, RFile)){
        if(tempKalimat == data.NoRek){
            *ctgrs = data.UserName;
        }
    }

    fclose(RFile);

}

//modul interface
void pauseAndClear(){
    Sleep(2000);
    system("cls");
}
