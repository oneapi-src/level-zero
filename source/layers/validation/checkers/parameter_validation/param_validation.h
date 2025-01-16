

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
        const ze_base_properties_t *base = reinterpret_cast<const ze_base_properties_t*> (descriptor);
        while(base){
            if((base->stype > ZE_STRUCTURE_TYPE_EXTERNAL_MEMORY_EXPORT_WIN32 && 
               base->stype < ZE_STRUCTURE_TYPE_DEVICE_RAYTRACING_EXT_PROPERTIES) || 
               (base->stype > ZE_STRUCTURE_TYPE_IMAGE_VIEW_PLANAR_EXT_DESC && 
               base->stype < ZE_STRUCTURE_TYPE_RELAXED_ALLOCATION_LIMITS_EXP_DESC) ||
               (base->stype > ZE_STRUCTURE_TYPE_MEMORY_SUB_ALLOCATIONS_EXP_PROPERTIES &&
                base->stype < ZE_STRUCTURE_TYPE_MUTABLE_COMMAND_LIST_EXP_PROPERTIES) ||
               base->stype > ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC)
                return ZE_RESULT_ERROR_INVALID_ARGUMENT;
            base = reinterpret_cast<const ze_base_properties_t*>(base->pNext);
        }
        return ZE_RESULT_SUCCESS;
    }

    #include "extension_validation.inl"

}