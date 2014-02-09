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
Frame BoxSkosDuzy {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh BoxSkosDuzy1 {
 22;
1.000000;-1.000000;2.013110;,
1.000000;1.000000;0.013110;,
1.000000;-1.000000;0.013110;,
1.000000;1.000000;2.013110;,
-1.000000;-1.000000;-0.013110;,
1.000000;-1.000000;0.013110;,
-1.000000;-1.000000;-2.013110;,
1.000000;-1.000000;2.013110;,
-1.000000;1.000000;-0.013110;,
-1.000000;-1.000000;-2.013110;,
-1.000000;1.000000;-2.013110;,
-1.000000;-1.000000;-0.013110;,
1.000000;1.000000;2.013110;,
-1.000000;1.000000;-2.013110;,
1.000000;1.000000;0.013110;,
-1.000000;1.000000;-0.013110;,
-1.000000;-1.000000;-2.013110;,
-1.000000;1.000000;-2.013110;,
-1.000000;1.000000;-0.013110;,
1.000000;-1.000000;2.013110;,
-1.000000;-1.000000;-0.013110;,
1.000000;1.000000;2.013110;;

 12;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;2,16,1;,
3;16,17,1;,
3;20,19,18;,
3;19,21,18;;
MeshMaterialList {
 1;
 12;
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
 22;
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;;

 12;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;2,16,1;,
3;16,17,1;,
3;20,19,18;,
3;19,21,18;;
 }
MeshTextureCoords {
 22;
0.987290;0.246120;,
0.754590;0.013420;,
0.754590;0.246120;,
0.987290;0.013420;,
0.947210;0.392520;,
0.806460;0.353830;,
0.987750;0.252300;,
0.765930;0.494050;,
0.992410;0.488260;,
0.759710;0.255560;,
0.759710;0.488260;,
0.992410;0.255560;,
0.762820;0.492350;,
0.993520;0.259060;,
0.808570;0.353740;,
0.947780;0.397670;,
0.518850;0.246120;,
0.518850;0.013420;,
0.653180;0.246290;,
0.995370;0.005910;,
0.653180;0.005910;,
0.995370;0.246290;;
}
}
 }
