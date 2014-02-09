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
Frame platforma_narozna {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh platforma_narozna1 {
 55;
10.000000;10.000000;-4.321700;,
-0.928200;10.000000;0.678300;,
-10.033300;10.000000;-4.321700;,
10.000000;10.000000;0.678300;,
-10.033300;-10.000000;-4.321700;,
-10.033300;10.000000;4.321700;,
-10.000000;-10.000000;4.321700;,
-10.033300;10.000000;-4.321700;,
-0.928200;10.000000;0.678300;,
-6.769100;-6.736000;4.321700;,
-6.769100;10.000000;4.321700;,
-0.447500;-0.447400;0.678300;,
-6.769100;-6.736000;4.321700;,
-10.033300;10.000000;4.321700;,
-6.769100;10.000000;4.321700;,
-10.000000;-10.000000;4.321700;,
-10.033300;-10.000000;-4.321700;,
10.000000;10.000000;-4.321700;,
-10.033300;10.000000;-4.321700;,
10.033300;-10.000000;-4.321700;,
10.000000;10.000000;0.678300;,
10.033300;-10.000000;-4.321700;,
10.033300;-0.894900;0.678300;,
10.000000;10.000000;-4.321700;,
10.033300;-10.000000;-4.321700;,
-10.000000;-10.000000;4.321700;,
10.033300;-10.000000;4.321700;,
-9.966700;-10.000000;-4.321700;,
10.033300;-6.735800;4.321700;,
-0.447500;-0.447400;0.678300;,
10.033300;-0.894900;0.678300;,
-6.769100;-6.736000;4.321700;,
10.033300;-6.735800;4.321700;,
10.033300;-10.000000;4.321700;,
-0.928200;10.000000;0.678300;,
-6.769100;10.000000;4.321700;,
-10.033300;10.000000;-4.321700;,
-10.033300;10.000000;4.321700;,
-10.033300;-10.000000;-4.321700;,
-10.033300;10.000000;-4.321700;,
-0.447500;-0.447400;0.678300;,
-0.928200;10.000000;0.678300;,
10.000000;10.000000;0.678300;,
10.033300;-10.000000;-4.321700;,
-9.966700;-10.000000;-4.321700;,
10.033300;-10.000000;-4.321700;,
-10.033300;-10.000000;-4.321700;,
10.033300;-6.735800;4.321700;,
10.033300;-0.894900;0.678300;,
10.033300;-10.000000;-4.321700;,
10.033300;-10.000000;4.321700;,
10.033300;-0.894900;0.678300;,
10.033300;-10.000000;-4.321700;,
-10.033300;-10.000000;-4.321700;,
10.000000;10.000000;-4.321700;;

 29;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;12,15,32;,
3;15,33,32;,
3;36,35,34;,
3;36,37,35;,
3;38,39,38;,
3;42,41,40;,
3;38,38,43;,
3;46,45,44;,
3;49,48,47;,
3;49,47,50;,
3;42,40,51;,
3;53,52,52;,
3;52,54,52;;
MeshMaterialList {
 1;
 29;
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
 0.588000;0.588000;0.588000;1.000000;;
10.000000;
 0.000000;0.000000;0.000000;;
 0.117600;0.117600;0.117600;;
 }
}

 MeshNormals {
 55;
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
-0.999998;-0.000800;0.001900;,
-0.999998;-0.000800;0.001900;,
-0.999998;-0.000800;0.001900;,
-0.999998;-0.000800;0.001900;,
0.510513;0.009000;0.859823;,
0.510513;0.009000;0.859823;,
0.510513;0.009000;0.859823;,
0.510513;0.009000;0.859823;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.999996;0.002200;-0.002000;,
0.999996;0.002200;-0.002000;,
0.999996;0.002200;-0.002000;,
0.999996;0.002200;-0.002000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.008400;0.511710;0.859117;,
0.008400;0.511710;0.859117;,
0.008400;0.511710;0.859117;,
0.008400;0.511710;0.859117;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;0.000000;1.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;;

 29;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;12,15,32;,
3;15,33,32;,
3;36,35,34;,
3;36,37,35;,
3;38,39,38;,
3;42,41,40;,
3;38,38,43;,
3;46,45,44;,
3;49,48,47;,
3;49,47,50;,
3;42,40,51;,
3;53,52,52;,
3;52,54,52;;
 }
MeshTextureCoords {
 55;
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.000000;1.000000;,
0.866300;0.380800;,
0.800900;0.421600;,
0.764300;0.324800;,
0.764300;0.421600;,
0.753300;0.351700;,
0.753300;0.351700;,
0.877000;0.120300;,
0.882900;0.247800;,
0.749500;0.247800;,
0.978000;0.351700;,
-0.006000;0.687700;,
0.457200;0.687700;,
-0.007500;0.687700;,
0.948600;0.422100;,
0.883200;0.381300;,
0.985100;0.325300;,
0.985100;0.422100;,
0.749000;0.114800;,
0.976400;0.367700;,
0.751700;0.367700;,
0.976100;0.367700;;
}
}
 }