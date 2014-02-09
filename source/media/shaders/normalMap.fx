float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WVP;
float4 CameraPos;
float3 lightDir = float3(0,1,0);

texture Texture;
sampler2D SamplerSimple = sampler_state{
    Texture = <Texture>;
    MinFilter = Linear;  
    MagFilter = Linear;
    MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture NormalMap;
sampler2D SamplerNormalMap = sampler_state{
    Texture = <NormalMap>;
    MinFilter = Linear;  
    MagFilter = Linear;
    MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_Input{
    float4 Pos		: POSITION;
	float3 Normal	: NORMAL0;
	float2 Tex0		: TEXCOORD0;
	float3 Tangent	: TANGENT;
	float3 Binormal	: BINORMAL;
};
struct VS_Output{
    float4  Pos     : POSITION;
    float2  Tex0    : TEXCOORD0;
	float3 Light : TEXCOORD1;
	float3 View : TEXCOORD2;
	float3 Att : TEXCOORD3;
    
 };
struct PS_Output{
	float4 Color : COLOR;
};
VS_Output VS(VS_Input In){
    VS_Output Out = (VS_Output) 0;
    Out.Pos		=	mul(In.Pos,WVP);
    Out.Tex0	=	In.Tex0;
    
    float3x3 worldToTangentSpace;
		worldToTangentSpace[0] = mul(In.Tangent, World);
		worldToTangentSpace[1] = mul(cross(In.Tangent, In.Normal), World);
		worldToTangentSpace[2] = mul(In.Normal, World);
    
    Out.Light.xyz = mul(worldToTangentSpace, lightDir);
	float3 PosWorld = normalize(mul(In.Pos, World));
	float3 Viewer = CameraPos - PosWorld; // V
	Out.View = mul(worldToTangentSpace, Viewer);
	
	float LightRange = 0.3;
	// point light
	Out.Att = Out.Light * LightRange;
    return Out;
}
PS_Output PS(VS_Output In){
    PS_Output Out = (PS_Output) 0;
    
	float4 color = tex2D(SamplerSimple, In.Tex0); // fetch color map
	float3 bumpNormal = 2 * (tex2D(SamplerNormalMap, In.Tex0) - 0.5); // bump map

	float3 LightDir = normalize(In.Light); // L
	float3 ViewDir = normalize(In.View); // V

	float4 diff = saturate(dot(bumpNormal, LightDir)); // diffuse comp.

	float shadow = saturate(4 * diff); // compute self-shadowing term

	float3 Reflect = normalize(2 * diff * bumpNormal - LightDir); // R

	// gloss map in color.w restricts spec reflection
	float4 spec = min(pow(saturate(dot(Reflect, ViewDir)), 3), color.w);
	
	float4 Attenuation = mul(In.Att, In.Att);
	
	//Out.Color =  0.2 * color + shadow * (color * diff + spec) * (1 - Attenuation);
    Out.Color =   0.2 * color + shadow * (color * diff + spec) * (1 - Attenuation);
    
    
    
    
    /*float4 diffuse = tex2D(SamplerSimple,  In.Tex0);
    float4 ambient = {0.4, 0.4, 0.4, 1.0};

    float3 Normal = normalize(In.Normal);
	float3 LightDir = normalize(lightDir);
	float3 ViewDir = normalize(In.CamDir);
	float4 diff = saturate(dot(Normal, LightDir));
	
	float shadow = saturate(4* diff);
	
	float3 Reflect = normalize(2 * diff * Normal - LightDir);
	float4 specular = pow(saturate(dot(Reflect, ViewDir)), 8);
    
	Out.Color = diffuse;
	*/
    return Out;
}

technique Simple{
    pass P0{
        VertexShader = compile vs_2_0 VS();
        PixelShader  = compile ps_2_0 PS();
        ZEnable          = True;
        ZWriteEnable	 = True;
        CullMode         = None;
        Lighting         = True;
		//fillmode = wireframe;
    }
}


/********** SIMPLE END ************/