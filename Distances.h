#pragma once

#include "DistLookupTable.h"
#include "Word.h"
#include "WordElem.h"

#include <cmath>

class Distances
{
public:

	Distances()
	{
	}

	static double minDist(int i, int j, Word& word, Word& word1)
	{
		double d = 0.0;
		double d1 = 0.0;
		for (int k = 0; k < word.word.size(); k++){
			WordElem wordelem = word.word.at(k);
			WordElem wordelem1 = word1.word.at(k);
			d1 += pow(dist(wordelem, wordelem1), 2.0);
		}
		d1 = std::sqrt(d1);
		d = std::sqrt((double) (i / j)) * d1;
		return d;
	}

private:

	static double dist(WordElem& wordelem, WordElem& wordelem1)
	{
		if (wordelem.cardinality == wordelem1.cardinality)
		{
			return DistLookupTable::cell(wordelem.cardinality, wordelem.value, wordelem1.value);
		}
		if (wordelem.cardinality > wordelem1.cardinality)
		{
			WordElem wordelem2 = WordElem::promoteToHigherCardForDist(wordelem1, wordelem, wordelem.cardinality);
			return DistLookupTable::cell(wordelem.cardinality, wordelem2.value, wordelem.value);
		} else
		{
			WordElem wordelem3 = WordElem::promoteToHigherCardForDist(wordelem, wordelem1, wordelem1.cardinality);
			return DistLookupTable::cell(wordelem1.cardinality, wordelem3.value, wordelem1.value);
		}
	}

};