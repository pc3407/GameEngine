//--------------------------------------------------------------------------------------
// File: BasicHLSL11_VS.hlsl
//
// The vertex shader file for the BasicHLSL11 sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
    
	output.Position = input.Position;
	output.Color = input.Color;
    
	return output;
}


float4 PS(VS_OUTPUT output) : SV_TARGET
{
	return output.Color;
}