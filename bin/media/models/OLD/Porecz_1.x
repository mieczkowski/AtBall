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
Frame porecz_1 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
-20.285759,-8.634752,-2.327346,1.000000;;
 }
Mesh porecz_11 {
 216;
21.141468;8.680398;2.447495;,
21.134901;8.656855;1.966472;,
21.140497;8.680081;1.966472;,
21.135916;8.657161;2.447596;,
21.157888;8.697746;2.447013;,
21.156958;8.697398;1.966472;,
21.180777;8.704556;2.446279;,
21.179871;8.704165;1.966472;,
21.204000;8.699004;2.445490;,
21.203096;8.698570;1.966472;,
21.221338;8.682578;2.444858;,
21.220415;8.682111;1.966472;,
21.228142;8.659678;2.444551;,
21.227182;8.659197;1.966472;,
21.222589;8.636440;2.444653;,
21.227182;8.659197;1.966472;,
21.221586;8.635970;1.966472;,
21.228142;8.659678;2.444551;,
21.206171;8.619092;2.445135;,
21.205126;8.618653;1.966472;,
21.183281;8.612282;2.445869;,
21.182213;8.611886;1.966472;,
21.160057;8.617833;2.446657;,
21.158987;8.617481;1.966472;,
21.142721;8.634260;2.447290;,
21.141668;8.633941;1.966472;,
21.135916;8.657161;2.447596;,
21.134901;8.656855;1.966472;,
21.131968;8.679883;2.505199;,
21.126808;8.656667;2.502920;,
21.147316;8.697173;2.511221;,
21.168741;8.703905;2.519372;,
21.190504;8.698274;2.527467;,
21.206770;8.681789;2.533339;,
21.213182;8.658868;2.535413;,
21.208021;8.635652;2.533134;,
21.213182;8.658868;2.535413;,
21.192673;8.618361;2.527112;,
21.171247;8.611629;2.518961;,
21.149487;8.617261;2.510865;,
21.133221;8.633746;2.504994;,
21.126808;8.656667;2.502920;,
21.101114;8.678824;2.554871;,
21.126808;8.656667;2.502920;,
21.131968;8.679883;2.505199;,
21.097227;8.655652;2.550543;,
21.112986;8.695995;2.566491;,
21.101114;8.678824;2.554871;,
21.129662;8.702564;2.582290;,
21.146673;8.696770;2.598033;,
21.159462;8.680166;2.609503;,
21.164600;8.657201;2.613626;,
21.206770;8.681789;2.533339;,
21.213182;8.658868;2.535413;,
21.159462;8.680166;2.609503;,
21.160715;8.634028;2.609298;,
21.208021;8.635652;2.533134;,
21.148842;8.616858;2.597678;,
21.160715;8.634028;2.609298;,
21.132168;8.610290;2.581880;,
21.115156;8.616083;2.566136;,
21.102367;8.632688;2.554666;,
21.133221;8.633746;2.504994;,
21.102367;8.632688;2.554666;,
21.053608;8.677383;2.588949;,
21.051680;8.654270;2.583215;,
21.060125;8.694392;2.604410;,
21.053608;8.677383;2.588949;,
21.069485;8.700739;2.625455;,
21.079182;8.694722;2.646445;,
21.086617;8.677957;2.661756;,
21.089796;8.654932;2.667285;,
21.086617;8.677957;2.661756;,
21.087870;8.631819;2.661551;,
21.081352;8.614810;2.646090;,
21.087870;8.631819;2.661551;,
21.071991;8.608463;2.625045;,
21.062294;8.614480;2.604054;,
21.054859;8.631247;2.588744;,
21.054859;8.631247;2.588744;,
20.996677;8.675779;2.602244;,
20.997099;8.652732;2.595961;,
20.996778;8.692607;2.619204;,
20.996677;8.675779;2.602244;,
20.997374;8.698706;2.642296;,
20.998306;8.692443;2.665333;,
20.999323;8.675496;2.682142;,
21.000154;8.652405;2.688220;,
20.999323;8.675496;2.682142;,
21.000576;8.629358;2.681937;,
21.000475;8.612531;2.664978;,
21.000576;8.629358;2.681937;,
20.999880;8.606431;2.641886;,
20.998947;8.612694;2.618848;,
20.997931;8.629642;2.602039;,
20.997931;8.629642;2.602039;,
21.205126;8.618653;1.966472;,
21.158987;8.617481;1.966472;,
21.182213;8.611886;1.966472;,
21.134901;8.656855;1.966472;,
21.227182;8.659197;1.966472;,
21.221586;8.635970;1.966472;,
21.203096;8.698570;1.966472;,
21.156958;8.697398;1.966472;,
21.179871;8.704165;1.966472;,
19.571865;8.661036;2.642296;,
19.572769;8.654975;2.619204;,
19.571253;8.654734;2.665333;,
19.571096;8.637756;2.682142;,
19.571438;8.614654;2.688220;,
19.571096;8.637756;2.682142;,
19.572187;8.591615;2.681937;,
19.573141;8.574814;2.664978;,
19.572187;8.591615;2.681937;,
19.574045;8.568753;2.641886;,
19.574657;8.575055;2.618848;,
19.574472;8.615135;2.595961;,
19.574814;8.592032;2.602039;,
19.428886;8.635438;2.447495;,
19.436638;8.612258;1.966472;,
19.435610;8.612513;2.447596;,
19.429871;8.635172;1.966472;,
19.411606;8.651931;2.447013;,
19.412554;8.651631;1.966472;,
19.388401;8.657571;2.446279;,
19.389326;8.657227;1.966472;,
19.365490;8.650847;2.445490;,
19.366413;8.650459;1.966472;,
19.349009;8.633562;2.444858;,
19.349955;8.633142;1.966472;,
19.343376;8.610346;2.444551;,
19.344358;8.609916;1.966472;,
19.350100;8.587420;2.444653;,
19.344358;8.609916;1.966472;,
19.343376;8.610346;2.444551;,
19.351126;8.587002;1.966472;,
19.367378;8.570929;2.445135;,
19.368443;8.570542;1.966472;,
19.390583;8.565288;2.445869;,
19.391670;8.564947;1.966472;,
19.413496;8.572011;2.446657;,
19.414583;8.571714;1.966472;,
19.429976;8.589296;2.447290;,
19.431042;8.589031;1.966472;,
19.435610;8.612513;2.447596;,
19.436638;8.612258;1.966472;,
19.438400;8.635406;2.505199;,
19.444731;8.612482;2.502920;,
19.422194;8.651896;2.511221;,
19.400454;8.657531;2.519372;,
19.379007;8.650803;2.527467;,
19.363598;8.633513;2.533339;,
19.358356;8.610296;2.535413;,
19.364689;8.587372;2.533134;,
19.358356;8.610296;2.535413;,
19.380896;8.570883;2.527112;,
19.402636;8.565248;2.518961;,
19.424082;8.571976;2.510865;,
19.439491;8.589265;2.504994;,
19.444731;8.612482;2.502920;,
19.469267;8.635916;2.554871;,
19.444731;8.612482;2.502920;,
19.474325;8.612970;2.550543;,
19.438400;8.635406;2.505199;,
19.456539;8.652462;2.566491;,
19.469267;8.635916;2.554871;,
19.439552;8.658175;2.582290;,
19.422857;8.651525;2.598033;,
19.410927;8.634294;2.609503;,
19.406960;8.611097;2.613626;,
19.363598;8.633513;2.533339;,
19.410927;8.634294;2.609503;,
19.358356;8.610296;2.535413;,
19.412018;8.588152;2.609298;,
19.364689;8.587372;2.533134;,
19.424746;8.571606;2.597678;,
19.412018;8.588152;2.609298;,
19.441732;8.565892;2.581880;,
19.458427;8.572542;2.566136;,
19.470358;8.589774;2.554666;,
19.439491;8.589265;2.504994;,
19.470358;8.589774;2.554666;,
19.516787;8.636888;2.588949;,
19.519884;8.613902;2.583215;,
19.509415;8.653543;2.604410;,
19.516787;8.636888;2.588949;,
19.499743;8.659407;2.625455;,
19.490364;8.652905;2.646445;,
19.483791;8.635784;2.661756;,
19.481785;8.612628;2.667285;,
19.483791;8.635784;2.661756;,
19.484880;8.589643;2.661551;,
19.492252;8.572987;2.646090;,
19.484880;8.589643;2.661551;,
19.501925;8.567123;2.625045;,
19.511303;8.573624;2.604054;,
19.517876;8.590746;2.588744;,
19.517876;8.590746;2.588744;,
19.573723;8.638174;2.602244;,
19.573723;8.638174;2.602244;,
19.574814;8.592032;2.602039;,
19.412554;8.651631;1.966472;,
19.436638;8.612258;1.966472;,
19.429871;8.635172;1.966472;,
19.366413;8.650459;1.966472;,
19.344358;8.609916;1.966472;,
19.349955;8.633142;1.966472;,
19.368443;8.570542;1.966472;,
19.414583;8.571714;1.966472;,
21.220415;8.682111;1.966472;,
21.140497;8.680081;1.966472;,
21.141668;8.633941;1.966472;,
19.389326;8.657227;1.966472;,
19.351126;8.587002;1.966472;,
19.391670;8.564947;1.966472;,
19.431042;8.589031;1.966472;;

 284;
3;2,1,0;,
3;1,3,0;,
3;5,2,4;,
3;2,0,4;,
3;7,5,6;,
3;5,4,6;,
3;9,7,8;,
3;7,6,8;,
3;11,9,10;,
3;9,8,10;,
3;13,11,12;,
3;11,10,12;,
3;16,15,14;,
3;15,17,14;,
3;19,16,18;,
3;16,14,18;,
3;21,19,20;,
3;19,18,20;,
3;23,21,22;,
3;21,20,22;,
3;25,23,24;,
3;23,22,24;,
3;27,25,26;,
3;25,24,26;,
3;0,3,28;,
3;3,29,28;,
3;4,0,30;,
3;0,28,30;,
3;6,4,31;,
3;4,30,31;,
3;8,6,32;,
3;6,31,32;,
3;10,8,33;,
3;8,32,33;,
3;12,10,34;,
3;10,33,34;,
3;14,17,35;,
3;17,36,35;,
3;18,14,37;,
3;14,35,37;,
3;20,18,38;,
3;18,37,38;,
3;22,20,39;,
3;20,38,39;,
3;24,22,40;,
3;22,39,40;,
3;26,24,41;,
3;24,40,41;,
3;44,43,42;,
3;43,45,42;,
3;30,28,46;,
3;28,47,46;,
3;31,30,48;,
3;30,46,48;,
3;32,31,49;,
3;31,48,49;,
3;33,32,50;,
3;32,49,50;,
3;53,52,51;,
3;52,54,51;,
3;56,53,55;,
3;53,51,55;,
3;37,35,57;,
3;35,58,57;,
3;38,37,59;,
3;37,57,59;,
3;39,38,60;,
3;38,59,60;,
3;40,39,61;,
3;39,60,61;,
3;43,62,45;,
3;62,63,45;,
3;42,45,64;,
3;45,65,64;,
3;46,47,66;,
3;47,67,66;,
3;48,46,68;,
3;46,66,68;,
3;49,48,69;,
3;48,68,69;,
3;50,49,70;,
3;49,69,70;,
3;51,54,71;,
3;54,72,71;,
3;55,51,73;,
3;51,71,73;,
3;57,58,74;,
3;58,75,74;,
3;59,57,76;,
3;57,74,76;,
3;60,59,77;,
3;59,76,77;,
3;61,60,78;,
3;60,77,78;,
3;45,63,65;,
3;63,79,65;,
3;64,65,80;,
3;65,81,80;,
3;66,67,82;,
3;67,83,82;,
3;68,66,84;,
3;66,82,84;,
3;69,68,85;,
3;68,84,85;,
3;70,69,86;,
3;69,85,86;,
3;71,72,87;,
3;72,88,87;,
3;73,71,89;,
3;71,87,89;,
3;74,75,90;,
3;75,91,90;,
3;76,74,92;,
3;74,90,92;,
3;77,76,93;,
3;76,92,93;,
3;78,77,94;,
3;77,93,94;,
3;65,79,81;,
3;79,95,81;,
3;98,97,96;,
3;97,99,96;,
3;101,96,100;,
3;96,102,100;,
3;104,102,103;,
3;102,99,103;,
3;84,82,105;,
3;82,106,105;,
3;85,84,107;,
3;84,105,107;,
3;86,85,108;,
3;85,107,108;,
3;87,88,109;,
3;88,110,109;,
3;89,87,111;,
3;87,109,111;,
3;90,91,112;,
3;91,113,112;,
3;92,90,114;,
3;90,112,114;,
3;93,92,115;,
3;92,114,115;,
3;81,95,116;,
3;95,117,116;,
3;120,119,118;,
3;119,121,118;,
3;118,121,122;,
3;121,123,122;,
3;122,123,124;,
3;123,125,124;,
3;124,125,126;,
3;125,127,126;,
3;126,127,128;,
3;127,129,128;,
3;128,129,130;,
3;129,131,130;,
3;134,133,132;,
3;133,135,132;,
3;132,135,136;,
3;135,137,136;,
3;136,137,138;,
3;137,139,138;,
3;138,139,140;,
3;139,141,140;,
3;140,141,142;,
3;141,143,142;,
3;142,143,144;,
3;143,145,144;,
3;147,120,146;,
3;120,118,146;,
3;146,118,148;,
3;118,122,148;,
3;148,122,149;,
3;122,124,149;,
3;149,124,150;,
3;124,126,150;,
3;150,126,151;,
3;126,128,151;,
3;151,128,152;,
3;128,130,152;,
3;154,134,153;,
3;134,132,153;,
3;153,132,155;,
3;132,136,155;,
3;155,136,156;,
3;136,138,156;,
3;156,138,157;,
3;138,140,157;,
3;157,140,158;,
3;140,142,158;,
3;158,142,159;,
3;142,144,159;,
3;162,161,160;,
3;161,163,160;,
3;165,146,164;,
3;146,148,164;,
3;164,148,166;,
3;148,149,166;,
3;166,149,167;,
3;149,150,167;,
3;167,150,168;,
3;150,151,168;,
3;171,170,169;,
3;170,172,169;,
3;169,172,173;,
3;172,174,173;,
3;176,153,175;,
3;153,155,175;,
3;175,155,177;,
3;155,156,177;,
3;177,156,178;,
3;156,157,178;,
3;178,157,179;,
3;157,158,179;,
3;181,180,162;,
3;180,161,162;,
3;183,162,182;,
3;162,160,182;,
3;185,165,184;,
3;165,164,184;,
3;184,164,186;,
3;164,166,186;,
3;186,166,187;,
3;166,167,187;,
3;187,167,188;,
3;167,168,188;,
3;190,171,189;,
3;171,169,189;,
3;189,169,191;,
3;169,173,191;,
3;193,176,192;,
3;176,175,192;,
3;192,175,194;,
3;175,177,194;,
3;194,177,195;,
3;177,178,195;,
3;195,178,196;,
3;178,179,196;,
3;197,181,183;,
3;181,162,183;,
3;116,183,198;,
3;183,182,198;,
3;199,185,106;,
3;185,184,106;,
3;106,184,105;,
3;184,186,105;,
3;105,186,107;,
3;186,187,107;,
3;107,187,108;,
3;187,188,108;,
3;110,190,109;,
3;190,189,109;,
3;109,189,111;,
3;189,191,111;,
3;113,193,112;,
3;193,192,112;,
3;112,192,114;,
3;192,194,114;,
3;114,194,115;,
3;194,195,115;,
3;115,195,200;,
3;195,196,200;,
3;117,197,116;,
3;197,183,116;,
3;203,202,201;,
3;202,204,201;,
3;206,204,205;,
3;204,207,205;,
3;204,202,207;,
3;202,208,207;,
3;81,116,80;,
3;116,198,80;,
3;82,83,106;,
3;83,199,106;,
3;93,115,94;,
3;115,200,94;,
3;102,209,100;,
3;99,210,103;,
3;99,102,96;,
3;99,97,211;,
3;204,212,201;,
3;207,213,205;,
3;208,214,207;,
3;208,202,215;;
MeshMaterialList {
 1;
 284;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
Material _1_-_Defaultsdf {
 1.000000;1.000000;1.000000;1.000000;;
8.000000;
 0.500000;0.500000;0.500000;;
 0.000000;0.000000;0.000000;;
 }
}

 MeshNormals {
 216;
-0.874080;0.480781;-0.069529;,
-0.999672;-0.025509;0.002078;,
-0.878574;0.477604;0.001407;,
-0.996280;-0.026265;-0.082078;,
-0.513444;0.857307;-0.037421;,
-0.522134;0.852863;0.000344;,
-0.013507;0.999898;0.004551;,
-0.025727;0.999669;-0.000810;,
0.486803;0.872410;0.043856;,
0.477656;0.878545;-0.001738;,
0.853901;0.515651;0.070407;,
0.853024;0.521867;-0.002198;,
0.996498;0.027146;0.079085;,
0.999679;0.025256;-0.002080;,
0.880853;-0.468385;0.068660;,
0.999679;0.025256;-0.002080;,
0.878306;-0.478097;-0.001427;,
0.996498;0.027146;0.079085;,
0.533790;-0.844634;0.040760;,
0.521521;-0.853239;-0.000406;,
0.040909;-0.999162;0.000872;,
0.025042;-0.999686;0.000725;,
-0.466542;-0.883563;-0.040686;,
-0.478065;-0.878323;0.001670;,
-0.847241;-0.526382;-0.071443;,
-0.853088;-0.521762;0.002171;,
-0.996280;-0.026265;-0.082078;,
-0.999672;-0.025509;0.002078;,
-0.816333;0.493828;-0.299555;,
-0.935698;-0.023838;-0.351997;,
-0.468334;0.868332;-0.163287;,
0.003119;0.999870;0.015819;,
0.466676;0.864207;0.188042;,
0.804271;0.507192;0.309685;,
0.935697;0.023839;0.351997;,
0.830679;-0.465540;0.305361;,
0.935697;0.023839;0.351997;,
0.512922;-0.839251;0.180469;,
0.057367;-0.998329;0.006936;,
-0.420571;-0.890978;-0.171107;,
-0.788410;-0.534712;-0.304128;,
-0.935698;-0.023838;-0.351997;,
-0.639825;0.499884;-0.583730;,
-0.935698;-0.023838;-0.351997;,
-0.816333;0.493828;-0.299555;,
-0.729860;-0.016776;-0.683391;,
-0.370562;0.871686;-0.320698;,
-0.639825;0.499884;-0.583730;,
-0.003534;0.999642;0.026530;,
0.358928;0.860511;0.361513;,
0.624440;0.501022;0.599209;,
0.729860;0.016777;0.683391;,
0.804271;0.507192;0.309685;,
0.935697;0.023839;0.351997;,
0.624440;0.501022;0.599209;,
0.650848;-0.471708;0.594885;,
0.830679;-0.465540;0.305361;,
0.405174;-0.842947;0.353940;,
0.650848;-0.471708;0.594885;,
0.050714;-0.998557;0.017647;,
-0.322799;-0.887624;-0.328518;,
-0.611902;-0.528656;-0.588302;,
-0.788410;-0.534712;-0.304128;,
-0.611902;-0.528656;-0.588302;,
-0.368034;0.508130;-0.778688;,
-0.412907;-0.007160;-0.910745;,
-0.220011;0.876253;-0.428691;,
-0.368034;0.508130;-0.778688;,
-0.013778;0.999331;0.033878;,
0.193017;0.855477;0.480524;,
0.347534;0.492621;0.797837;,
0.412908;0.007161;0.910744;,
0.347534;0.492621;0.797837;,
0.373942;-0.480108;0.793514;,
0.239263;-0.847980;0.472951;,
0.373942;-0.480108;0.793514;,
0.040470;-0.998868;0.024996;,
-0.172248;-0.883057;-0.436511;,
-0.340111;-0.520411;-0.783260;,
-0.340111;-0.520411;-0.783260;,
-0.144430;0.430627;-0.890899;,
-0.150950;-0.087590;-0.984653;,
-0.097479;0.912684;-0.396869;,
-0.144430;0.430627;-0.890899;,
-0.021833;0.997830;-0.062114;,
0.056397;0.897300;0.437803;,
0.117511;0.564637;0.816931;,
0.148182;0.090635;0.984798;,
0.117511;0.564637;0.816931;,
0.142556;-0.407460;0.902028;,
0.101018;-0.805182;0.584361;,
0.142556;-0.407460;0.902028;,
0.031669;-0.993778;0.106785;,
-0.048118;-0.913291;-0.404455;,
-0.121229;-0.429944;-0.894680;,
-0.121229;-0.429944;-0.894680;,
0.521521;-0.853239;-0.000406;,
-0.478065;-0.878323;0.001670;,
0.025042;-0.999686;0.000725;,
-0.999672;-0.025509;0.002078;,
0.999679;0.025256;-0.002080;,
0.878306;-0.478097;-0.001427;,
0.477656;0.878545;-0.001738;,
-0.522134;0.852863;0.000344;,
-0.025727;0.999669;-0.000810;,
-0.010102;0.998250;-0.058269;,
0.044439;0.894318;-0.445220;,
-0.038906;0.894195;0.445983;,
-0.059730;0.554178;0.830252;,
-0.067339;0.069616;0.995299;,
-0.059730;0.554178;0.830252;,
-0.058102;-0.432699;0.899664;,
-0.031836;-0.822526;0.567835;,
-0.058102;-0.432699;0.899664;,
0.005731;-0.996470;0.083748;,
0.052512;-0.963581;-0.262209;,
0.116094;0.008078;-0.993205;,
0.089664;-0.475078;-0.875363;,
0.848554;0.524521;-0.069528;,
0.999679;0.025253;0.002078;,
0.996329;0.024330;-0.082078;,
0.853204;0.521576;0.001407;,
0.469273;0.882260;-0.037421;,
0.478176;0.878264;0.000344;,
-0.037257;0.999295;0.004551;,
-0.025039;0.999686;-0.000810;,
-0.530450;0.846581;0.043856;,
-0.521626;0.853172;-0.001738;,
-0.878969;0.471653;0.070406;,
-0.878411;0.477902;-0.002198;,
-0.996592;-0.023462;0.079084;,
-0.999672;-0.025510;-0.002080;,
-0.855946;-0.512487;0.068659;,
-0.999672;-0.025510;-0.002080;,
-0.996592;-0.023462;0.079084;,
-0.852911;-0.522054;-0.001427;,
-0.490235;-0.870637;0.040760;,
-0.477546;-0.878607;-0.000406;,
0.009853;-0.999951;0.000872;,
0.025726;-0.999669;0.000725;,
0.510782;-0.858747;-0.040686;,
0.522025;-0.852928;0.001670;,
0.872863;-0.482706;-0.071442;,
0.878469;-0.477795;0.002171;,
0.996329;0.024330;-0.082078;,
0.999679;0.025253;0.002078;,
0.790219;0.534621;-0.299555;,
0.935702;0.023680;-0.351997;,
0.423662;0.890981;-0.163287;,
-0.053859;0.998423;0.015818;,
-0.509930;0.839411;0.188042;,
-0.828973;0.465725;0.309684;,
-0.935701;-0.023681;0.351997;,
-0.805981;-0.507100;0.305361;,
-0.935701;-0.023681;0.351997;,
-0.469668;-0.864201;0.180469;,
-0.006627;-0.999954;0.006935;,
0.465247;-0.868486;-0.171107;,
0.814530;-0.494011;-0.304127;,
0.935702;0.023680;-0.351997;,
0.613631;0.531711;-0.583729;,
0.935702;0.023680;-0.351997;,
0.729770;0.020288;-0.683391;,
0.790219;0.534621;-0.299555;,
0.325847;0.889368;-0.320698;,
0.613631;0.531711;-0.583729;,
-0.047203;0.998533;0.026530;,
-0.402138;0.841186;0.361513;,
-0.649062;0.468686;0.599209;,
-0.729770;-0.020286;0.683391;,
-0.828973;0.465725;0.309684;,
-0.649062;0.468686;0.599209;,
-0.935701;-0.023681;0.351997;,
-0.626069;-0.504132;0.594885;,
-0.805981;-0.507100;0.305361;,
-0.361873;-0.862423;0.353941;,
-0.626069;-0.504132;0.594885;,
0.000028;-0.999844;0.017647;,
0.367431;-0.870098;-0.328518;,
0.637943;-0.496921;-0.588301;,
0.814530;-0.494011;-0.304127;,
0.637943;-0.496921;-0.588301;,
0.341772;0.526153;-0.778688;,
0.412739;0.013804;-0.910745;,
0.175258;0.886290;-0.428690;,
0.341772;0.526153;-0.778688;,
-0.036957;0.998742;0.033878;,
-0.236184;0.844579;0.480523;,
-0.372088;0.474347;0.797838;,
-0.412739;-0.013803;0.910745;,
-0.372088;0.474347;0.797838;,
-0.349095;-0.498465;0.793514;,
-0.195919;-0.859030;0.472951;,
-0.349095;-0.498465;0.793514;,
0.010275;-0.999635;0.024996;,
0.216842;-0.873177;-0.436511;,
0.366085;-0.502480;-0.783260;,
0.366085;-0.502480;-0.783260;,
0.121699;0.436746;-0.891315;,
0.121699;0.436746;-0.891315;,
0.089664;-0.475078;-0.875363;,
0.478176;0.878264;0.000344;,
0.999679;0.025253;0.002078;,
0.853204;0.521576;0.001407;,
-0.521626;0.853172;-0.001738;,
-0.999672;-0.025510;-0.002080;,
-0.878411;0.477902;-0.002198;,
-0.477546;-0.878607;-0.000406;,
0.522025;-0.852928;0.001670;,
0.853024;0.521867;-0.002198;,
-0.878574;0.477604;0.001407;,
-0.853088;-0.521762;0.002171;,
-0.025039;0.999686;-0.000810;,
-0.852911;-0.522054;-0.001427;,
0.025726;-0.999669;0.000725;,
0.878469;-0.477795;0.002171;;

 284;
3;2,1,0;,
3;1,3,0;,
3;5,2,4;,
3;2,0,4;,
3;7,5,6;,
3;5,4,6;,
3;9,7,8;,
3;7,6,8;,
3;11,9,10;,
3;9,8,10;,
3;13,11,12;,
3;11,10,12;,
3;16,15,14;,
3;15,17,14;,
3;19,16,18;,
3;16,14,18;,
3;21,19,20;,
3;19,18,20;,
3;23,21,22;,
3;21,20,22;,
3;25,23,24;,
3;23,22,24;,
3;27,25,26;,
3;25,24,26;,
3;0,3,28;,
3;3,29,28;,
3;4,0,30;,
3;0,28,30;,
3;6,4,31;,
3;4,30,31;,
3;8,6,32;,
3;6,31,32;,
3;10,8,33;,
3;8,32,33;,
3;12,10,34;,
3;10,33,34;,
3;14,17,35;,
3;17,36,35;,
3;18,14,37;,
3;14,35,37;,
3;20,18,38;,
3;18,37,38;,
3;22,20,39;,
3;20,38,39;,
3;24,22,40;,
3;22,39,40;,
3;26,24,41;,
3;24,40,41;,
3;44,43,42;,
3;43,45,42;,
3;30,28,46;,
3;28,47,46;,
3;31,30,48;,
3;30,46,48;,
3;32,31,49;,
3;31,48,49;,
3;33,32,50;,
3;32,49,50;,
3;53,52,51;,
3;52,54,51;,
3;56,53,55;,
3;53,51,55;,
3;37,35,57;,
3;35,58,57;,
3;38,37,59;,
3;37,57,59;,
3;39,38,60;,
3;38,59,60;,
3;40,39,61;,
3;39,60,61;,
3;43,62,45;,
3;62,63,45;,
3;42,45,64;,
3;45,65,64;,
3;46,47,66;,
3;47,67,66;,
3;48,46,68;,
3;46,66,68;,
3;49,48,69;,
3;48,68,69;,
3;50,49,70;,
3;49,69,70;,
3;51,54,71;,
3;54,72,71;,
3;55,51,73;,
3;51,71,73;,
3;57,58,74;,
3;58,75,74;,
3;59,57,76;,
3;57,74,76;,
3;60,59,77;,
3;59,76,77;,
3;61,60,78;,
3;60,77,78;,
3;45,63,65;,
3;63,79,65;,
3;64,65,80;,
3;65,81,80;,
3;66,67,82;,
3;67,83,82;,
3;68,66,84;,
3;66,82,84;,
3;69,68,85;,
3;68,84,85;,
3;70,69,86;,
3;69,85,86;,
3;71,72,87;,
3;72,88,87;,
3;73,71,89;,
3;71,87,89;,
3;74,75,90;,
3;75,91,90;,
3;76,74,92;,
3;74,90,92;,
3;77,76,93;,
3;76,92,93;,
3;78,77,94;,
3;77,93,94;,
3;65,79,81;,
3;79,95,81;,
3;98,97,96;,
3;97,99,96;,
3;101,96,100;,
3;96,102,100;,
3;104,102,103;,
3;102,99,103;,
3;84,82,105;,
3;82,106,105;,
3;85,84,107;,
3;84,105,107;,
3;86,85,108;,
3;85,107,108;,
3;87,88,109;,
3;88,110,109;,
3;89,87,111;,
3;87,109,111;,
3;90,91,112;,
3;91,113,112;,
3;92,90,114;,
3;90,112,114;,
3;93,92,115;,
3;92,114,115;,
3;81,95,116;,
3;95,117,116;,
3;120,119,118;,
3;119,121,118;,
3;118,121,122;,
3;121,123,122;,
3;122,123,124;,
3;123,125,124;,
3;124,125,126;,
3;125,127,126;,
3;126,127,128;,
3;127,129,128;,
3;128,129,130;,
3;129,131,130;,
3;134,133,132;,
3;133,135,132;,
3;132,135,136;,
3;135,137,136;,
3;136,137,138;,
3;137,139,138;,
3;138,139,140;,
3;139,141,140;,
3;140,141,142;,
3;141,143,142;,
3;142,143,144;,
3;143,145,144;,
3;147,120,146;,
3;120,118,146;,
3;146,118,148;,
3;118,122,148;,
3;148,122,149;,
3;122,124,149;,
3;149,124,150;,
3;124,126,150;,
3;150,126,151;,
3;126,128,151;,
3;151,128,152;,
3;128,130,152;,
3;154,134,153;,
3;134,132,153;,
3;153,132,155;,
3;132,136,155;,
3;155,136,156;,
3;136,138,156;,
3;156,138,157;,
3;138,140,157;,
3;157,140,158;,
3;140,142,158;,
3;158,142,159;,
3;142,144,159;,
3;162,161,160;,
3;161,163,160;,
3;165,146,164;,
3;146,148,164;,
3;164,148,166;,
3;148,149,166;,
3;166,149,167;,
3;149,150,167;,
3;167,150,168;,
3;150,151,168;,
3;171,170,169;,
3;170,172,169;,
3;169,172,173;,
3;172,174,173;,
3;176,153,175;,
3;153,155,175;,
3;175,155,177;,
3;155,156,177;,
3;177,156,178;,
3;156,157,178;,
3;178,157,179;,
3;157,158,179;,
3;181,180,162;,
3;180,161,162;,
3;183,162,182;,
3;162,160,182;,
3;185,165,184;,
3;165,164,184;,
3;184,164,186;,
3;164,166,186;,
3;186,166,187;,
3;166,167,187;,
3;187,167,188;,
3;167,168,188;,
3;190,171,189;,
3;171,169,189;,
3;189,169,191;,
3;169,173,191;,
3;193,176,192;,
3;176,175,192;,
3;192,175,194;,
3;175,177,194;,
3;194,177,195;,
3;177,178,195;,
3;195,178,196;,
3;178,179,196;,
3;197,181,183;,
3;181,162,183;,
3;116,183,198;,
3;183,182,198;,
3;199,185,106;,
3;185,184,106;,
3;106,184,105;,
3;184,186,105;,
3;105,186,107;,
3;186,187,107;,
3;107,187,108;,
3;187,188,108;,
3;110,190,109;,
3;190,189,109;,
3;109,189,111;,
3;189,191,111;,
3;113,193,112;,
3;193,192,112;,
3;112,192,114;,
3;192,194,114;,
3;114,194,115;,
3;194,195,115;,
3;115,195,200;,
3;195,196,200;,
3;117,197,116;,
3;197,183,116;,
3;203,202,201;,
3;202,204,201;,
3;206,204,205;,
3;204,207,205;,
3;204,202,207;,
3;202,208,207;,
3;81,116,80;,
3;116,198,80;,
3;82,83,106;,
3;83,199,106;,
3;93,115,94;,
3;115,200,94;,
3;102,209,100;,
3;99,210,103;,
3;99,102,96;,
3;99,97,211;,
3;204,212,201;,
3;207,213,205;,
3;208,214,207;,
3;208,202,215;;
 }
MeshTextureCoords {
 216;
1.817825;-0.424222;,
1.806806;3.275955;,
1.816319;3.275955;,
1.808379;-0.425003;,
1.843755;-0.420514;,
1.842310;3.275955;,
1.879223;-0.414870;,
1.877814;3.275955;,
1.914724;-0.408803;,
1.913318;3.275955;,
1.940746;-0.403939;,
1.939308;3.275955;,
1.950317;-0.401581;,
1.948821;3.275955;,
-0.940871;-0.402361;,
-0.948821;3.275955;,
-0.939308;3.275955;,
-0.950317;-0.401581;,
-0.914940;-0.406070;,
-0.913318;3.275955;,
-0.879472;-0.411714;,
-0.877814;3.275955;,
-0.843971;-0.417781;,
-0.842310;3.275955;,
-0.817949;-0.422645;,
-0.816319;3.275955;,
-0.808379;-0.425003;,
-0.806806;3.275955;,
1.803193;-0.868102;,
1.794351;-0.850570;,
1.827474;-0.914422;,
1.860689;-0.977120;,
1.893937;-1.039395;,
1.918310;-1.084560;,
1.927277;-1.100515;,
-0.918435;-1.082983;,
-0.927277;-1.100515;,
-0.894153;-1.036661;,
-0.860938;-0.973965;,
-0.827690;-0.911690;,
-0.803317;-0.866524;,
-0.794351;-0.850570;,
1.755701;0.283758;,
1.794351;0.491055;,
1.803193;0.281258;,
1.748818;0.493452;,
1.774630;-1.339581;,
1.755701;-1.250195;,
1.800533;-1.461107;,
1.826469;-1.582210;,
1.845489;-1.670441;,
-0.852496;0.494924;,
-0.918310;0.281201;,
-0.927277;0.490989;,
-0.845489;0.285033;,
-0.845614;0.704618;,
-0.918435;0.700786;,
-0.826685;-1.579478;,
-0.845614;-1.668864;,
-0.800782;-1.457951;,
-0.774846;-1.336848;,
-0.755826;-1.248616;,
1.803317;0.700844;,
1.755826;0.703343;,
1.682580;0.285893;,
1.678714;0.495499;,
1.693267;-1.631262;,
1.682580;-1.512331;,
1.707912;-1.793148;,
1.722590;-1.954611;,
1.733369;-2.072387;,
-0.737360;0.498287;,
-0.733369;0.288307;,
-0.733494;0.707893;,
-0.722806;-1.951878;,
-0.733494;-2.070810;,
-0.708161;-1.789993;,
-0.693483;-1.628529;,
-0.682705;-1.510753;,
1.682705;0.705478;,
1.594962;0.287339;,
1.594710;0.496885;,
1.595773;-1.745060;,
1.594962;-1.614601;,
1.596928;-1.922692;,
1.598116;-2.099901;,
1.599019;-2.229204;,
-0.599396;0.500564;,
-0.599019;0.290524;,
-0.599144;0.710110;,
-0.598332;-2.097169;,
-0.599144;-2.227627;,
-0.597178;-1.919537;,
-0.595989;-1.742327;,
-0.595086;-1.613024;,
1.595086;0.706925;,
1.913318;0.854599;,
1.842310;0.854599;,
1.877814;0.910813;,
1.806806;0.491223;,
1.948821;0.491223;,
1.939308;0.701018;,
1.913318;0.127847;,
1.842310;0.127848;,
1.877814;0.071633;,
-0.596928;-1.922692;,
-0.595773;-1.745060;,
-0.598116;-2.099901;,
-0.599019;-2.229204;,
1.599396;0.513962;,
1.599019;0.303923;,
1.599144;0.723508;,
1.598332;-2.097169;,
1.599144;-2.227627;,
1.597178;-1.919537;,
1.595989;-1.742327;,
-0.594710;0.510284;,
-0.595086;0.720323;,
-0.817824;-0.424222;,
-0.806806;3.275955;,
-0.808379;-0.425003;,
-0.816319;3.275955;,
-0.843755;-0.420514;,
-0.842310;3.275955;,
-0.879223;-0.414870;,
-0.877814;3.275955;,
-0.914724;-0.408803;,
-0.913317;3.275955;,
-0.940746;-0.403939;,
-0.939308;3.275955;,
-0.950317;-0.401581;,
-0.948821;3.275955;,
1.940871;-0.402361;,
1.948821;3.275955;,
1.950317;-0.401581;,
1.939308;3.275955;,
1.914940;-0.406070;,
1.913317;3.275955;,
1.879472;-0.411714;,
1.877814;3.275955;,
1.843971;-0.417781;,
1.842310;3.275955;,
1.817949;-0.422645;,
1.816319;3.275955;,
1.808379;-0.425003;,
1.806806;3.275955;,
-0.803193;-0.868102;,
-0.794350;-0.850570;,
-0.827474;-0.914422;,
-0.860689;-0.977120;,
-0.893937;-1.039395;,
-0.918310;-1.084560;,
-0.927277;-1.100515;,
1.918435;-1.082983;,
1.927277;-1.100515;,
1.894153;-1.036661;,
1.860938;-0.973965;,
1.827690;-0.911690;,
1.803317;-0.866524;,
1.794350;-0.850570;,
-0.755701;0.297156;,
-0.794350;0.504454;,
-0.748818;0.506850;,
-0.803193;0.294657;,
-0.774630;-1.339581;,
-0.755701;-1.250195;,
-0.800533;-1.461107;,
-0.826469;-1.582210;,
-0.845489;-1.670441;,
1.852496;0.508324;,
1.918310;0.294600;,
1.845489;0.298432;,
1.927277;0.504388;,
1.845613;0.718018;,
1.918435;0.714185;,
1.826685;-1.579478;,
1.845613;-1.668864;,
1.800782;-1.457951;,
1.774846;-1.336848;,
1.755826;-1.248616;,
-0.803317;0.714243;,
-0.755826;0.716742;,
-0.682580;0.299291;,
-0.678714;0.508897;,
-0.693267;-1.631262;,
-0.682580;-1.512331;,
-0.707912;-1.793148;,
-0.722590;-1.954611;,
-0.733369;-2.072387;,
1.737360;0.511685;,
1.733369;0.301706;,
1.733494;0.721291;,
1.722806;-1.951878;,
1.733494;-2.070810;,
1.708162;-1.789993;,
1.693483;-1.628529;,
1.682705;-1.510753;,
-0.682705;0.718877;,
-0.594962;0.300737;,
-0.594962;-1.614601;,
1.595086;-1.613024;,
-0.842310;0.141247;,
-0.806806;0.504622;,
-0.816319;0.294827;,
-0.913317;0.141247;,
-0.948821;0.504623;,
-0.939308;0.294827;,
-0.913317;0.867998;,
-0.842310;0.867998;,
1.939308;0.281428;,
1.816319;0.281428;,
1.816319;0.701019;,
-0.877814;0.085032;,
-0.939308;0.714418;,
-0.877814;0.924213;,
-0.816319;0.714418;;
}
}
 }