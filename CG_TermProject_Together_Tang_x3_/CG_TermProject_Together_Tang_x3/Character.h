#pragma once
#include "stdafx.h"
#include "Common.h"
#include "GameObject.h"
#include "BitmapMgr.h"
class CCharacter : public CGameObject
{
	CBitmapMgr*		m_pBitmapMgr;
	bool			m_bIsSniperMode;
	float			m_fSniper;
	Vec3			m_fCameraPos;
	Vec3			m_fCameraRotate;
	int				m_iCameradistance;
	bool			m_bKeyUpState[4];
public:
	CCharacter(CBitmapMgr* _pBitmapMgr);
	~CCharacter();

	virtual GLvoid Initialize();
	virtual GLvoid Draw();
	virtual GLvoid Update();
	virtual bool Collision();
	virtual GLvoid DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize);
public:
	GLfloat	GetSpeed();
	Vec3	GetPosition();
	Vec3	GetCameraRotate();
	Vec3	GetCameraPos();
	float	GetSniper();
	bool	GetSniperMode();
	bool	GetKeyUpState(KeyUpState _eState);
	int		GetCameraDistance();
public:
	void	SetSniper(float _fSniper);
	void	SetSniperMode(bool _bMode);
	void	SetKeyUpstate(KeyUpState _eState, bool _bState);
	void	SetCameraPos(float _fPos,int _Type);
	void	SetCameraRotate(float _fPos, int _Type);
	void	SetCameraDistance(int _iDistance);
	//void	SetCameraRotate(float _fX, float _fY, float _fZ);


};

