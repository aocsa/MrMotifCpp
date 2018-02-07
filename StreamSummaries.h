#pragma once

#include <algorithm>
#include "Word.h"

class StreamBucket : public std::map<Word, int> {

public:
	StreamBucket() 
		: std::map<Word, int>()
	{
	}

	StreamBucket(const Word &word, int count) 
		: std::map<Word, int>()
	{
		insert ( std::make_pair(word, count) );
	}

};

class StreamSummary : public std::map<int, StreamBucket>{

public:
	void update(const Word &word, int count) {
		iterator streamBucket = find(count-1);
		iterator streamBucketNext = find(count);

		if (streamBucket == end()) {
			if (streamBucketNext == end()) {
				(*this)[count] = StreamBucket(word,count);
			}
			else {
				streamBucketNext->second[word]  = count;
			}
		}
		else {
			streamBucket->second.erase( streamBucket->second.find(word) );

			if (streamBucket->second.empty()) {
				erase( find(count-1) );
			}

			if (streamBucketNext == end()) {
				(*this)[count] = StreamBucket(word,count);
			}
			else {
				streamBucketNext->second[word]  = count;
			}
		}
	}

	Word getLast() {
		Word ret (0,0);

		iterator firstEntry = begin();

		if (firstEntry == end()) return ret; //@todo:  check return NULL; solution: ret.isvalid()

		StreamBucket::iterator iter = firstEntry->second.begin();
		for (; iter != firstEntry->second.end(); iter++ ) {
			ret = iter->first;
			break;
		}
		return ret;
	}

};


class StreamSummaries : public std::map<int,StreamSummary>
{
public:

	StreamSummaries() 
		: std::map<int,StreamSummary>()
	{

	}
	StreamSummaries(const MotifParameters& params)
		: std::map<int,StreamSummary>()
	{
		for (int k = params.initialCardinality; k <= params.maxCardinality; k *= 2) {
			initCardinality(k);
		}
	}

	void initCardinality(int card) {
		insert( std::make_pair(card, StreamSummary()) );
	}

	void updateBucket(const Word &word, int card, int count) {

		iterator oneStreamSummary = find(card);

		if (oneStreamSummary == end()) {
			StreamSummary ssum;
			ssum.update(word, count);
			(*this)[card] = ssum;
		}
		else { 
			oneStreamSummary->second.update(word,count);
		}
	}

};

