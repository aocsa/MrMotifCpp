#pragma once

#include <map>
#include "MotifTreeElement.h"

class MotifTree : public  std::map<int,MotifTreeElement> {

public :
	void update(int card, Word parentWord, Word childWord) {
		std::map<int,MotifTreeElement>::iterator iter = this->find(card);

		if (iter == this->end()) {
			MotifTreeElement motifTreeElement; 
			motifTreeElement.initialize(parentWord, childWord);		// 1
			this->insert( std::make_pair( card, motifTreeElement ) );
		}
		else {
			MotifTreeElement &motifTreeElement = iter->second; 
			MotifTreeElement::iterator elemIter = motifTreeElement.find(parentWord) ;
			if (elemIter == motifTreeElement.end () ) {
				motifTreeElement.initialize(parentWord, childWord);			
			}
			else {
				elemIter->second.insert(childWord);
			}
		}
	}
};

