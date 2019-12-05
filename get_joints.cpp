/* Updating contents:
   1. Get the intrinsics and extrinsics parameters of color and depth camera
   2. Add timestamp for each frame information
*/

#include "get_record_config.h"
#include "joints_struct.h"
#include"getAngel.h"


#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
#include <k4arecord/types.h>
#include <k4arecord/playback.h>
#include <k4abt.h>
#include <k4abttypes.h>
#include <math.h>
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define VERIFY(result, error)                                                                            \
	if(result != K4A_RESULT_SUCCEEDED)                                                                   \
	{                                                                                                    \
		printf("%s \n - (File: %s, Function: %s, Line: %d)\n", error, __FILE__, __FUNCTION__, __LINE__); \
		exit(1);                                                                                         \
	}                                                                                                    \



k4a_float3_t tf_source_depth;
k4a_float3_t tf_source_color;
k4a_float3_t tf_target_color;
k4a_float3_t tf_target_depth;


k4a_float3_t tf_source_color_to_world;

//获取所有的文件名
void GetAllFiles(string path, vector<string> & files)
{

	long long  hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

}

//获取特定格式的文件名
void GetAllFormatFiles(string path, vector<string> & files, string format)
{
	//文件句柄  
	long long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}

int joints(string files)
{
	//帧计数
	int frame_count0 = 0;

	//内部时钟
	uint64_t timestamp0;

	//showimg();
	//Get the configurations of the record
	k4a_record_configuration_t deviceConfig0;
	//Open the record and do verification
	const char* record_path0 = files.c_str();
	k4a_playback_t  playback0;
	VERIFY(k4a_playback_open(record_path0, &playback0), "Open record0 mvk failed!");
	VERIFY(k4a_playback_get_record_configuration(playback0, &deviceConfig0), "Get record0 info failed!");
	get_record_config(deviceConfig0);
	//Calibrate the sensor
	k4a_calibration_t playback_calibration0;
	VERIFY(k4a_playback_get_calibration(playback0, &playback_calibration0),
		"Get depth camera0 calibration failed!");

	//Create a tracker
	k4abt_tracker_t tracker0 = NULL;
	k4abt_tracker_configuration_t tracker_config0 = K4ABT_TRACKER_CONFIG_DEFAULT;
	VERIFY(k4abt_tracker_create(&playback_calibration0, tracker_config0, &tracker0), "Body tracker0 initialization failed!");
	get_calibration_of_playback(playback_calibration0);

	FILE* fp0;
	int last = files.find_last_of(".");   //从尾开始寻找字符'.'的位置
	files.replace(last, 4, ".txt");   //从位置pos开始，之后的4个字符替换为txt
	fp0 = fopen(files.c_str(), "w");
	while (1)
	{
		// Capture a depth frame
		k4a_capture_t playback_capture0;
		k4a_stream_result_t get_capture_result0 = k4a_playback_get_next_capture(playback0, &playback_capture0);



		if (get_capture_result0 == K4A_WAIT_RESULT_SUCCEEDED)
		{
			//printf("%d\n", frame_count0);
			//Add the new captured frame to the input queue
			k4a_wait_result_t queue_capture_result0 = k4abt_tracker_enqueue_capture(tracker0, playback_capture0, K4A_WAIT_INFINITE);//异步提取骨骼信息

			///* get depth image from record*/
			//k4a_image_t get_depth_img0 = k4a_capture_get_depth_image(playback_capture0);
			//k4a_image_release(get_depth_img0);
			k4a_capture_release(playback_capture0);

			if (queue_capture_result0 == K4A_WAIT_RESULT_TIMEOUT)// && queue_capture_result1 == K4A_WAIT_RESULT_TIMEOUT)
			{
				// It should never hit timeout when K4A_WAIT_INFINITE is set.
				printf("Error! Add capture to tracker process queue timeout!\n");
				break;
			}
			else if (queue_capture_result0 == K4A_WAIT_RESULT_FAILED)// && queue_capture_result1 == K4A_WAIT_RESULT_FAILED)
			{
				printf("Error! Add capture to tracker process queue failed!\n");
				break;
			}

			//Get access to the tracker data
			k4abt_frame_t body_frame0 = NULL;
			k4a_wait_result_t pop_frame_result0 = k4abt_tracker_pop_result(tracker0, &body_frame0, K4A_WAIT_INFINITE);

			if (pop_frame_result0 == K4A_WAIT_RESULT_SUCCEEDED)
			{
				//Get the number of detecied human bodies
				//size_t num_bodies = k4abt_frame_get_num_bodies(body_frame0);
				//Get access to every idex of human bodies
				k4abt_skeleton_t skeleton0;
				k4a_result_t get_body_skeleton0 = k4abt_frame_get_body_skeleton(body_frame0, 0, &skeleton0);

				if (get_body_skeleton0 == K4A_RESULT_SUCCEEDED)
				{
					frame_count0++;

					if (frame_count0 >= 1)
					{
						////***************求角度*******************
						//float* joints_Angel;
						//joints_Angel = JointsPositionToAngel(skeleton0);
						//for (int i = 0; i < 12; i++)
						//{
						//	printf("%f", joints_Angel[i]);
						//	printf("   ");
						//}
						//****************************************
						timestamp0 = k4abt_frame_get_device_timestamp_usec(body_frame0);
						fprintf(fp0, "%llu,", timestamp0);
						for (int i = 0; i < 32; i++) {

							// write the raw cordinates into the txt file

							tf_source_depth.xyz.x = skeleton0.joints[i].position.xyz.x;
							tf_source_depth.xyz.y = skeleton0.joints[i].position.xyz.y;
							tf_source_depth.xyz.z = skeleton0.joints[i].position.xyz.z;

							/* Doing cordinate translation there */
							k4a_result_t tf_result = k4a_calibration_3d_to_3d(&playback_calibration0, &tf_source_depth, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_COLOR, &tf_target_color);
							// write the transfered cordinates into the txt file
							if (tf_result == K4A_RESULT_SUCCEEDED)
							{
								fprintf(fp0, "%f,%f,%f,", tf_target_color.xyz.x, tf_target_color.xyz.y, tf_target_color.xyz.z);
							}
							else {
								printf("Cordinates transfered failed!\n");
							}

							//fprintf(fp0, "%f,%f,%f,", skeleton0.joints[i].position.xyz.x, skeleton0.joints[i].position.xyz.y, skeleton0.joints[i].position.xyz.z);
						}
						fprintf(fp0, "\n");
					}
				}
				else if (get_body_skeleton0 == K4A_RESULT_FAILED)
				{
					printf("Get body skeleton failed!!\n");
				}
				uint32_t id = k4abt_frame_get_body_id(body_frame0, 1);
				//printf("Body ID is %u\n", id);

				//}
				//printf("%zu bodies are detected!\n", num_bodies);

				k4abt_frame_release(body_frame0);
			}
			else if (pop_frame_result0 == K4A_WAIT_RESULT_TIMEOUT)
			{
				//  It should never hit timeout when K4A_WAIT_INFINITE is set.
				printf("Error! Pop body frame result timeout!\n");
				break;
			}
			else
			{
				printf("Pop body frame result failed!\n");
				break;
			}

		}
		else if (get_capture_result0 == K4A_WAIT_RESULT_TIMEOUT)
		{
			// It should never hit time out when K4A_WAIT_INFINITE is set.
			printf("Record0 finished! Please check the txt files under the path you set!\n");
			break;
		}
		else
		{
			printf("Get depth capture0 returned error: %d\n", get_capture_result0);
			//printf("Get depth capture1 returned error: %d\n", get_capture_result1);
			break;
		}
	}

	k4abt_tracker_shutdown(tracker0);
	k4abt_tracker_destroy(tracker0);
	k4a_playback_close(playback0);
	fclose(fp0);
	return 0;
}

int main(int argc, char** argv)
{
	string filePath = argv[1];
	vector<string> files;

	//读取所有的文件，包括子文件的文件
	//GetAllFiles(filePath, files);

	//读取所有格式为mkv的文件
	string format = ".mkv";
	GetAllFormatFiles(filePath, files, format);
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		joints(files[i]);
	}

	
	return 0;
}
