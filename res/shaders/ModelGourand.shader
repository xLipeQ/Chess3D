#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 v_Normal;

out vec2 v_TexCoord;
out vec4 v_Color;
out vec3 f_Normal;
out vec3 FragPos;

// Imports the camera matrix from the main function
uniform mat4 u_camMatrix;
uniform mat4 u_Model;
uniform vec4 u_Color;

uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;
uniform bool u_FogEnabled;

struct Light{
	vec4 m_LightColor;
	vec3 m_LightPos;
	bool m_PointLight;
};

#define NR_POINT_LIGHTS 3
uniform Light pointLights[NR_POINT_LIGHTS];

vec4 PointLight(Light light)
{
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = light.m_LightPos - vec3(position);

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 0.00007;
	float b = 0.0014;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// diffuse lighting
	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_ViewPos - vec3(position));
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (diffuse * inten + specular * inten) * light.m_LightColor * u_Color * texture(u_Texture, texCoord);
}

vec4 Spotlight(Light light)
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// diffuse lighting
	vec3 normal = normalize(v_Normal);
	vec3 lightDirection = normalize(light.m_LightPos - vec3(position));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(u_ViewPos - vec3(position));
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(-light.m_LightPos, -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (diffuse * inten + specular * inten) * light.m_LightColor * u_Color * texture(u_Texture, texCoord);
}

float CalcFogFactor()
{
	float fogIntensity = 0.8f;
	if (fogIntensity == 0) 
		return 1;
	
	float gradient = (fogIntensity * fogIntensity - 50 * fogIntensity + 60);
	float distance = length(u_ViewPos - vec3(position));
	
	float fog = exp(-pow((gradient / distance), 4));
	fog = clamp(fog, 0.0, 1.0);
	
	return fog;
}


void main()
{
	v_TexCoord = texCoord;
	gl_Position = u_camMatrix * u_Model * position;
	FragPos = vec3(u_Model * position);
	f_Normal = v_Normal;

	vec3 result;
	float ambient = 0.1f;
	result += vec3(v_Color * texture(u_Texture, v_TexCoord) * ambient); 
	for(int i=0; i<NR_POINT_LIGHTS; i++)
	{
		if(pointLights[i].m_PointLight)
			result += vec3(PointLight(pointLights[i]));
		else
			result += vec3(Spotlight(pointLights[i]));	
	}

	if(u_FogEnabled)
		result += CalcFogFactor() * vec3(0.4f, 0.4f, 0.4f);

	v_Color = vec4(result, 1.0f);
};






#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
	
in vec2 v_TexCoord;
in vec4 v_Color;
in vec3 v_Normal;
in vec3 FragPos;


void main()
{
	color = v_Color;
};