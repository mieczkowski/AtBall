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
Frame BoxWciecieStart {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh BoxWciecieStart1 {
 43;
1.000000;-0.728750;1.000000;,
-0.300340;-0.364370;0.893810;,
1.000000;-0.364370;0.827600;,
-0.585680;-0.728750;1.000000;,
1.000000;1.000000;-1.000000;,
-1.000000;1.000000;1.000000;,
-1.000000;1.000000;-1.000000;,
1.000000;1.000000;1.000000;,
1.000000;0.728750;1.000000;,
-1.000000;1.000000;1.000000;,
1.000000;1.000000;1.000000;,
-0.585680;0.728750;1.000000;,
1.000000;0.000000;0.780750;,
-0.300340;0.364380;0.893810;,
1.000000;0.364380;0.827600;,
-0.234070;0.000000;0.874220;,
-1.000000;1.000000;-1.000000;,
-1.000000;-1.000000;1.000000;,
-1.000000;-1.000000;-1.000000;,
-0.234070;0.000000;0.874220;,
-0.300340;-0.364370;0.893810;,
1.000000;-0.364370;0.827600;,
1.000000;1.000000;-1.000000;,
1.000000;-1.000000;-1.000000;,
1.000000;0.000000;0.780750;,
-0.585680;0.728750;1.000000;,
-0.300340;0.364380;0.893810;,
-1.000000;-1.000000;-1.000000;,
1.000000;-1.000000;1.000000;,
1.000000;-1.000000;-1.000000;,
-1.000000;-1.000000;1.000000;,
1.000000;-1.000000;1.000000;,
-0.585680;-0.728750;1.000000;,
-1.000000;1.000000;-1.000000;,
1.000000;1.000000;-1.000000;,
-0.585680;-0.728750;1.000000;,
-1.000000;-1.000000;1.000000;,
-0.300340;-0.364370;0.893810;,
1.000000;-0.728750;1.000000;,
1.000000;0.728750;1.000000;,
1.000000;-1.000000;1.000000;,
1.000000;0.000000;0.780750;,
1.000000;0.364380;0.827600;;

 32;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,5,16;,
3;12,19,2;,
3;19,20,2;,
3;23,22,21;,
3;22,24,21;,
3;8,25,14;,
3;25,26,14;,
3;29,28,27;,
3;28,17,27;,
3;31,0,30;,
3;0,32,30;,
3;34,23,33;,
3;23,27,33;,
3;25,9,35;,
3;9,36,35;,
3;25,35,19;,
3;35,37,19;,
3;23,21,38;,
3;22,7,39;,
3;38,40,23;,
3;22,42,41;,
3;22,39,42;,
3;25,19,13;;
MeshMaterialList {
 1;
 32;
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
Material _9___Default {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 43;
0.000000;0.427680;0.903930;,
0.181240;0.100680;0.978272;,
0.007370;0.401262;0.915934;,
0.036260;0.294081;0.955092;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.074910;-0.127170;0.989048;,
0.172700;-0.112750;0.978500;,
0.070560;-0.112170;0.991181;,
0.182440;-0.007470;0.983189;,
0.000000;1.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.182440;-0.007470;0.983189;,
0.181240;0.100680;0.978272;,
0.007370;0.401262;0.915934;,
0.000000;1.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.074910;-0.127170;0.989048;,
0.000000;0.000000;1.000000;,
0.172700;-0.112750;0.978500;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.036260;0.294081;0.955092;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.036260;0.294081;0.955092;,
-1.000000;0.000000;0.000000;,
0.181240;0.100680;0.978272;,
0.000000;0.427680;0.903930;,
0.000000;0.000000;1.000000;,
1.000000;0.000000;0.000000;,
0.074910;-0.127170;0.989048;,
0.070560;-0.112170;0.991181;;

 32;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,5,16;,
3;12,19,2;,
3;19,20,2;,
3;23,22,21;,
3;22,24,21;,
3;8,25,14;,
3;25,26,14;,
3;29,28,27;,
3;28,17,27;,
3;31,0,30;,
3;0,32,30;,
3;34,23,33;,
3;23,27,33;,
3;25,9,35;,
3;9,36,35;,
3;25,35,19;,
3;35,37,19;,
3;23,21,38;,
3;22,7,39;,
3;38,40,23;,
3;22,42,41;,
3;22,39,42;,
3;25,19,13;;
 }
MeshTextureCoords {
 43;
0.753260;0.037620;,
0.910930;0.081800;,
0.753260;0.081800;,
0.910930;0.081800;,
0.997600;0.497490;,
0.752490;0.254810;,
0.752490;0.497490;,
0.752490;0.254810;,
0.753260;0.214340;,
0.996880;0.248910;,
0.753260;0.248910;,
0.996880;0.248910;,
0.753260;0.125980;,
0.910930;0.170160;,
0.753260;0.170160;,
0.910930;0.170160;,
0.997600;0.497490;,
0.752490;0.254810;,
0.752490;0.497490;,
0.902890;0.125980;,
0.902890;0.125980;,
0.919700;0.275730;,
0.752490;0.497490;,
0.997600;0.497490;,
0.752490;0.497490;,
0.945530;0.214340;,
0.945530;0.214340;,
0.997600;0.497490;,
0.752490;0.254810;,
0.752490;0.497490;,
0.996890;0.001930;,
0.753260;0.001930;,
0.753260;0.037620;,
0.752490;0.254810;,
0.997600;0.254810;,
0.945530;0.037620;,
0.996880;0.248910;,
0.945530;0.037620;,
0.964360;0.254810;,
0.785740;0.254810;,
0.997600;0.254810;,
0.875050;0.281410;,
0.830390;0.275730;;
}
}
 }