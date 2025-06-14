#version 330 core
out vec4 FragColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

in vec3 Normal;
in vec3 CurrentPosition;

void main()
{
	float ambience = 0.20f;
	vec3 NewNormal = normalize(Normal);
	vec3 LightDirection = normalize(lightPos-CurrentPosition);

	float SpecularLight = 0.50f;
	vec3 ViewDirection = normalize(camPos-CurrentPosition);
	vec3 ReflectionDirection = reflect(-LightDirection,NewNormal);
	float SpecularAmount = pow(max(dot(ViewDirection,ReflectionDirection),0.0f),8);
	float Specular = SpecularLight*SpecularAmount;

	float Diffuse = max(dot(NewNormal,LightDirection),0.0f);
    FragColor = vec4(0.2,0.3,0.5,1.0f) * (Diffuse+ambience+Specular);
}