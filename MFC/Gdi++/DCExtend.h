#pragma once

#include "DrawManager_Export.h"

class DRAWMANAGER_API CDCExtend
{
public:
	CDCExtend(void);
	virtual ~CDCExtend(void);
public:
	static CSize MMtoPixel(CDC * pDC,const CSize & s);
	static CSize PixeltoMM(CDC * pDC,const CSize & s);
	static CRect MMtoPixel(CDC * pDC,const CRect & rc);
	static CRect PixeltoMM(CDC * pDC,const CRect & rc);
	//////////////////////////////////////////////////////////////////////////
	static double MMtoPixelX(CDC * pDC,const float & mm);
	static double MMtoPixelY(CDC * pDC,const float & mm);
	static double PixeltoMMX(CDC * pDC,const int & pixel);
	static double PixeltoMMY(CDC * pDC,const int & pixel);
public:
	static float m_HIMETRIC_INCH;
};
