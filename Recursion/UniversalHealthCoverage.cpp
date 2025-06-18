/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "console.h"
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "simpio.h"

using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
Vector<Vector<Set<string>>> findSubsets(Vector<Set<string>>& locations) {
	Vector<Vector<Set<string>>> allSubsets;
     if(locations.size()==0){
        Vector< Set<string> > emptySet;
		allSubsets.add(emptySet);
        return allSubsets;
    }

    Set<string> loc = locations[0];
    locations.remove(0);
    Vector<Vector<Set<string>>> result=findSubsets(locations);
    allSubsets=result;
    for(int i = 0; i < result.size(); i++){
        Vector<Set<string>> subset = result[i];
        subset.add(loc);
        allSubsets.add(subset);
    }
    return allSubsets;
}
Set<string> makeVectIntoSet(Vector<Set<string> > v){
	Set<string> res;
	foreach(Set<string> set in v){
		foreach(string s in set){
				res.add(s);
			}
		}
		return res;
	}

bool containsEveryString(Vector<Set<string> > v,Set<string> cities){
	Set<string> vectIntoSet=makeVectIntoSet(v);
	if(vectIntoSet!=cities){
		return false;
	}
	return true;
}
void checkTheSubs(Set<string> cities, Vector<Vector<Set<string> > >  &subsets){
	Vector<Vector<Set<string> > >  newV;
	for( int i=0; i<subsets.size();i++){
		if(containsEveryString(subsets[i], cities)){
			newV.add(subsets[i]);
		}	
	}
	subsets=newV;	
}
void findMinimalSize(Vector<Vector<Set<string> > >  allSubsetsOfLocs, Vector< Set<string> >& result,int &minSize){
	for(int i=0;i<allSubsetsOfLocs.size(); i++){
		if(allSubsetsOfLocs[i].size()<minSize){
			minSize=allSubsetsOfLocs[i].size();
			result=allSubsetsOfLocs[i];
		}
	}	
}
void generateTheRes(Set<string>& cities,Vector< Set<string> > locations,int numHospitals,Vector< Set<string> >& result){
	int locationsSize=locations.size();
	Vector<Vector<Set<string> > >  allSubsetsOfLocs=findSubsets(locations);
	checkTheSubs(cities, allSubsetsOfLocs);
	findMinimalSize(allSubsetsOfLocs, result, locationsSize);
	
}
bool canOfferUniversalCoverage(Set<string>& cities,Vector< Set<string> >& locations,int numHospitals,Vector< Set<string> >& result){
	  generateTheRes(cities, locations, numHospitals, result);
		if(result.size()<=numHospitals){
			 return true;
		  }
		else{
		 result.clear();
		 return false;
		}          
}


int main() {
	Vector<Set<string> > locations;
	Set<string> setOfLocs;
	for(int i=0;i <4; i++){
		locations.add(setOfLocs);
	}
	locations[0] += "A", "B", "C";
	locations[1] += "A", "C", "D";
	locations[2] += "B", "F";
	locations[3] += "C", "E", "F";
	Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F";
	Vector<Set<string> > result;
	int numHospitals = getInteger("Enter maximum amount of hospitals: ");
	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout<<"it is possible"<<endl;
		cout << result << endl;
	}
	else{
		cout<<"it is not possible"<<endl;
		cout<<result<<endl;
	}
	return 0;
    
}
