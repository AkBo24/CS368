/*****************************************************************************
Name: Akshay Bodla
Wisc ID: bodla
CS Login: akshay
Semester: Fall 2020
*****************************************************************************/

#include <iostream>
#include <string>
using namespace std;

// function declarations -- do not change these two lines
// complete the function definitions below main
string Get_Name();
void Print_Welcome_Message(string name);

// do not change main
int main() {
    string name;
    name = Get_Name();
    cout<<endl;
    Print_Welcome_Message(name);
}

/* Prompt the user for their name and return it
 * input: none
 * output: a string with the user's name
 * notes: "Blackbeard", "Anne Bonne", and "Captain Jack Sparrow" 
 * are all valid names. The user may also choose not to enter 
 * a name 
 * */
string Get_Name(){
    // write your code here
    // declare a variable to hold the user's name
    string name;
   
    // prompt the user to enter their name 
    cout<<"Enter your name: ";
    getline(cin, name); //get the entire line a user inputs
    
    // get the name entered by the user
    return name;
}

/* Prints a friendly welcome message surrounded by a box of stars
 * input: a string containing the user's name
 * output: writes the welcome message to the screen
 * */
void Print_Welcome_Message(string name) {
    // replace this hard coded test message with your work
    string welcome; 
    if(name.length()>0) welcome = "* Hello " + name + "! Welcome to CS 368(C++) *";
    else     welcome = "* Hello! Welcome to CS 368(C++) *";

    //Use a for loop to keep the length 
    //of the top & bottom rows the same as the welcome message
    string astr = "", spacer = "";
    for(int i = 0; i < welcome.length(); i++) {
        astr   += "*";
        spacer += " ";
    }

    //Add astrics for the spacers between the top/bottom row & welcome message
    spacer[0] = '*'; 
    spacer[welcome.length()-1] = '*'; 

    //Print welcome message
    cout<<astr<<endl;
    cout<<spacer<<endl;
    cout<<welcome<<endl;
    cout<<spacer<<endl;
    cout<<astr<<endl;
}


