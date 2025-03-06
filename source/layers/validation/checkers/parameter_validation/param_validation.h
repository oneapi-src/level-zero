

#pragma once 

#include "ze_validation_layer.h"
#include "ze_parameter_validation.h"
#include "zet_parameter_validation.h"
#include "zes_parameter_validation.h"
#include <vector>


namespace validation_layer
{

    class parameterValidationChecker : public validationChecker {
        public:
            parameterValidationChecker();
            ~parameterValidationChecker();
        bool enableParameterValidation = false;
    };
    extern class parameterValidationChecker parameterChecker;

    class ParameterValidation {
    public:
        ZEParameterValidation zeParamValidation;
        ZESParameterValidation zesParamValidation;
        ZETParameterValidation zetParamValidation;
        template <typename T> static ze_result_t validateExtensions(T descriptor);
    };

    template <typename T>
    ze_result_t ParameterValidation::validateExtensions(T descriptor){
        return ZE_RESULT_SUCCESS;
    }

    #include "extension_validation.inl"

}