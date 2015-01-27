//
//	Author:	Michael Cameron
//	Email:	chronokun@hotmail.com
//

// Libraries Include
#include "libraries.h"
// Local Includes
#include "objloader.h"
#include "brush.h"

static CObjLoader s_ObjLoader;

std::string StringFromBrush(const TBrush& _krBrush)
{
	std::stringstream ssOut;
	ssOut << "brush" << std::endl;
	ssOut << "\tvertices" << std::endl;
	ssOut << std::fixed;
	for(const TVector3d& krVertex : _krBrush.m_Positions)
	{
		ssOut << "\t\t" << krVertex.m_dX << " " << krVertex.m_dY << " " << -krVertex.m_dZ << std::endl;
	}
	ssOut << "\tfaces" << std::endl;
	for(size_t i = 0; i < _krBrush.m_Faces.size(); ++i)
	{
		const std::vector<size_t>& krFace = _krBrush.m_Faces[i];
		ssOut << "\t\t" << 0.0f << " " << 0.0f << " " << 1.0f << " " << 1.0f << " " << 0.0f;
		for(const size_t kIndex : krFace)
		{
			ssOut << " " << kIndex;
		}
		if(i)
		{
			ssOut << " " << "internal/editor/textures/editor_nolight";
		}
		ssOut << std::endl;
	}

	return(ssOut.str());
}

int main(const int _kiArgC, const char** _kppcArgv)
{
	// Check we have correct number of parameters
	if(_kiArgC < 3)
	{
		return(3);
	}

	const bool kbLoaded = s_ObjLoader.LoadFile(_kppcArgv[1]);
	if(!kbLoaded)
	{
		return(2);
	}

	std::vector<TBrush> Brushes;
	for(size_t i = 0; i < s_ObjLoader.GetMeshCount(); ++i)
	{
		for(size_t j = 0; j < s_ObjLoader.GetFaceCount(i); ++j)
		{
			std::vector<TVector3d> Face;
			s_ObjLoader.GetFace(Face, i, j);
			Brushes.push_back(ExtrudeBrushFromFace(Face));
		}
	}

	std::ofstream OutFile;
	OutFile.open(_kppcArgv[2]);
	if(OutFile.is_open())
	{
		OutFile << "reflex map version 6\n"
				<< "entity\n"
				<< "\ttype WorldSpawn\n"
				<< "\tColourXRGB32 clearColor ffffff\n"
				<< "\tColourXRGB32 worldColor0 0\n"
				<< "\tColourXRGB32 worldColor1 0\n";

		for(const TBrush& krBrush : Brushes)
		{
			OutFile << StringFromBrush(krBrush);
		}
		OutFile.close();
	}
	else
	{
		return(1);
	}

	return(0);
}