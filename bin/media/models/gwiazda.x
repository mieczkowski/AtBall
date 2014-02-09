xof 0302txt 0032
Header {
 1;
 0;
 1;
}
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}
template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}
Frame Hedra01 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh Hedra011 {
 132;
0.000000;1.010000;0.000000;,
0.505000;-0.312100;-0.817100;,
0.505000;-0.312100;0.817100;,
0.505000;-0.312100;0.817100;,
-0.312100;-0.817100;-0.505000;,
-0.817100;0.505000;0.312100;,
-0.817100;0.505000;0.312100;,
0.000000;0.000000;-1.010000;,
0.817100;0.505000;0.312100;,
0.817100;0.505000;0.312100;,
0.312100;-0.817100;-0.505000;,
-0.505000;-0.312100;0.817100;,
-0.505000;-0.312100;0.817100;,
-0.505000;-0.312100;-0.817100;,
0.000000;1.010000;0.000000;,
-0.505000;-0.312100;-0.817100;,
0.312100;-0.817100;0.505000;,
0.817100;0.505000;-0.312100;,
0.817100;0.505000;-0.312100;,
0.000000;0.000000;1.010000;,
-0.817100;0.505000;-0.312100;,
-0.817100;0.505000;-0.312100;,
-0.312100;-0.817100;0.505000;,
0.505000;-0.312100;-0.817100;,
1.010000;0.000000;0.000000;,
-0.312100;0.817100;-0.505000;,
-0.312100;-0.817100;-0.505000;,
-0.312100;-0.817100;0.505000;,
-0.312100;0.817100;0.505000;,
1.010000;0.000000;0.000000;,
0.000000;0.000000;1.010000;,
0.817100;-0.505000;-0.312100;,
-0.817100;-0.505000;-0.312100;,
-0.817100;-0.505000;-0.312100;,
0.505000;0.312100;-0.817100;,
-0.312100;0.817100;0.505000;,
0.505000;0.312100;0.817100;,
-0.817100;-0.505000;0.312100;,
-0.312100;0.817100;-0.505000;,
0.505000;0.312100;-0.817100;,
0.000000;-1.010000;0.000000;,
0.505000;0.312100;0.817100;,
0.817100;-0.505000;-0.312100;,
0.312100;0.817100;0.505000;,
-0.505000;0.312100;-0.817100;,
-0.505000;0.312100;-0.817100;,
-0.505000;0.312100;0.817100;,
0.000000;-1.010000;0.000000;,
0.817100;-0.505000;0.312100;,
0.000000;0.000000;-1.010000;,
-0.817100;-0.505000;0.312100;,
-0.505000;0.312100;0.817100;,
0.312100;0.817100;-0.505000;,
0.817100;-0.505000;0.312100;,
0.312100;0.817100;0.505000;,
0.312100;-0.817100;0.505000;,
-1.010000;0.000000;0.000000;,
-1.010000;0.000000;0.000000;,
0.312100;-0.817100;-0.505000;,
0.312100;0.817100;-0.505000;,
0.000000;0.279200;0.451700;,
0.505000;-0.312100;0.817100;,
-0.817100;0.505000;0.312100;,
0.817100;0.505000;0.312100;,
-0.505000;-0.312100;0.817100;,
0.000000;1.010000;0.000000;,
0.000000;0.279200;-0.451700;,
-0.505000;-0.312100;-0.817100;,
0.817100;0.505000;-0.312100;,
-0.817100;0.505000;-0.312100;,
0.505000;-0.312100;-0.817100;,
0.000000;1.010000;0.000000;,
0.279200;-0.451700;0.000000;,
0.505000;-0.312100;-0.817100;,
-0.312100;-0.817100;0.505000;,
1.010000;0.000000;0.000000;,
-0.312100;-0.817100;-0.505000;,
0.505000;-0.312100;0.817100;,
-0.451700;0.000000;0.279200;,
-0.817100;0.505000;-0.312100;,
0.000000;0.000000;1.010000;,
-0.817100;-0.505000;-0.312100;,
-0.312100;0.817100;0.505000;,
-0.312100;-0.817100;0.505000;,
0.279200;0.451700;0.000000;,
-0.312100;0.817100;0.505000;,
0.505000;0.312100;-0.817100;,
0.505000;0.312100;0.817100;,
-0.312100;0.817100;-0.505000;,
1.010000;0.000000;0.000000;,
0.000000;-0.279200;-0.451700;,
-0.817100;-0.505000;-0.312100;,
0.817100;-0.505000;-0.312100;,
-0.505000;0.312100;-0.817100;,
0.000000;-1.010000;0.000000;,
0.505000;0.312100;-0.817100;,
0.000000;-0.279200;0.451700;,
0.000000;-1.010000;0.000000;,
-0.505000;0.312100;0.817100;,
0.817100;-0.505000;0.312100;,
-0.817100;-0.505000;0.312100;,
0.505000;0.312100;0.817100;,
-0.279200;0.451700;0.000000;,
-0.505000;0.312100;-0.817100;,
0.312100;0.817100;0.505000;,
-1.010000;0.000000;0.000000;,
0.312100;0.817100;-0.505000;,
-0.505000;0.312100;0.817100;,
0.451700;0.000000;-0.279200;,
0.312100;0.817100;-0.505000;,
0.312100;-0.817100;-0.505000;,
0.817100;0.505000;0.312100;,
0.000000;0.000000;-1.010000;,
0.817100;-0.505000;0.312100;,
-0.279200;-0.451700;0.000000;,
-1.010000;0.000000;0.000000;,
0.312100;-0.817100;0.505000;,
-0.505000;-0.312100;-0.817100;,
-0.505000;-0.312100;0.817100;,
0.312100;-0.817100;-0.505000;,
0.451700;0.000000;0.279200;,
0.312100;-0.817100;0.505000;,
0.312100;0.817100;0.505000;,
0.817100;-0.505000;-0.312100;,
0.000000;0.000000;1.010000;,
0.817100;0.505000;-0.312100;,
-0.451700;0.000000;-0.279200;,
-0.817100;0.505000;0.312100;,
-0.312100;-0.817100;-0.505000;,
-0.312100;0.817100;-0.505000;,
-0.817100;-0.505000;0.312100;,
0.000000;0.000000;-1.010000;;

 80;
3;2,1,0;,
3;5,4,3;,
3;8,7,6;,
3;11,10,9;,
3;14,13,12;,
3;17,16,15;,
3;20,19,18;,
3;23,22,21;,
3;26,25,24;,
3;29,28,27;,
3;32,31,30;,
3;35,34,33;,
3;38,37,36;,
3;41,40,39;,
3;44,43,42;,
3;47,46,45;,
3;50,49,48;,
3;53,52,51;,
3;56,55,54;,
3;59,58,57;,
3;62,61,60;,
3;63,62,60;,
3;64,63,60;,
3;65,64,60;,
3;61,65,60;,
3;68,67,66;,
3;69,68,66;,
3;70,69,66;,
3;71,70,66;,
3;67,71,66;,
3;74,73,72;,
3;75,74,72;,
3;76,75,72;,
3;77,76,72;,
3;73,77,72;,
3;80,79,78;,
3;81,80,78;,
3;82,81,78;,
3;83,82,78;,
3;79,83,78;,
3;86,85,84;,
3;87,86,84;,
3;88,87,84;,
3;89,88,84;,
3;85,89,84;,
3;92,91,90;,
3;93,92,90;,
3;94,93,90;,
3;95,94,90;,
3;91,95,90;,
3;98,97,96;,
3;99,98,96;,
3;100,99,96;,
3;101,100,96;,
3;97,101,96;,
3;104,103,102;,
3;105,104,102;,
3;106,105,102;,
3;107,106,102;,
3;103,107,102;,
3;110,109,108;,
3;111,110,108;,
3;112,111,108;,
3;113,112,108;,
3;109,113,108;,
3;116,115,114;,
3;117,116,114;,
3;118,117,114;,
3;119,118,114;,
3;115,119,114;,
3;122,121,120;,
3;123,122,120;,
3;124,123,120;,
3;125,124,120;,
3;121,125,120;,
3;128,127,126;,
3;129,128,126;,
3;130,129,126;,
3;131,130,126;,
3;127,131,126;;
MeshMaterialList {
 1;
 80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
Material Material {
 0.752941;0.752941;0.752941;1.000000;;
8.000000;
 0.301176;0.301176;0.301176;;
 0.023529;0.023529;0.023529;;
 }
}

 MeshNormals {
 132;
0.934183;0.356794;0.000000;,
0.934183;0.356794;0.000000;,
0.934183;0.356794;0.000000;,
-0.577350;-0.577350;0.577350;,
-0.577350;-0.577350;0.577350;,
-0.577350;-0.577350;0.577350;,
0.000000;0.934183;-0.356794;,
0.000000;0.934183;-0.356794;,
0.000000;0.934183;-0.356794;,
0.577350;-0.577350;0.577350;,
0.577350;-0.577350;0.577350;,
0.577350;-0.577350;0.577350;,
-0.934183;0.356794;0.000000;,
-0.934183;0.356794;0.000000;,
-0.934183;0.356794;0.000000;,
0.577350;-0.577350;-0.577350;,
0.577350;-0.577350;-0.577350;,
0.577350;-0.577350;-0.577350;,
0.000000;0.934183;0.356794;,
0.000000;0.934183;0.356794;,
0.000000;0.934183;0.356794;,
-0.577350;-0.577350;-0.577350;,
-0.577350;-0.577350;-0.577350;,
-0.577350;-0.577350;-0.577350;,
0.356794;0.000000;-0.934183;,
0.356794;0.000000;-0.934183;,
0.356794;0.000000;-0.934183;,
0.356794;0.000000;0.934183;,
0.356794;0.000000;0.934183;,
0.356794;0.000000;0.934183;,
0.000000;-0.934183;0.356794;,
0.000000;-0.934183;0.356794;,
0.000000;-0.934183;0.356794;,
-0.577350;0.577350;-0.577350;,
-0.577350;0.577350;-0.577350;,
-0.577350;0.577350;-0.577350;,
-0.577350;0.577350;0.577350;,
-0.577350;0.577350;0.577350;,
-0.577350;0.577350;0.577350;,
0.934183;-0.356794;0.000000;,
0.934183;-0.356794;0.000000;,
0.934183;-0.356794;0.000000;,
0.577350;0.577350;-0.577350;,
0.577350;0.577350;-0.577350;,
0.577350;0.577350;-0.577350;,
-0.934183;-0.356794;0.000000;,
-0.934183;-0.356794;0.000000;,
-0.934183;-0.356794;0.000000;,
0.000000;-0.934183;-0.356794;,
0.000000;-0.934183;-0.356794;,
0.000000;-0.934183;-0.356794;,
0.577350;0.577350;0.577350;,
0.577350;0.577350;0.577350;,
0.577350;0.577350;0.577350;,
-0.356794;0.000000;0.934183;,
-0.356794;0.000000;0.934183;,
-0.356794;0.000000;0.934183;,
-0.356794;0.000000;-0.934183;,
-0.356794;0.000000;-0.934183;,
-0.356794;0.000000;-0.934183;,
0.000000;0.525687;0.850678;,
0.000000;0.525687;0.850678;,
0.000000;0.525687;0.850678;,
0.000000;0.525687;0.850678;,
0.000000;0.525687;0.850678;,
0.000000;0.525687;0.850678;,
-0.000000;0.525687;-0.850678;,
-0.000000;0.525687;-0.850678;,
0.000000;0.525687;-0.850678;,
0.000000;0.525687;-0.850678;,
0.000000;0.525687;-0.850678;,
-0.000000;0.525687;-0.850678;,
0.525687;-0.850678;0.000000;,
0.525687;-0.850678;0.000000;,
0.525687;-0.850678;0.000000;,
0.525687;-0.850678;-0.000000;,
0.525687;-0.850678;0.000000;,
0.525687;-0.850678;0.000000;,
-0.850678;0.000000;0.525687;,
-0.850678;0.000000;0.525687;,
-0.850678;-0.000000;0.525687;,
-0.850678;0.000000;0.525687;,
-0.850678;0.000000;0.525687;,
-0.850678;0.000000;0.525687;,
0.525687;0.850678;0.000000;,
0.525687;0.850678;0.000000;,
0.525687;0.850678;0.000000;,
0.525687;0.850678;0.000000;,
0.525687;0.850678;0.000000;,
0.525687;0.850678;0.000000;,
-0.000000;-0.525687;-0.850678;,
-0.000000;-0.525687;-0.850678;,
0.000000;-0.525687;-0.850678;,
0.000000;-0.525687;-0.850678;,
0.000000;-0.525687;-0.850678;,
-0.000000;-0.525687;-0.850678;,
0.000000;-0.525687;0.850678;,
0.000000;-0.525687;0.850678;,
0.000000;-0.525687;0.850678;,
0.000000;-0.525687;0.850678;,
0.000000;-0.525687;0.850678;,
0.000000;-0.525687;0.850678;,
-0.525687;0.850678;0.000000;,
-0.525687;0.850678;0.000000;,
-0.525687;0.850678;0.000000;,
-0.525687;0.850678;-0.000000;,
-0.525687;0.850678;0.000000;,
-0.525687;0.850678;0.000000;,
0.850678;0.000000;-0.525687;,
0.850678;0.000000;-0.525687;,
0.850678;0.000000;-0.525687;,
0.850678;0.000000;-0.525687;,
0.850678;-0.000000;-0.525687;,
0.850678;0.000000;-0.525687;,
-0.525687;-0.850678;0.000000;,
-0.525687;-0.850678;0.000000;,
-0.525687;-0.850678;-0.000000;,
-0.525687;-0.850678;0.000000;,
-0.525687;-0.850678;0.000000;,
-0.525687;-0.850678;0.000000;,
0.850678;-0.000000;0.525687;,
0.850678;-0.000000;0.525687;,
0.850678;0.000000;0.525687;,
0.850678;0.000000;0.525687;,
0.850678;0.000000;0.525687;,
0.850678;-0.000000;0.525687;,
-0.850678;0.000000;-0.525687;,
-0.850678;0.000000;-0.525687;,
-0.850678;0.000000;-0.525687;,
-0.850678;0.000000;-0.525687;,
-0.850678;0.000000;-0.525687;,
-0.850678;0.000000;-0.525687;;

 80;
3;2,1,0;,
3;5,4,3;,
3;8,7,6;,
3;11,10,9;,
3;14,13,12;,
3;17,16,15;,
3;20,19,18;,
3;23,22,21;,
3;26,25,24;,
3;29,28,27;,
3;32,31,30;,
3;35,34,33;,
3;38,37,36;,
3;41,40,39;,
3;44,43,42;,
3;47,46,45;,
3;50,49,48;,
3;53,52,51;,
3;56,55,54;,
3;59,58,57;,
3;62,61,60;,
3;63,62,60;,
3;64,63,60;,
3;65,64,60;,
3;61,65,60;,
3;68,67,66;,
3;69,68,66;,
3;70,69,66;,
3;71,70,66;,
3;67,71,66;,
3;74,73,72;,
3;75,74,72;,
3;76,75,72;,
3;77,76,72;,
3;73,77,72;,
3;80,79,78;,
3;81,80,78;,
3;82,81,78;,
3;83,82,78;,
3;79,83,78;,
3;86,85,84;,
3;87,86,84;,
3;88,87,84;,
3;89,88,84;,
3;85,89,84;,
3;92,91,90;,
3;93,92,90;,
3;94,93,90;,
3;95,94,90;,
3;91,95,90;,
3;98,97,96;,
3;99,98,96;,
3;100,99,96;,
3;101,100,96;,
3;97,101,96;,
3;104,103,102;,
3;105,104,102;,
3;106,105,102;,
3;107,106,102;,
3;103,107,102;,
3;110,109,108;,
3;111,110,108;,
3;112,111,108;,
3;113,112,108;,
3;109,113,108;,
3;116,115,114;,
3;117,116,114;,
3;118,117,114;,
3;119,118,114;,
3;115,119,114;,
3;122,121,120;,
3;123,122,120;,
3;124,123,120;,
3;125,124,120;,
3;121,125,120;,
3;128,127,126;,
3;129,128,126;,
3;130,129,126;,
3;131,130,126;,
3;127,131,126;;
 }
MeshTextureCoords {
 132;
0.000000;0.500000;,
-0.404500;1.154500;,
0.404500;1.154500;,
-0.154500;0.750000;,
-0.404500;1.154500;,
0.250000;1.404500;,
-0.404500;0.845500;,
0.000000;1.500000;,
0.404500;0.845500;,
0.250000;0.595500;,
-0.404500;0.845500;,
-0.154500;1.250000;,
0.404500;1.154500;,
-0.404500;1.154500;,
0.000000;0.500000;,
-0.154500;1.250000;,
-0.404500;0.845500;,
0.250000;0.595500;,
0.404500;1.154500;,
0.000000;0.500000;,
-0.404500;1.154500;,
0.250000;1.404500;,
-0.404500;1.154500;,
-0.154500;0.750000;,
0.000000;0.500000;,
0.404500;1.154500;,
-0.404500;1.154500;,
-0.404500;1.154500;,
0.404500;1.154500;,
0.000000;0.500000;,
0.000000;0.500000;,
0.404500;1.154500;,
-0.404500;1.154500;,
-0.154500;1.250000;,
-0.404500;0.845500;,
0.250000;0.595500;,
0.404500;0.845500;,
0.154500;1.250000;,
-0.250000;0.595500;,
-0.404500;0.845500;,
0.000000;1.500000;,
0.404500;0.845500;,
-0.250000;0.595500;,
0.404500;0.845500;,
0.154500;1.250000;,
-0.404500;0.845500;,
0.404500;0.845500;,
0.000000;1.500000;,
0.404500;0.845500;,
0.000000;1.500000;,
-0.404500;0.845500;,
0.154500;1.250000;,
0.404500;0.845500;,
-0.250000;0.595500;,
0.404500;0.845500;,
-0.404500;0.845500;,
0.000000;1.500000;,
0.000000;1.500000;,
-0.404500;0.845500;,
0.404500;0.845500;,
0.138200;1.000000;,
-0.154500;0.750000;,
0.250000;1.404500;,
0.250000;0.595500;,
-0.154500;1.250000;,
0.500000;1.000000;,
0.138200;1.000000;,
-0.154500;1.250000;,
0.250000;0.595500;,
0.250000;1.404500;,
-0.154500;0.750000;,
0.500000;1.000000;,
0.138200;1.000000;,
0.250000;1.404500;,
-0.154500;0.750000;,
0.500000;1.000000;,
-0.154500;1.250000;,
0.250000;0.595500;,
0.138200;1.000000;,
-0.154500;0.750000;,
0.500000;1.000000;,
-0.154500;1.250000;,
0.250000;0.595500;,
0.250000;1.404500;,
0.138200;1.000000;,
-0.154500;0.750000;,
0.250000;1.404500;,
0.250000;0.595500;,
-0.154500;1.250000;,
0.500000;1.000000;,
-0.138200;1.000000;,
-0.250000;1.404500;,
-0.250000;0.595500;,
0.154500;1.250000;,
-0.500000;1.000000;,
0.154500;0.750000;,
-0.138200;1.000000;,
-0.500000;1.000000;,
0.154500;1.250000;,
-0.250000;0.595500;,
-0.250000;1.404500;,
0.154500;0.750000;,
-0.138200;1.000000;,
-0.250000;1.404500;,
0.154500;0.750000;,
-0.500000;1.000000;,
0.154500;1.250000;,
-0.250000;0.595500;,
-0.138200;1.000000;,
-0.250000;0.595500;,
-0.250000;1.404500;,
0.154500;0.750000;,
-0.500000;1.000000;,
0.154500;1.250000;,
-0.138200;1.000000;,
-0.500000;1.000000;,
0.154500;0.750000;,
-0.250000;1.404500;,
-0.250000;0.595500;,
0.154500;1.250000;,
0.138200;1.000000;,
0.250000;1.404500;,
0.250000;0.595500;,
-0.154500;1.250000;,
0.500000;1.000000;,
-0.154500;0.750000;,
-0.138200;1.000000;,
0.154500;0.750000;,
-0.250000;1.404500;,
-0.250000;0.595500;,
0.154500;1.250000;,
-0.500000;1.000000;;
}
}
 }