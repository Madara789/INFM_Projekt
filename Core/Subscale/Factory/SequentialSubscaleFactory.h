#pragma once

#include "../SubscaleFactoryInterface.h"

class SequentialSubscaleFactory : public SubscaleFactoryInterface
{
public:
	Subscale make() override;
    ~SequentialSubscaleFactory() override = default;
};