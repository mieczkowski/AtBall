#include "FrustrumShapes.h"
#include "Mesh.h"
#include "Camera.h"
#include "Logger.h"
#include "Directx.h"

float CFrustrumShape::GetRadius(void){
	return 0.0f;
}
D3DXVECTOR3 CFrustrumShape::GetCenter(void){
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}
D3DXVECTOR3 CFrustrumShape::GetMinPoint(void){
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}
D3DXVECTOR3 CFrustrumShape::GetMaxPoint(void){
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}
/////////////////////

bool CFrustrumSphere::Compute(CMesh* mesh, D3DXVECTOR3 scale){
	LPD3DXMESH tmpMesh = mesh->GetScaledMesh(scale);
	if(tmpMesh == NULL){
		ELOG("CFrustrumSphere","Compute","Nie mozna pobrac zeskalowanego mesha!");
		return false;
	}
	char* pData = NULL;
	if ( FAILED( tmpMesh->LockVertexBuffer( 0, (void**)&pData ) ) ){
		ELOG("CFrustrumSphere","Compute","Failed to lock Vertex buffer!");
		SAFE_RELEASE(tmpMesh);
		return false;
	}
	if(D3DXComputeBoundingSphere( (D3DXVECTOR3*)pData, 
		mesh->GetVerticesNum(), 
		mesh->GetVertexSize(), 
		&center, &radius )!=D3D_OK){
			ELOG("CFrustrumSphere","Compute","Failed to compute BSphere!");
			SAFE_RELEASE(tmpMesh);
			return false;
	}

	if ( FAILED( (tmpMesh->UnlockVertexBuffer() ) )){
		ELOG("CFrustrumSphere","Compute","Failed to unlock Vertex buffer!");
		SAFE_RELEASE(tmpMesh);
		return true;
	} 
	SAFE_RELEASE(tmpMesh);
	return true;
}

bool CFrustrumSphere::InFrustum(D3DXVECTOR3 objectPosition){
	D3DXVECTOR3 spherePosition = D3DXVECTOR3(objectPosition.x/*+center.x*/,objectPosition.y/*+center.y*/,objectPosition.z/*+center.z*/);
	D3DXPLANE* frustum=Camera.GetFrustum();
	for ( int i = 0; i < 6; i++ )
	{
		float temp = D3DXPlaneDotCoord( &frustum[i], &spherePosition );
		if ( temp + radius*5 < 0 )
		{
			return false; // Outside the frustum, reject it!
		}
	}
	return true; 
}

D3DXVECTOR3 CFrustrumSphere::GetCenter(void){
	return center;
}
float CFrustrumSphere::GetRadius(void){
	return radius;
}

/////////////////////////

bool CFrustrumBox::Compute(CMesh* mesh, D3DXVECTOR3 scale){
	char* pData = NULL;
	LPD3DXMESH tmpMesh = mesh->GetScaledMesh(scale);
	if(tmpMesh == NULL){
		ELOG("CFrustrumSphere","Compute","Nie mozna pobrac zeskalowanego mesha!");
		return false;
	}
	if ( FAILED( tmpMesh->LockVertexBuffer(0,(void**)&pData ) ) ){
		ELOG("CFrustrumBox","Compute","Failed to lock Vertex buffer!");
		SAFE_RELEASE(tmpMesh);
		return false;
	}
	if(D3DXComputeBoundingBox( (D3DXVECTOR3*)pData, 
		mesh->GetVerticesNum(), 
		mesh->GetVertexSize(), 
		&pMin, &pMax )){
			ELOG("CFrustrumBox","Compute","Failed to compute BSphere!");
			SAFE_RELEASE(tmpMesh);
			return false;
	}

	if ( FAILED( tmpMesh->UnlockVertexBuffer() ) ){
		ELOG("CFrustrumBox","Compute","Failed to unlock Vertex buffer!");
		SAFE_RELEASE(tmpMesh);
		return true;
	} 
	return true;
}

bool CFrustrumBox::InFrustum(D3DXVECTOR3 objectPosition){
	D3DXVECTOR3 center = D3DXVECTOR3(pMax.x-pMin.x,pMax.y-pMin.y,pMax.z-pMin.z);

	float sizeX = ((pMax.x-pMin.x)/2)*5;
	float sizeY = ((pMax.y-pMin.y)/2)*5;
	float sizeZ = ((pMax.z-pMin.z)/2)*5;

	//D3DXVECTOR3 centerInWorld = D3DXVECTOR3(objectPosition.x+center.x,objectPosition.y+center.y,objectPosition.z+center.z);

	D3DXPLANE* frustum=Camera.GetFrustum();

	for(int i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x - sizeX, objectPosition.y - sizeY,
			objectPosition.z - sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x + sizeX, objectPosition.y - sizeY,
			objectPosition.z - sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x - sizeX, objectPosition.y + sizeY,
			objectPosition.z - sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x + sizeX, objectPosition.y + sizeY,
			objectPosition.z - sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x - sizeX, objectPosition.y - sizeY,
			objectPosition.z + sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x + sizeX, objectPosition.y - sizeY,
			objectPosition.z + sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x - sizeX, objectPosition.y + sizeY,
			objectPosition.z + sizeZ)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&frustum[i],
			&D3DXVECTOR3(objectPosition.x + sizeX, objectPosition.y + sizeY,
			objectPosition.z + sizeZ)) >= 0.0f)
			continue;

		return false;
	}

	return true;
}

D3DXVECTOR3 CFrustrumBox::GetMinPoint(void){
	return pMin;
}
D3DXVECTOR3 CFrustrumBox::GetMaxPoint(void){
	return pMax;
}