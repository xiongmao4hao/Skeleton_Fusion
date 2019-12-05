#include <stdio.h>
#include <stdlib.h>

#include <k4a/k4a.h>
#include <k4arecord/types.h>
#include <k4arecord/playback.h>
#include <k4abt.h>
#include "get_record_config.h"

void get_record_config(k4a_record_configuration_t devConfig) {
	switch (devConfig.depth_mode) {
	case K4A_DEPTH_MODE_NFOV_2X2BINNED:
		printf("Depth mode of this record is NFOV_BINNED\n");
		break;
	case K4A_DEPTH_MODE_NFOV_UNBINNED:
		printf("Depth mode of this record is UNBINNED\n");
		break;
	case K4A_DEPTH_MODE_WFOV_2X2BINNED:
		printf("Depth mode of this record is WFOV_UNBINNED\n");
		break;
	case K4A_DEPTH_MODE_PASSIVE_IR:
		printf("Depth mode of this record is PASSIVE_IR\n");
		break;
	}
	switch (devConfig.camera_fps) {
	case K4A_FRAMES_PER_SECOND_30:
		printf("Frame rate of this record is 30fps\n");
		break;
	case K4A_FRAMES_PER_SECOND_15:
		printf("Frame rate of this record is 15fps\n");
		break;
	case K4A_FRAMES_PER_SECOND_5:
		printf("Frame rate of this record is 5fps\n");
		break;
	}
	switch (devConfig.wired_sync_mode) {
	case K4A_WIRED_SYNC_MODE_STANDALONE:
		printf("This record is standalone!\n");
		break;
	case K4A_WIRED_SYNC_MODE_MASTER:
		printf("This record is from the master!\n");
		break;
	case K4A_WIRED_SYNC_MODE_SUBORDINATE:
		printf("This record is from the sub!\n");
		break;
	}
}

void get_calibration_of_playback(k4a_calibration_t playback_calib) {
	
	float intrinsics_param[15];
	//float extrinsics_rotation_matrix[9];
	//float extrinsics_translate_matrix[3];
	
	FILE *fp_depth_ip;
	fp_depth_ip = fopen("C:\\Users\\tsz\\Desktop\\depth_intrinsics_param.txt", "a");
	FILE *fp_color_ip;
	fp_color_ip = fopen("C:\\Users\\tsz\\Desktop\\color_intrinsics_param.txt", "a");
	//FILE *fp_er;
	//fp_er = fopen("D:\\Users\\Desktop\\depth_rotation.txt", "a");
	//FILE *fp_et;
	//fp_et = fopen("D:\\Users\\Desktop\\depth_translation.txt", "a");
	for (int i = 0; i < 15; i++)
	{
		intrinsics_param[i] = playback_calib.color_camera_calibration.intrinsics.parameters.v[i];
		if (i == 14)
		{
			fprintf(fp_color_ip, "%f\n", intrinsics_param[i]);
		}else
		fprintf(fp_color_ip, "%f ", intrinsics_param[i]);
	}
	fclose(fp_color_ip);
	
	for (int i = 0; i < 15; i++)
	{
		intrinsics_param[i] = playback_calib.depth_camera_calibration.intrinsics.parameters.v[i];
		if (i == 14)
		{
			fprintf(fp_depth_ip, "%f\n", intrinsics_param[i]);
		}else
		fprintf(fp_depth_ip, "%f ", intrinsics_param[i]);
	}
	fclose(fp_depth_ip);
	
	//for (int i = 0; i < 9; i++)
	//{
	//	extrinsics_rotation_matrix[i] = playback_calib.depth_camera_calibration.extrinsics.rotation[i];
	//	//printf("%f\n", playback_calib.depth_camera_calibration.extrinsics.rotation[i]);
	//	fprintf(fp_er, "%f,", extrinsics_rotation_matrix[i]);
	//}
	//fclose(fp_er);
	//for (int i = 0; i < 3; i++)
	//{
	//	extrinsics_translate_matrix[i] = playback_calib.depth_camera_calibration.extrinsics.translation[i];
	//	fprintf(fp_et, "%f,", extrinsics_translate_matrix[i]);
	//}
	//fclose(fp_et);
}




