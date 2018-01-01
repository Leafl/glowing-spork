#version 330 core

// Variables coming in from the vertex shader
in vec3 color;
in vec3 Normal;
in vec3 FragPos;
in vec2 vs_tex_coord;//

out vec4 FragColor;

uniform sampler2D tex;


uniform vec3 EyePosition;

uniform vec3 ambientColor;
uniform float ambientWeight;

uniform vec3 pointLightColor;
uniform float pointWeight;
uniform float Shininess;
uniform float Strength;
uniform vec3 LightPosition;

uniform float ConstantAttenuation;
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;

void main()
{
	vec4 texColor = texture(tex, vs_tex_coord);
	vec3 Color = vec3(texColor.rgb);

	//amvient
	vec3 ambient = ambientColor * Color;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPosition - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointWeight * pointLightColor * diff * Color;

	//specular
	vec3 viewDir = normalize(EyePosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), Shininess);
	vec3 specular = pointWeight * (pointLightColor * Strength) * (spec * Color);

	//attenuation
	float distance = length(LightPosition - FragPos);
	float attenuation = 1.0/ (ConstantAttenuation + LinearAttenuation * distance + QuadraticAttenuation *( distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient * ambientWeight) + diffuse + specular;
	FragColor = vec4(result, 1.0);
	
	
}
