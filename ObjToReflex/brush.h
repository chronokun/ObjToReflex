//
//	Author:	Michael Cameron
//	Email:	chronokun@hotmail.com
//

#pragma once

#ifndef __BRUSH_H__
#define __BRUSH_H__

// Prototypes
struct TVector3d;

struct TBrush
{
	std::vector<TVector3d> m_Positions;
	std::vector<std::vector<size_t>> m_Faces;
};

TBrush ExtrudeBrushFromFace(const std::vector<TVector3d>& _krFace);

#endif