#include "database.hpp"
using namespace std;

vector<string> schema = {"Name","Email","Password"}; 

void DeleteUser(DataBase &data, json &UserData){
    data.Open();
    data.Delete("Name", UserData["Name"]);
    data.Save();
}

void UpdateUser(DataBase &data, json &UserData){
    data.Open();
    UserData = data.Update("Name", UserData["Name"]);
    data.Save();
}

void Profile(DataBase &data, json &UserData){
    int choice;
    cout<<"\n>>$ "<<UserData["Name"]<<" Profile $<<";
    cout<<"\n---------------------------\n";
    for(string i: schema){
        cout<<i<<" -> "<<UserData[i]<<endl;
    }
    cout<<"\n---------------------------\n";
    cout<<"\n_____Settings_____
            \n1. Edit Profile
            \n2. LogOut
            \n3. Delete Account
            \n4. Exit
            \n__________________\n>> ";
    cin>>choice;
    switch(choice){
        case 1:
            UpdateUser(data, UserData);
            cout<<"\n***Updated Profile***\n";
            Profile(data, UserData);
            break;
        case 2:
            cout<<"\n***Logged Out***\n";
            break;
        case 3:
            DeleteUser(data, UserData);
            cout<<"\n***Deleted Account***\n";
            break;
        case 4:
            return;
    }
}

void SignUp(DataBase &data){
    string name, email, password, confirm_pwd;
    cout<<"Enter the name: ";
    cin>>name;
    cout<<"Enter the email: ";
    cin>>email;
    cout<<"Enter the password: ";
    cin>>password;
    cout<<"Confirm the password: ";
    cin>>confirm_pwd;

    if(password == confirm_pwd){
        data.Open();
        json UserData = data.Create({name,email,password});
        data.Save();
        Profile(data, UserData);
    }else{
        cout<<"\nPassword does not match\n";
        SignUp(data);
    }
}

void LogIn(DataBase &data){
    string email, password;
    cout<<"Enter the Email: ";
    cin>>email;

    data.Open();
    json UserData = data.Read("Email", email);
    data.Save();

    if(UserData == NULL){
        return;
    }

    cout<<"Enter the password: ";
    cin>>password;
    cout<<UserData<<endl;    

    if(UserData["Password"] == password){
        cout<<UserData.dump(2)<<endl;
        Profile(data, UserData);
    }else{
        cout<<"Incorrect password.\n";
        LogIn(data);
    }
}

int main(){
    
    DataBase users(schema);
    
    int choice;
    cout<<"Choose the option:
            \n1. SignUp
            \n2. LogIn
            \n>>> ";
    cin>>choice;

    switch(choice){
        case 1:
            SignUp(users);
            break;
        case 2:
            LogIn(users);
            break;
        default:
            cout<<"\nInvalid Option\n";
    }

    return 0;
}