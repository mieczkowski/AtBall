#pragma once
#include "stdfx.h"
#include <vector>
using namespace std;
class NxTriangleMeshShapeDesc;
class NxConvexShapeDesc;
class CMesh
{
public:
	CMesh(){
		model=NULL;
		ppMaterials=NULL;
		ppAdjacency=NULL;
		numMaterials=0;
		numVertices=0;
		numFaces=0;
	}
	~CMesh(){ Clear(); }
public:
	bool Load(string tmpFileName);
	void Clear(){SAFE_RELEASE(model);}

	LPD3DXMESH GetModel(){return model;}
	DWORD GetVerticesNum(){return numVertices;}
	DWORD GetMaterialsNum(){return numMaterials;}
	DWORD GetVertexSize(){return vertexSize;}
	DWORD GetFacesNum(){return numFaces;}
	LPD3DXBUFFER GetMaterialsBuff(){return ppMaterials;}
	vector<short> GetIndicesList();
	vector<float> GetVerticesList(D3DXVECTOR3 scale);
	bool GenerateTriangleMeshShapeDesc(NxTriangleMeshShapeDesc* shape, D3DXVECTOR3 scale);
	NxConvexShapeDesc* GenerateConvexMeshDesc(D3DXVECTOR3 scale);
	virtual void OptimizeMesh();

	//bool CalcBounds(ID3DXMesh *pMesh, D3DXVECTOR3 *vCenter, float *radius);
	bool ScaleMesh(LPD3DXMESH mesh, D3DXVECTOR3 scale);
	LPD3DXMESH GetScaledMesh(D3DXVECTOR3 scale);
protected:
	LPD3DXMESH model;
	DWORD numVertices;
	DWORD numMaterials;
	DWORD numFaces;
	LPD3DXBUFFER ppAdjacency;
	LPD3DXBUFFER ppMaterials;
	DWORD vertexSize;
	std::string fileName;

};
