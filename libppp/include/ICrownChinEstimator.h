﻿#pragma once

#include "CommonHelpers.h"

namespace ppp {
FWD_DECL(LandMarks)
FWD_DECL(ConfigLoader)
FWD_DECL(ICrownChinEstimator)

class ICrownChinEstimator : NonCopyable
{
public:
    virtual ~ICrownChinEstimator() = default;

    /*!@brief Configures the detector from Json data !*/
    virtual void configure(const ConfigLoaderSPtr & config) = 0;

    /*!@brief Estimate chin and crown point from the available landmarks!
     *  The result is written in the same LandMark structure !*/
    virtual bool estimateCrownChin(LandMarks & landmarks) = 0;
};
} // namespace ppp
