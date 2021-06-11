#include "StdAfx.h"
#include "DCExtend.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(push)
#pragma warning(disable:4244)

float CDCExtend::m_HIMETRIC_INCH  = 25.4f  ;  // HIMETRIC units per inch

CDCExtend::CDCExtend(void)
{
}

CDCExtend::~CDCExtend(void)
{
	
}
CSize CDCExtend::MMtoPixel(CDC * pDC,const CSize & s)
{
	CSize size;
	size.cx = (long)((float)s.cx*(float)pDC->GetDeviceCaps(LOGPIXELSX))/m_HIMETRIC_INCH;

	size.cy = (long)((float)s.cy*(float)pDC->GetDeviceCaps(LOGPIXELSY))/m_HIMETRIC_INCH;

	return size;
}
CSize CDCExtend::PixeltoMM(CDC * pDC,const CSize & s)
{
	CSize size;
	size.cx = (long)(((float)s.cx*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSX));
	size.cx = (long)(((float)s.cy*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSY));
	return size;
}
CRect CDCExtend::MMtoPixel(CDC * pDC,const CRect & rc)
{
	CRect r;
	r.left =(long)(((float)rc.left*(float)pDC->GetDeviceCaps(LOGPIXELSX))/m_HIMETRIC_INCH);

	r.top = (long)(((float)rc.top*(float)pDC->GetDeviceCaps(LOGPIXELSY))/m_HIMETRIC_INCH);

	r.right =(long)(((float)rc.right*(float)pDC->GetDeviceCaps(LOGPIXELSX))/m_HIMETRIC_INCH);

	r.bottom = (long)(((float)rc.bottom*(float)pDC->GetDeviceCaps(LOGPIXELSY))/m_HIMETRIC_INCH);

	return r;
}
CRect CDCExtend::PixeltoMM(CDC * pDC,const CRect & rc)
{
	CRect r;
	r.left = (((float)rc.left*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSX));
	r.top = (((float)rc.top*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSY));
	r.right = (((float)rc.right*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSX));
	r.bottom = (((float)rc.bottom*m_HIMETRIC_INCH)/(float)pDC->GetDeviceCaps(LOGPIXELSY));
	return r;
}
double CDCExtend::MMtoPixelX(CDC * pDC,const float & mm)
{
	return ((mm*(double)pDC->GetDeviceCaps(LOGPIXELSX))/m_HIMETRIC_INCH);
}
double CDCExtend::MMtoPixelY(CDC * pDC,const float & mm)
{
	return ((mm*(double)pDC->GetDeviceCaps(LOGPIXELSY))/m_HIMETRIC_INCH);
}
double CDCExtend::PixeltoMMX(CDC * pDC,const int & pixel)
{
	return (double)((((double)pixel*m_HIMETRIC_INCH)/(double)pDC->GetDeviceCaps(LOGPIXELSX)));
}
double CDCExtend::PixeltoMMY(CDC * pDC,const int & pixel)
{
	return (double)((((double)pixel*m_HIMETRIC_INCH)/(double)pDC->GetDeviceCaps(LOGPIXELSY)));
}
#pragma warning(pop)