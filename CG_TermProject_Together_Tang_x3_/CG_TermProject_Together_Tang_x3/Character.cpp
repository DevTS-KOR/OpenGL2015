#include "stdafx.h"
#include "Character.h"
#include "BitmapMgr.h"

CCharacter::CCharacter(CBitmapMgr* _pBitmapMgr) : m_pBitmapMgr(_pBitmapMgr)
{
	Initialize();
}


CCharacter::~CCharacter()
{
}

GLvoid CCharacter::Initialize()
{
	m_tPosition = { 0, 100, MAP_SIZE/2 };
	m_fCameraRotate = { 0, -90, 0 };
	m_fSpeed = 5;
	m_fSniper = 0;
	m_iCameradistance = 0;
	m_bIsSniperMode = false;
	for (size_t i = 0; i < 4; i++)
		m_bKeyUpState[i] = false;
	/*cout << "X " << m_tPosition.fX << "Y " << m_tPosition.fY << "Z " << m_tPosition.fZ << endl;*/
}

GLvoid CCharacter::Draw()
{
}

GLvoid CCharacter::Update()
{
	if (m_bKeyUpState[KEYUP_UP])
	{
		m_tPosition.fX += m_fSpeed * cos((-m_fCameraRotate.fX - 90) * PI / 180);
		m_tPosition.fZ += m_fSpeed * sin((-m_fCameraRotate.fX - 90) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_DOWN])
	{
		m_tPosition.fX -= m_fSpeed * cos((-m_fCameraRotate.fX - 90) * PI / 180);
		m_tPosition.fZ -= m_fSpeed * sin((-m_fCameraRotate.fX - 90) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_LEFT])
	{
		m_tPosition.fX -= m_fSpeed * cos((-m_fCameraRotate.fX) * PI / 180);
		m_tPosition.fZ -= m_fSpeed * sin((-m_fCameraRotate.fX) * PI / 180);
	}
	if (m_bKeyUpState[KEYUP_RIGHT])
	{
		m_tPosition.fX += m_fSpeed * cos((-m_fCameraRotate.fX) * PI / 180);
		m_tPosition.fZ += m_fSpeed * sin((-m_fCameraRotate.fX) * PI / 180);
	}

}

bool CCharacter::Collision()
{
	return 0;
}

GLvoid CCharacter::DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)
{
}

GLfloat CCharacter::GetSpeed()
{
	return m_fSpeed;
}

Vec3 CCharacter::GetPosition()
{
	return m_tPosition;
}

bool CCharacter::GetSniperMode()
{
	return m_bIsSniperMode;
}

float CCharacter::GetSniper()
{
	return m_fSniper;
}

void CCharacter::SetSniper(float _fSniper)
{
	m_fSniper = _fSniper;
}

void CCharacter::SetSniperMode(bool _bMode)
{
	m_bIsSniperMode = _bMode;
}

bool CCharacter::GetKeyUpState(KeyUpState _eState)
{
	return m_bKeyUpState[_eState];
}

void CCharacter::SetKeyUpstate(KeyUpState _eState,bool _bState)
{

	m_bKeyUpState[_eState] = _bState;

}

Vec3 CCharacter::GetCameraRotate()
{
	return m_fCameraRotate;
}

Vec3 CCharacter::GetCameraPos()
{
	return m_fCameraPos;
}

void CCharacter::SetCameraPos(float _fPos,int _Type)
{
	switch (_Type)
	{
	case 1:
		m_fCameraPos.fX = _fPos;
		break;
	case 2:
		m_fCameraPos.fY = _fPos;
		break;
	case 3:
		m_fCameraPos.fZ = _fPos;
		break;
	default:
		break;
	}
}

void CCharacter::SetCameraRotate(float _fPos, int _Type)
{
	switch (_Type)
	{
	case 1:
		m_fCameraRotate.fX = _fPos;
		break;
	case 2:
		m_fCameraRotate.fY = _fPos;
		break;
	case 3:
		m_fCameraRotate.fZ = _fPos;
		break;
	default:
		break;
	}
}

int CCharacter::GetCameraDistance()
{
	return m_iCameradistance;
}

void CCharacter::SetCameraDistance(int _iDistance)
{
	m_iCameradistance = _iDistance;
}
