// Libraries Include
#include "libraries.h"
// This Include
#include "objloader.h"

static const size_t s_kLineSize = 65536;

const bool CObjLoader::LoadFile(const char* _kpcFilename)
{
	std::ifstream InFile;
	char pcLine[s_kLineSize];
	const char* kpcDelim  = " /";
	char* pcToken;
	char* pcContext;
	std::vector<std::vector<std::string>> Tokens;

	bool bNormals = false;
	bool bTexCoords = false;

	InFile.open(_kpcFilename);
	if(InFile.is_open())
	{
		while(InFile.getline(pcLine, s_kLineSize))
		{
			Tokens.push_back(std::vector<std::string>());
			pcToken = strtok_s(pcLine, kpcDelim, &pcContext);
			while(pcToken != NULL)
			{
				Tokens[Tokens.size()-1].push_back(std::string(pcToken));
				pcToken = strtok_s(NULL, kpcDelim, &pcContext);
			}
		}
		InFile.close();
	}
	else
	{
		return(false);
	}

	for(const std::vector<std::string>& krLine : Tokens)
	{
		if(krLine[0].compare("o") == 0)
		{
			this->m_Meshes.push_back(TMesh());
			this->m_Meshes[this->m_Meshes.size()-1].m_MeshName = krLine[1];
		}
		else if(krLine[0].compare("v") == 0)
		{
			this->m_Meshes[this->m_Meshes.size()-1].m_VertexPositions.push_back(TVector3d());
			this->m_Meshes[this->m_Meshes.size()-1].m_VertexPositions[this->m_Meshes[this->m_Meshes.size()-1].m_VertexPositions.size()-1]
				= TVector3d{std::stod(krLine[1]), std::stod(krLine[2]), std::stod(krLine[3])};
		}
		else if(krLine[0].compare("vn") == 0)
		{
			bNormals = true;
		}
		else if(krLine[0].compare("vt") == 0)
		{
			bTexCoords = true;
		}
		else if(krLine[0].compare("f") == 0)
		{
			this->m_Meshes[this->m_Meshes.size()-1].m_Faces.push_back(std::vector<size_t>());
			for(size_t i = 1; i < krLine.size(); ++i)
			{
				this->m_Meshes[this->m_Meshes.size()-1].m_Faces[this->m_Meshes[this->m_Meshes.size()-1].m_Faces.size()-1].push_back(std::stol(krLine[i]));

				if(bTexCoords)
				{
					i++;
				}
				if(bNormals)
				{
					i++;
				}
			}
		}
	}

	return(true);
}

void CObjLoader::Unload()
{
	this->m_Meshes.clear();
}

const size_t CObjLoader::GetMeshCount() const
{
	return(this->m_Meshes.size());
}

const size_t CObjLoader::GetFaceCount(const size_t _kMesh) const
{
	return(this->m_Meshes[_kMesh].m_Faces.size());
}

void CObjLoader::GetFace(std::vector<TVector3d>& _rResult, const size_t _kMesh, const size_t _kFace) const
{
	_rResult.resize(this->m_Meshes[_kMesh].m_Faces[_kFace].size());
	for(size_t i = 0; i < this->m_Meshes[_kMesh].m_Faces[_kFace].size(); ++i)
	{
		const size_t kIndex = this->m_Meshes[_kMesh].m_Faces[_kFace][i] - 1;
		_rResult[i] = this->m_Meshes[_kMesh].m_VertexPositions[kIndex];
	}
}
