#pragma once
#include <vector>
#include <string>
#include "Word.h"
#include "MotifParameters.h"
#include "MotifTree.h"
#include "MotifLocationManager.h"
#include "MotifCountmanager.h"
#include "StreamSummaries.h"

#include <iostream>
class MrMotif
{
public: 
	MotifParameters params;
	MotifTree motifTree;
	MotifLocationManager locations;
	MotifCountmanager count;
	StreamSummaries streamSummary;


public:
	MrMotif(const MotifParameters &params_)
		:  params(params_), count (params_), streamSummary(params_)
	{

	}
	~MrMotif(void) {

	}

	MotifParameters & getParams() {
		return params;
	}

	void processWord(const Word &iSaxWord, const std::vector<double>  & buf, std::string locationInfo) {
		int currentCardinality = params.initialCardinality;

		Word parentWord = iSaxWord;

		while (currentCardinality <= params.maxCardinality) {

			Word childWord = incrementWord(buf, currentCardinality, locationInfo);

			if (currentCardinality > params.initialCardinality) {
				motifTree.update(currentCardinality / 2, parentWord, childWord);
			}
			currentCardinality *= 2;
			parentWord = childWord;
		}
		/*for (int k = getParams().initialCardinality; k <= getParams().maxCardinality; k *= 2) {
			printf("%d: %d \n" , k, count[k].size());
		}*/
	}


private :
	Word incrementWord(const std::vector<double> & series, int cardinality, std::string locationInfo) {

			Word promotedWord(series, params.wordLength, cardinality);

			if (params.locationOn > 0)
				locations.addLocation(promotedWord, locationInfo);
			
			MotifCount::iterator iter = count[cardinality].find(promotedWord);
			
			if (iter != count[cardinality].end()) {
				// increment count.
				count.incCount(cardinality, promotedWord);
			} else {
				if ( !params.spaceSaving ) {
					count.incCount(cardinality, promotedWord);
				}else {
					//incrementNotMonitored(promotedWord, cardinality);
				}
			}
			streamSummary.updateBucket(promotedWord, cardinality, count[cardinality][promotedWord]);
			return promotedWord;
	}
	 


};

