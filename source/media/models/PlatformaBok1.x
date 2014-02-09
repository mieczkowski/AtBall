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
Frame PlatformaBok1 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh PlatformaBok11 {
 32;
1.000000;-1.000000;-0.432170;,
-1.000000;1.000000;-0.432170;,
-1.000000;-1.000000;-0.432170;,
1.000000;1.000000;-0.432170;,
1.000000;-0.089490;0.067830;,
-1.000000;1.000000;0.067830;,
1.000000;1.000000;0.067830;,
-1.000000;-0.089490;0.067830;,
1.000000;-0.673580;0.432170;,
-1.000000;-0.673580;0.432170;,
1.000000;-1.000000;0.432170;,
-1.000000;-1.000000;0.432170;,
1.000000;1.000000;0.067830;,
-1.000000;1.000000;-0.432170;,
1.000000;1.000000;-0.432170;,
-1.000000;1.000000;0.067830;,
1.000000;-0.089490;0.067830;,
1.000000;1.000000;-0.432170;,
1.000000;-1.000000;-0.432170;,
1.000000;1.000000;0.067830;,
-1.000000;-1.000000;0.432170;,
1.000000;-1.000000;-0.432170;,
-1.000000;-1.000000;-0.432170;,
1.000000;-1.000000;0.432170;,
-1.000000;1.000000;0.067830;,
-1.000000;-1.000000;-0.432170;,
-1.000000;1.000000;-0.432170;,
-1.000000;-0.089490;0.067830;,
1.000000;-0.673580;0.432170;,
1.000000;-1.000000;0.432170;,
-1.000000;-0.673580;0.432170;,
-1.000000;-1.000000;0.432170;;

 20;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;4,7,8;,
3;7,9,8;,
3;8,9,10;,
3;9,11,10;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;16,28,18;,
3;28,29,18;,
3;31,30,25;,
3;30,27,25;;
MeshMaterialList {
 1;
 20;
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
Material _9___Default {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 32;
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.529253;0.848464;,
0.000000;0.529253;0.848464;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.529253;0.848464;,
0.000000;0.000000;1.000000;,
0.000000;0.529253;0.848464;,
0.000000;0.000000;1.000000;;

 20;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;4,7,8;,
3;7,9,8;,
3;8,9,10;,
3;9,11,10;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;16,28,18;,
3;28,29,18;,
3;31,30,25;,
3;30,27,25;;
 }
MeshTextureCoords {
 32;
0.996580;0.495990;,
0.753870;0.253270;,
0.753870;0.495990;,
0.996580;0.253270;,
0.990570;0.114280;,
0.752400;0.244020;,
0.990570;0.244020;,
0.752400;0.114280;,
0.990570;0.044730;,
0.752400;0.044730;,
0.990570;0.005860;,
0.752400;0.005860;,
0.755140;0.410620;,
0.997860;0.349940;,
0.755140;0.349940;,
0.997860;0.410620;,
0.864010;0.385630;,
0.996230;0.324950;,
0.753520;0.324950;,
0.996230;0.385630;,
0.753520;0.424310;,
0.996230;0.319410;,
0.753520;0.319410;,
0.996230;0.424310;,
0.753520;0.385300;,
0.996230;0.324620;,
0.753520;0.324620;,
0.885730;0.385300;,
0.793130;0.429840;,
0.753520;0.429840;,
0.956620;0.429520;,
0.996230;0.429520;;
}
}
 }
