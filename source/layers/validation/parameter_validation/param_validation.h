

#pragma once 

#include "ze_parameter_validation.h"
#include "zet_parameter_validation.h"
#include "zes_parameter_validation.h"


namespace validation_layer
{

    class ParameterValidation {
    public:
        ZEParameterValidation zeParamValidation;
        ZESParameterValidation zesParamValidation;
        ZETParameterValidation zetParamValidation;

    };

}