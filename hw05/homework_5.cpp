/* ******************************************************
 * Name: Akshay Bodla
 * Wisc ID: bodla
 * OS: linux
 * IDE (or text editor): vim
 * Compiler: g++
 * How long did the assignment take you to complete in minutes:
 * What other resources did you consult (copy and paste links below):
 *
 */ // ******************************************************
#include <iostream>
#include <map>
#include <set>

using namespace std;

/*
Notes:
	1. Do not modify the names of any templated classes or functions. 
		- Custom classes and functions may be added as part of the solution, 
		  however, the tests will be run against the templated classes / functions
	2. If you find an error in this script, please post in piazza.
	3. Compile and run this file on the CSL machines before your final submission.
*/

/* Start Test Methods */
void Test_Show_Ship_Manifest();
void Test_Drop_Off_Passengers();
void Test_Combine_Manifests();
void Test_Get_Passengers_Overlapping_Desired_Destinations();
/* End Test Methods */

/* Prototypes for the functions you will write */
string Show_Ship_Manifest(map<string, set<string> > ship_manifest);
map<string, set<string> > Drop_Off_Passengers(map<string, set<string> > ship_manifest, set<string> passengers);
map<string, set<string> > Combine_Manifests(map<string, set<string> > ship_manifest, map<string, set<string> > other_ship_manifest);
set<string> Get_Passengers_Overlapping_Desired_Destinations(map<string, set<string> > ship_manifest, set<string> passengers);

int main() {
	Test_Show_Ship_Manifest();
	Test_Drop_Off_Passengers();
	Test_Combine_Manifests();
	Test_Get_Passengers_Overlapping_Desired_Destinations();
	return 0;
}

string Show_Ship_Manifest(map<string, set<string> > ship_manifest) {
	/*This function formats a given ship manifest.
	Args:
		ship_manifest: mapping of passengers to the planets each passenger wants to visit.
	Returns:
		A string representing the ship manifest. 
	Example:
		ship_manifest = {"Passenger 001": {"Venus"}, "Passenger 002": {"Earth", "Mars"}}
		output="{Passenger 001: {Venus}, Passenger 002: {Earth, Mars}}"
	*/

    if (ship_manifest.empty()) return "{}";

    string out = "{", curr = "";
    for (auto e : ship_manifest) {
        //cout << e.first << endl;
       
        //add all destinations to output
        curr = e.first+": {"; 
        for (auto dest : e.second) {
            curr += dest + ", ";
        }

        //remve last ", " if e.second is not empty
        if(!e.second.empty())
            curr = curr.substr(0,curr.length()-2);
        out += curr+"}, ";

    }

    //remove last "}, " from output
    out = out.substr(0, out.length()-3);
	return out+"}}";
}

map<string, set<string> > Drop_Off_Passengers(map<string, set<string> > ship_manifest, set<string> passengers) {
	/*This function removes passengers from a ship's manifest. If a passenger to remove is not on the manifest, do nothing for that passenger and continue removing the other passengers.
	Args:
		ship_manifest: mapping of passengers to the planets each passenger wants to visit.
		passengers: set of passengers to remove from the ship manifest. 
	Returns:
		A new ship manifest mapping that does not contain any of the removed passengers.
	Example:
		ship_manifest = {"Passenger 001": {"Venus"}, "Passenger 002": {"Earth", "Mars"}}
		passengers = {"Passenger 002", "Passenger 003"}
		result = {"Passenger 001": {"Venus"}}
	*/
    map<string, set<string> > kept(ship_manifest);
    for (auto pass : passengers){
        
        //skip passenger if passenger not in ship_manifest
        if(!kept.count(pass))
            continue;

        //erase passenger from kept manifest
        map<string, set<string> >::iterator it = kept.find(pass); 
        kept.erase(it);

    }
	return kept;
}

map<string, set<string> > Combine_Manifests(map<string, set<string> > ship_manifest, map<string, set<string> > other_ship_manifest) {
	/*This function combines the manifests of 2 ships. These ships CAN have the same passengers that CAN have different desired planets. 
	Args:
		ship_manifest: mapping of passengers to the planets each passenger wants to visit.
		other_ship_manifest: mapping of passengers to the planets each passenger wants to visit. 
	Returns:
		A new ship manifest mapping that contains the union of passengers and their destinations from both ships. 
	Example:
		ship_manifest = {"Passenger 001": {"Venus"}, "Passenger 002": {"Earth", "Mars"}}
		other_ship_manifest = {"Passenger 002": {"Venus"}, "Passenger 003": {"Pluto""}}

		result = {"Passenger 001": {"Venus"}, "Passenger 002": {"Earth", "Mars", "Venus"}, "Passenger 003": {"Pluto""}}
	*/

    if(ship_manifest.empty())
        return map<string, set<string> > (other_ship_manifest);
    if(other_ship_manifest.empty())
        return map<string, set<string> > (ship_manifest);

    //case: neither manifest is empty
    map <string, set<string> > both;
    pair<string, set<string> > other;

    //first iterate through ship_manifest
    for(auto pass : ship_manifest){
        
        //check if the current passenger is in other manifest
        //if not, then add the current passenger data as is
        if(other_ship_manifest.count(pass.first)) {

            //if yes, create a set containing both planets and then add to the 
            //combined data
            set<string> dests;
            other = *(other_ship_manifest.find(pass.first));

            dests.insert(pass.second.begin(), pass.second.end());
            dests.insert(other.second.begin(), other.second.end());

            both[pass.first] = dests;
        }
        else
            both[pass.first] = pass.second;
    }


    //iterate through the other manifest, add any passengers not in both and not in first manifest
    for(auto pass : other_ship_manifest) {
        if(both.count(pass.first)) //skip if cur passenger is already in both manifests
            continue;
        both[pass.first] = pass.second;
    }

	return both;
}

set<string> Get_Passengers_Overlapping_Desired_Destinations(map<string, set<string> > ship_manifest, set<string> passengers) {
	/*This function gets overlapping desired destinations for a group of passengers 
	Args:
		ship_manifest: mapping of passengers to the planets each passenger wants to visit.
		passengers: set of passengers
	Returns:
		A set of destinations that each of the passengers in the group share
	Example:
		ship_manifest = {"Passenger 001": {"Venus", "Mars", "Pluto"}, "Passenger 002": {"Venus"}, "Passenger 003": {"Venus", "Mars"}}
		passengers = {"Passenger 001", "Passenger 003"}
		result = {"Venus", "Mars"}
	*/

    multiset<string> all;
    set<string> overlap;

    //first get all of the planets for the group of passengers
    for(auto e : ship_manifest) {
        if(!passengers.count(e.first))
            continue;

        for(auto planet : e.second)
            all.insert(planet);
        //all.insert(e.second);
    }


    //iterate through all planets and count the number of times the planet is in all
    //if count == to the size of passenger groups, then it is shared between the passengers
    for(auto planet : all) {
        if(all.count(planet) == passengers.size())
            overlap.insert(planet);
    }

	return overlap;
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

string Show_Set(set<string> my_set) {
	string res = "{";

	int i = 0;
	for(auto const& el: my_set) {
		res = res + el;
		if(i < my_set.size() - 1) {
			res += ", ";
		}
		i += 1;
	}
	res += "}";
	return res;
}

void Test_Show_Ship_Manifest() {
	Assert_With_Message(
		"Show_Ship_Manifest - Empty Manifest", 
		Show_Ship_Manifest({}),
		"{}"
	);

	Assert_With_Message(
		"Show_Ship_Manifest - One Passenger in Manifest", 
		Show_Ship_Manifest(
			{
				{"Passenger 001", {"Venus"}}, 
			}
		),
		"{Passenger 001: {Venus}}"
	);

	Assert_With_Message(
		"Show_Ship_Manifest - One Passenger Without Destination in Manifest", 
		Show_Ship_Manifest(
			{
				{"Passenger 001", {}}, 
			}
		),
		"{Passenger 001: {}}"
	);

	Assert_With_Message(
		"Show_Ship_Manifest - Multiple Passengers in Manifest", 
		Show_Ship_Manifest(
			{
				{"Passenger 001", {"Venus"}}, 
				{"Passenger 002", {"Earth", "Mars"}},
				{"Passenger 003", {"Earth", "Neptune", "Pluto"}}
			}
		),
		"{Passenger 001: {Venus}, Passenger 002: {Earth, Mars}, Passenger 003: {Earth, Neptune, Pluto}}"
	);
}
void Test_Drop_Off_Passengers() {
	Assert_With_Message(
		"Drop_Off_Passengers - Empty Manifest, Empty Passenger", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{},
				{}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Drop_Off_Passengers - Remove One Passenger from Empty Manifest", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{},
				{"Passenger 001"}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Drop_Off_Passengers - Remove One Passenger from Manifest", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{
					{"Passenger 001", {}}
				}, 
				{"Passenger 001"}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Drop_Off_Passengers - Remove One Passenger from Manifest", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{
					{"Passenger 001", {"Venus"}}, 
					{"Passenger 002", {"Earth", "Mars"}},
					{"Passenger 003", {"Earth", "Neptune", "Pluto"}}
				},
				{"Passenger 003"}
			)
		),
		"{Passenger 001: {Venus}, Passenger 002: {Earth, Mars}}"
	);
	Assert_With_Message(
		"Drop_Off_Passengers - Remove Two Passengers from Manifest", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{
					{"Passenger 001", {"Venus"}}, 
					{"Passenger 002", {"Earth", "Mars"}},
					{"Passenger 003", {"Earth", "Neptune", "Pluto"}}
				},
				{"Passenger 002", "Passenger 003"}
			)
		),
		"{Passenger 001: {Venus}}"
	);
	Assert_With_Message(
		"Drop_Off_Passengers - Remove Two Passengers from Manifest with 2 Unremoved", 
		Show_Ship_Manifest(
			Drop_Off_Passengers(
				{
					{"Passenger 001", {"Venus"}}, 
					{"Passenger 002", {"Earth", "Mars"}},
					{"Passenger 003", {"Earth", "Neptune", "Pluto"}}
				},
				{"Passenger 002", "Passenger 003", "Passenger 004", "Passenger 005"}
			)
		),
		"{Passenger 001: {Venus}}"
	);
}

void Test_Combine_Manifests() {
	Assert_With_Message(
		"Combine_Manifests - Empty Manifests", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{},
				{}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Combine_Manifests - One Empty Manifest", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{
					{"Passenger 001", {"Venus"}}
				}, 
				{}
			)
		),
		"{Passenger 001: {Venus}}"
	);
	Assert_With_Message(
		"Combine_Manifests - One Empty Manifest (2)", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{},
				{
					{"Passenger 001", {"Venus"}}
				}
			)
		),
		"{Passenger 001: {Venus}}"
	);
	Assert_With_Message(
		"Combine_Manifests - Manifests With Unshared Passengers", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{
					{"Passenger 001", {"Venus"}}
				}, 
				{
					{"Passenger 002", {"Venus"}}
				}
			)
		),
		"{Passenger 001: {Venus}, Passenger 002: {Venus}}"
	);
	Assert_With_Message(
		"Combine_Manifests - Manifests With Shared Passengers", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{
					{"Passenger 001", {"Venus", "Neptune"}}
				}, 
				{
					{"Passenger 001", {"Venus", "Mars"}}
				}
			)
		),
		"{Passenger 001: {Mars, Neptune, Venus}}"
	);
	Assert_With_Message(
		"Combine_Manifests - Manifests With Shared and Unshared Passengers", 
		Show_Ship_Manifest(
			Combine_Manifests(
				{
					{"Passenger 001", {}},
					{"Passenger 002", {"Neptune"}},
					{"Passenger 003", {"Pluto"}},
					{"Passenger 004", {"Saturn"}}
				}, 
				{
					{"Passenger 001", {"Venus"}},
					{"Passenger 002", {}},
					{"Passenger 003", {"Mars"}},
					{"Passenger 005", {"Jupiter"}}
				}
			)
		),
		"{Passenger 001: {Venus}, Passenger 002: {Neptune}, Passenger 003: {Mars, Pluto}, Passenger 004: {Saturn}, Passenger 005: {Jupiter}}"
	);
}

void Test_Get_Passengers_Overlapping_Desired_Destinations() {
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Empty Manifest, Empty Passengers", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{},
				{}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Empty Manifest, Non-Empty Passengers", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{},
				{"Passenger 001"}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Non-Empty Manifest, Empty Passengers", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {}},
				},
				{}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - 1 Passenger In Manifest", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {"Venus"}},
				},
				{"Passenger 001"}
			)
		),
		"{Venus}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - 1 Passenger Not In Manifest", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {}},
				},
				{"Passenger 002"}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With No Overlap", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {"Venus"}},
					{"Passenger 002", {"Mars"}},
					{"Passenger 003", {"Neptune"}},
					{"Passenger 004", {"Pluto"}},
					{"Passenger 005", {"Mercury"}},
					{"Passenger 006", {"Uranus"}},
					{"Passenger 007", {"Jupiter"}},
					{"Passenger 008", {"Saturn"}},
					{"Passenger 009", {"Earth"}}
				},
				{"Passenger 001", "Passenger 009"}
			)
		),
		"{}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With Overlap", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {"Venus", "Earth"}},
					{"Passenger 002", {"Mars", "Earth"}},
					{"Passenger 003", {"Neptune"}},
					{"Passenger 004", {"Pluto"}},
					{"Passenger 005", {"Mercury", "Earth"}},
					{"Passenger 006", {"Uranus", "Earth"}},
					{"Passenger 007", {"Jupiter"}},
					{"Passenger 008", {"Saturn"}},
					{"Passenger 009", {"Earth", "Mars"}}
				},
				{"Passenger 001", "Passenger 002", "Passenger 005", "Passenger 009"}
			)
		),
		"{Earth}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With Multiple Overlap", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {"Venus", "Earth"}},
					{"Passenger 002", {"Mars", "Earth", "Venus"}},
					{"Passenger 003", {"Neptune"}},
					{"Passenger 004", {"Pluto"}},
					{"Passenger 005", {"Mercury", "Earth", "Venus"}},
					{"Passenger 006", {"Uranus", "Earth", "Venus"}},
					{"Passenger 007", {"Jupiter"}},
					{"Passenger 008", {"Saturn"}},
					{"Passenger 009", {"Earth", "Mars", "Venus"}}
				},
				{"Passenger 001", "Passenger 002", "Passenger 005", "Passenger 009"}
			)
		),
		"{Earth, Venus}"
	);
	Assert_With_Message(
		"Get_Passengers_Overlapping_Desired_Destinations - Manifest With Passengers With One Group Member Missing", 
		Show_Set(
			Get_Passengers_Overlapping_Desired_Destinations(
				{
					{"Passenger 001", {"Venus", "Earth"}},
					{"Passenger 002", {"Mars", "Earth", "Venus"}},
					{"Passenger 003", {"Neptune"}},
					{"Passenger 004", {"Pluto"}},
					{"Passenger 005", {"Mercury", "Earth", "Venus"}},
					{"Passenger 006", {"Uranus", "Earth", "Venus"}},
					{"Passenger 007", {"Jupiter"}},
					{"Passenger 008", {"Saturn"}},
					{"Passenger 009", {"Earth", "Mars", "Venus"}}
				},
				{"Passenger 001", "Passenger 002", "Passenger 005", "Passenger ???"}
			)
		),
		"{}"
	);
}
