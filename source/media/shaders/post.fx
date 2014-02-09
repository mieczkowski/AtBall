texture ScreenTexture;
sampler TextureSampler = sampler_state{
    Texture = <ScreenTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;

	AddressU = Wrap;
	AddressV = Wrap;
};
struct VS_Input{
    float4 Pos		: POSITION;
	float2 Tex0		: TEXCOORD0;
};
struct VS_Output{
    float4  Pos     : POSITION;
    float2  Tex0    : TEXCOORD0;
 };
struct PS_Output{
	float4 Color : COLOR;
};
VS_Output VS(VS_Input In){
    VS_Output Out = (VS_Output) 0;
    Out.Pos		=	In.Pos;
    Out.Tex0	=	In.Tex0;
    return Out;
}
PS_Output PS_Sepia(VS_Output In){
	PS_Output Out = (PS_Output) 0;
	float4 color = tex2D(TextureSampler, In.Tex0); 
	
	float4 outputColor = color;
    outputColor.r = (color.r * 0.393) + (color.g * 0.769) + (color.b * 0.189);
    outputColor.g = (color.r * 0.349) + (color.g * 0.686) + (color.b * 0.168);    
    outputColor.b = (color.r * 0.272) + (color.g * 0.534) + (color.b * 0.131);
	
	Out.Color = outputColor;
    return Out;
}
PS_Output PS_Clean(VS_Output In){
	PS_Output Out = (PS_Output) 0;
	Out.Color = tex2D(TextureSampler, In.Tex0); 
    return Out;
}
PS_Output PS_Color(VS_Output In){
	PS_Output Out = (PS_Output) 0;
	Out.Color = tex2D(TextureSampler, In.Tex0);
	Out.Color.r = Out.Color.r * 1.3;
	Out.Color.g = Out.Color.g * 1;
	Out.Color.b = Out.Color.b * 1.3;
	
    return Out;
}
PS_Output PS_BW(VS_Output In){
	PS_Output Out = (PS_Output) 0;
	float4 color = tex2D(TextureSampler, In.Tex0);
	float value = (color.r + color.g + color.b) / 3; 
    color.r = value;
    color.g = value;
    color.b = value;
	Out.Color = color; 
    return Out;
}

technique Sepia{
    pass Pass1{
		VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_Sepia();
    }
}
technique BW{
    pass Pass1{
		VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_BW();
    }
}
technique Color{
	pass Pass1{
		VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_Color();
    }
}
technique Clean{
	pass Pass1{
		VertexShader = compile vs_2_0 VS();
        PixelShader = compile ps_2_0 PS_Clean();
    }
}
