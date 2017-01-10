/*
 * sdi_vm_thermal_sensor_api.c
 * Thermal Sensor VM functionality implements sdi-api headers
 *
 * Copyright (c) 2015, Dell Inc. All Rights Reserved
 */

#include "sdi_entity.h"
#include "sdi_thermal.h"
#include "sdi_sys_vm.h"
#include "sdi_db.h"

/*
 * Retrieve the temperature using the specified sensor.
 */
t_std_error sdi_temperature_get(sdi_resource_hdl_t sensor_hdl, int *temp)
{
    STD_ASSERT(temp != NULL);

    return sdi_db_int_field_get(sdi_get_db_handle(), sensor_hdl,
                                TABLE_THERMAL_SENSOR, THERMAL_TEMPERATURE, temp);
}

static const char * sdi_threshold_to_string(sdi_threshold_t threshold_type)
{
    switch (threshold_type) {
        case SDI_LOW_THRESHOLD:
            return THERMAL_THRESHOLD_LOW;
        case SDI_HIGH_THRESHOLD:
            return THERMAL_THRESHOLD_HIGH;
        case SDI_CRITICAL_THRESHOLD:
            return THERMAL_THRESHOLD_CRITICAL;
        default:
            return NULL;
    }
}

/*
 * Retrieve the threshold set for the specified temperature sensor.
 */
t_std_error sdi_temperature_threshold_get(sdi_resource_hdl_t sensor_hdl, 
        sdi_threshold_t threshold_type,  int *val)
{
    const char *threshold = sdi_threshold_to_string(threshold_type);

    STD_ASSERT(val != NULL);

    if (!threshold) {
        return STD_ERR(BOARD, PARAM, EINVAL);
    }

    return sdi_db_int_field_get(sdi_get_db_handle(), sensor_hdl,
                                TABLE_THERMAL_SENSOR, threshold, val);
}

/*
 * Set the threshold for the specified temperature sensor.
 */
t_std_error sdi_temperature_threshold_set(sdi_resource_hdl_t sensor_hdl,
        sdi_threshold_t threshold_type, int val)
{
    const char *threshold = sdi_threshold_to_string(threshold_type);

    if (!threshold) {
        return STD_ERR(BOARD, PARAM, EINVAL);
    }

    return sdi_db_int_field_target_set(sdi_get_db_handle(), sensor_hdl,
                                TABLE_THERMAL_SENSOR, threshold, &val);
}

/*
 * Retrieve the status of the specified sensor.
 */
t_std_error sdi_temperature_status_get(sdi_resource_hdl_t sensor_hdl, bool *alert_on)
{
    STD_ASSERT(alert_on != NULL);

    return sdi_db_int_field_get(sdi_get_db_handle(), sensor_hdl,
                                TABLE_THERMAL_SENSOR, THERMAL_FAULT,
                                (int *)alert_on);
}
