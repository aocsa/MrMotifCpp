#pragma once
#include <map>
#include <vector>
#include <string>
#include "Word.h"

struct WordHasher{

  static const int bucket_size = 80000;

  size_t operator() (const Word& word) const
  {
	std::string s = word.toBinaryString();
    size_t h = 0;
    std::string::const_iterator p, p_end;
    for(p = s.begin(), p_end = s.end(); p != p_end; ++p)
    {
      h = 31 * h + (*p);
    }
    return h;
  }

  bool operator() (const Word& s1, const Word& s2) const
  {
	  return s1 < s2;
  }
};

class MotifLocationManager : public std::map<Word, std::vector<std::string> > 
{
public:

	void addLocation(const Word &saxWord, std::string fullPath) {
		
		iterator iter = this->find(saxWord);

		if ( iter == this->end()) { //  get(saxWord)==null
			std::vector<std::string >  v; 
			v.push_back(fullPath);
			insert( std::make_pair(saxWord, v ));
		}
		else { 
			iter->second.push_back(fullPath);
		}
	}

	void deleteLocation(const Word &lw) {
		iterator iter = this->find(lw);
		if ( iter != this->end()) { 
			std::vector<std::string> v = iter->second;
			v.clear();
			this->erase(iter);
		}
	}

};

