#pragma once
#include <iostream>



class CImguiManager
{
public:
	//Imgui�̃V���O���g����.
	static CImguiManager& GetInstance()
	{
		static CImguiManager instance;
		return instance;
	}

public:
	CImguiManager();
	~CImguiManager();

public:


private:

};