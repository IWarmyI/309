#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Compliment = false;

out vec4 Fragment;

void main()
{
	//store color in vec in case of compliment
	vec3 colorOutput = Color;
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
	{
		colorOutput = SolidColor;
	}
	//subtract color from white to get compliment
	if (Compliment)
	{
		colorOutput = vec3(1.0f) - colorOutput;
	}

	Fragment = vec4(colorOutput, 1);

	return;
}