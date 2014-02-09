shared uniform extern float4x4 gViewProj :VIEWPROJECTION;
uniform extern float4x4 gWorld : WORLD;
    
 texture skybox;

samplerCUBE skySampler = sampler_state
{
    texture = <skybox> ;
    magfilter = LINEAR;
    minfilter = LINEAR;
    mipfilter = LINEAR;
    AddressU = MIRROR;
    AddressV = MIRROR;
    AddressW = MIRROR;
};   

struct PS_INPUT_SKY
{
    float4 Pos : POSITION;
    float3 Tex : TEXCOORD0;
};	


PS_INPUT_SKY VS_Sky( float3 pos :POSITION)
{
    PS_INPUT_SKY output = (PS_INPUT_SKY) 0;
    // transform as vector not as point
    float4 hPos = float4(pos,0);

    output.Pos = mul (hPos , gWorld);
    output.Pos = mul (output.Pos , gViewProj).xyww;
    
    output.Tex  =pos.xzy;
    return output;
}
float4 PS_Sky ( PS_INPUT_SKY input) : COLOR0
{
    return texCUBE(skySampler,input.Tex);
}

technique SkyBox
{
    pass P1
    {
        VertexShader = compile vs_3_0 VS_Sky();
        PixelShader = compile ps_3_0 PS_Sky();
    }
}