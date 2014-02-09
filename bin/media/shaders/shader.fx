texture Texture;
float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WVP;
float4 CameraPos;
float3 lightDir = float3(10.0,120.0,10.0);
sampler2D SamplerSimple = sampler_state{
    Texture = <Texture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;

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
    //float3  Color : COLOR;
    float2  Tex0    : TEXCOORD0;
    float3 Normal   : TEXCOORD1;
    float3 CamDir   : TEXCOORD2;
    
 };
struct PS_Output{
	float4 Color : COLOR;
};
VS_Output VS(VS_Input In){
    VS_Output Out = (VS_Output) 0;
    
    Out.Pos		=	mul(In.Pos,WVP);
    Out.Tex0	=	In.Tex0;
    Out.Normal  =   mul(float4(In.Normal, 1),World);
    Out.CamDir  =   CameraPos - mul(In.Pos, World);
    return Out;
}
PS_Output PS(VS_Output In){
    PS_Output Out = (PS_Output) 0;
    float4 diffuse = tex2D(SamplerSimple,  In.Tex0);
    float4 ambient = {0.4, 0.4, 0.4, 1.0};

    float3 Normal = normalize(In.Normal);
	float3 LightDir = normalize(lightDir);
	float3 ViewDir = normalize(In.CamDir);
	float4 diff = saturate(dot(Normal, LightDir));
	
	float shadow = saturate(4* diff);
	
	float3 Reflect = normalize(2 * diff * Normal - LightDir);
	float4 specular = pow(saturate(dot(Reflect, ViewDir)), 8);
    
    //float4 diffuseLambert = saturate(dot(normalize(In.Normal), normalize(lightDir)));
    
    
    //return ambient + shadow * (diffuse * diff + specular);
    //Out.Color = ambient + shadow * (diffuse* diff + specular);
	Out.Color = diffuse;
	Out.Color.a = 0.3;
    //float3 H = normalize(-lightDir + In.CamDir);
    //float4 specularBlinn = pow(dot(H, In.Normal), 16);
	
    //float3 R = reflect(lightDir, In.Normal);
    //float4 specularPhong = pow(dot(normalize(R), normalize(CameraDir)), 16);
	
	//Out.Color = tex2D(SamplerSimple,  In.Tex0) * (diffuseLambert + specularBlinn);
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