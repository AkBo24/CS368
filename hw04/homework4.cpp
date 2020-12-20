/* ******************************************************
 * Name: Akshay Bodla
 * Wisc ID: Bodla
 * OS: Linux (Mac OS)
 * IDE (or text editor): vim
 * Compiler: g++
 * How long did the assignment take you to complete in minutes:
 * What other resources did you consult (copy and paste links below):
 *
 */ // ******************************************************
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

/* Start Test Methods */

void Test_Format_Numbers();
void Test_Insert_Numbers_By_Index();
void Test_Delete_Numbers_By_Index();
void Test_Get_Numbers_Sum();
void Test_Get_Numbers_Average();
void Test_Sort_Numbers();
void Test_Sort_Ascending_And_Remove_Duplicates();
void Test_Remove_Numbers();

/* End Test Methods */

string Format_Numbers(vector<int>& numbers);
void Insert_Numbers_By_Index(vector<int>& numbers, int index, int value);
void Delete_Numbers_By_Index(vector<int>& numbers, int index);
int Get_Numbers_Sum(vector<int> numbers);
float Get_Numbers_Average(vector<int> numbers);
void Sort_Numbers(vector<int>& numbers, bool ascending = true);
void Sort_Ascending_And_Remove_Duplicates(vector<int>& numbers);
void Remove_Numbers(vector<int>& numbers, vector<int> numbers_to_remove);


int main() {
	Test_Format_Numbers();
	Test_Insert_Numbers_By_Index();
	Test_Delete_Numbers_By_Index(); 
	Test_Get_Numbers_Sum();
	Test_Get_Numbers_Average();
	Test_Sort_Numbers();
	Test_Sort_Ascending_And_Remove_Duplicates();
	Test_Remove_Numbers();

	return 0;
}

string Format_Numbers(vector<int>& numbers) {
	/*
		This function takes a vector of integers and returns a formatted string 
			of each element and it's corresponding index.
		Example: numbers = {1, 2, 3}, output="[(0, 1), (1, 2), (2, 3)]"
	*/

    string out = "[";
    for(int i = 0; i < numbers.size(); i++) 
      out += "(" + to_string(i) + ", " + to_string(numbers[i]) + "), ";

    if(numbers.size() > 0)
        out = out.substr(0,out.length()-2);
    out += "]";

    return out;
}

void Insert_Numbers_By_Index(vector<int>& numbers, int index, int value) {
	/*
	If the given index is negative, insert the value into position 0.
	If the given index is greater than the size of the vector, insert the value at the end of the vector.
	Otherwise insert the value at the index provided.
	*/

    if(index < 0) {
        numbers.insert(numbers.begin(), value);
        return;
    }
    else if(index > numbers.size()){
        //end - 1 to dereference the last position
        numbers.insert(numbers.end(), value);
        return;
    }

    //Index is in bounds, add by advancing an iterator
    auto it = numbers.begin();
    advance(it, index);
    numbers.insert(it, value);

}

void Delete_Numbers_By_Index(vector<int>& numbers, int index) {
	/*
	If the given index is negative, remove the integer at index 0.
	If the given index is greater than the size of the vector, remove the last integer in the vector.
	If the vector is empty, make no changes to the vector
	Otherwise, if the given index is valid, remove the number at that index.
	*/

    if(numbers.size() == 0) {
        return;
    }
    else if(index < 0) {
        numbers.erase(numbers.begin());
        return;
    }
    else if(index > numbers.size()){
        numbers.pop_back();
        return;
    }

    //Index is in bounds, remove by advancing an iterator 
    auto it = numbers.begin();
    advance(it, index);
    numbers.erase(it);
}

int Get_Numbers_Sum(vector<int> numbers) {
	/*
	This function computes and returns the sum of the numbers in the vector.  
	It takes one parameter: the vector of numbers. We do not need to modify the vector so use call by value to make a copy of the vector.
	*/
    int total = 0;
    for(auto it = numbers.begin(); it != numbers.end(); it++)
        total += (*it);

	return total;
}

float Get_Numbers_Average(vector<int> numbers) {
	/*
	This function computes and returns the average of the numbers in the vector.  
	It takes one parameter: the vector of numbers. We do not need to modify the vector so use call by value to make a copy of the vector.
	*/
	return numbers.size() == 0? 0 : (float)(Get_Numbers_Sum(numbers))/(float)(numbers.size());
}

void Sort_Numbers(vector<int>& numbers, bool ascending) {
	/*
	This function sorts the numbers in ascending by default.
	If ascending is false, the numbers are sorted in descending order.
	*/
   return ascending ?  sort(numbers.begin(), numbers.end()) : sort(numbers.begin(), numbers.end(), greater<int>());
}

void Sort_Ascending_And_Remove_Duplicates(vector<int>& numbers) {
	/*
	This function sorts the numbers in ascending order, then removes duplicate numbers.
	*/

    Sort_Numbers(numbers, true);
    

    //remove duplicates, numbers is gauranteed to be sorted
    //delete each duplicate that follows numbers[i]
    int curr;
    for(int i = 0; i < numbers.size(); i++) {
        curr = numbers[i];
        for(int j = i+1; j < numbers.size(); j++) {
            if(numbers[j] != curr) break;
            numbers.erase(numbers.begin()+j);
        }
    }
}

void Remove_Numbers(vector<int>& numbers, vector<int> numbers_to_remove) {
	/*
	This function removes ALL occurences of numbers in numbers_to_remove from numbers (if present).	
	Example: If numbers = {0, 1, 2, 3, 3} and numbers_to_remove = {3}, numbers becomes: {0, 1, 2}
	*/

    if (numbers.empty()) return;


    vector<int>::iterator instance;
    for(auto remove = numbers_to_remove.begin(); remove != numbers_to_remove.end(); remove++) {
        
        //iterate until we can no longer find any instances of the number to remove
        while((instance = find(numbers.begin(), numbers.end(), *remove)) != numbers.end())
           // cout << "Instance position: " << *instance << endl
           //      << "Size :" << numbers.size() << endl
           //      << "Remove Number: " << *remove << endl
           //      << "Before: " << Format_Numbers(numbers )<< endl;
            numbers.erase(instance);
            //cout << "After: " << Format_Numbers(numbers) << endl << endl;
    }
}


/*
	The Below Functions Are For Testing Purposes Only
*/

template<typename T1, typename T2>
void Assert_With_Message(string test_name, T1 v1, T2 v2) {
	cout << endl << "Test ";
	if (v1 != v2) {
		cout << "Failed: " << test_name << endl;
		cout << v1 << " != " << v2 << endl;
		exit(EXIT_FAILURE);
	} else {
		cout << "Passed: " << test_name << endl;
	}
}

void Test_Format_Numbers() {
	// Test when numbers is empty
	vector<int> numbers = {};
	Assert_With_Message("Format_Numbers - Empty Vector", Format_Numbers(numbers), "[]");

	// Test positive numbers
	numbers = {1, 2, 3, 5, 8};
	Assert_With_Message(
		"Format_Numbers - Vector with Positive Ints", 
		Format_Numbers(numbers), 
		"[(0, 1), (1, 2), (2, 3), (3, 5), (4, 8)]"
	);

	// Test negative numbers
	numbers = {-1, -2, -3, -5, -8};
	Assert_With_Message(
		"Format_Numbers - Vector with Negative Ints",
		Format_Numbers(numbers),
		"[(0, -1), (1, -2), (2, -3), (3, -5), (4, -8)]"
	);
}

void Test_Insert_Numbers_By_Index() {
	// Test when numbers is empty
	vector<int> numbers = {};
	vector<int> expected_result = {10};
	Insert_Numbers_By_Index(numbers, 0, 10);
	Assert_With_Message("Insert_Numbers_By_Index - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with negative index
	numbers = {1, 2, 3};
	expected_result = {10, 1, 2, 3};
	Insert_Numbers_By_Index(numbers, -2, 10);
	Assert_With_Message("Insert_Numbers_By_Index - Negative", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test positive indexes within bounds
	numbers = {1, 2, 3};
	expected_result = {1, 10, 2, 3};
	Insert_Numbers_By_Index(numbers, 1, 10);
	Assert_With_Message("Insert_Numbers_By_Index - Insert at Index", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test positive indexes out of bounds
	numbers = {1, 2, 3};
	expected_result = {1, 2, 3, 10};
	Insert_Numbers_By_Index(numbers, 6, 10);
	Assert_With_Message(
		"Insert_Numbers_By_Index - Index Bigger Than Vector", 
		Format_Numbers(numbers), 
		Format_Numbers(expected_result)
	);
}

void Test_Delete_Numbers_By_Index() {
	// Test when numbers is empty
	vector<int> numbers = {};
	vector<int> expected_result = {};
	Delete_Numbers_By_Index(numbers, 0);
	Assert_With_Message("Delete_Numbers_By_Index - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with negative index
	numbers = {1, 2, 3};
	expected_result = {2, 3};
	Delete_Numbers_By_Index(numbers, -2);
	Assert_With_Message("Delete_Numbers_By_Index - Negative", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test positive indexes within bounds
	numbers = {1, 2, 3};
	expected_result = {1, 3};
	Delete_Numbers_By_Index(numbers, 1);
	Assert_With_Message("Delete_Numbers_By_Index - Insert at Index", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test positive indexes out of bounds
	numbers = {1, 2, 3};
	expected_result = {1, 2};
	Delete_Numbers_By_Index(numbers, 10);
	Assert_With_Message(
		"Delete_Numbers_By_Index - Index Bigger Than Vector", 
		Format_Numbers(numbers), 
		Format_Numbers(expected_result)
	);
}

void Test_Get_Numbers_Sum() {
	// Test when numbers is empty
	vector<int> numbers = {};
	int expected_result = 0;
	Assert_With_Message("Get_Numbers_Sum - Empty Vector", Get_Numbers_Sum(numbers), expected_result);

	// Test with negative numbers
	numbers = {-1, -2, -3};
	expected_result = -6;
	Assert_With_Message("Get_Numbers_Sum - Negative", Get_Numbers_Sum(numbers), expected_result);

	// Test with positive numbers
	numbers = {1, 2, 3};
	expected_result = 6;
	Assert_With_Message("Get_Numbers_Sum - Positive", Get_Numbers_Sum(numbers), expected_result);
}

void Test_Get_Numbers_Average() {
	// Test when numbers is empty
	vector<int> numbers = {};
	float expected_result = 0;
	Assert_With_Message("Get_Numbers_Average - Empty Vector", Get_Numbers_Average(numbers), expected_result);

	// Test with negative numbers
	numbers = {-1, -2, -3};
	expected_result = -2;
	Assert_With_Message("Get_Numbers_Average - Negative", Get_Numbers_Average(numbers), expected_result);

	// Test with positive numbers
	numbers = {1, 2, 3};
	expected_result = 2;
	Assert_With_Message("Get_Numbers_Average - Positive", Get_Numbers_Average(numbers), expected_result);	

	// Test with float answer
	numbers = {1, 1, 2, 3};
	expected_result = 1.75;
	Assert_With_Message("Get_Numbers_Average - Float Answer", Get_Numbers_Average(numbers), expected_result);	
}

void Test_Sort_Numbers() {
	// Test when numbers is empty
	vector<int> numbers = {};
	vector<int> expected_result = {};
	Sort_Numbers(numbers);
	Assert_With_Message("Sort_Numbers - Ascending - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	numbers = {};
	expected_result = {};
	Sort_Numbers(numbers, false);
	Assert_With_Message("Sort_Numbers - Descending - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive numbers
	numbers = {5, 0, 2, 3, 1, 4};
	expected_result = {0, 1, 2, 3, 4, 5};
	Sort_Numbers(numbers);
	Assert_With_Message("Sort_Numbers - Ascending - Positive Nums", Format_Numbers(numbers), Format_Numbers(expected_result));

	numbers = {5, 0, 2, 3, 1, 4};
	expected_result = {5, 4, 3, 2, 1, 0};
	Sort_Numbers(numbers, false);
	Assert_With_Message("Sort_Numbers - Descending - Positive Nums", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive and negative numbers
	numbers = {5, 0, 2, -3, 1, -4};
	expected_result = {-4, -3, 0, 1, 2, 5};
	Sort_Numbers(numbers);
	Assert_With_Message("Sort_Numbers - Ascending - All Nums", Format_Numbers(numbers), Format_Numbers(expected_result));

	numbers = {5, 0, 2, -3, 1, -4};
	expected_result = {5, 2, 1, 0, -3, -4};
	Sort_Numbers(numbers, false);
	Assert_With_Message("Sort_Numbers - Descending - All Nums", Format_Numbers(numbers), Format_Numbers(expected_result));
}

void Test_Sort_Ascending_And_Remove_Duplicates() {
	// Test when numbers is empty
	vector<int> numbers = {};
	vector<int> expected_result = {};
	Sort_Ascending_And_Remove_Duplicates(numbers);
	Assert_With_Message("Sort_Ascending_And_Remove_Duplicates - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive numbers
	numbers = {0, 5, 0, 2, 1, 3, 1, 4, 2};
	expected_result = {0, 1, 2, 3, 4, 5};
	Sort_Ascending_And_Remove_Duplicates(numbers);
	Assert_With_Message("Sort_Ascending_And_Remove_Duplicates - Positive Nums", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive and negative numbers
	numbers = {5, -3, 0, 2, -3, 1, -4, 0};
	expected_result = {-4, -3, 0, 1, 2, 5};
	Sort_Ascending_And_Remove_Duplicates(numbers);
	Assert_With_Message("Sort_Ascending_And_Remove_Duplicates - All Nums", Format_Numbers(numbers), Format_Numbers(expected_result));
}

void Test_Remove_Numbers() {
	// Test when numbers is empty
	vector<int> numbers = {}, numbers_to_remove = {};
	vector<int> expected_result = {};
	Remove_Numbers(numbers, numbers_to_remove);
	Assert_With_Message("Remove_Numbers - Empty Vector", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive numbers
	numbers = {0, 5, 0, 2, 1, 3, 1, 4, 2};
	numbers_to_remove = {0, 1, 5};
	expected_result = {2, 3, 4, 2};
	Remove_Numbers(numbers, numbers_to_remove);
	Assert_With_Message("Remove_Numbers - Positive Nums", Format_Numbers(numbers), Format_Numbers(expected_result));

	// Test with positive and negative numbers
	numbers = {5, -3, 0, 2, -3, 1, -4, 0};
	numbers_to_remove = {0, 1, 5, -3, -4};
	expected_result = {2};
	Remove_Numbers(numbers, numbers_to_remove);
	Assert_With_Message("Remove_Numbers - All Nums", Format_Numbers(numbers), Format_Numbers(expected_result));
}
