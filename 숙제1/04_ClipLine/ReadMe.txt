========================================================================
       WIN32 APPLICATION : winmain
========================================================================


AppWizard has created this winmain application for you.  

This file contains a summary of what you will find in each of the files that
make up your winmain application.

winmain.cpp
    This is the main application source file.

winmain.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.
	

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named winmain.pch and a precompiled types file named StdAfx.obj.


/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.


/////////////////////////////////////////////////////////////////////////////
	for (i = 1; i < sheight; ++i)
		memcpy(Bits + scanline * i, Bits, scanline);
/*
PutPixel�� ���ϴ� x,y ��ǥ���� ���
PutPixel�� rgbĮ�� ����
���ϴ� �������� ȭ�� Ŭ����(memcpy..)
HLine+Ŭ����
VLine+Ŭ����
DrawBox
FillBox
*/