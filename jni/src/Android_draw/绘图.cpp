#include "绘图.h"

void 绘图::初始化绘图(int x, int y)
{
	if (y < x)
	{
		this->px = x;
		this->py = y;
	}
	else
	{
		this->px = y;
		this->py = x;
	}
}

void 绘图::绘制方框(Vector4D &屏幕坐标, bool isboot)
{
	if (isboot)
	{
		ImGui::GetForegroundDrawList()->AddRect({(屏幕坐标.X + 屏幕坐标.Z / 2) - 屏幕坐标.Z / 2.0f, 屏幕坐标.Y - 屏幕坐标.Z}, {屏幕坐标.X + 屏幕坐标.Z / 1.12f, 屏幕坐标.Y + 屏幕坐标.Z}, 颜色.绿色, {0.0}, 0, {1});
	}
	else
	{
		ImGui::GetForegroundDrawList()->AddRect({(屏幕坐标.X + 屏幕坐标.Z / 2) - 屏幕坐标.Z / 2.0f, 屏幕坐标.Y - 屏幕坐标.Z}, {屏幕坐标.X + 屏幕坐标.Z / 1.12f, 屏幕坐标.Y + 屏幕坐标.Z}, 颜色.红色, {0.0}, 0, {1});
	}
}

void 绘图::绘制人数(int &人数)
{
	ImGui::GetForegroundDrawList()->AddRectFilled({px - 50, 100 - 30}, {px + 50, 100 + 30}, 颜色.绿色, {40});
	string str1;
	if (人数 == 0)
	{
		str1 += "安全";
	}
	else
	{
		str1 += to_string(人数);
	}
	auto textSize = ImGui::CalcTextSize(str1.c_str(), 0, 25);
	ImGui::GetForegroundDrawList()->AddText(NULL, 30, {px + 3 - (textSize.x / 2), 85}, ImColor(255, 255, 255), str1.c_str());
}

void 绘图::绘制距离(Vector4D &屏幕坐标, int 距离)
{
	string s;
	s += " [";
	s += to_string((int)距离);
	s += " 米]";
	auto textSize = ImGui::CalcTextSize(s.c_str(), 0, 25);
	ImGui::GetForegroundDrawList()->AddText(NULL, 35, {屏幕坐标.X + 屏幕坐标.Z - (textSize.x / 2), 屏幕坐标.Y - 屏幕坐标.Z + 120}, 颜色.绿色, s.c_str());
}

void 绘图::绘制射线(Vector4D &屏幕坐标, bool isboot)
{
	if (isboot)
	{
		ImGui::GetForegroundDrawList()->AddLine({px, 150}, {屏幕坐标.X + 屏幕坐标.Z, 屏幕坐标.Y - 屏幕坐标.Z - 50}, 颜色.绿色, {3});
	}
	else
	{
		ImGui::GetForegroundDrawList()->AddLine({px, 150}, {屏幕坐标.X + 屏幕坐标.Z, 屏幕坐标.Y - 屏幕坐标.Z - 50}, 颜色.红色, {3});
	}
}

void 绘图::绘制名字(Vector4D &屏幕坐标, int 队伍, const string 名字, bool isboot)
{
	string s;
	s += "[";
	s += to_string((int)队伍);
	s += "] ";
	s += 名字;
	auto textSize = ImGui::CalcTextSize(s.c_str(), 0, 25);
	ImGui::GetForegroundDrawList()->AddText(NULL, 35, {屏幕坐标.X + 屏幕坐标.Z - (textSize.x / 2), 屏幕坐标.Y - 屏幕坐标.Z - 95}, 颜色.白色, s.c_str());
	//}
}

void 绘图::绘制血量(Vector4D &屏幕坐标,float 最大血量,float 当前血量,bool isboot){
	string duo;
	duo+=to_string((int)当前血量);
	auto textSize = ImGui::CalcTextSize(duo.c_str(),0,25);
	ImGui::GetForegroundDrawList()->AddText(NULL,30,{
			屏幕坐标.X+屏幕坐标.Z/2-(textSize.x/2),屏幕坐标.Y-屏幕坐标.Z-55
		},ImColor(235,75,220),duo.c_str());
}


/*
	  Vector2D Head;	//头部1
	  Vector2D Chest;	//胸部2
	  Vector2D Pelvis;	//盆骨3
	  Vector2D Left_Shoulder;	//左肩膀4
	  Vector2D Right_Shoulder;	//右肩膀5
	  Vector2D Left_Elbow;	//左手肘6
	  Vector2D Right_Elbow;	//右手肘7
	  Vector2D Left_Wrist;	//左手腕8
	  Vector2D Right_Wrist;	//右手腕9
	  Vector2D Left_Thigh;	//左大腿10
	  Vector2D Right_Thigh;	//右大腿11
	  Vector2D Left_Knee;	//左膝盖12
	  Vector2D Right_Knee;	//右膝盖13
	  Vector2D Left_Ankle;	//左脚腕14
	  Vector2D Right_Ankle;	//右脚腕15*/

void 绘图::绘制骨骼(BoneData 骨骼, Vector4D &屏幕坐标)
{
	ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(骨骼.Head.X, 骨骼.Head.Y), 屏幕坐标.W / 13, 颜色.白色, 0, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Pelvis.X, 骨骼.Pelvis.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Left_Shoulder.X, 骨骼.Left_Shoulder.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Shoulder.X, 骨骼.Left_Shoulder.Y}, {骨骼.Left_Elbow.X, 骨骼.Left_Elbow.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Elbow.X, 骨骼.Left_Elbow.Y}, {骨骼.Left_Wrist.X, 骨骼.Left_Wrist.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Right_Shoulder.X, 骨骼.Right_Shoulder.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Shoulder.X, 骨骼.Right_Shoulder.Y}, {骨骼.Right_Elbow.X, 骨骼.Right_Elbow.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Elbow.X, 骨骼.Right_Elbow.Y}, {骨骼.Right_Wrist.X, 骨骼.Right_Wrist.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Pelvis.X, 骨骼.Pelvis.Y}, {骨骼.Left_Thigh.X, 骨骼.Left_Thigh.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Thigh.X, 骨骼.Left_Thigh.Y}, {骨骼.Left_Knee.X, 骨骼.Left_Knee.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Knee.X, 骨骼.Left_Knee.Y}, {骨骼.Left_Ankle.X, 骨骼.Left_Ankle.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Pelvis.X, 骨骼.Pelvis.Y}, {骨骼.Right_Thigh.X, 骨骼.Right_Thigh.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Thigh.X, 骨骼.Right_Thigh.Y}, {骨骼.Right_Knee.X, 骨骼.Right_Knee.Y}, 颜色.白色, 骨骼粗细);
	ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Knee.X, 骨骼.Right_Knee.Y}, {骨骼.Right_Ankle.X, 骨骼.Right_Ankle.Y}, 颜色.白色, 骨骼粗细);
}
