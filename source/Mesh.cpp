#include "Mesh.h"
#include "Logger.h"
#include "Physx.h"
#include "Directx.h"
#include "Stream.h"
using namespace std;

/*bool CMesh::CalcBounds(ID3DXMesh *pMesh, D3DXVECTOR3 *vCenter, float *radius){
	BYTE *ptr=NULL;
	HRESULT hr;
	if (!pMesh){
		ELOG("CMesh", "CalcBounds", "Mesh == null!");
		return false;
	}
	DWORD numVerts=pMesh->GetNumVertices();
	DWORD fvfSize = vertexSize; //D3DXGetFVFVertexSize(pMesh->GetFVF());  // See DX8 Version
	if (FAILED(hr=pMesh->LockVertexBuffer(0,(LPVOID*)&ptr))){
		ELOG("CMesh", "CalcBounds", "LockVertexBuffer Failed!");
		return false;
	}
	if (FAILED(hr=D3DXComputeBoundingSphere((D3DXVECTOR3 *) ptr, numVerts, fvfSize, vCenter, radius ))){
		ELOG("CMesh", "CalcBounds", "ComputeBoundingSphere Failed!");
		return false;
	}
	if (FAILED(hr=pMesh->UnlockVertexBuffer())){
		ELOG("CMesh", "CalcBounds", "UnlockVertexBuffer Failed!");
		return false;
	}
	return true;
}*/
bool CMesh::ScaleMesh(ID3DXMesh *pMesh, D3DXVECTOR3 scale){
	if (!pMesh){
		ELOG("CMesh", "ScaleMesh", "Mesh == null!");
		return false;
	}
	D3DXVECTOR3 vOff = D3DXVECTOR3(0.0f,0.0f,0.0f);
	DWORD numVerts=pMesh->GetNumVertices();
	BYTE *ptr = NULL;
	if (FAILED(pMesh->LockVertexBuffer(0,(LPVOID*)&ptr))){
		ELOG("CMesh", "ScaleMesh", "LockVertexBuffer Failed!");
		return false;
	}
	for (DWORD i=0;i<numVerts;i++){
		D3DXVECTOR3 *vPtr=(D3DXVECTOR3 *) ptr;
		*vPtr+=vOff;
		vPtr->x*=scale.x;
		vPtr->y*=scale.y;
		vPtr->z*=scale.z;
		ptr+=vertexSize;
	}
	if (FAILED(pMesh->UnlockVertexBuffer())){
		ELOG("CMesh", "ScaleMesh", "UnlockVertexBuffer Failed!");
		return false;
	}
	return true;
}
LPD3DXMESH CMesh::GetScaledMesh(D3DXVECTOR3 scale){
	//tworzymy nowego tymczasowego mesha
	ID3DXMesh* TempMesh = NULL;
	D3DVERTEXELEMENT9 decl[] = 
	{
		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0,28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0,36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		{0,48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		D3DDECL_END()
	};
	model->CloneMesh( model->GetOptions(), decl, DirectX.GetDevice(), &TempMesh );

	if(!ScaleMesh(TempMesh,scale)){
		ELOG("CMesh", "ScaleMesh", "ScaleMesh Failed!");
		return NULL;
	}
	return TempMesh;
}

bool CMesh::Load(string tmpFileName){
	if(!DirectX.GetDevice()) return false;
	fileName = tmpFileName;
	if(D3DXLoadMeshFromX(fileName.c_str(),D3DXMESH_MANAGED,DirectX.GetDevice(),
		&ppAdjacency,&ppMaterials,0,&numMaterials, &model)!=D3D_OK){
			ELOG("Mesh", "Set", string("Nie mo¿na za³adowaæ modelu! Nazwa: ") + fileName);
		return false;
	}else{
		OptimizeMesh();
// 		if(NormalizeMesh(model, 3.0f, FALSE)) return true;
// 		else{
// 			ELOG("CMesh", "Load", "Nie mozna zeskalowac mesha!");
// 			return false;
// 		}
		return true;
	}
}

void CMesh::OptimizeMesh(){
	numVertices=model->GetNumVertices();
	DWORD FVF = model->GetFVF();
	ID3DXMesh* TempMesh = NULL;
	D3DVERTEXELEMENT9 decl[] = 
		 	{
		 		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		 		{0,16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		 		{0,28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		 		{0,36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		 		{0,48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		 		D3DDECL_END()
		 	};
	model->CloneMesh( model->GetOptions(),
			decl,
			DirectX.GetDevice(), &TempMesh );
	SAFE_RELEASE( model );
	if(D3DXComputeTangentFrameEx(
		TempMesh,                // Input mesh
		D3DDECLUSAGE_TEXCOORD, 0,      // Vertex element of input tex-coords.
		D3DDECLUSAGE_BINORMAL, 0,      // Vertex element to output binormal.
		D3DDECLUSAGE_TANGENT, 0,       // Vertex element to output tangent.
		D3DDECLUSAGE_NORMAL, 0,        // Vertex element to output normal.
		0,                             // Options
		0,                             // Adjacency
		0.01f, 0.25f, 0.01f,           // Thresholds for handling errors
		&model,                   // Output mesh
		0) != D3D_OK){
		ELOG("Mesh", "OptimizeMesh", string("Nie mo¿na zoptymalizowaæ modelu [D3DXComputeTangentFrameEx]! Nazwa") + fileName);
	}  
	SAFE_RELEASE( TempMesh );
	//model = TempMesh;


	numFaces = model->GetNumFaces()*3;
	
// 	OptimizeInplace( 
// 		D3DXMESHOPT_ATTRSORT |    // Reorders faces to optimize for fewer attribute bundle state changes and enhanced ID3DXBaseMesh::DrawSubset performance.
// 		D3DXMESHOPT_VERTEXCACHE | // Reorders faces to increase the cache hit rate of vertex caches.
// 		D3DXMESHOPT_IGNOREVERTS,  // Optimize the faces only; do not optimize the vertices.
// 		pAdj, 
// 		NULL, NULL, NULL );
	DWORD* rgdwAdjacency = new DWORD[numFaces];

	if( !rgdwAdjacency == NULL )
	{
		if(model->GenerateAdjacency(0.0f , rgdwAdjacency ) == D3D_OK){//1e-6f
			if(model->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, 
				rgdwAdjacency, NULL, NULL, NULL )!=D3D_OK){
					ELOG("Mesh", "OptimizeMesh", string("Nie mo¿na zoptymalizowaæ modelu [OptimizeInplace]! Nazwa") + fileName);
			}
		}else{
			//ELOG("Mesh", "OptimizeMesh", string("Nie mo¿na zoptymalizowaæ modelu [GenerateAdjacency]! Nazwa") + fileName);
		}
				
		
		delete []rgdwAdjacency;
	}

	numVertices=model->GetNumVertices();
	//vertexSize=D3DXGetFVFVertexSize(FVF);
	//if(!(FVF & D3DFVF_NORMAL)) vertexSize+= 3*D3DXGetFVFVertexSize(D3DFVF_NORMAL);
	vertexSize = 15 * sizeof(float);//D3DXFVFVertexSize(D3DFVF_TEX0) + 3 * D3DXGetFVFVertexSize(D3DFVF_NORMAL) + D3DXGetFVFVertexSize(D3DFVF_XYZW);

	return;
}



// void CMesh::OptimizeMesh(){
// 	type = RST_SIMPLE;
// 	numVertices=model->GetNumVertices();
// 	DWORD FVF = model->GetFVF();
// 	ID3DXMesh* TempMesh = NULL;
// 
// 	if(!(FVF & D3DFVF_NORMAL))
// 	{
// 		model->CloneMeshFVF( model->GetOptions(),
// 			FVF | D3DFVF_NORMAL,
// 			DirectX.GetDevice(), &TempMesh );
// 
// 		D3DXComputeNormals( TempMesh, NULL );
// 		//D3DXComputeTangentFrame(TempMesh)
// 		SAFE_RELEASE( model );
// 		model = TempMesh;
// 	}
// 
// 	numFaces = model->GetNumFaces()*3;
// 	DWORD* rgdwAdjacency = new DWORD[numFaces];
// 
// 	if( !rgdwAdjacency == NULL )
// 	{
// 		TempMesh=model;
// 		TempMesh->GenerateAdjacency( 1e-6f, rgdwAdjacency );
// 		if(TempMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, 
// 			rgdwAdjacency, NULL, NULL, NULL )!=D3D_OK)
// 			ELOG("Mesh", "OptimizeMesh", string("Nie mo¿na zoptymalizowaæ modelu! Nazwa") + fileName);
// 		delete []rgdwAdjacency;
// 		model = TempMesh;
// 	}
// 
// 	numVertices=model->GetNumVertices();
// 	vertexSize=D3DXGetFVFVertexSize(FVF);
// 
// 	return;
// }

// void CMeshNormal::OptimizeMesh(){
// 	type = RST_NORMALMAP;
// 	numVertices=model->GetNumVertices();
// 	DWORD FVF = model->GetFVF();
// 	ID3DXMesh* TempMesh = NULL;
// 	D3DVERTEXELEMENT9 decl[] = 
// 	{
// 		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
// 		{0,16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
// 		{0,28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
// 		{0,36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
// 		{0,48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
// 		D3DDECL_END()
// 	};
// 	model->CloneMesh( model->GetOptions(),
// 		decl,
// 		DirectX.GetDevice(), &TempMesh );
// 
// 	D3DXComputeNormals( TempMesh, NULL );
// 	D3DXComputeTangent(TempMesh, 0, 0, 0,true, NULL);
// 	D3DXComputeTangentFrame(TempMesh, NULL);
// 	/*
// 	D3DXComputeTangentFrameEx(
// 	clonedTempMesh,                // Input mesh
// 	D3DDECLUSAGE_TEXCOORD, 0,      // Vertex element of input tex-coords.
// 	D3DDECLUSAGE_BINORMAL, 0,      // Vertex element to output binormal.
// 	D3DDECLUSAGE_TANGENT, 0,       // Vertex element to output tangent.
// 	D3DDECLUSAGE_NORMAL, 0,        // Vertex element to output normal.
// 	0,                             // Options
// 	0,                             // Adjacency
// 	0.01f, 0.25f, 0.01f,           // Thresholds for handling errors
// 	&mSceneMesh,                   // Output mesh
// 	0)
// 	*/
// 	SAFE_RELEASE( model );
// 	model = TempMesh;
// 
// 	numFaces = model->GetNumFaces()*3;
// 	DWORD* rgdwAdjacency = new DWORD[numFaces];
// 
// 	if( !rgdwAdjacency == NULL )
// 	{
// 		TempMesh=model;
// 		TempMesh->GenerateAdjacency( 1e-6f, rgdwAdjacency );
// 		if(TempMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_COMPACT, 
// 			rgdwAdjacency, NULL, NULL, NULL )!=D3D_OK)
// 			ELOG("Mesh", "OptimizeMesh", string("Nie mo¿na zoptymalizowaæ modelu! Nazwa") + fileName);
// 		delete []rgdwAdjacency;
// 		model = TempMesh;
// 	}
// 
// 	numVertices=model->GetNumVertices();
// 	vertexSize=D3DXGetFVFVertexSize(FVF);
// 	if(!(FVF & D3DFVF_NORMAL)) vertexSize+= 3*D3DXGetFVFVertexSize(D3DFVF_NORMAL);
// 	
// 
// 	return;
// }

std::vector<float> CMesh::GetVerticesList(D3DXVECTOR3 scale){
	vector<float> vertices;
	D3DXVECTOR3 vCenter;
	//float radius;
	HRESULT hr;

// 	if (FAILED(hr=CalcBounds(model,&vCenter,&radius))){
// 		ELOG("CMesh", "GetVerticesList", "CalcBounds failed!");
// 		return vertices;
// 	}
	//D3DXVECTOR3 scale = D3DXVECTOR3(3, 3, 3);

	D3DXVECTOR3 vOff;
	if (false) vOff=-vCenter;
	else vOff=D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	hr = NULL;

	BYTE* vbptr = NULL;
	model->LockVertexBuffer(0, (LPVOID*)&vbptr);

	if(FAILED(hr)){
		ELOG("Mesh", "GetVerticesList", "Failed to lock vertex buffer!");
	}

	int ii = -1;
	for(int i = 0; i < (int)numVertices; i++)
	{
		ii++;
		D3DXVECTOR3* pos = (D3DXVECTOR3*)vbptr;
		*pos+=vOff;
		vertices.push_back(pos->x*scale.x);
		vertices.push_back(pos->y*scale.y);
		vertices.push_back(pos->z*scale.z);

		vbptr += vertexSize;
	}
	hr = model->UnlockVertexBuffer();

	if(FAILED(hr)){
		ELOG("Mesh", "GetVerticesList", "Failed to unlock vertex buffer!");
		return vertices;
	}

	vbptr=NULL;
	delete vbptr;

	return vertices;
}

std::vector<short> CMesh::GetIndicesList(void)
{
	//LPVOID * ppData;

	HRESULT hr =NULL;


	DWORD stride = sizeof(short);
	BYTE* ibptr = NULL;

	short* indices = new short[numFaces];

	vector<short> copy;

	hr = model->LockIndexBuffer(0, (LPVOID*)&indices);

	if(FAILED(hr)){
		ELOG("Mesh", "GetInicesList", "Failed to lock index buffer!");
	}

	for(int i = 0; i < (int)numFaces; i++)
	{
		copy.push_back(indices[i]);
	}

	hr = model->UnlockIndexBuffer();
	if(FAILED(hr)){
		ELOG("Mesh", "GetInicesList", "Failed to unlock index buffer!");
	}


	indices=NULL;
	delete indices;
	return copy;
}

bool CMesh::GenerateTriangleMeshShapeDesc(NxTriangleMeshShapeDesc* shape, D3DXVECTOR3 scale)
{
	vector<float> vertices = GetVerticesList(scale);
	vector<short> indices = GetIndicesList();

	NxVec3* verts = new NxVec3[numVertices];

	int ii = -1;

	for(unsigned int i = 0; i < numVertices; i++)
	{
		++ii;
		verts[i].x = vertices[ii];//2;
		verts[i].y = vertices[++ii];//2;
		verts[i].z = vertices[++ii];//2;
	}

	NxU32 *tris = new NxU32[numFaces];

	ii = 0;

	for(unsigned int NumInd = 0; NumInd < numFaces; NumInd++)
	{
		tris[NumInd] = indices[ii];
		NumInd++;
		tris[NumInd] = indices[++ii];
		NumInd++;
		tris[NumInd] = indices[++ii];
		++ii;
	}

	// Build physical model
	NxTriangleMeshDesc TriMeshDesc;
	TriMeshDesc.numVertices = numVertices;
	TriMeshDesc.numTriangles = numFaces/3;
	TriMeshDesc.pointStrideBytes = sizeof(NxVec3);
	TriMeshDesc.triangleStrideBytes = 3*sizeof(NxU32);
	TriMeshDesc.points = verts;
	TriMeshDesc.triangles = tris;
	TriMeshDesc.flags = NULL;


	//NxTriangleMeshShapeDesc ShapeDesc;
	NxInitCooking(Physx.GetAllocator(),NULL);

	if(!TriMeshDesc.isValid()){
		ELOG("CMesh","GenerateTriangleMeshShapeDesc",string("TriangleMeshDesc is invalid."));
		return false;
	}

	MemoryWriteBuffer buf;

	if(!NxCookTriangleMesh(TriMeshDesc, buf)){
		ELOG("CMesh","GenerateTriangleMeshShapeDesc",string("Error while cooking tringle mesh."));
		return false;
	}
	shape->meshData = Physx.GetPhysicsSDK()->createTriangleMesh(MemoryReadBuffer(buf.data));
	shape->shapeFlags = NX_SF_FEATURE_INDICES;

	delete[] verts;
	delete[] tris;
	vertices.clear();
	indices.clear();

	if(!shape->isValid()){
		ELOG("CMesh","GenerateTriangleMeshShapeDesc",string("ShapeDesc is invalid."));
		return false;
	}
	return true;
}

NxConvexShapeDesc* CMesh::GenerateConvexMeshDesc(D3DXVECTOR3 scale){
	std::vector<float> vertices = this->GetVerticesList(scale);
	NxVec3* verts = new NxVec3[numVertices];
	int ii = -1;
	for(unsigned int i = 0; i < numVertices; i++)
	{
		++ii;
		verts[i].x = vertices[ii];//2;
		verts[i].y = vertices[++ii];//2;
		verts[i].z = vertices[++ii];//2;
	}
	////Create pointer for indices
	/*NxU32 *tris = new NxU32[NumTriangles * 3];*/
	ii = 0;
	/*for(int NumInd = 0; NumInd < NumTriangles * 3; NumInd++)
	{
	tris[NumInd] = indices[ii];
	NumInd++;
	tris[NumInd] = indices[++ii];
	NumInd++;
	tris[NumInd] = indices[++ii];
	++ii;
	}*/

	// Build physical model
	NxConvexMeshDesc convexDesc;
	convexDesc.numVertices = numVertices;
	convexDesc.pointStrideBytes = sizeof(NxVec3);
	convexDesc.points = verts;
	convexDesc.flags = NX_CF_COMPUTE_CONVEX;
	// Cooking from memory
	MemoryWriteBuffer buf;
	NxInitCooking(Physx.GetAllocator(),NULL);
	bool status = convexDesc.isValid();
	if(!status){
		ELOG("Mesh","GenerateConvexShapeDesc","Convex Description is invalid");
		return NULL;
	}
	NxConvexShapeDesc *convexShapeDesc = new NxConvexShapeDesc(); 
	status=NxCookConvexMesh(convexDesc,buf);
	if(status){       
		convexShapeDesc->meshData = Physx.GetPhysicsSDK()->createConvexMesh(MemoryReadBuffer(buf.data));
		status = convexShapeDesc->isValid();
		if(!status){
			ELOG("Mesh","GenerateConvexShapeDesc","Error while creating ConvexMesh");
			return NULL;
		}
	}else{
		ELOG("Mesh","GenerateConvexShapeDesc","Error while cooking ConvexMesh");
		return NULL;
	}
	delete[] verts;
	NxCloseCooking();
	status=convexShapeDesc->isValid();
	if(!status)	{
		ELOG("Mesh","GenerateConvexShapeDesc","B³ad przy tworzeniu CovexMesha");
		return NULL;
	}
	return convexShapeDesc;
}