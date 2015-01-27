//
//	Author:	Michael Cameron
//	Email:	chronokun@hotmail.com
//

#pragma once

#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__

// Prototypes
struct TVector3d;

// Structs
struct TMesh
{
	std::string m_MeshName;
	std::vector<TVector3d> m_VertexPositions;
	std::vector<std::vector<size_t>> m_Faces;
};

class CObjLoader
{
	// Member Variables
protected:
	std::vector<TMesh> m_Meshes;

public:
	//

	// Member Functions
protected:
	//

public:
	const bool LoadFile(const char* _kpcFilename);
	void Unload();
	const size_t GetMeshCount() const;
	const size_t GetFaceCount(const size_t _kMesh) const;
	void GetFace(std::vector<TVector3d>& _rResult, const size_t _kMesh, const size_t _kFace) const;

};

#endif