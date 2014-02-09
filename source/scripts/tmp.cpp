bool CMesh::CalcBounds(ID3DXMesh *pMesh, D3DXVECTOR3 *vCenter, float *radius){
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
}
bool CMesh::ScaleMesh(ID3DXMesh *pMesh, float scale, D3DXVECTOR3 *offset){
	BYTE *ptr=NULL;
	HRESULT hr;
	D3DXVECTOR3 vOff;
	if (!pMesh){
		ELOG("CMesh", "ScaleMesh", "Mesh == null!");
		return false;
	}
	if (offset) vOff = *offset;
	else vOff=D3DXVECTOR3(0.0f,0.0f,0.0f);
	DWORD numVerts=pMesh->GetNumVertices();
	// get the FVF flags
	//DWORD fvf=pMesh->GetFVF();
	// calculate vertex size
	DWORD vertSize= vertexSize;//D3DXGetFVFVertexSize(fvf);
	if (FAILED(hr=pMesh->LockVertexBuffer(0,(LPVOID*)&ptr))){
		ELOG("CMesh", "ScaleMesh", "LockVertexBuffer Failed!");
		return false;
	}
	for (DWORD i=0;i<numVerts;i++){
		//get pointer to location
		D3DXVECTOR3 *vPtr=(D3DXVECTOR3 *) ptr;
		//scale the vertex
		*vPtr+=vOff;
		vPtr->x*=scale;
		vPtr->y*=scale;
		vPtr->z*=scale;
		// increment pointer to next vertex
		ptr+=vertSize;
	}
	if (FAILED(hr=pMesh->UnlockVertexBuffer())){
		ELOG("CMesh", "ScaleMesh", "UnlockVertexBuffer Failed!");
		return false;
	}
	return true;
}
bool CMesh::NormalizeMesh(ID3DXMesh *pMesh, float scaleTo, BOOL bCenter){
	D3DXVECTOR3 vCenter;
	float radius;
	HRESULT hr;
	if (FAILED(hr=CalcBounds(pMesh,&vCenter,&radius))){
		ELOG("CMesh", "NormalizeMesh", "CalcBounds failed!");
		return false;
	}

	// calculate scaling factor
	float scale=scaleTo;///radius;

	D3DXVECTOR3 vOff;
	if (bCenter) vOff=-vCenter;
	else vOff=D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	if(!ScaleMesh(pMesh,scale,&vOff)){
		ELOG("CMesh", "ScaleMesh", "ScaleMesh Failed!");
		return false;
	}
	return true;
}