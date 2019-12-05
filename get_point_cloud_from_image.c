//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <k4a/k4a.h>
//#include <k4arecord/types.h>
//#include <k4arecord/playback.h>
//#include <k4abt.h>
//#include "get_point_cloud_from_image.h"
//
//
//
//void create_xy_table(const k4a_calibration_t* calibration, k4a_image_t xy_table)
//{
//	k4a_float2_t* table_data = (k4a_float2_t*)(void*)k4a_image_get_buffer(xy_table);
//	
//	int width = calibration->depth_camera_calibration.resolution_width;//获取像素宽度信息
//	int height = calibration->depth_camera_calibration.resolution_height;//获取像素高度信息
//
//	k4a_float2_t p;
//	k4a_float3_t ray;
//	int valid;
//
//	for (int y = 0, idx = 0; y < height; y++)
//	{
//		p.xy.y = (float)y;
//		for (int x = 0; x < width; x++, idx++)
//		{
//			p.xy.x = (float)x;
//
//			k4a_calibration_2d_to_3d(calibration, &p, 1.f, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &ray, &valid);
//
//			if (valid)
//			{
//				table_data[idx].xy.x = ray.xyz.x;
//				table_data[idx].xy.y = ray.xyz.y;
//			}
//			else
//			{
//				table_data[idx].xy.x = nanf("");
//				table_data[idx].xy.y = nanf("");
//			}
//		}
//	}
//}
//
///*
//  rotation_flag == 1: Yes,use the ratation matirx 1 to 0 and translation matrix 1 to 0
//				   2: Yes,use the ratation matirx 2 to 0 and translation matrix 2 to 0
//				   3: Yes,use the ratation matirx 3 to 0 and translation matrix 3 to 0
//				   0: No 
//*/
//void generate_point_cloud(const k4a_calibration_t* calibration,
//						  const k4a_image_t depth_image,
//						  const k4a_image_t xy_table,
//						  k4a_image_t point_cloud,
//						  int* point_count,
//						  const char *file_path,
//						  int rotation_flag)
//{
//	int width = k4a_image_get_width_pixels(depth_image);
//	int height = k4a_image_get_height_pixels(depth_image);
//
//	uint16_t* depth_data = (uint16_t*)(void*)k4a_image_get_buffer(depth_image);//转空后转换了数据类型
//	k4a_float2_t* xy_table_data = (k4a_float2_t*)(void*)k4a_image_get_buffer(xy_table);
//	k4a_float3_t* point_cloud_data = (k4a_float3_t*)(void*)k4a_image_get_buffer(point_cloud);
//
//	FILE* f_cloud;
//	f_cloud = fopen(file_path, "a");
//	
//	*point_count = 0;
//	for (int i = 0; i < width * height; i++)
//	{
//		if (depth_data[i] != 0 && !isnan(xy_table_data[i].xy.x) && !isnan(xy_table_data[i].xy.y))
//		{		
//			point_cloud_data[i].xyz.x = xy_table_data[i].xy.x * (float)depth_data[i];
//			point_cloud_data[i].xyz.y = xy_table_data[i].xy.y * (float)depth_data[i];
//			point_cloud_data[i].xyz.z = (float)depth_data[i];
//			tf_source_depth.xyz.x = point_cloud_data[i].xyz.x;
//			tf_source_depth.xyz.y = point_cloud_data[i].xyz.y;
//			tf_source_depth.xyz.z = point_cloud_data[i].xyz.z;
//			if (rotation_flag == 0)
//			{
//				fprintf(f_cloud, "%f,%f,%f\n", point_cloud_data[i].xyz.x, point_cloud_data[i].xyz.y, point_cloud_data[i].xyz.z);
//			}
//			else if(rotation_flag == 1)
//			{
//				/* Doing cordinate translation there */
//				k4a_result_t tf_result = k4a_calibration_3d_to_3d(calibration, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[0][0]
//						+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[0][1]
//						+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[0][2]) + translation_matrix_1t0[0];
//					tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[1][0]
//						+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[1][1]
//						+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[1][2]) + translation_matrix_1t0[1];
//					tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[2][0]
//						+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[2][1]
//						+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[2][2]) + translation_matrix_1t0[2];
//				}
//
//				// write the transfered cordinates into the txt file
//				tf_result = k4a_calibration_3d_to_3d(calibration, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					fprintf(f_cloud, "%f,%f,%f\n", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//					   
//				}
//
//			}
//			else if (rotation_flag == 2)
//			{
//				/* Doing cordinate translation there */
//				k4a_result_t tf_result = k4a_calibration_3d_to_3d(calibration, &point_cloud_data[i], K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_2t0_inv[0][0]
//						+ tf_target_color.xyz.y * rotation_matrix_2t0_inv[0][1]
//						+ tf_target_color.xyz.z * rotation_matrix_2t0_inv[0][2]) + translation_matrix_2t0[0];
//					tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_2t0_inv[1][0]
//						+ tf_target_color.xyz.y * rotation_matrix_2t0_inv[1][1]
//						+ tf_target_color.xyz.z * rotation_matrix_2t0_inv[1][2]) + translation_matrix_2t0[1];
//					tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_2t0_inv[2][0]
//						+ tf_target_color.xyz.y * rotation_matrix_2t0_inv[2][1]
//						+ tf_target_color.xyz.z * rotation_matrix_2t0_inv[2][2]) + translation_matrix_2t0[2];
//				}
//
//				// write the transfered cordinates into the txt file
//				tf_result = k4a_calibration_3d_to_3d(calibration, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					fprintf(f_cloud, "%f,%f,%f\n", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//
//				}
//			}
//			else if (rotation_flag == 3)
//			{
//				/* Doing cordinate translation there */
//				k4a_result_t tf_result = k4a_calibration_3d_to_3d(calibration, &point_cloud_data[i], K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_3t0_inv[0][0]
//						+ tf_target_color.xyz.y * rotation_matrix_3t0_inv[0][1]
//						+ tf_target_color.xyz.z * rotation_matrix_3t0_inv[0][2]) + translation_matrix_3t0[0];
//					tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_3t0_inv[1][0]
//						+ tf_target_color.xyz.y * rotation_matrix_3t0_inv[1][1]
//						+ tf_target_color.xyz.z * rotation_matrix_3t0_inv[1][2]) + translation_matrix_3t0[1];
//					tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_3t0_inv[2][0]
//						+ tf_target_color.xyz.y * rotation_matrix_3t0_inv[2][1]
//						+ tf_target_color.xyz.z * rotation_matrix_3t0_inv[2][2]) + translation_matrix_3t0[2];
//				}
//
//				// write the transfered cordinates into the txt file
//				tf_result = k4a_calibration_3d_to_3d(calibration, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//				if (tf_result == K4A_RESULT_SUCCEEDED)
//				{
//					fprintf(f_cloud, "%f,%f,%f\n", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//
//				}
//			}
//			
//			(*point_count)++;
//		}
//		else
//		{
//			point_cloud_data[i].xyz.x = nanf("");
//			point_cloud_data[i].xyz.y = nanf("");
//			point_cloud_data[i].xyz.z = nanf("");
//		}
//	}
//	fclose(f_cloud);
//}
