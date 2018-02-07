#pragma once

#include <map>
#include <string>
#include "MotifCount.h"
#include "MotifParameters.h"
#include "Utils.h"
#include "TSUtils.h"
#include "MotifLocationManager.h"

struct ReverseComparator{

	bool operator () (const std::pair<int, Word>& o1, const std::pair<int, Word> & o2) const {
		return !(o1.second < o2.second); //@todo: check
	}
	
};

// ok!
class MotifCountmanager : public  std::map<int, MotifCount> 
{

public:
	typedef std::pair<int, Word> Pair;

public:

	MotifCountmanager(const MotifParameters &params) {
		for (int i = params.initialCardinality; i <= params.maxCardinality; i*=2 ) 
			insert( std::make_pair(i, MotifCount() ) );
	}

	void incCount(int card, const Word &saxWord) {
		std::map<int, MotifCount>::iterator iter = this->find(card);
		
		if( iter == this->end() ) {
			MotifCount motifCount;
			motifCount.incCount(saxWord);
			(*this)[card] = motifCount;
		}
		else {
			iter->second.incCount(saxWord);
		}
	}

	std::string printTopK(const MotifParameters &params,  MotifLocationManager &locations) {

		std::string sb = "";

		int currentCardinality = params.maxCardinality,
			initialCardinality = params.initialCardinality;

		while (currentCardinality >= initialCardinality) {
			sb.append(printTopKCard(currentCardinality, params, locations));
			sb.append("**************************\n");
			currentCardinality/=2;
		}


		return sb;

	}

	std::string  printTopKCard(int  card, const MotifParameters &params, MotifLocationManager &locationMan) {
		std::string sb = "";

		int topk = params.topk;


		std::vector< Pair > pair;
		
		/*LinkedList<Pair> pair = new LinkedList<Pair>();
		for (Word w: this.get(card).keySet()) {
			pair.add(new Pair(get(card).get(w),w));
		}*/

		iterator iter = this->find(card); 
		MotifCount::iterator itMtCount = iter->second.begin();
		for ( ; itMtCount != iter->second.end() ; itMtCount++)
		{
			Word w = itMtCount->first;
			pair.push_back( std::make_pair( iter->second[w], w) ); 
		}
		
		//std::stable_sort( pair.begin(), pair.end(), ReverseComparator() );

		for (int i = 0; i < pair.size(); i++) {
			Pair onePair  =  pair[i];
			
			if (topk-- == 0) //@todo check
				break;

			sb.append(  Utils::convertToStr(onePair.first)  + " " + onePair.second.toString() );

			//MotifLocationManager::iterator iter = locationMan.find(onePair.second);
			//MotifLocationManager
			std::vector<std::string> &locations = locationMan[ onePair.second ];
			//std::vector<std::string> &locations  = iter->second;

			std::string file;
			if (locations.size() != 0) {
				sb.append("(");
				for (int i=0;i<locations.size();i++) {
					sb.append(locations.at(i)); 
					if (i<10 || params.locationOn==2) 
						sb.append(",");
					else { 
						sb.append("..."); break; 
					}
				}
				sb.append(")");
			}
			sb.append("\n");
		}
		return sb;
	}

};

