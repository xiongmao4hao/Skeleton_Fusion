#pragma once
#ifndef GET_RECORD_CONFIG_H
#define GET_RECORD_CONFIG_H

#include <k4a/k4a.h>
#include <k4arecord/types.h>
#include <k4arecord/playback.h>
#include <k4abt.h>

#ifdef __cplusplus
extern "C" {
#endif
	void get_record_config(k4a_record_configuration_t devConfig);
	void get_calibration_of_playback(k4a_calibration_t playback_calib);
#ifdef __cplusplus
}
#endif

#endif
