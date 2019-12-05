#include"getAngel.h"
#define PI 3.1415926


k4abt_skeleton_t skeleton0;

float GetAngel(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz)
{
	float A, B, C, A2, B2, C2, pos, posAngel, Angle;
	C2 = (ax - bx) * (ax - bx) + (ay - by) * (ay - by) + (az - bz) * (az - bz);
	B2 = (ax - cx) * (ax - cx) + (ay - cy) * (ay - cy) + (az - cz) * (az - cz);
	A2 = (bx - cx) * (bx - cx) + (by - cy) * (by - cy) + (bz - cz) * (bz - cz);
	C = sqrt(C2);
	B = sqrt(B2);
	A = sqrt(A2);
	pos = (A2 + C2 - B2) / (2 * A * C);
	posAngel = acos(pos);
	Angle = (posAngel * 180) / PI;
	return Angle;
}
float *JointsPositionToAngel( k4abt_skeleton_t skeleton0)

{
	
	float Angel[12];
	Angel[0] = GetAngel(skeleton0.joints[8].position.xyz.x, skeleton0.joints[8].position.xyz.y, skeleton0.joints[8].position.xyz.z, skeleton0.joints[7].position.xyz.x, skeleton0.joints[7].position.xyz.y, skeleton0.joints[7].position.xyz.z, skeleton0.joints[6].position.xyz.x, skeleton0.joints[6].position.xyz.y, skeleton0.joints[6].position.xyz.z);
	Angel[1] = GetAngel(skeleton0.joints[7].position.xyz.x, skeleton0.joints[7].position.xyz.y, skeleton0.joints[7].position.xyz.z, skeleton0.joints[6].position.xyz.x, skeleton0.joints[6].position.xyz.y, skeleton0.joints[6].position.xyz.z, skeleton0.joints[5].position.xyz.x, skeleton0.joints[5].position.xyz.y, skeleton0.joints[5].position.xyz.z);
	Angel[2] = GetAngel(skeleton0.joints[6].position.xyz.x, skeleton0.joints[6].position.xyz.y, skeleton0.joints[6].position.xyz.z, skeleton0.joints[5].position.xyz.x, skeleton0.joints[5].position.xyz.y, skeleton0.joints[5].position.xyz.z, skeleton0.joints[4].position.xyz.x, skeleton0.joints[4].position.xyz.y, skeleton0.joints[4].position.xyz.z);
	Angel[3] = GetAngel(skeleton0.joints[15].position.xyz.x, skeleton0.joints[15].position.xyz.y, skeleton0.joints[15].position.xyz.z, skeleton0.joints[14].position.xyz.x, skeleton0.joints[14].position.xyz.y, skeleton0.joints[14].position.xyz.z, skeleton0.joints[13].position.xyz.x, skeleton0.joints[13].position.xyz.y, skeleton0.joints[13].position.xyz.z);
	Angel[4] = GetAngel(skeleton0.joints[14].position.xyz.x, skeleton0.joints[14].position.xyz.y, skeleton0.joints[14].position.xyz.z, skeleton0.joints[13].position.xyz.x, skeleton0.joints[13].position.xyz.y, skeleton0.joints[13].position.xyz.z, skeleton0.joints[12].position.xyz.x, skeleton0.joints[12].position.xyz.y, skeleton0.joints[12].position.xyz.z);
	Angel[5] = GetAngel(skeleton0.joints[13].position.xyz.x, skeleton0.joints[13].position.xyz.y, skeleton0.joints[13].position.xyz.z, skeleton0.joints[12].position.xyz.x, skeleton0.joints[12].position.xyz.y, skeleton0.joints[12].position.xyz.z, skeleton0.joints[11].position.xyz.x, skeleton0.joints[11].position.xyz.y, skeleton0.joints[11].position.xyz.z);
	Angel[6] = GetAngel(skeleton0.joints[18].position.xyz.x, skeleton0.joints[18].position.xyz.y, skeleton0.joints[18].position.xyz.z, skeleton0.joints[19].position.xyz.x, skeleton0.joints[19].position.xyz.y, skeleton0.joints[19].position.xyz.z, skeleton0.joints[20].position.xyz.x, skeleton0.joints[20].position.xyz.y, skeleton0.joints[20].position.xyz.z);
	Angel[7] = GetAngel(skeleton0.joints[19].position.xyz.x, skeleton0.joints[19].position.xyz.y, skeleton0.joints[19].position.xyz.z, skeleton0.joints[20].position.xyz.x, skeleton0.joints[20].position.xyz.y, skeleton0.joints[20].position.xyz.z, skeleton0.joints[21].position.xyz.x, skeleton0.joints[21].position.xyz.y, skeleton0.joints[21].position.xyz.z);
	Angel[8] = GetAngel(skeleton0.joints[22].position.xyz.x, skeleton0.joints[22].position.xyz.y, skeleton0.joints[22].position.xyz.z, skeleton0.joints[23].position.xyz.x, skeleton0.joints[23].position.xyz.y, skeleton0.joints[23].position.xyz.z, skeleton0.joints[24].position.xyz.x, skeleton0.joints[24].position.xyz.y, skeleton0.joints[24].position.xyz.z);
	Angel[9] = GetAngel(skeleton0.joints[23].position.xyz.x, skeleton0.joints[23].position.xyz.y, skeleton0.joints[23].position.xyz.z, skeleton0.joints[24].position.xyz.x, skeleton0.joints[24].position.xyz.y, skeleton0.joints[24].position.xyz.z, skeleton0.joints[25].position.xyz.x, skeleton0.joints[25].position.xyz.y, skeleton0.joints[25].position.xyz.z);
	Angel[10] = GetAngel(skeleton0.joints[26].position.xyz.x, skeleton0.joints[26].position.xyz.y, skeleton0.joints[26].position.xyz.z, skeleton0.joints[3].position.xyz.x, skeleton0.joints[3].position.xyz.y, skeleton0.joints[3].position.xyz.z, skeleton0.joints[2].position.xyz.x, skeleton0.joints[2].position.xyz.y, skeleton0.joints[2].position.xyz.z);
	Angel[11] = GetAngel(skeleton0.joints[2].position.xyz.x, skeleton0.joints[2].position.xyz.y, skeleton0.joints[2].position.xyz.z, skeleton0.joints[1].position.xyz.x, skeleton0.joints[1].position.xyz.y, skeleton0.joints[1].position.xyz.z, skeleton0.joints[0].position.xyz.x, skeleton0.joints[0].position.xyz.y, skeleton0.joints[0].position.xyz.z);
	//Angel[12] =
	/*Angel[13] =
	Angel[14] =
	Angel[15] =
	Angel[16] =
	Angel[17] =
	*/



	return Angel;
}