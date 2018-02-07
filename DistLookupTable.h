#pragma once

#include "BreakPoints.h"

#include <cmath>


class DistLookupTable
{
public:

	DistLookupTable()
	{
	}

	static double cell(int i, int j, int k)
	{
		if (fabs((double) (j - k)) <= 1) {
			return 0.0;
		} else {
			return beta(i, std::max(j, k) - 1) - beta(i, std::min(j, k));
		}
	}

private:

	static double beta(int i, int j)
	{
		return BreakPoints::getCutpoints(i).at(j + 1);
	}

};