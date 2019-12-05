///* Updating contents:
//   1. Get the intrinsics and extrinsics parameters of color and depth camera
//   2. Add timestamp for each frame information
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <k4a/k4a.h>
//#include <k4arecord/types.h>
//#include <k4arecord/playback.h>
//#include <k4abt.h>
//#include <k4abttypes.h>
//#include <math.h>
//#include "get_record_config.h"
//#include "joints_struct.h"
//#include "get_point_cloud_from_image.h"
//#include"getAngel.h"
//
//#define VERIFY(result, error)                                                                            \
//	if(result != K4A_RESULT_SUCCEEDED)                                                                   \
//	{                                                                                                    \
//		printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
//		exit(1);                                                                                         \
//	}                                                                                                    \
//
// //Transfer subordianate camera cordinate to the master cordinate 
//float rotation_matrix_1t0_inv[3][3] = { 0.5383 ,-0.0305  ,  0.8422,
//	0.0351  ,  0.9993  ,  0.0137,
//   -0.8420   , 0.0222   , 0.5390 }
//
//;
////float rotation_matrix_1t0_inv[3][3] = { 0.330552068083262	,-0.0437319514055451,0.942774016778222,
////										0.0350421307123446,	0.998805789986333,	0.0340447200739945,
////										 -0.943136988650651,	0.0217832577003699,	0.331689780250977 };//now
////float rotation_matrix_1t0_inv[3][3] = { 0.9805, -0.0043, 0.1963,               //MATLAB
////										0.0036, 1, 0.0041,
////										-0.1964, -0.0033, 0.9805 };
////float rotation_matrix_1t0_inv[3][3] = { 0.99563776, - 0.03371681,  0.08699784, 0.03306991, 0.99941371,  0.00886674, -0.08724579, - 0.00595105,  0.99616904 };
//
//
//
//float rotation_matrix_2t0_inv[3][3] = { 0, 0, 0,
//										0, 0, 0,
//										0, 0, 0 };
//
//float rotation_matrix_3t0_inv[3][3] = { 0, 0, 0,
//										0, 0, 0,
//										0, 0, 0 };
//
////
////float rotation_matrix_0_to_world_inv[3][3] = { 0.0011,    0.9988 ,   0.0489,
////											 - 0.9998 ,   0.0020 ,- 0.0183
////											 - 0.0183 ,- 0.0489   , 0.9986 };
//float rotation_matrix_0_to_world_inv[3][3] = {  1, 0, 0,
//												0, 1, 0,
//												0, 0, 1 };
////float rotation_matrix_0_to_world_inv[3][3] = { 0.0010931, -0.99983107, -0.0183475, 0.99880355, 0.00198863, -0.04886228, 0.04889052, - 0.01827214, 0.99863699 };
//
//
////float translation_matrix_1t0[3] = { -2671.9622, -98.9040, 2165.5250 };
//float translation_matrix_1t0[3] = {	-2065.4 ,-1.5   , 751.3 };
////float translation_matrix_1t0[3] = { -1032.13,11.422,574.179230280614 };//now
////float translation_matrix_1t0[3] = { -603.584302, -21.3494605, 0.492303564 };
//
//
//float translation_matrix_2t0[3] = { 0, 0, 0 };
//float translation_matrix_3t0[3] = { 0, 0, 0 };
//
//
////float translation_matrix_0_to_world[3] = { 1293.1, 1780.8, -2297.5 };
//float translation_matrix_0_to_world[3] = { 0, 0, 0 };
////float translation_matrix_0_to_world[3] = { 1292.8,	391.4, -1911.0 };
//
//k4a_float3_t tf_source_depth;
//k4a_float3_t tf_source_color;
//k4a_float3_t tf_target_color;
//k4a_float3_t tf_target_depth;
//
//
//k4a_float3_t tf_source_color_to_world;
//
//
//int main(int argc, char** argv)
//{
//	int frame_count0 = 0;
//	int frame_count1 = 0;
//	int frame_count2 = 0;
//	int frame_count3 = 0;
//
//	uint64_t timestamp0;
//	uint64_t timestamp1;
//	uint64_t timestamp2;
//	uint64_t timestamp3;
//
//	float tf_x = 0;
//	float tf_y = 0;
//	float tf_z = 0;
//
//	//showimg();
//	//Get the configurations of the record
//	k4a_record_configuration_t deviceConfig0;
//	//Open the record and do verification
//	const char *record_path0 = argv[1];
//	k4a_playback_t  playback0;
//	VERIFY(k4a_playback_open(record_path0, &playback0), "Open record0 mvk failed!");
//	VERIFY(k4a_playback_get_record_configuration(playback0, &deviceConfig0), "Get record0 info failed!");
//	get_record_config(deviceConfig0);
//	//Calibrate the sensor
//	k4a_calibration_t playback_calibration0;
//	VERIFY(k4a_playback_get_calibration(playback0, &playback_calibration0),
//		"Get depth camera0 calibration failed!");
//
//	//Create a tracker
//	k4abt_tracker_t tracker0 = NULL;
//	k4abt_tracker_configuration_t tracker_config0 = K4ABT_TRACKER_CONFIG_DEFAULT;
//	VERIFY(k4abt_tracker_create(&playback_calibration0, tracker_config0, &tracker0), "Body tracker0 initialization failed!");
//	get_calibration_of_playback(playback_calibration0);
//
//	/*k4a_image_t depth_image0 = NULL;
//	k4a_image_t xy_table0 = NULL;
//	k4a_image_t point_cloud0 = NULL;
//	int point_count0 = 0;
//	char *fp0_cloud = "D:\\Azure Kinect DK\\Data_plot\\Point_cloud_1009_1_0.txt";
//
//	k4a_image_create(K4A_IMAGE_FORMAT_CUSTOM,
//		playback_calibration0.depth_camera_calibration.resolution_width,
//		playback_calibration0.depth_camera_calibration.resolution_height,
//		playback_calibration0.depth_camera_calibration.resolution_width * (int)sizeof(k4a_float2_t),
//		&xy_table0);
//
//	create_xy_table(&playback_calibration0, xy_table0);
//
//	k4a_image_create(K4A_IMAGE_FORMAT_CUSTOM,
//		playback_calibration0.depth_camera_calibration.resolution_width,
//		playback_calibration0.depth_camera_calibration.resolution_height,
//		playback_calibration0.depth_camera_calibration.resolution_width * (int)sizeof(k4a_float3_t),
//		&point_cloud0);*/
//	FILE* fp0;
//	fp0 = fopen(argv[3], "w");
//	while (1)
//	{
//		// Capture a depth frame
//		k4a_capture_t playback_capture0;
//		k4a_wait_result_t get_capture_result0 = k4a_playback_get_next_capture(playback0, &playback_capture0);
//		
//		
//
//		if (get_capture_result0 == K4A_WAIT_RESULT_SUCCEEDED)
//		{
//			//printf("%d\n", frame_count0);
//			//Add the new captured frame to the input queue
//			k4a_wait_result_t queue_capture_result0 = k4abt_tracker_enqueue_capture(tracker0, playback_capture0, K4A_WAIT_INFINITE);//异步提取骨骼信息
//
//			///* get depth image from record*/
//			k4a_image_t get_depth_img0 = k4a_capture_get_depth_image(playback_capture0);
//			k4a_capture_release(playback_capture0);
//
//			if (queue_capture_result0 == K4A_WAIT_RESULT_TIMEOUT)// && queue_capture_result1 == K4A_WAIT_RESULT_TIMEOUT)
//			{
//				// It should never hit timeout when K4A_WAIT_INFINITE is set.
//				printf("Error! Add capture to tracker process queue timeout!\n");
//				break;
//			}
//			else if (queue_capture_result0 == K4A_WAIT_RESULT_FAILED)// && queue_capture_result1 == K4A_WAIT_RESULT_FAILED)
//			{
//				printf("Error! Add capture to tracker process queue failed!\n");
//				break;
//			}
//
//			//Get access to the tracker data
//			k4abt_frame_t body_frame0 = NULL;
//			k4a_wait_result_t pop_frame_result0 = k4abt_tracker_pop_result(tracker0, &body_frame0, K4A_WAIT_INFINITE);
//
//			if (pop_frame_result0 == K4A_WAIT_RESULT_SUCCEEDED)
//			{
//				//Get the number of detecied human bodies
//				//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame0);
//				//Get access to every idex of human bodies
//				//for (size_t i = 0; i < num_bodies; i++)
//				//{
//				k4abt_skeleton_t skeleton0;
//				k4a_result_t get_body_skeleton0 = k4abt_frame_get_body_skeleton(body_frame0, 0, &skeleton0);
//
//				if (get_body_skeleton0 == K4A_RESULT_SUCCEEDED)
//				{
//					frame_count0++;
//					//if (frame_count0 <= 35 && frame_count0 > 30)
//					//{
//					//	/*printf point cloud from depth image */
//					//	if (get_depth_img0 != NULL)
//					//	{
//					//		generate_point_cloud(&playback_calibration0, get_depth_img0, xy_table0, point_cloud0, &point_count0, fp0_cloud, 0);
//					//		// Release the image
//					//		k4a_image_release(get_depth_img0);
//					//	}
//					//	else
//					//	{
//					//		printf("Get depth image failed !!\n");
//					//	}
//					//}
//
//					if (frame_count0 >= 30)
//					{
//				//***************求角度*******************
//						float* joints_Angel;
//						joints_Angel = JointsPositionToAngel(skeleton0);
//						for (int i = 0; i < 12;i++) 
//						{
//							printf("%f", joints_Angel[i]);
//							printf("   ");
//						}
//	            //****************************************
//						timestamp0 = k4abt_frame_get_device_timestamp_usec(body_frame0);
//						fprintf(fp0, "%llu,", timestamp0);
//						for (int i = 0; i < 31; i++) {
//
//							// write the raw cordinates into the txt file
//
//							tf_source_depth.xyz.x = skeleton0.joints[i].position.xyz.x;
//							tf_source_depth.xyz.y = skeleton0.joints[i].position.xyz.y;
//							tf_source_depth.xyz.z = skeleton0.joints[i].position.xyz.z;
//
//							/* Doing cordinate translation there */
//							k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration0, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//							if (tf_result == K4A_RESULT_SUCCEEDED)
//							{
//								tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[0][0]
//									+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[0][1]
//									+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[0][2]) + translation_matrix_0_to_world[0];
//								tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[1][0]
//									+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[1][1]
//									+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[1][2]) + translation_matrix_0_to_world[1];
//								tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[2][0]
//									+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[2][1]
//									+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[2][2]) + translation_matrix_0_to_world[2];
//							}
//
//							// write the transfered cordinates into the txt file
//							if (tf_result == K4A_RESULT_SUCCEEDED)
//							{
//								fprintf(fp0, "%f,%f,%f,", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//							}
//							else {
//								printf("Cordinates transfered failed!\n");
//							}
//
//							//fprintf(fp0, "%f,%f,%f,", skeleton0.joints[i].position.xyz.x, skeleton0.joints[i].position.xyz.y, skeleton0.joints[i].position.xyz.z);
//						}
//						tf_source_depth.xyz.x = skeleton0.joints[31].position.xyz.x;
//						tf_source_depth.xyz.y = skeleton0.joints[31].position.xyz.y;
//						tf_source_depth.xyz.z = skeleton0.joints[31].position.xyz.z;
//
//						k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration0, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//						if (tf_result == K4A_RESULT_SUCCEEDED)
//						{
//							tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[0][0]
//								+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[0][1]
//								+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[0][2]) + translation_matrix_0_to_world[0];
//							tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[1][0]
//								+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[1][1]
//								+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[1][2]) + translation_matrix_0_to_world[1];
//							tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_0_to_world_inv[2][0]
//								+ tf_target_color.xyz.y * rotation_matrix_0_to_world_inv[2][1]
//								+ tf_target_color.xyz.z * rotation_matrix_0_to_world_inv[2][2]) + translation_matrix_0_to_world[2];
//						}
//						// write the transfered cordinates into the txt file
//						if (tf_result == K4A_RESULT_SUCCEEDED)
//						{
//							fprintf(fp0, "%f,%f,%f\n", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//						}
//						else {
//							printf("Cordinates transfered failed!\n");
//						}
//
//						//fprintf(fp0, "%f,%f,%f\n", skeleton0.joints[25].position.xyz.x, skeleton0.joints[25].position.xyz.y, skeleton0.joints[25].position.xyz.z);
//						
//						//printf("%f, %f, %f\n", skeleton0.joints[25].position.xyz.x, skeleton0.joints[25].position.xyz.y, skeleton0.joints[25].position.xyz.z);
//						//printf("%f, %f, %f\n", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//					}
//				}
//				else if (get_body_skeleton0 == K4A_RESULT_FAILED)
//				{
//					printf("Get body skeleton failed!!\n");
//				}
//				uint32_t id = k4abt_frame_get_body_id(body_frame0, 1);
//				//printf("Body ID is %u\n", id);
//
//				//}
//				//printf("%zu bodies are detected!\n", num_bodies);
//
//				k4abt_frame_release(body_frame0);
//			}
//			else if (pop_frame_result0 == K4A_WAIT_RESULT_TIMEOUT)
//			{
//				//  It should never hit timeout when K4A_WAIT_INFINITE is set.
//				printf("Error! Pop body frame result timeout!\n");
//				break;
//			}
//			else
//			{
//				printf("Pop body frame result failed!\n");
//				break;
//			}
//
//		}
//		else if (get_capture_result0 == K4A_WAIT_RESULT_TIMEOUT)
//		{
//			// It should never hit time out when K4A_WAIT_INFINITE is set.
//			printf("Record0 finished! Please check the txt files under the path you set!\n");
//			break;
//		}
//		else
//		{
//			printf("Get depth capture0 returned error: %d\n", get_capture_result0);
//			//printf("Get depth capture1 returned error: %d\n", get_capture_result1);
//			break;
//		}
//	}
//
//	k4abt_tracker_shutdown(tracker0);
//	k4abt_tracker_destroy(tracker0);
//	k4a_playback_close(playback0);
//	fclose(fp0);
//
//
//
//
//	k4a_record_configuration_t deviceConfig1;
//	const char* record_path1 = argv[2];
//	k4a_playback_t  playback1;
//	VERIFY(k4a_playback_open(record_path1, &playback1), "Open record1 mvk failed!");
//	VERIFY(k4a_playback_get_record_configuration(playback1, &deviceConfig1), "Get record1 info failed!");
//	get_record_config(deviceConfig1);
//	k4a_calibration_t playback_calibration1;
//	VERIFY(k4a_playback_get_calibration(playback1, &playback_calibration1),
//		"Get depth camera1 calibration failed!");
//
//	k4abt_tracker_t tracker1 = NULL;
//	k4abt_tracker_configuration_t tracker_config1 = K4ABT_TRACKER_CONFIG_DEFAULT;
//	VERIFY(k4abt_tracker_create(&playback_calibration1, tracker_config1,&tracker1), "Body tracker1 initialization failed!");
//	get_calibration_of_playback(playback_calibration1);
//
//	/*k4a_image_t depth_image1 = NULL;
//	k4a_image_t xy_table1 = NULL;
//	k4a_image_t point_cloud1 = NULL;
//	int point_count1 = 0;
//	char* fp1_cloud = "D:\\Azure Kinect DK\\Data_plot\\Point_cloud_1009_1_1.txt";
//
//	k4a_image_create(K4A_IMAGE_FORMAT_CUSTOM,
//		playback_calibration1.depth_camera_calibration.resolution_width,
//		playback_calibration1.depth_camera_calibration.resolution_height,
//		playback_calibration1.depth_camera_calibration.resolution_width* (int)sizeof(k4a_float2_t),
//		&xy_table1);
//
//	create_xy_table(&playback_calibration1, xy_table1);
//
//	k4a_image_create(K4A_IMAGE_FORMAT_CUSTOM,
//		playback_calibration1.depth_camera_calibration.resolution_width,
//		playback_calibration1.depth_camera_calibration.resolution_height,
//		playback_calibration1.depth_camera_calibration.resolution_width* (int)sizeof(k4a_float3_t),
//		&point_cloud1);*/
//
//
//	while (1)
//	{
//		// Capture a depth frame
//		k4a_capture_t playback_capture1;
//		k4a_wait_result_t get_capture_result1 = k4a_playback_get_next_capture(playback1, &playback_capture1);//顺序捕获帧
//
//		if (get_capture_result1 == K4A_WAIT_RESULT_SUCCEEDED)
//		{
//			//printf("%d\n", frame_count0);
//			//Add the new captured frame to the input queue
//			k4a_wait_result_t queue_capture_result1 = k4abt_tracker_enqueue_capture(tracker1, playback_capture1, K4A_WAIT_INFINITE);
//
//			///* get depth image from record*/
//			k4a_image_t get_depth_img1 = k4a_capture_get_depth_image(playback_capture1);
//			k4a_capture_release(playback_capture1);
//
//			if (queue_capture_result1 == K4A_WAIT_RESULT_TIMEOUT)
//			{
//				// It should never hit timeout when K4A_WAIT_INFINITE is set.
//				printf("Error! Add capture to tracker process queue timeout!\n");
//				break;
//			}
//			else if (queue_capture_result1 == K4A_WAIT_RESULT_FAILED)
//			{
//				printf("Error! Add capture to tracker process queue failed!\n");
//				break;
//			}
//
//			//Get access to the tracker data
//			k4abt_frame_t body_frame1 = NULL;
//			k4a_wait_result_t pop_frame_result1 = k4abt_tracker_pop_result(tracker1, &body_frame1, K4A_WAIT_INFINITE);
//
//			if (pop_frame_result1 == K4A_WAIT_RESULT_SUCCEEDED)
//			{
//				//Get the number of detecied human bodies
//				//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame0);
//				//Get access to every idex of human bodies
//				//for (size_t i = 0; i < num_bodies; i++)
//				//{
//				k4abt_skeleton_t skeleton1;
//				k4a_result_t get_body_skeleton1 = k4abt_frame_get_body_skeleton(body_frame1, 0, &skeleton1);
//
//				if (get_body_skeleton1 == K4A_RESULT_SUCCEEDED)
//				{
//					frame_count1++;
//					
//					//if (frame_count1 <= 35 && frame_count1 > 30)
//					//{
//					//	/*printf point cloud from depth image */
//					//	if (get_depth_img1 != NULL)
//					//	{
//					//		generate_point_cloud(&playback_calibration1,get_depth_img1, xy_table1, point_cloud1, &point_count1, fp1_cloud, 1);
//					//		// Release the image
//					//		k4a_image_release(get_depth_img1);
//					//	}
//					//	else
//					//	{
//					//		printf("Get depth image failed !!\n");
//					//	}
//					//}
//
//					if (frame_count1 >= 30)
//					{
//						FILE *fp1;
//						FILE *fp1_ori;
//						fp1 = fopen("D:\\Azure Kinect DK\\Data_plot\\joints_position1009_1_0.txt", "w");
//						fp1_ori = fopen("D:\\Azure Kinect DK\\Data_plot\\joints_position1009_1_0_ori.txt", "w");
//						timestamp1 = k4abt_frame_get_device_timestamp_usec(body_frame1);
//						fprintf(fp1, "%llu,", timestamp1);
//						fprintf(fp1_ori, "%llu,", timestamp1);
//						for (int i = 0; i < 31; i++) {
//							tf_source_depth.xyz.x = skeleton1.joints[i].position.xyz.x;
//							tf_source_depth.xyz.y = skeleton1.joints[i].position.xyz.y;
//							tf_source_depth.xyz.z = skeleton1.joints[i].position.xyz.z;
//
//
//							/* Doing cordinate translation there */
//							k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//							if (tf_result == K4A_RESULT_SUCCEEDED)
//							{
//								tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[0][0]
//									+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[0][1]
//									+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[0][2]) + translation_matrix_1t0[0];
//								tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[1][0]
//									+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[1][1]
//									+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[1][2]) + translation_matrix_1t0[1];
//								tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[2][0]
//									+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[2][1]
//									+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[2][2]) + translation_matrix_1t0[2];
//								//fprintf(fp1, "%f,%f,%f,", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//								/**********************************************************************************************/
//								tf_source_color_to_world.xyz.x = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[0][0]
//									+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[0][1]
//									+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[0][2]) + translation_matrix_0_to_world[0];
//								tf_source_color_to_world.xyz.y = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[1][0]
//									+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[1][1]
//									+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[1][2]) + translation_matrix_0_to_world[1];
//								tf_source_color_to_world.xyz.z = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[2][0]
//									+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[2][1]
//									+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[2][2]) + translation_matrix_0_to_world[2];
//							}
//							printf("%f, %f, %f\n", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//							// write the transfered cordinates into the txt file
//							//tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//							if (tf_result == K4A_RESULT_SUCCEEDED)
//							{
//								fprintf(fp1, "%f,%f,%f,", tf_source_color_to_world.xyz.x, tf_source_color_to_world.xyz.y, tf_source_color_to_world.xyz.z);
//								fprintf(fp1_ori, "%f,%f,%f,", tf_target_color.xyz.x, tf_target_color.xyz.y, tf_target_color.xyz.z);
//							}
//							else {
//								printf("Cordinates transfered failed!\n");
//							}
//						}
//						tf_source_depth.xyz.x = skeleton1.joints[31].position.xyz.x;
//						tf_source_depth.xyz.y = skeleton1.joints[31].position.xyz.y;
//						tf_source_depth.xyz.z = skeleton1.joints[31].position.xyz.z;
//						
//						k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//						if (tf_result == K4A_RESULT_SUCCEEDED)
//						{
//							tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[0][0]
//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[0][1]
//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[0][2]) + translation_matrix_1t0[0];
//							tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[1][0]
//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[1][1]
//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[1][2]) + translation_matrix_1t0[1];
//							tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[2][0]
//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[2][1]
//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[2][2]) + translation_matrix_1t0[2];
//							//fprintf(fp1, "%f,%f,%f\n", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//							/**********************************************************************************************/
//							tf_source_color_to_world.xyz.x = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[0][0]
//								+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[0][1]
//								+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[0][2]) + translation_matrix_0_to_world[0];
//							tf_source_color_to_world.xyz.y = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[1][0]
//								+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[1][1]
//								+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[1][2]) + translation_matrix_0_to_world[1];
//							tf_source_color_to_world.xyz.z = (tf_source_color.xyz.x * rotation_matrix_0_to_world_inv[2][0]
//								+ tf_source_color.xyz.y * rotation_matrix_0_to_world_inv[2][1]
//								+ tf_source_color.xyz.z * rotation_matrix_0_to_world_inv[2][2]) + translation_matrix_0_to_world[2];
//
//						}
//						// write the transfered cordinates into the txt file
//						//tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//						if (tf_result == K4A_RESULT_SUCCEEDED)
//						{
//							fprintf(fp1, "%f,%f,%f\n", tf_source_color_to_world.xyz.x, tf_source_color_to_world.xyz.y, tf_source_color_to_world.xyz.z);
//							fprintf(fp1_ori, "%f,%f,%f\n,", tf_target_color.xyz.x, tf_target_color.xyz.y, tf_target_color.xyz.z);
//						}
//						else {
//							printf("Cordinates transfered failed!\n");
//						}
//						fclose(fp1);
//						fclose(fp1_ori);
//						printf("%f, %f, %f\n", tf_source_color.xyz.x, tf_source_color.xyz.y, tf_source_color.xyz.z);
//					}
//				}
//				else if (get_body_skeleton1 == K4A_RESULT_FAILED)
//				{
//					printf("Get body skeleton failed!!\n");
//				}
//				uint32_t id = k4abt_frame_get_body_id(body_frame1, 1);
//				//printf("Body ID is %u\n", id);
//
//				//}
//				//printf("%zu bodies are detected!\n", num_bodies);
//
//				k4abt_frame_release(body_frame1);
//			}
//			else if (pop_frame_result1 == K4A_WAIT_RESULT_TIMEOUT)
//			{
//				//  It should never hit timeout when K4A_WAIT_INFINITE is set.
//				printf("Error! Pop body frame result timeout!\n");
//				break;
//			}
//			else
//			{
//				printf("Pop body frame result failed!\n");
//				break;
//			}
//		}
//		else if (get_capture_result1 == K4A_WAIT_RESULT_TIMEOUT)
//		{
//			// It should never hit time out when K4A_WAIT_INFINITE is set.
//			printf("Record1 finished! Please check the txt files under the path you set!\n");
//			break;
//		}
//		else
//		{
//			printf("Get depth capture1 returned error: %d\n", get_capture_result1);
//			//printf("Get depth capture1 returned error: %d\n", get_capture_result1);
//			break;
//		}
//	}
//	k4abt_tracker_shutdown(tracker1);
//	k4abt_tracker_destroy(tracker1);
//	k4a_playback_close(playback1);
//
//
//	//k4a_record_configuration_t deviceConfig2;
//	//const char* record_path2 = "D:\\Azure Kinect DK\\Azure Kinect DK\\tools\\body-819-1-3.mkv";
//	//k4a_playback_t  playback2;
//	//VERIFY(k4a_playback_open(record_path2, &playback2), "Open record2 mvk failed!");
//	//VERIFY(k4a_playback_get_record_configuration(playback2, &deviceConfig2), "Get record2 info failed!");
//	//get_record_config(deviceConfig2);
//	//k4a_calibration_t playback_calibration2;
//	//VERIFY(k4a_playback_get_calibration(playback2, &playback_calibration2),
//	//	"Get depth camera2 calibration failed!");
//
//	//k4abt_tracker_t tracker2 = NULL;
//	//VERIFY(k4abt_tracker_create(&playback_calibration2, &tracker2), "Body tracker2 initialization failed!");
//	//get_calibration_of_playback(playback_calibration2);
//	//while (1)
//	//{
//	//	// Capture a depth frame
//	//	k4a_capture_t playback_capture2;
//	//	k4a_wait_result_t get_capture_result2 = k4a_playback_get_next_capture(playback2, &playback_capture2);
//
//	//	if (get_capture_result2 == K4A_WAIT_RESULT_SUCCEEDED)
//	//	{
//	//		//printf("%d\n", frame_count0);
//	//		//Add the new captured frame to the input queue
//	//		k4a_wait_result_t queue_capture_result2 = k4abt_tracker_enqueue_capture(tracker2, playback_capture2, K4A_WAIT_INFINITE);
//	//		k4a_capture_release(playback_capture2);
//	//		if (queue_capture_result2 == K4A_WAIT_RESULT_TIMEOUT)
//	//		{
//	//			// It should never hit timeout when K4A_WAIT_INFINITE is set.
//	//			printf("Error! Add capture to tracker process queue timeout!\n");
//	//			break;
//	//		}
//	//		else if (queue_capture_result2 == K4A_WAIT_RESULT_FAILED)
//	//		{
//	//			printf("Error! Add capture to tracker process queue failed!\n");
//	//			break;
//	//		}
//
//	//		//Get access to the tracker data
//	//		k4abt_frame_t body_frame2 = NULL;
//	//		k4a_wait_result_t pop_frame_result2 = k4abt_tracker_pop_result(tracker2, &body_frame2, K4A_WAIT_INFINITE);
//
//	//		if (pop_frame_result2 == K4A_WAIT_RESULT_SUCCEEDED)
//	//		{
//	//			//Get the number of detecied human bodies
//	//			//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame0);
//	//			//Get access to every idex of human bodies
//	//			//for (size_t i = 0; i < num_bodies; i++)
//	//			//{
//	//			k4abt_skeleton_t skeleton2;
//	//			k4a_result_t get_body_skeleton2 = k4abt_frame_get_body_skeleton(body_frame2, 0, &skeleton2);
//
//	//			if (get_body_skeleton2 == K4A_RESULT_SUCCEEDED)
//	//			{
//	//				frame_count2++;
//
//	//				if (frame_count2 >= 30)
//	//				{
//	//					FILE *fp2;
//	//					fp2 = fopen("D:\\Azure Kinect DK\\Data_plot\\joints_position2.txt", "a");
//	//					timestamp2 = k4abt_frame_get_timestamp_usec(body_frame2);
//	//					fprintf(fp2, "%llu,", timestamp2);
//	//					for (int i = 0; i < 25; i++) {
//	//						tf_source_depth.xyz.x = skeleton2.joints[i].position.xyz.x;
//	//						tf_source_depth.xyz.y = skeleton2.joints[i].position.xyz.y;
//	//						tf_source_depth.xyz.z = skeleton2.joints[i].position.xyz.z;
//	//						/* Doing cordinate translation there */
//	//						k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration2, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//	//						if (tf_result == K4A_RESULT_SUCCEEDED)
//	//						{
//	//							tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[0][0]
//	//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[0][1]
//	//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[0][2]) + translation_matrix_1t0[0];
//	//							tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[1][0]
//	//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[1][1]
//	//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[1][2]) + translation_matrix_1t0[1];
//	//							tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[2][0]
//	//								+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[2][1]
//	//								+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[2][2]) + translation_matrix_1t0[2];
//	//						}
//	//						// write the transfered cordinates into the txt file
//	//						tf_result = k4a_calibration_3d_to_3d(&playback_calibration2, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//	//						if (tf_result == K4A_RESULT_SUCCEEDED)
//	//						{
//	//							fprintf(fp2, "%f,%f,%f,", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//	//						}
//	//						else {
//	//							printf("Cordinates transfered failed!\n");
//	//						}
//	//					}
//	//					tf_source_depth.xyz.x = skeleton2.joints[25].position.xyz.x;
//	//					tf_source_depth.xyz.y = skeleton2.joints[25].position.xyz.y;
//	//					tf_source_depth.xyz.z = skeleton2.joints[25].position.xyz.z;
//
//	//					k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
//	//					if (tf_result == K4A_RESULT_SUCCEEDED)
//	//					{
//	//						tf_source_color.xyz.x = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[0][0]
//	//							+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[0][1]
//	//							+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[0][2]) + translation_matrix_1t0[0];
//	//						tf_source_color.xyz.y = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[1][0]
//	//							+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[1][1]
//	//							+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[1][2]) + translation_matrix_1t0[1];
//	//						tf_source_color.xyz.z = (tf_target_color.xyz.x * rotation_matrix_1t0_inv[2][0]
//	//							+ tf_target_color.xyz.y * rotation_matrix_1t0_inv[2][1]
//	//							+ tf_target_color.xyz.z * rotation_matrix_1t0_inv[2][2]) + translation_matrix_1t0[2];
//	//					}
//	//					// write the transfered cordinates into the txt file
//	//					tf_result = k4a_calibration_3d_to_3d(&playback_calibration1, &tf_source_color, K4A_CALIBRATION_TYPE_COLOR, K4A_CALIBRATION_TYPE_DEPTH, &tf_target_depth);
//	//					if (tf_result == K4A_RESULT_SUCCEEDED)
//	//					{
//	//						fprintf(fp2, "%f,%f,%f\n", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//	//					}
//	//					else {
//	//						printf("Cordinates transfered failed!\n");
//	//					}
//	//					fclose(fp2);
//	//					printf("%f:, %f, %f\n", tf_target_depth.xyz.x, tf_target_depth.xyz.y, tf_target_depth.xyz.z);
//	//				}
//	//			}
//	//			else if (get_body_skeleton2 == K4A_RESULT_FAILED)
//	//			{
//	//				printf("Get body skeleton failed!!\n");
//	//			}
//	//			uint32_t id = k4abt_frame_get_body_id(body_frame2, 1);
//	//			//printf("Body ID is %u\n", id);
//	//			//}
//	//			//printf("%zu bodies are detected!\n", num_bodies);
//
//	//			k4abt_frame_release(body_frame2);
//	//		}
//	//		else if (pop_frame_result2 == K4A_WAIT_RESULT_TIMEOUT)
//	//		{
//	//			//  It should never hit timeout when K4A_WAIT_INFINITE is set.
//	//			printf("Error! Pop body frame result timeout!\n");
//	//			break;
//	//		}
//	//		else
//	//		{
//	//			printf("Pop body frame result failed!\n");
//	//			break;
//	//		}
//	//	}
//	//	else if (get_capture_result2 == K4A_WAIT_RESULT_TIMEOUT)
//	//	{
//	//		// It should never hit time out when K4A_WAIT_INFINITE is set.
//	//		printf("Record2 finished! Please check the txt files under the path you set!\n");
//	//		break;
//	//	}
//	//	else
//	//	{
//	//		printf("Get depth capture2 returned error: %d\n", get_capture_result2);
//	//		//printf("Get depth capture1 returned error: %d\n", get_capture_result1);
//	//		break;
//	//	}
//	//}
//	//k4abt_tracker_shutdown(tracker2);
//	//k4abt_tracker_destroy(tracker2);
//	//k4a_playback_close(playback2);
//
//
//	//k4a_record_configuration_t deviceConfig3;
//	//const char* record_path3 = "E:\\Azure Kinect DK\\tools\\output-004.mkv";
//	//k4a_playback_t  playback3;
//	//VERIFY(k4a_playback_open(record_path3, &playback3), "Open record3 mvk failed!");
//	//VERIFY(k4a_playback_get_record_configuration(playback3, &deviceConfig3), "Get record3 info failed!");
//	//get_record_config(deviceConfig3);
//	//k4a_calibration_t playback_calibration3;
//	//VERIFY(k4a_playback_get_calibration(playback3, &playback_calibration3),
//	//	"Get depth camera3 calibration failed!");
//
//	//k4abt_tracker_t tracker3 = NULL;
//	//VERIFY(k4abt_tracker_create(&playback_calibration3, &tracker3), "Body tracker3 initialization failed!");
//	//get_calibration_of_playback(playback_calibration3);
//	//while (1)
//	//{
//	//	// Capture a depth frame
//	//	k4a_capture_t playback_capture3;
//	//	k4a_wait_result_t get_capture_result3 = k4a_playback_get_next_capture(playback3, &playback_capture3);
//
//	//	if (get_capture_result3 == K4A_WAIT_RESULT_SUCCEEDED)
//	//	{
//	//		//printf("%d\n", frame_count0);
//	//		//Add the new captured frame to the input queue
//	//		k4a_wait_result_t queue_capture_result3 = k4abt_tracker_enqueue_capture(tracker3, playback_capture3, K4A_WAIT_INFINITE);
//	//		k4a_capture_release(playback_capture3);
//	//		if (queue_capture_result3 == K4A_WAIT_RESULT_TIMEOUT)
//	//		{
//	//			// It should never hit timeout when K4A_WAIT_INFINITE is set.
//	//			printf("Error! Add capture to tracker process queue timeout!\n");
//	//			break;
//	//		}
//	//		else if (queue_capture_result3 == K4A_WAIT_RESULT_FAILED)
//	//		{
//	//			printf("Error! Add capture to tracker process queue failed!\n");
//	//			break;
//	//		}
//
//	//		//Get access to the tracker data
//	//		k4abt_frame_t body_frame3 = NULL;
//	//		k4a_wait_result_t pop_frame_result3 = k4abt_tracker_pop_result(tracker3, &body_frame3, K4A_WAIT_INFINITE);
//
//	//		if (pop_frame_result3 == K4A_WAIT_RESULT_SUCCEEDED)
//	//		{
//	//			//Get the number of detecied human bodies
//	//			//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame0);
//	//			//Get access to every idex of human bodies
//	//			//for (size_t i = 0; i < num_bodies; i++)
//	//			//{
//	//			k4abt_skeleton_t skeleton3;
//	//			k4a_result_t get_body_skeleton3 = k4abt_frame_get_body_skeleton(body_frame3, 0, &skeleton3);
//
//	//			if (get_body_skeleton3 == K4A_RESULT_SUCCEEDED)
//	//			{
//	//				frame_count3++;
//
//	//				if (frame_count3 >= 30)
//	//				{
//	//					FILE *fp3;
//	//					fp3 = fopen("D:\\Users\\Desktop\\joints_position3.txt", "a");
//	//					timestamp3 = k4abt_frame_get_timestamp_usec(body_frame3);
//	//					fprintf(fp3, "%llu,", timestamp3);
//	//					for (int i = 0; i < 25; i++) {
//	//						tf_x = (skeleton3.joints[i].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[0][0]
//	//							+ (skeleton3.joints[i].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[0][1]
//	//							+ (skeleton3.joints[i].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[0][2];
//	//						tf_y = (skeleton3.joints[i].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[1][0]
//	//							+ (skeleton3.joints[i].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[1][1]
//	//							+ (skeleton3.joints[i].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[1][2];
//	//						tf_z = (skeleton3.joints[i].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[2][0]
//	//							+ (skeleton3.joints[i].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[2][1]
//	//							+ (skeleton3.joints[i].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[2][2];
//	//						fprintf(fp3, "%f,%f,%f,", tf_x, tf_y, tf_z);
//	//					}
//	//					tf_x = (skeleton3.joints[25].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[0][0]
//	//						+ (skeleton3.joints[25].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[0][1]
//	//						+ (skeleton3.joints[25].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[0][2];
//	//					tf_y = (skeleton3.joints[25].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[1][0]
//	//						+ (skeleton3.joints[25].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[1][1]
//	//						+ (skeleton3.joints[25].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[1][2];
//	//					tf_z = (skeleton3.joints[25].position.xyz.x - translation_matrix_2t0[0])*rotation_matrix_2t0_inv[2][0]
//	//						+ (skeleton3.joints[25].position.xyz.y - translation_matrix_2t0[1])*rotation_matrix_2t0_inv[2][1]
//	//						+ (skeleton3.joints[25].position.xyz.z - translation_matrix_2t0[2])*rotation_matrix_2t0_inv[2][2];
//	//					fprintf(fp3, "%f,%f,%f,", tf_x, tf_y, tf_z);
//	//					fclose(fp3);
//	//					printf("%f:, %f, %f\n", tf_x, tf_y, tf_z);
//	//				}
//	//			}
//	//			else if (get_body_skeleton3 == K4A_RESULT_FAILED)
//	//			{
//	//				printf("Get body skeleton failed!!\n");
//	//			}
//	//			uint32_t id = k4abt_frame_get_body_id(body_frame3, 1);
//	//			printf("Body ID is %u\n", id);
//	//			//}
//	//			//printf("%zu bodies are detected!\n", num_bodies);
//
//	//			k4abt_frame_release(body_frame3);
//	//		}
//	//		else if (pop_frame_result3 == K4A_WAIT_RESULT_TIMEOUT)
//	//		{
//	//			//  It should never hit timeout when K4A_WAIT_INFINITE is set.
//	//			printf("Error! Pop body frame result timeout!\n");
//	//			break;
//	//		}
//	//		else
//	//		{
//	//			printf("Pop body frame result failed!\n");
//	//			break;
//	//		}
//	//	}
//	//	else if (get_capture_result3 == K4A_WAIT_RESULT_TIMEOUT)
//	//	{
//	//		// It should never hit time out when K4A_WAIT_INFINITE is set.
//	//		printf("Record3 finished! Please check the txt files under the path you set!\n");
//	//		break;
//	//	}
//	//	else
//	//	{
//	//		printf("Get depth capture3 returned error: %d\n", get_capture_result3);
//	//		break;
//	//	}
//	//}
//	//k4abt_tracker_shutdown(tracker3);
//	//k4abt_tracker_destroy(tracker3);
//	//k4a_playback_close(playback3);
//
//	//k4a_device_t device = NULL;
//	//k4a_device_open(0, &device);
//
//	//// Start camera. Make sure depth camera is enabled.
//	//k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
//	//deviceConfig.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
//	//deviceConfig.color_resolution = K4A_COLOR_RESOLUTION_OFF;
//	//k4a_device_start_cameras(device, &deviceConfig);
//
//	//k4a_calibration_t sensor_calibration;
//	//VERIFY(k4a_device_get_calibration(device, deviceConfig.depth_mode, deviceConfig.color_resolution, &sensor_calibration),
//	//	"Get depth camera calibration failed!");
//
//	//k4abt_tracker_t tracker = NULL;
//	//VERIFY(k4abt_tracker_create(&sensor_calibration, &tracker), "Body tracker initialization failed!");
//
//	return 0;
//}
