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
Frame podjazd_prosty_2 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
-28.775822,-19.314899,-1.000000,1.000000;;
 }
Mesh podjazd_prosty_21 {
 18;
30.352184;20.314899;0.000000;,
27.199459;18.314899;0.000000;,
30.352184;18.314899;0.000000;,
27.199459;20.314899;0.000000;,
30.352184;20.314899;0.000000;,
30.352184;18.314899;2.000000;,
30.352184;20.314899;2.000000;,
30.352184;18.314899;0.000000;,
30.352184;20.314899;2.000000;,
27.199459;18.314899;0.000000;,
27.199459;20.314899;0.000000;,
30.352184;18.314899;2.000000;,
30.352184;18.314899;2.000000;,
30.352184;18.314899;0.000000;,
27.199459;18.314899;0.000000;,
27.199459;20.314899;0.000000;,
30.352184;20.314899;0.000000;,
30.352184;20.314899;2.000000;;

 8;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;17,16,15;;
MeshMaterialList {
 1;
 8;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
Material _9_-_Default {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 18;
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;-0.000000;-1.000000;,
1.000000;0.000000;0.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
0.000000;-0.000000;-1.000000;,
1.000000;0.000000;0.000000;;

 8;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;17,16,15;;
 }
MeshTextureCoords {
 18;
0.968353;0.255796;,
0.814734;0.497954;,
0.814735;0.255796;,
0.814734;0.497954;,
0.810254;0.495963;,
0.963873;0.342345;,
0.963872;0.495963;,
0.963873;0.342345;,
0.990439;0.245877;,
0.541771;0.005533;,
0.541770;0.245875;,
0.541771;0.005533;,
0.809948;0.497954;,
0.963566;0.497955;,
0.963567;0.255796;,
0.963873;0.249325;,
0.963872;0.491483;,
0.810254;0.491482;;
}
}
 }
