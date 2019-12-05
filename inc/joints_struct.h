#ifndef JOINTS_STRUCT_H
#define JOINTS_STRUCT_H

//6min, 30fps
typedef struct position {
	float x[12000];
	float y[12000];
	float z[12000];
} position_t;

typedef struct orientation {
	float w[12000];
	float x[12000];
	float y[12000];
	float z[12000];
} orientation_t; 

typedef struct joint {
	position_t joint_position;
	orientation_t joint_orientation;
} joint_t;

typedef struct body_joints {
	joint_t JOINT_PELVIS;
	joint_t JOINT_SPINE_NAVAL;
	joint_t JOINT_SPINE_CHEST;
	joint_t JOINT_NECK;
	joint_t JOINT_CLAVICLE_LEFT;
	joint_t JOINT_SHOULDER_LEFT;
	joint_t JOINT_ELBOW_LEFT;
	joint_t JOINT_WRIST_LEFT;
	joint_t JOINT_CLAVICLE_RIGHT;
	joint_t JOINT_SHOULDER_RIGHT;
	joint_t JOINT_ELBOW_RIGHT;
	joint_t JOINT_WRIST_RIGHT;
	joint_t JOINT_HIP_LEFT;
	joint_t JOINT_KNEE_LEFT;
	joint_t JOINT_ANKLE_LEFT;
	joint_t JOINT_FOOT_LEFT;
	joint_t JOINT_HIP_RIGHT;
	joint_t JOINT_KNEE_RIGHT;
	joint_t JOINT_ANKLE_RIGHT;
	joint_t JOINT_FOOT_RIGHT;
	joint_t JOINT_HEAD;
	joint_t JOINT_NOSE;
	joint_t JOINT_EYE_LEFT;
	joint_t JOINT_EAR_LEFT;
	joint_t JOINT_EYE_RIGHT;
	joint_t JOINT_EAR_RIGHT;
} body_joints_t;

#endif