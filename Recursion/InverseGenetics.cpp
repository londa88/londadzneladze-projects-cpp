/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"

using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein

 */
void makeSubsetsHelper(string protein, string current, Map<char, Set<string>> codons, Set<string>& result) {
    if (protein.size()==0) {
        result.add(current);
        return;
    }
    
    Set<string> rnaList = codons.get(protein[0]);
    foreach (string rna in rnaList) {
        makeSubsetsHelper(protein.substr(1), current + rna, codons, result);
    }
}
Set<string> makeSubsets(string protein, Map<char, Set<string>> codons) {
    Set<string> result;
    makeSubsetsHelper(protein, "", codons, result);
    return result;
}
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	 Set<string> allSubsets=makeSubsets(protein, codons);
	 foreach(string str in allSubsets){
		 cout<<str<<endl;
	 }
	
}


Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string enterProtein=getLine("protein: ");
	string protein=toUpperCase(enterProtein);
	
	listAllRNAStrandsFor(protein, codons);

	

    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
