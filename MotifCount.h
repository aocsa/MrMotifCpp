#pragma once

#include <map>
#include "Word.h"

class MotifCount : public std::map<Word,int>
{
public:

	bool hasWord(const Word &w) {
		std::map<Word,int>::iterator iter = this->find(w);

		if (iter == this->end() ) 
			return false;
		else
			return true;
	}



	void incCount(Word w) {
		(*this)[w] ++; 

		/*std::map<Word,int>::iterator iter = this->find(w);

		if (iter != this->end() ) {
			int val = iter->second;
			(*this)[w] = val + 1;
		}
		else {
			insert( std::make_pair(w,1) );
		}*/

	}


	void printCountGreaterThan(int u) {

		std::map<Word,int>::iterator iter = this->begin();

		for( ; iter != this->end(); iter++) {
			if (iter->second > u) {
				//printf( w + " -> "+ get(w)); //@todo, printf
			}
		}

	}


	
};

