// Libraries Include
#include "libraries.h"
// This Include
#include "brush.h"

TBrush ExtrudeBrushFromFace(const std::vector<TVector3d>& _krFace)
{
	TBrush Brush;

	const TVector3d kNormal = GetPolygonNormal(TVector3d(), _krFace.data(), _krFace.size());

	TVector3d Average{0.0, 0.0, 0.0};
	for(const TVector3d& krVertex : _krFace)
	{
		Add(Average, Average, krVertex);
	}
	const TVector3d kCenter = ScalarMultiply(TVector3d(), Average, (1.0 / (double)_krFace.size()));

	const TVector3d kBackPoint = Add(TVector3d(), kCenter, ScalarMultiply(TVector3d(), kNormal, -4.0));

	Brush.m_Positions.resize(_krFace.size() + 1);
	for(size_t i = 0; i < _krFace.size(); ++i)
	{
		Brush.m_Positions[i] = _krFace[i];
	}
	Brush.m_Positions[Brush.m_Positions.size()-1] = kBackPoint;

	// Add indices
	Brush.m_Faces.resize(_krFace.size()+1);
	for(size_t i = 0; i < Brush.m_Positions.size()-1; ++i)
	{
		Brush.m_Faces[0].push_back(i);
	}
	for(size_t i = 1; i < Brush.m_Faces.size(); ++i)
	{
		Brush.m_Faces[i].push_back(i-1);
		Brush.m_Faces[i].push_back(Brush.m_Positions.size()-1);
		Brush.m_Faces[i].push_back(i % (Brush.m_Faces.size()-1));
	}

	for(std::vector<size_t>& rFace : Brush.m_Faces)
	{
		std::reverse(rFace.begin(), rFace.end());
	}

	return(Brush);
}
