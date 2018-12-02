////////////////////////////////////////////////////////////////////////////////
// Filename: light.ps
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float padding;

};

Texture2D shaderTexture;
SamplerState SampleType;


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 TreePixelShader(PixelInputType input) : SV_TARGET
{

	float3 lightDir;
float lightIntensity;
float4 color;
float4 textureColor;

// Sample the pixel color from the texture using the sampler at this texture coordinate location.
textureColor = shaderTexture.Sample(SampleType, input.tex);


color = ambientColor;

// Invert the light direction for calculations.
lightDir = -lightDirection;

// Calculate the amount of light on this pixel.
lightIntensity = saturate(dot(input.normal, lightDir));
if (lightIntensity > 0.0f)
{
	color += (diffuseColor * lightIntensity);

	// Saturate the ambient and diffuse color.
	color = saturate(color);
}


// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
color += saturate(diffuseColor * lightIntensity / 2);

// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
color = color * textureColor;


return color;
}
