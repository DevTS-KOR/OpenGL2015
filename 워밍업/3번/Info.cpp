#include "stdafx.h"
#include "Info.h"


CInfo::CInfo(int _iInput) : iInput(_iInput)
{
}


CInfo::~CInfo()
{
}

int CInfo::GetInput(void)
{
	return iInput;
}