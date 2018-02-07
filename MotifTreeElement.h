#pragma once

#include <map>
#include <set>
#include "Word.h"

class MotifTreeElement : public std::map<Word, std::set<Word> > {

public:
	/*public MotifTreeElement(int size) {
		super(size);
	}*/

	void initialize(const Word &parentWord, const Word &childWord) {
		std::set<Word> s;
		s.insert(childWord);
		insert( std::make_pair(parentWord,  s) ) ;
	}


};

