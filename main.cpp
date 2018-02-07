#include "RandomProjection.h"
#include "MrMotif.h"
#include "Distances.h"
#include "Word.h"
#include "WordElem.h"
#include "TSUtils.h"
#include "ParallelRandomProjection.h"

#include "SAX.h"
#include "WordElem.h"
#include "Word.h"

#include <iostream>
#include <fstream>
#include <ctime>

#define LENGTH 10

void fill_array(std::vector<double>& a){
	for (int i = 0; i < a.size(); i++)
		a.at(i) = (double)i;
}

void print_vector(std::vector<double>& a){
	for (int i = 0; i < a.size(); i++){
		double tmp = a.at(i);
		printf("%.2f , ", tmp);
	}
	printf("\n");
}

void temp(std::vector<double>& ad, int l, int i){
	std::vector<double> tmp ( ad.begin()+l, ad.begin()+i );
	printf("Size: %d\n", tmp.size());
	std::vector<double>::iterator it;
	for ( it=tmp.begin() ; it < tmp.end(); it++ )
		printf("%.2f ", *it);
	printf("\n");
}

void test_distances(){

	WordElem we11 ( 3, 4 );
	WordElem we12 ( 3, 4 );
	WordElem we13 ( 1, 4 );
	WordElem we14 ( 0, 4 );
	std::vector<WordElem> arraylist;
	arraylist.push_back(we11);
	arraylist.push_back(we12);
	arraylist.push_back(we13);
	arraylist.push_back(we14);
	std::vector<int> vector;
	vector.push_back(4);
	vector.push_back(4);
	vector.push_back(4);
	vector.push_back(4);

	Word word (arraylist, vector, 4);

	WordElem we21 ( 0, 4 );
	WordElem we22 ( 1, 4 );
	WordElem we23 ( 3, 4 );
	WordElem we24 ( 3, 4 );
	std::vector<WordElem> arraylist1;
	arraylist1.push_back(we21);
	arraylist1.push_back(we22);
	arraylist1.push_back(we23);
	arraylist1.push_back(we24);
	std::vector<int> vector1;
	vector1.push_back(4);
	vector1.push_back(4);
	vector1.push_back(4);
	vector1.push_back(4);

	Word word1 (arraylist1, vector1, 4);

	printf("%.16f\n", Distances::minDist(8, 4, word, word1));
}

void test_distLookupTable(){
	printf("%.17f\n", DistLookupTable::cell(54, 4, 2));
}


void testWord() {
	WordElem wordelem  (4, 8);
	WordElem wordelem1 (4, 8);
	WordElem wordelem2 (1, 2);
	WordElem wordelem3 (3, 4);

	std::cout << wordelem.equals(wordelem1) << std::endl;
	std::cout << wordelem.equals(wordelem2) << std::endl;
	std::cout << wordelem.equals(wordelem3) << std::endl;
	std::cout << wordelem2.equals(wordelem3) << std::endl;

	std::cout << Utils::padBytesToCardinality("001", 16) << std::endl;

	double ad[] = {-10, 3, 2, 22, -81, -25, 20, 0.0, 4, 2, 
		30, -20, 15, 18, 500, 50
	};
	double ad1[] = {
		10, 3, 2, -50, -81, -25, 20, 0.0, 15, 18, 
		500, 50, 4, 2, 30, -20
	};
	std::vector<double> vad(ad, ad + sizeof(ad) / sizeof(ad[0]) );
	std::vector<double> vad1(ad1, ad1 + sizeof(ad1) / sizeof(ad1[0]) ); 

	Word word1 (vad, 4, 4);
	Word word2 (vad1, 4, 4);

	Word word3 (vad, 4, 8);

	Word word4(vad, 4, 2);

	std::cout << word1.toString() << std::endl;
	std::cout << word1.toBinaryString() << std::endl;
	std::cout << word1.hashCode() << std::endl;
	std::cout << word2.toString() << std::endl;
	std::cout << word2.toBinaryString() << std::endl;
	std::cout << word2.hashCode() << std::endl;
	std::cout << word3.toString() << std::endl;
	std::cout << word3.toBinaryString() << std::endl;
	std::cout << word3.hashCode() << std::endl;
	std::cout << word4.toString() << std::endl;
	std::cout << word4.toBinaryString() << std::endl;
	std::cout << word4.hashCode() << std::endl;
	std::cout << word1.equals(word2) << std::endl;
	std::cout << word1.equals(word1) << std::endl;
	std::cout << word3.equals(word4) << std::endl;
	std::cout << std::endl;
	std::cout << word1.binaryEquals(word2) << std::endl;
	std::cout << word1.binaryEquals(word2) << std::endl;
	std::cout << word3.binaryEquals(word4) << std::endl;

	std::cout << std::endl;
	std::cout << Utils::numberOfBytes(2) << std::endl;
	std::cout << Utils::numberOfBytes(4) << std::endl;
	std::cout << Utils::numberOfBytes(8) << std::endl;


}

void testRandomProjection(){
	clock_t begin = clock();
	std::string db = "10000.txt";
	RandomProjection rp;
	MotifParameters params;

	std::ifstream ifs  (db.c_str()); 
	
	std::string line;
	
	int iter = 0;
	while ( getline(ifs, line) ) {
		std::vector<double> ts;
		double value;

		std::stringstream ss (line);
		while ( ss >>  value)
			ts.push_back(value);

		Word isaxWord(ts, params.wordLength, params.initialCardinality);
		rp.addWord(isaxWord);

		//std::cout << isaxWord.toString() << std::endl;
		//std::cout << iter++ << std::endl;
	}
	rp.randomProjection();
	rp.showResult();
	clock_t end = clock();
	std::cout << "Exec time (ms): " << ( end - begin ) << std::endl;
}

void testParallelRandomProjection(){
	clock_t begin = clock();
	std::string db = "10000.txt";
	ParallelRandomProjection rp;
	MotifParameters params;

	std::ifstream ifs  (db.c_str()); 

	std::string line;

	int iter = 0;
	while ( getline(ifs, line) ) {
		std::vector<double> ts;
		double value;

		std::stringstream ss (line);
		while ( ss >>  value)
			ts.push_back(value);

		Word isaxWord(ts, params.wordLength, params.initialCardinality);
		rp.addWord(isaxWord);

		std::cout << isaxWord.toString() << std::endl;
		//std::cout << iter++ << std::endl;
		iter++ ;
	}
	rp.randomProjection();
	rp.showResult();
	rp.show1MotifResult();
	clock_t end = clock();
	std::cout << "Exec time (ms): " << ( end - begin ) << std::endl;
}

void testMrMotif() {
	clock_t begin = clock();
	std::string db = "10000.txt";
	MotifParameters params;
	params.initialCardinality = 4;

	MrMotif motifMining(params);

	std::ifstream ifs  (db.c_str()); 
	std::string line;
	int iter = 0;
	while ( getline(ifs, line)  ) {
		std::vector<double> ts;
		double value;

		std::stringstream ss (line);
		while ( ss >> value)
			ts.push_back(value);

		Word isaxWord(ts, params.wordLength, params.initialCardinality);
		motifMining.processWord(isaxWord, ts, db + "-" + Utils::convertToStr(iter) );
		std::cout << isaxWord.toString() << std::endl;

		//std::cout << "iteration: " << iter << std::endl;
		//if (iter % 10 == 0 ) {
			/*
			std::cout << motifMining.count.printTopK(params, motifMining.locations) << std::endl;
			std::cout <<  "Counter sizes: " << std::endl;
			for (int k = motifMining.getParams().initialCardinality; k <= motifMining.getParams().maxCardinality; k *= 2) {
				printf("%d: %d \n" , k, motifMining.count[k].size());
			}*/
			//system("pause");
		//}
		iter++ ;
	}
	
	clock_t end = clock();
	std::cout << "Exec time (ms): " << ( end - begin ) << std::endl;

	std::cout << motifMining.count.printTopK(params, motifMining.locations) << std::endl;

	std::cout <<  "Counter sizes: " << std::endl;
	
    for (int k = motifMining.getParams().initialCardinality; k <= motifMining.getParams().maxCardinality; k *= 2) {
		printf("%d: %d \n" , k, motifMining.count[k].size());
	}
}
//

int main() {

	//testWord();
	//test_distances();	
	//test_distLookupTable();

	//testRandomProjection();
	//testParallelRandomProjection();
	testMrMotif();
    return 0;
}
