#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>

struct Vector2D
{
	float X;
	float Y;
};

struct Vector3D
{
	float X;
	float Y;
	float Z;
};

struct Vector4D
{
	float X;
	float Y;
	float Z;
	float W;
};

struct BoneData
{
	Vector2D Head;			 // 头部
	Vector2D Chest;			 // 胸部
	Vector2D Pelvis;		 // 盆骨
	Vector2D Left_Shoulder;	 // 左肩膀
	Vector2D Right_Shoulder; // 右肩膀
	Vector2D Left_Elbow;	 // 左手肘
	Vector2D Right_Elbow;	 // 右手肘
	Vector2D Left_Wrist;	 // 左手腕
	Vector2D Right_Wrist;	 // 右手腕
	Vector2D Left_Thigh;	 // 左大腿
	Vector2D Right_Thigh;	 // 右大腿
	Vector2D Left_Knee;		 // 左膝盖
	Vector2D Right_Knee;	 // 右膝盖
	Vector2D Left_Ankle;	 // 左脚腕
	Vector2D Right_Ankle;	 // 右脚腕
};

#endif