//
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <k4a/k4a.h>
//#include <k4arecord/types.h>
//#include <k4arecord/playback.h>
//#include <k4abt.h>
//#include <math.h>
//#include <get_record_config.h>
//
//#define VERIFY(result, error)                                                                            \
//	if(result != K4A_RESULT_SUCCEEDED)                                                                   \
//	{                                                                                                    \
//		printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
//		exit(1);                                                                                         \
//	}                                                                                                    \
//
//int main()
//{
//	//Get the configurations of the record
//	k4a_record_configuration_t deviceConfig;
//
//	//Open the record and do verification
//	const char *record_path = "E:\\Azure Kinect DK\\tools\\output-1.mkv";
//	k4a_playback_t  playback;
//	VERIFY(k4a_playback_open(record_path, &playback), "Open record mvk failed!");
//	VERIFY(k4a_playback_get_record_configuration(playback, &deviceConfig), "Get record info failed!");
//	get_record_config(deviceConfig);
//
//	//Calibrate the sensor
//	k4a_calibration_t playback_calibration;
//	VERIFY(k4a_playback_get_calibration(playback, &playback_calibration),
//		"Get depth camera calibration failed!");
//	
//	//Create a tracker
//	k4abt_tracker_t tracker = NULL;
//	VERIFY(k4abt_tracker_create(&playback_calibration, &tracker), "Body tracker initialization failed!");
//
//	int frame_count = 0;
//	while (1)
//	{
//		
//		// Capture a depth frame
//		k4a_capture_t playback_capture;
//		k4a_wait_result_t get_capture_result = k4a_playback_get_next_capture(playback, &playback_capture);
//		if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
//		{
//			frame_count++;
//			//printf("%d\n", frame_count);
//			//Add the new captured frame to the input queue
//			k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(tracker, playback_capture, K4A_WAIT_INFINITE);
//			k4a_capture_release(playback_capture);
//			if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
//			{
//				// It should never hit timeout when K4A_WAIT_INFINITE is set.
//				printf("Error! Add capture to tracker process queue timeout!\n");
//				break;
//			}
//			else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
//			{
//				printf("Error! Add capture to tracker process queue failed!\n");
//				break;
//			}
//
//			//Get access to the tracker data
//			k4abt_frame_t body_frame = NULL;
//			k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);
//			if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
//			{
//				//Get the number of detecied human bodies
//				size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
//				//Get access to every idex of human bodies
//				for (size_t i = 0; i < num_bodies; i++)
//				{
//					k4abt_skeleton_t skeleton;
//					k4a_result_t get_body_skeleton = k4abt_frame_get_body_skeleton(body_frame, i, &skeleton);
//					//k4abt_frame_get_body_skeleton(body_frame, i, &skeleton);
//					if (get_body_skeleton == K4A_RESULT_SUCCEEDED)
//					{
//						if (frame_count >= 20)
//						{
//							FILE *fp;
//							fp = fopen("D:\\Users\\Desktop\\Data_plot\\joints_position.txt", "a");
//							for (int i = 0; i < 25; i++) {
//								fprintf(fp, "%f,%f,%f,", skeleton.joints[i].position.xyz.x, skeleton.joints[i].position.xyz.y, skeleton.joints[i].position.xyz.z);
//							}
//							fprintf(fp, "%f,%f,%f\n", skeleton.joints[25].position.xyz.x, skeleton.joints[25].position.xyz.y, skeleton.joints[25].position.xyz.z);
//							fclose(fp);
//							printf("%f:, %f, %f\n", skeleton.joints[25].position.xyz.x, skeleton.joints[25].position.xyz.y, skeleton.joints[25].position.xyz.z);
//
//						}
//						
//					}
//					else if (get_body_skeleton == K4A_RESULT_FAILED)
//					{
//						printf("Get body skeleton failed!!");
//					}
//					uint32_t id = k4abt_frame_get_body_id(body_frame, i);
//					//printf("Body ID is %u\n", id);
//
//				}
//				//printf("%zu bodies are detected!\n", num_bodies);
//
//				k4abt_frame_release(body_frame);
//			}
//			else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
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
//		else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)
//		{
//			// It should never hit time out when K4A_WAIT_INFINITE is set.
//			printf("Record finished! Please check the txt files under the path you set!\n");
//			break;
//		}
//		//else
//		//{
//		//	printf("Get depth capture returned error: %d\n", get_capture_result);
//		//	break;
//		//}
//
//	}
///*
//int frame_count = 0;
//do
//{
//k4a_capture_t sensor_capture;
//// Capture a depth frame
//k4a_wait_result_t get_capture_result = k4a_device_get_capture(device, &sensor_capture, K4A_WAIT_INFINITE);
//if (get_capture_result == K4A_WAIT_RESULT_SUCCEEDED)
//{
//frame_count++;
////Add the new captured frame to the input queue
//k4a_wait_result_t queue_capture_result = k4abt_tracker_enqueue_capture(tracker, sensor_capture, K4A_WAIT_INFINITE);
//k4a_capture_release(sensor_capture);
//if (queue_capture_result == K4A_WAIT_RESULT_TIMEOUT)
//{
//// It should never hit timeout when K4A_WAIT_INFINITE is set.
//printf("Error! Add capture to tracker process queue timeout!\n");
//break;
//}
//else if (queue_capture_result == K4A_WAIT_RESULT_FAILED)
//{
//printf("Error! Add capture to tracker process queue failed!\n");
//break;
//}
//
////Get access to the tracker data
//k4abt_frame_t body_frame = NULL;
//k4a_wait_result_t pop_frame_result = k4abt_tracker_pop_result(tracker, &body_frame, K4A_WAIT_INFINITE);
//if (pop_frame_result == K4A_WAIT_RESULT_SUCCEEDED)
//{
////Get the number of detecied human bodies
//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame);
////Get access to every idex of human bodies
//for (size_t i = 0; i < num_bodies; i++)
//{
//k4abt_skeleton_t skeleton;
//k4a_result_t get_body_skeleton = k4abt_frame_get_body_skeleton(body_frame, i, &skeleton);
////k4abt_frame_get_body_skeleton(body_frame, i, &skeleton);
//if (get_body_skeleton == K4A_RESULT_SUCCEEDED)
//{
//FILE *fp0;
//FILE *fp1;
//FILE *fp2;
//fp0 = fopen("D:\\Users\\Desktop\\Data_plot\\ls_position.txt", "a");
//fp1 = fopen("D:\\Users\\Desktop\\Data_plot\\le_position.txt", "a");
//fp2 = fopen("D:\\Users\\Desktop\\Data_plot\\lw_position.txt", "a");
//if (fp0 == NULL || fp1 == NULL || fp2 == NULL)
//{
//printf("create file failed\n");
//return -1;
//}
//else
//{
//float ls_p_x = skeleton.joints[5].position.xyz.x;
//float ls_p_y = skeleton.joints[5].position.xyz.y;
//float ls_p_z = skeleton.joints[5].position.xyz.z;
//float le_p_x = skeleton.joints[6].position.xyz.x;
//float le_p_y = skeleton.joints[6].position.xyz.y;
//float le_p_z = skeleton.joints[6].position.xyz.z;
//float lw_p_x = skeleton.joints[7].position.xyz.x;
//float lw_p_y = skeleton.joints[7].position.xyz.y;
//float lw_p_z = skeleton.joints[7].position.xyz.z;
//double distance_ls2le = 0;
//double distance_le2lw = 0;
//double distance_lw2ls = 0;
//double angle_lef_arm = 0;
//fprintf(fp0, "%f,%f,%f\n", ls_p_x, ls_p_y, ls_p_z);
//fprintf(fp1, "%f,%f,%f\n", le_p_x, le_p_y, le_p_z);
//fprintf(fp2, "%f,%f,%f\n", lw_p_x, lw_p_y, lw_p_z);
//fclose(fp0);
//fclose(fp1);
//fclose(fp2);
//distance_ls2le = sqrt(pow((ls_p_x - le_p_x), 2)+pow((ls_p_y - le_p_y), 2)+pow((ls_p_z - le_p_z), 2));
//distance_le2lw = sqrt(pow((le_p_x - lw_p_x), 2)+pow((le_p_y - lw_p_y), 2)+pow((le_p_z - lw_p_z), 2));
//distance_lw2ls = sqrt(pow((lw_p_x - ls_p_x), 2)+pow((lw_p_y - ls_p_y), 2)+pow((lw_p_z - ls_p_z), 2));
//angle_lef_arm = 180.0/3.141592*acos((distance_ls2le*distance_ls2le+distance_le2lw*distance_le2lw-distance_lw2ls*distance_lw2ls)/(2*distance_ls2le*distance_le2lw));
//printf("angle_lef_arm:%lf, distance_ls2le:%lf, distance_le2lw:%lf, distance_lw2ls:%lf\n", angle_lef_arm, distance_ls2le, distance_le2lw, distance_lw2ls);
////printf("x: %f, y: %f, z: %f\n", skeleton.joints[7].position.xyz.x, skeleton.joints[7].position.xyz.y, skeleton.joints[7].position.xyz.z);
//}
//}
//else if (get_body_skeleton == K4A_RESULT_FAILED)
//{
//printf("Get body skeleton failed!!");
//}
//uint32_t id = k4abt_frame_get_body_id(body_frame, i);
////printf("Body ID is %u\n", id);
//
//}
////printf("%zu bodies are detected!\n", num_bodies);
//
//k4abt_frame_release(body_frame);
//}
//else if (pop_frame_result == K4A_WAIT_RESULT_TIMEOUT)
//{
////  It should never hit timeout when K4A_WAIT_INFINITE is set.
//printf("Error! Pop body frame result timeout!\n");
//break;
//}
//else
//{
//printf("Pop body frame result failed!\n");
//break;
//}
//}
//else if (get_capture_result == K4A_WAIT_RESULT_TIMEOUT)
//{
//// It should never hit time out when K4A_WAIT_INFINITE is set.
//printf("Error! Get depth frame time out!\n");
//break;
//}
//else
//{
//printf("Get depth capture returned error: %d\n", get_capture_result);
//break;
//}
//
//} while (frame_count < 500);
//
//printf("Finished body tracking processing!\n");
//
//k4abt_tracker_shutdown(tracker);
//k4abt_tracker_destroy(tracker);
//k4a_device_stop_cameras(device);
//k4a_device_close(device);
//*/
//	k4abt_tracker_shutdown(tracker);
//	k4abt_tracker_destroy(tracker);
//	k4a_playback_close(playback);
//	return 0;
//}
