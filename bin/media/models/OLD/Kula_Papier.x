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
Frame kula_papier {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
-13.980545,-3.075096,-1.025764,1.000000;;
 }
Mesh kula_papier1 {
 164;
13.699600;3.075416;1.797887;,
13.484012;3.255479;1.655673;,
13.659151;3.192074;1.965457;,
13.337757;3.075096;1.791809;,
13.575433;3.413825;1.655673;,
13.764904;3.254838;1.797887;,
13.715497;3.531353;1.655673;,
13.809535;3.371294;1.965457;,
13.868926;3.708118;1.791809;,
13.930261;3.350307;1.797887;,
14.070152;3.593888;1.655673;,
14.039936;3.411920;1.965457;,
14.301939;3.631767;1.791809;,
14.118298;3.317151;1.797887;,
14.382031;3.413825;1.655673;,
14.242548;3.294943;1.965457;,
14.584568;3.294943;1.791809;,
14.241030;3.170885;1.797887;,
14.505202;3.075416;1.655673;,
14.322565;3.075096;1.965457;,
14.322565;3.075096;1.965457;,
14.584568;2.855250;1.791809;,
14.241030;2.979948;1.797887;,
14.505202;3.075416;1.655673;,
14.382031;2.737008;1.655673;,
14.242548;2.855250;1.965457;,
14.301939;2.518426;1.791809;,
14.118298;2.833681;1.797887;,
14.070153;2.556944;1.655673;,
14.039936;2.738272;1.965457;,
13.868927;2.442074;1.791809;,
13.930262;2.800525;1.797887;,
13.715497;2.619479;1.655673;,
13.809535;2.778898;1.965457;,
13.488142;2.661920;1.791809;,
13.764905;2.895993;1.797887;,
13.484012;2.895352;1.655673;,
13.659151;2.958118;1.965457;,
13.337757;3.075096;1.791809;,
13.699600;3.075416;1.797887;,
13.166747;3.371294;1.525764;,
13.268490;3.075416;1.437242;,
13.434655;3.531951;1.437242;,
13.547532;3.825096;1.525764;,
13.855399;3.774868;1.437242;,
14.130929;3.927965;1.525764;,
14.333853;3.690504;1.437242;,
14.643959;3.631767;1.525764;,
14.646141;3.318333;1.437242;,
14.846571;3.075097;1.525764;,
14.646141;2.832500;1.437242;,
14.846571;3.075097;1.525764;,
14.643959;2.518426;1.525764;,
14.333853;2.460329;1.437242;,
14.102064;2.375965;1.437242;,
13.855400;2.375964;1.437242;,
13.547533;2.325096;1.525764;,
13.434655;2.618881;1.437242;,
13.166748;2.778897;1.525764;,
13.268490;3.075416;1.437242;,
13.219378;3.351799;1.168984;,
12.995737;3.075096;1.199412;,
13.226138;3.708118;1.199412;,
13.574688;3.775241;1.168984;,
13.809535;4.044942;1.199412;,
14.119055;3.871228;1.168984;,
14.472949;3.927965;1.199412;,
14.597763;3.594846;1.168984;,
14.905962;3.411921;1.199412;,
14.786820;3.075417;1.168984;,
14.905962;2.738273;1.199412;,
14.786820;3.075417;1.168984;,
14.597764;2.555987;1.168984;,
14.472950;2.222228;1.199412;,
14.119056;2.279604;1.168984;,
13.809536;2.105250;1.199412;,
13.574688;2.375590;1.168984;,
13.226139;2.442073;1.199412;,
13.219378;2.799033;1.168985;,
12.995737;3.075096;1.199412;,
13.219378;3.351799;0.883408;,
13.170643;3.075416;0.883408;,
13.359700;3.594845;0.883408;,
13.488141;3.927965;0.852116;,
13.838408;3.871228;0.883408;,
14.119055;3.871228;0.883408;,
14.382776;3.775241;0.883408;,
14.734951;3.708119;0.852116;,
14.738087;3.351799;0.883408;,
14.965353;3.075097;0.852116;,
14.738087;2.799034;0.883408;,
14.965353;3.075097;0.852116;,
14.734952;2.442074;0.852116;,
14.382776;2.375591;0.883408;,
14.151556;2.105250;0.852116;,
13.838409;2.279604;0.883408;,
13.488142;2.222227;0.852116;,
13.359700;2.555986;0.883408;,
13.265139;2.857103;0.822519;,
13.170643;3.075416;0.883408;,
13.311323;3.318333;0.615150;,
13.114520;3.075096;0.525764;,
13.317131;3.631766;0.525764;,
13.623611;3.690503;0.615150;,
13.830161;3.927965;0.525764;,
14.102064;3.774868;0.615150;,
14.413557;3.825096;0.525764;,
14.522808;3.531951;0.615150;,
14.794343;3.371295;0.525764;,
14.688973;3.075417;0.615150;,
14.794343;2.778898;0.525764;,
14.688973;3.075417;0.615150;,
14.522809;2.618882;0.615150;,
14.413558;2.325097;0.525764;,
14.102064;2.375965;0.615150;,
13.830162;2.222228;0.525764;,
13.623611;2.460328;0.615150;,
13.434655;2.618881;0.615150;,
13.311323;2.832498;0.615150;,
13.114520;3.075096;0.525764;,
13.376522;3.294942;0.259720;,
13.452262;3.075416;0.396719;,
13.575432;3.413825;0.396719;,
13.659151;3.631767;0.259720;,
13.887311;3.593888;0.396719;,
14.092164;3.708118;0.259720;,
14.241967;3.531353;0.396719;,
14.472949;3.488272;0.259720;,
14.473452;3.255480;0.396719;,
14.623333;3.075097;0.259720;,
14.473452;2.895353;0.396719;,
14.623333;3.075097;0.259720;,
14.472949;2.661921;0.259720;,
14.241967;2.619480;0.396719;,
14.092164;2.442074;0.259720;,
13.887312;2.556944;0.396719;,
13.659152;2.518425;0.259720;,
13.575433;2.737007;0.396719;,
13.376522;2.855249;0.259720;,
13.452262;3.075416;0.396719;,
13.716434;3.170885;0.254505;,
13.638525;3.075096;0.086071;,
13.718542;3.294943;0.086071;,
13.839166;3.317151;0.254505;,
13.921154;3.411920;0.086071;,
14.027203;3.350307;0.254505;,
14.151555;3.371294;0.086071;,
14.192559;3.254839;0.254505;,
14.301939;3.192074;0.086071;,
14.257864;3.075416;0.254505;,
14.301939;2.958118;0.086071;,
14.257864;3.075416;0.254505;,
14.192559;2.895994;0.254505;,
14.151555;2.778898;0.086071;,
14.027203;2.800525;0.254505;,
13.921154;2.738272;0.086071;,
13.839166;2.833681;0.254505;,
13.718543;2.855250;0.086071;,
13.716434;2.979947;0.254505;,
13.638525;3.075096;0.086071;,
13.980545;3.075096;2.025764;,
13.980545;3.075096;2.025764;,
13.980545;3.075096;0.025764;,
13.980545;3.075096;0.025764;;

 288;
3;2,1,0;,
3;1,3,0;,
3;5,4,2;,
3;4,1,2;,
3;7,6,5;,
3;6,4,5;,
3;9,8,7;,
3;8,6,7;,
3;11,10,9;,
3;10,8,9;,
3;13,12,11;,
3;12,10,11;,
3;15,14,13;,
3;14,12,13;,
3;17,16,15;,
3;16,14,15;,
3;19,18,17;,
3;18,16,17;,
3;22,21,20;,
3;21,23,20;,
3;25,24,22;,
3;24,21,22;,
3;27,26,25;,
3;26,24,25;,
3;29,28,27;,
3;28,26,27;,
3;31,30,29;,
3;30,28,29;,
3;33,32,31;,
3;32,30,31;,
3;35,34,33;,
3;34,32,33;,
3;37,36,35;,
3;36,34,35;,
3;39,38,37;,
3;38,36,37;,
3;1,40,3;,
3;40,41,3;,
3;4,42,1;,
3;42,40,1;,
3;6,43,4;,
3;43,42,4;,
3;8,44,6;,
3;44,43,6;,
3;10,45,8;,
3;45,44,8;,
3;12,46,10;,
3;46,45,10;,
3;14,47,12;,
3;47,46,12;,
3;16,48,14;,
3;48,47,14;,
3;18,49,16;,
3;49,48,16;,
3;21,50,23;,
3;50,51,23;,
3;24,52,21;,
3;52,50,21;,
3;26,53,24;,
3;53,52,24;,
3;28,54,26;,
3;54,53,26;,
3;30,55,28;,
3;55,54,28;,
3;32,56,30;,
3;56,55,30;,
3;34,57,32;,
3;57,56,32;,
3;36,58,34;,
3;58,57,34;,
3;38,59,36;,
3;59,58,36;,
3;40,60,41;,
3;60,61,41;,
3;42,62,40;,
3;62,60,40;,
3;43,63,42;,
3;63,62,42;,
3;44,64,43;,
3;64,63,43;,
3;45,65,44;,
3;65,64,44;,
3;46,66,45;,
3;66,65,45;,
3;47,67,46;,
3;67,66,46;,
3;48,68,47;,
3;68,67,47;,
3;49,69,48;,
3;69,68,48;,
3;50,70,51;,
3;70,71,51;,
3;52,72,50;,
3;72,70,50;,
3;53,73,52;,
3;73,72,52;,
3;54,74,53;,
3;74,73,53;,
3;55,75,54;,
3;75,74,54;,
3;56,76,55;,
3;76,75,55;,
3;57,77,56;,
3;77,76,56;,
3;58,78,57;,
3;78,77,57;,
3;59,79,58;,
3;79,78,58;,
3;60,80,61;,
3;80,81,61;,
3;62,82,60;,
3;82,80,60;,
3;63,83,62;,
3;83,82,62;,
3;64,84,63;,
3;84,83,63;,
3;65,85,64;,
3;85,84,64;,
3;66,86,65;,
3;86,85,65;,
3;67,87,66;,
3;87,86,66;,
3;68,88,67;,
3;88,87,67;,
3;69,89,68;,
3;89,88,68;,
3;70,90,71;,
3;90,91,71;,
3;72,92,70;,
3;92,90,70;,
3;73,93,72;,
3;93,92,72;,
3;74,94,73;,
3;94,93,73;,
3;75,95,74;,
3;95,94,74;,
3;76,96,75;,
3;96,95,75;,
3;77,97,76;,
3;97,96,76;,
3;78,98,77;,
3;98,97,77;,
3;79,99,78;,
3;99,98,78;,
3;80,100,81;,
3;100,101,81;,
3;82,102,80;,
3;102,100,80;,
3;83,103,82;,
3;103,102,82;,
3;84,104,83;,
3;104,103,83;,
3;85,105,84;,
3;105,104,84;,
3;86,106,85;,
3;106,105,85;,
3;87,107,86;,
3;107,106,86;,
3;88,108,87;,
3;108,107,87;,
3;89,109,88;,
3;109,108,88;,
3;90,110,91;,
3;110,111,91;,
3;92,112,90;,
3;112,110,90;,
3;93,113,92;,
3;113,112,92;,
3;94,114,93;,
3;114,113,93;,
3;95,115,94;,
3;115,114,94;,
3;96,116,95;,
3;116,115,95;,
3;97,117,96;,
3;117,116,96;,
3;98,118,97;,
3;118,117,97;,
3;99,119,98;,
3;119,118,98;,
3;100,120,101;,
3;120,121,101;,
3;102,122,100;,
3;122,120,100;,
3;103,123,102;,
3;123,122,102;,
3;104,124,103;,
3;124,123,103;,
3;105,125,104;,
3;125,124,104;,
3;106,126,105;,
3;126,125,105;,
3;107,127,106;,
3;127,126,106;,
3;108,128,107;,
3;128,127,107;,
3;109,129,108;,
3;129,128,108;,
3;110,130,111;,
3;130,131,111;,
3;112,132,110;,
3;132,130,110;,
3;113,133,112;,
3;133,132,112;,
3;114,134,113;,
3;134,133,113;,
3;115,135,114;,
3;135,134,114;,
3;116,136,115;,
3;136,135,115;,
3;117,137,116;,
3;137,136,116;,
3;118,138,117;,
3;138,137,117;,
3;119,139,118;,
3;139,138,118;,
3;120,140,121;,
3;140,141,121;,
3;122,142,120;,
3;142,140,120;,
3;123,143,122;,
3;143,142,122;,
3;124,144,123;,
3;144,143,123;,
3;125,145,124;,
3;145,144,124;,
3;126,146,125;,
3;146,145,125;,
3;127,147,126;,
3;147,146,126;,
3;128,148,127;,
3;148,147,127;,
3;129,149,128;,
3;149,148,128;,
3;130,150,131;,
3;150,151,131;,
3;132,152,130;,
3;152,150,130;,
3;133,153,132;,
3;153,152,132;,
3;134,154,133;,
3;154,153,133;,
3;135,155,134;,
3;155,154,134;,
3;136,156,135;,
3;156,155,135;,
3;137,157,136;,
3;157,156,136;,
3;138,158,137;,
3;158,157,137;,
3;139,159,138;,
3;159,158,138;,
3;2,0,160;,
3;5,2,160;,
3;7,5,160;,
3;9,7,160;,
3;11,9,160;,
3;13,11,160;,
3;15,13,160;,
3;17,15,160;,
3;19,17,160;,
3;22,20,161;,
3;25,22,161;,
3;27,25,161;,
3;29,27,161;,
3;31,29,161;,
3;33,31,161;,
3;35,33,161;,
3;37,35,161;,
3;39,37,161;,
3;141,140,162;,
3;140,142,162;,
3;142,143,162;,
3;143,144,162;,
3;144,145,162;,
3;145,146,162;,
3;146,147,162;,
3;147,148,162;,
3;148,149,162;,
3;151,150,163;,
3;150,152,163;,
3;152,153,163;,
3;153,154,163;,
3;154,155,163;,
3;155,156,163;,
3;156,157,163;,
3;157,158,163;,
3;158,159,163;;
MeshMaterialList {
 1;
 288;
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
Material _1_-_Defaultfdgfgh {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 164;
-0.549352;0.186552;0.814501;,
-0.409304;0.502693;0.761426;,
-0.441632;0.104038;0.891144;,
-0.643397;-0.067060;0.762590;,
-0.522281;0.412100;0.746590;,
-0.427748;0.546690;0.719835;,
-0.527618;0.441543;0.725713;,
-0.276653;0.226515;0.933892;,
-0.174373;0.621717;0.763585;,
0.095224;0.573554;0.813614;,
0.200842;0.625524;0.753911;,
-0.065757;0.351593;0.933841;,
0.265345;0.589646;0.762830;,
0.441503;0.379835;0.812896;,
0.555500;0.352082;0.753298;,
0.174673;0.314065;0.933195;,
0.582479;0.284112;0.761577;,
0.582942;0.011391;0.812434;,
0.653375;-0.084714;0.752280;,
0.336644;0.132644;0.932243;,
0.336644;0.132644;0.932243;,
0.630831;-0.154385;0.760406;,
0.457080;-0.362006;0.812422;,
0.653375;-0.084714;0.752280;,
0.448549;-0.484050;0.751332;,
0.346281;-0.111993;0.931422;,
0.345016;-0.627578;0.697932;,
0.120875;-0.569774;0.812863;,
0.110458;-0.780084;0.615848;,
0.195283;-0.308000;0.931129;,
-0.041005;-0.648372;0.760219;,
-0.272783;-0.513509;0.813571;,
-0.399097;-0.525751;0.751204;,
-0.048955;-0.360403;0.931511;,
-0.448749;-0.468031;0.761296;,
-0.539287;-0.214962;0.814224;,
-0.643249;-0.143546;0.752081;,
-0.269514;-0.240882;0.932383;,
-0.643397;-0.067060;0.762590;,
-0.549352;0.186552;0.814501;,
-0.831452;0.267758;0.486819;,
-0.863552;0.045572;0.502196;,
-0.525484;0.568002;0.633436;,
-0.498097;0.663838;0.557869;,
-0.103127;0.857539;0.503977;,
0.120561;0.864905;0.487241;,
0.471867;0.723649;0.503661;,
0.647816;0.586501;0.486159;,
0.826828;0.252507;0.502588;,
0.873947;0.035004;0.484760;,
0.796998;-0.336943;0.501262;,
0.873947;0.035004;0.484760;,
0.693560;-0.533866;0.483696;,
0.189692;-0.818903;0.541678;,
0.162764;-0.859216;0.485031;,
0.039530;-0.889015;0.456168;,
-0.405252;-0.775460;0.484183;,
-0.690491;-0.521818;0.500928;,
-0.808925;-0.331546;0.485507;,
-0.863552;0.045572;0.502196;,
-0.953664;0.300621;-0.012327;,
-0.993629;0.063037;0.093426;,
-0.761089;0.626618;0.167610;,
-0.478830;0.859783;0.177469;,
-0.106823;0.989812;0.094132;,
0.131269;0.991261;-0.013010;,
0.485488;0.857967;0.167909;,
0.763424;0.621107;0.177230;,
0.923100;0.346467;0.166872;,
0.984294;-0.013965;0.175982;,
0.930629;-0.326366;0.165575;,
0.984294;-0.013965;0.175982;,
0.745851;-0.642806;0.174660;,
0.504385;-0.847641;0.164622;,
0.095488;-0.932560;0.348158;,
-0.084431;-0.967251;0.239368;,
-0.503280;-0.846417;0.174036;,
-0.810205;-0.580843;0.078669;,
-0.913457;-0.400188;-0.073797;,
-0.993629;0.063037;0.093426;,
-0.925071;0.340578;-0.168080;,
-0.969821;-0.094986;-0.224555;,
-0.858762;0.458792;-0.228117;,
-0.482918;0.859735;-0.166272;,
0.012100;0.992379;-0.122627;,
0.174780;0.970126;-0.168248;,
0.301192;0.926002;-0.227604;,
0.763191;0.624560;-0.165725;,
0.920284;0.349796;-0.175272;,
0.985953;-0.010751;-0.166676;,
0.929920;-0.322588;-0.176595;,
0.985953;-0.010751;-0.166676;,
0.749348;-0.640518;-0.167973;,
0.505714;-0.844171;-0.177842;,
0.163583;-0.971944;-0.169011;,
-0.154724;-0.971713;-0.178424;,
-0.551044;-0.798212;-0.243328;,
-0.833979;-0.473054;-0.284074;,
-0.915456;-0.378467;-0.136762;,
-0.969821;-0.094986;-0.224555;,
-0.883480;0.336198;-0.326243;,
-0.917902;-0.077506;-0.389163;,
-0.724578;0.548784;-0.416920;,
-0.471073;0.725771;-0.501346;,
-0.116268;0.866734;-0.485029;,
0.179821;0.928906;-0.323725;,
0.416890;0.809157;-0.414087;,
0.633907;0.589433;-0.500730;,
0.833655;0.265027;-0.484541;,
0.863880;0.045011;-0.501682;,
0.809118;-0.330934;-0.485603;,
0.863880;0.045011;-0.501682;,
0.691004;-0.519130;-0.503009;,
0.408593;-0.771934;-0.487001;,
0.196821;-0.840931;-0.504081;,
-0.181696;-0.853675;-0.488083;,
-0.599302;-0.655626;-0.459338;,
-0.677190;-0.553615;-0.484690;,
-0.836902;-0.455182;-0.303982;,
-0.917902;-0.077506;-0.389163;,
-0.581351;0.282408;-0.763070;,
-0.651781;-0.088676;-0.753205;,
-0.555813;0.353999;-0.752168;,
-0.261803;0.592580;-0.761780;,
-0.196133;0.630152;-0.751292;,
0.182621;0.622880;-0.760704;,
0.255948;0.608687;-0.750993;,
0.540723;0.359837;-0.760353;,
0.586510;0.302285;-0.751419;,
0.645077;-0.070164;-0.760890;,
0.643067;-0.142870;-0.752365;,
0.645077;-0.070164;-0.760890;,
0.450117;-0.465471;-0.762057;,
0.402312;-0.520155;-0.753382;,
0.048090;-0.644243;-0.763308;,
-0.024208;-0.656434;-0.753995;,
-0.375792;-0.524395;-0.764062;,
-0.579734;-0.530683;-0.618291;,
-0.660703;-0.264811;-0.702387;,
-0.651781;-0.088676;-0.753205;,
-0.580703;0.012098;-0.814026;,
-0.334553;0.129550;-0.933430;,
-0.170733;0.318285;-0.932494;,
-0.434085;0.386499;-0.813750;,
0.077201;0.355125;-0.931625;,
-0.081315;0.576422;-0.813096;,
0.288613;0.222455;-0.931244;,
0.308370;0.494909;-0.812388;,
0.363408;-0.013188;-0.931537;,
0.553800;0.184530;-0.811945;,
0.270754;-0.239599;-0.932354;,
0.553800;0.184530;-0.811945;,
0.544686;-0.209870;-0.811956;,
0.056663;-0.354591;-0.933303;,
0.285705;-0.508281;-0.812418;,
-0.181919;-0.307652;-0.933946;,
-0.106342;-0.572276;-0.813137;,
-0.337187;-0.118125;-0.933997;,
-0.449974;-0.367812;-0.813780;,
-0.334553;0.129550;-0.933430;,
0.001272;-0.000224;0.999999;,
0.001272;-0.000224;0.999999;,
0.001273;-0.000225;-0.999999;,
0.001273;-0.000225;-0.999999;;

 288;
3;2,1,0;,
3;1,3,0;,
3;5,4,2;,
3;4,1,2;,
3;7,6,5;,
3;6,4,5;,
3;9,8,7;,
3;8,6,7;,
3;11,10,9;,
3;10,8,9;,
3;13,12,11;,
3;12,10,11;,
3;15,14,13;,
3;14,12,13;,
3;17,16,15;,
3;16,14,15;,
3;19,18,17;,
3;18,16,17;,
3;22,21,20;,
3;21,23,20;,
3;25,24,22;,
3;24,21,22;,
3;27,26,25;,
3;26,24,25;,
3;29,28,27;,
3;28,26,27;,
3;31,30,29;,
3;30,28,29;,
3;33,32,31;,
3;32,30,31;,
3;35,34,33;,
3;34,32,33;,
3;37,36,35;,
3;36,34,35;,
3;39,38,37;,
3;38,36,37;,
3;1,40,3;,
3;40,41,3;,
3;4,42,1;,
3;42,40,1;,
3;6,43,4;,
3;43,42,4;,
3;8,44,6;,
3;44,43,6;,
3;10,45,8;,
3;45,44,8;,
3;12,46,10;,
3;46,45,10;,
3;14,47,12;,
3;47,46,12;,
3;16,48,14;,
3;48,47,14;,
3;18,49,16;,
3;49,48,16;,
3;21,50,23;,
3;50,51,23;,
3;24,52,21;,
3;52,50,21;,
3;26,53,24;,
3;53,52,24;,
3;28,54,26;,
3;54,53,26;,
3;30,55,28;,
3;55,54,28;,
3;32,56,30;,
3;56,55,30;,
3;34,57,32;,
3;57,56,32;,
3;36,58,34;,
3;58,57,34;,
3;38,59,36;,
3;59,58,36;,
3;40,60,41;,
3;60,61,41;,
3;42,62,40;,
3;62,60,40;,
3;43,63,42;,
3;63,62,42;,
3;44,64,43;,
3;64,63,43;,
3;45,65,44;,
3;65,64,44;,
3;46,66,45;,
3;66,65,45;,
3;47,67,46;,
3;67,66,46;,
3;48,68,47;,
3;68,67,47;,
3;49,69,48;,
3;69,68,48;,
3;50,70,51;,
3;70,71,51;,
3;52,72,50;,
3;72,70,50;,
3;53,73,52;,
3;73,72,52;,
3;54,74,53;,
3;74,73,53;,
3;55,75,54;,
3;75,74,54;,
3;56,76,55;,
3;76,75,55;,
3;57,77,56;,
3;77,76,56;,
3;58,78,57;,
3;78,77,57;,
3;59,79,58;,
3;79,78,58;,
3;60,80,61;,
3;80,81,61;,
3;62,82,60;,
3;82,80,60;,
3;63,83,62;,
3;83,82,62;,
3;64,84,63;,
3;84,83,63;,
3;65,85,64;,
3;85,84,64;,
3;66,86,65;,
3;86,85,65;,
3;67,87,66;,
3;87,86,66;,
3;68,88,67;,
3;88,87,67;,
3;69,89,68;,
3;89,88,68;,
3;70,90,71;,
3;90,91,71;,
3;72,92,70;,
3;92,90,70;,
3;73,93,72;,
3;93,92,72;,
3;74,94,73;,
3;94,93,73;,
3;75,95,74;,
3;95,94,74;,
3;76,96,75;,
3;96,95,75;,
3;77,97,76;,
3;97,96,76;,
3;78,98,77;,
3;98,97,77;,
3;79,99,78;,
3;99,98,78;,
3;80,100,81;,
3;100,101,81;,
3;82,102,80;,
3;102,100,80;,
3;83,103,82;,
3;103,102,82;,
3;84,104,83;,
3;104,103,83;,
3;85,105,84;,
3;105,104,84;,
3;86,106,85;,
3;106,105,85;,
3;87,107,86;,
3;107,106,86;,
3;88,108,87;,
3;108,107,87;,
3;89,109,88;,
3;109,108,88;,
3;90,110,91;,
3;110,111,91;,
3;92,112,90;,
3;112,110,90;,
3;93,113,92;,
3;113,112,92;,
3;94,114,93;,
3;114,113,93;,
3;95,115,94;,
3;115,114,94;,
3;96,116,95;,
3;116,115,95;,
3;97,117,96;,
3;117,116,96;,
3;98,118,97;,
3;118,117,97;,
3;99,119,98;,
3;119,118,98;,
3;100,120,101;,
3;120,121,101;,
3;102,122,100;,
3;122,120,100;,
3;103,123,102;,
3;123,122,102;,
3;104,124,103;,
3;124,123,103;,
3;105,125,104;,
3;125,124,104;,
3;106,126,105;,
3;126,125,105;,
3;107,127,106;,
3;127,126,106;,
3;108,128,107;,
3;128,127,107;,
3;109,129,108;,
3;129,128,108;,
3;110,130,111;,
3;130,131,111;,
3;112,132,110;,
3;132,130,110;,
3;113,133,112;,
3;133,132,112;,
3;114,134,113;,
3;134,133,113;,
3;115,135,114;,
3;135,134,114;,
3;116,136,115;,
3;136,135,115;,
3;117,137,116;,
3;137,136,116;,
3;118,138,117;,
3;138,137,117;,
3;119,139,118;,
3;139,138,118;,
3;120,140,121;,
3;140,141,121;,
3;122,142,120;,
3;142,140,120;,
3;123,143,122;,
3;143,142,122;,
3;124,144,123;,
3;144,143,123;,
3;125,145,124;,
3;145,144,124;,
3;126,146,125;,
3;146,145,125;,
3;127,147,126;,
3;147,146,126;,
3;128,148,127;,
3;148,147,127;,
3;129,149,128;,
3;149,148,128;,
3;130,150,131;,
3;150,151,131;,
3;132,152,130;,
3;152,150,130;,
3;133,153,132;,
3;153,152,132;,
3;134,154,133;,
3;154,153,133;,
3;135,155,134;,
3;155,154,134;,
3;136,156,135;,
3;156,155,135;,
3;137,157,136;,
3;157,156,136;,
3;138,158,137;,
3;158,157,137;,
3;139,159,138;,
3;159,158,138;,
3;2,0,160;,
3;5,2,160;,
3;7,5,160;,
3;9,7,160;,
3;11,9,160;,
3;13,11,160;,
3;15,13,160;,
3;17,15,160;,
3;19,17,160;,
3;22,20,161;,
3;25,22,161;,
3;27,25,161;,
3;29,27,161;,
3;31,29,161;,
3;33,31,161;,
3;35,33,161;,
3;37,35,161;,
3;39,37,161;,
3;141,140,162;,
3;140,142,162;,
3;142,143,162;,
3;143,144,162;,
3;144,145,162;,
3;145,146,162;,
3;146,147,162;,
3;147,148,162;,
3;148,149,162;,
3;151,150,163;,
3;150,152,163;,
3;152,153,163;,
3;153,154,163;,
3;154,155,163;,
3;155,156,163;,
3;156,157,163;,
3;157,158,163;,
3;158,159,163;;
 }
MeshTextureCoords {
 164;
0.024425;0.649384;,
0.092396;0.595764;,
0.044045;0.660184;,
0.061252;0.567129;,
0.113746;0.630008;,
0.058172;0.677062;,
0.128400;0.668308;,
0.068424;0.697912;,
0.137061;0.709547;,
0.074695;0.721757;,
0.139706;0.752012;,
0.076328;0.747032;,
0.136297;0.793868;,
0.073217;0.771531;,
0.126626;0.833583;,
0.065763;0.793577;,
0.109770;0.870183;,
0.053861;0.812257;,
0.082468;0.902481;,
0.035648;0.825477;,
0.969898;0.403163;,
0.892321;0.456871;,
0.949182;0.390039;,
0.924240;0.490134;,
0.871460;0.418203;,
0.934954;0.370560;,
0.858186;0.375633;,
0.925322;0.347145;,
0.851568;0.330267;,
0.920209;0.320810;,
0.851568;0.283854;,
0.920209;0.293309;,
0.858185;0.238488;,
0.925322;0.266975;,
0.871459;0.195918;,
0.934953;0.243560;,
0.892319;0.157249;,
0.949180;0.224081;,
0.924238;0.123986;,
0.969897;0.210956;,
0.156820;0.546940;,
0.127793;0.497894;,
0.176076;0.596702;,
0.188999;0.647870;,
0.196919;0.700332;,
0.200287;0.753450;,
0.199056;0.806452;,
0.192685;0.858787;,
0.179816;0.910539;,
0.157171;0.962834;,
0.818906;0.505590;,
0.847129;0.560918;,
0.801358;0.450169;,
0.790820;0.393658;,
0.785818;0.336069;,
0.785817;0.278053;,
0.790819;0.220463;,
0.801356;0.163953;,
0.818903;0.108531;,
0.847125;0.053203;,
0.232290;0.518410;,
0.218018;0.455312;,
0.242200;0.577620;,
0.249527;0.635851;,
0.254909;0.694033;,
0.258617;0.752330;,
0.260642;0.810707;,
0.260731;0.869347;,
0.258247;0.929326;,
0.252019;0.993742;,
0.734868;0.531437;,
0.746068;0.601062;,
0.728098;0.466362;,
0.724145;0.402546;,
0.722311;0.338897;,
0.722310;0.275226;,
0.724144;0.211577;,
0.728096;0.147761;,
0.734865;0.082685;,
0.746064;0.013060;,
0.312652;0.513388;,
0.318881;0.448972;,
0.310169;0.573368;,
0.310258;0.632010;,
0.312284;0.690387;,
0.315992;0.748684;,
0.321374;0.806865;,
0.328702;0.865095;,
0.338612;0.924304;,
0.352885;0.987401;,
0.647106;0.531438;,
0.635908;0.601063;,
0.653876;0.466363;,
0.657828;0.402546;,
0.659662;0.338897;,
0.659661;0.275226;,
0.657827;0.211578;,
0.653873;0.147761;,
0.647103;0.082686;,
0.635904;0.013061;,
0.391082;0.532173;,
0.413727;0.479878;,
0.378214;0.583927;,
0.371843;0.636263;,
0.370613;0.689265;,
0.373982;0.742382;,
0.381903;0.794844;,
0.394826;0.846010;,
0.414084;0.895771;,
0.443111;0.944817;,
0.563069;0.505592;,
0.534847;0.560920;,
0.580615;0.450170;,
0.591153;0.393660;,
0.596155;0.336071;,
0.596154;0.278054;,
0.591152;0.220465;,
0.580613;0.163954;,
0.563066;0.108533;,
0.534843;0.053205;,
0.461128;0.572527;,
0.488429;0.540227;,
0.444273;0.609127;,
0.434602;0.648843;,
0.431194;0.690699;,
0.433840;0.733163;,
0.442501;0.774402;,
0.457156;0.812701;,
0.478507;0.846944;,
0.509652;0.875578;,
0.489653;0.456874;,
0.457734;0.490137;,
0.510513;0.418205;,
0.523786;0.375635;,
0.530404;0.330269;,
0.530404;0.283857;,
0.523785;0.238491;,
0.510512;0.195920;,
0.489651;0.157252;,
0.457732;0.123989;,
0.517038;0.630449;,
0.535251;0.617230;,
0.505136;0.649130;,
0.497683;0.671176;,
0.494572;0.695676;,
0.496206;0.720951;,
0.502477;0.744795;,
0.512729;0.765644;,
0.526856;0.782522;,
0.546476;0.793322;,
0.432791;0.390043;,
0.412075;0.403167;,
0.447019;0.370563;,
0.456650;0.347148;,
0.461763;0.320814;,
0.461763;0.293313;,
0.456649;0.266979;,
0.447018;0.243564;,
0.432790;0.224084;,
0.412074;0.210960;,
0.012569;0.738592;,
0.989044;0.307060;,
0.558332;0.704113;,
0.392928;0.307064;;
}
}
 }