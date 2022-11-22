#pragma once

#include "../Subscale.h"

class SubscaleFactoryInterface {
public:
	virtual Subscale make() = 0;
    virtual ~SubscaleFactoryInterface() = default;
};