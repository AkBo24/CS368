// writing on a text file
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <string.h> 
#include <bits/stdc++.h>

using namespace std;

const int MAX_NUMBER_OF_CUSTOMERS = 30;
const int MAX_NUMBER_OF_ITEM_TYPES = 15;

void getUnits(int* orders, string quantity, int max_orders);

/* TESTING
  To test your homework_3.cpp file, run: 
  
  ./run_tests.sh 
  
 You may need to first run - if you get a permission denied error: 
 
  chmod a+rwx run_tests.sh 

 When you first test, you will fail all test cases. Modify your code, retest, then modify again. Test driven development!
*/

  
// THIS IS A UTILITY FUNCTION USED FOR TESTING. DO NOT MODIFY.
void Print_Variables(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, double costs[], double percents[], const string input_filename);

// THESE ARE THE FOUR FUNCTIONS YOU WILL IMPLEMENT.
void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename);
void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers);
void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], double percents[], int number_of_customers, int number_of_items);
void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2],double costs[], double percents[], int number_of_customers, string output_filename);

int main () { 
    string customer_orders_filename, formatted_output_filename;
    cin >> customer_orders_filename >> formatted_output_filename;

    int number_of_items=0;
    int number_of_customers=0;
    string names[MAX_NUMBER_OF_CUSTOMERS][2];
    int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES];
    double prices[MAX_NUMBER_OF_ITEM_TYPES] = {0.0};
    double costs[MAX_NUMBER_OF_CUSTOMERS] = {0.0};
    double percents[MAX_NUMBER_OF_CUSTOMERS] = {0.0};

    Read_Customer_Orders_File(names, orders, prices, &number_of_customers, &number_of_items, customer_orders_filename);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);
   
    Format_Case_Of_Names(names, number_of_customers);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);
    
    Compute_Total_Cost_And_Percent(orders, prices, costs, percents, number_of_customers, number_of_items);
    Print_Variables(names, orders, prices, &number_of_customers, &number_of_items, costs, percents, customer_orders_filename);
    
    Write_Formatted_Summary(names, costs, percents, number_of_customers, formatted_output_filename);
    
    return 0;
}

void Read_Customer_Orders_File(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], 
                                    double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, const string input_filename) {
    ifstream cus_orders;
    cus_orders.open(input_filename, ios::in);

    if(!cus_orders)
        throw "File does not exist!";


    //first get the num of customers and items, tehn iterate getting all the orders
    string temp;
    getline(cus_orders, temp);
    *number_of_customers = stoi((temp.substr(temp.find(" ")+1)));

    getline(cus_orders, temp);
    *number_of_items = stoi((temp.substr(temp.find(" ")+1)));

    //get the line with prices and tokenize the line to get the prices
    getline(cus_orders, temp);
    int i = 0;
    while(temp.find(" ") != -1) {
        //try to convert the string into a float, if stof throws an error 
        //skip and "advance" the token
        try{
            prices[i] = stof(temp.substr(temp.find(" ") + 1));
            i++;
        }
        catch (invalid_argument& e) {
            
        }
        temp = temp.substr(temp.find(" ")+1);
    }

    //parse each order by field
    i = 0;
    while(getline(cus_orders, temp)) {
       temp = temp.substr(temp.find(" ") + 1); //skip customer id
       names[i][0] = temp.substr(0, temp.find(" ")); //get first name

       temp = temp.substr(temp.find(" ") + 1); //get next token
       names[i][1] = temp.substr(0,temp.find(" ")); // get last name

       temp = temp.substr(temp.find(" ") + 1); //get next token
       getUnits(orders[i], temp, *number_of_items ); //temp now points to the quantities
       i++;
    }
}

void getUnits(int* orders, string quantity, int max_orders) {
  int order_pos = 0, next_quant = quantity.find(" ");

  while(order_pos <= max_orders) {
    orders[order_pos] = stoi(quantity.substr(0, next_quant));
    quantity   = quantity.substr(next_quant+1);
    next_quant = quantity.find(" ");
    order_pos++;
  }
}

void Format_Case_Of_Names(string names[MAX_NUMBER_OF_CUSTOMERS][2], const int number_of_customers) { 

    //Make everything lower case, then capitalize the first letters of the first and last name
    for(int i = 0; i < number_of_customers; i++) {
       
        //toLower of first name
        for(long unsigned int j = 0; j < names[i][0].length(); j++) {
            if((int) names[i][0][j] >= 65 && (int) names[i][0][j] <= 90) 
                names[i][0][j] += 32;
        }
        
        //toLower of last name
        for(long unsigned int j = 0; j < names[i][1].length(); j++) {
            if((int) names[i][1][j] >= 65 && (int) names[i][1][j] <= 90) 
                names[i][1][j] += 32;
        }

        //Capitalize the first letters
        names[i][0][0] -= 32;
        names[i][1][0] -= 32;
    }

}

void Compute_Total_Cost_And_Percent(int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], double costs[], 
                                                        double percents[], int number_of_customers, int number_of_items) {
    
    //calculate the costs of each order and the total revenue
    float order_tot = 0, revenue = 0;    
    for(int order = 0; order < number_of_customers; ++order) {
        for(int item = 0; item < number_of_items; item++)
            order_tot += orders[order][item]*prices[item];
        costs[order] = order_tot;
        revenue += order_tot;
        order_tot = 0;
    }

    //find the revenue % each order took
    for(int order = 0; order < number_of_customers; order++){
        percents[order] = (costs[order]/revenue) * 100;
    }
}

void Write_Formatted_Summary(string names[MAX_NUMBER_OF_CUSTOMERS][2], double costs[], double percents[], int number_of_customers, string output_filename) {

    //opening output file
    ofstream outfile;
    outfile.open(output_filename, ios::out | ios::trunc);

    if(!outfile)
        throw "Error writing to output file";


    //generate output order-by-order, cost will format the cost and percent output
    string output  = "", cost = "";
    for(int cus = 0; cus < number_of_customers; cus++) {
        output = names[cus][1] + ", " + names[cus][0];

        //append the name and costs to the table
        outfile << output;
        outfile << setw(40-output.length()) << setprecision(2) << fixed << costs[cus];

        //append the percent to the table
        outfile << setw(20) << setprecision(1) << fixed << percents[cus] << endl;
    }

}


// THIS IS A UTILITY FUNCTION USED FOR TESTING. DO NOT MODIFY.
void Print_Variables(string names[MAX_NUMBER_OF_CUSTOMERS][2], int orders[MAX_NUMBER_OF_CUSTOMERS][MAX_NUMBER_OF_ITEM_TYPES], double prices[MAX_NUMBER_OF_ITEM_TYPES], int *number_of_customers, int *number_of_items, double costs[], double percents[], const string input_filename) {
    cout << "---- Start Test Output ----" << endl;
    cout << *number_of_customers << endl;
    cout << *number_of_items << endl;
    for (int i = 0; i < *number_of_items; ++i) {
      cout << "$" << prices[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < *number_of_customers; ++i) {
        cout << names[i][1] << ", " << names[i][0] << ": ";
        cout << "Orders=[";
        for (int j = 0; j < *number_of_items; ++j) {
            cout << orders[i][j] << ',';
        }
        cout << "], Cost=" << costs[i];
        cout << ", Percent=" << percents[i] << endl;
    }
    cout << "---- End Test Output ----" << endl;
}
