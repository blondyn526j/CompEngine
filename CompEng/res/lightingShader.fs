#version 330 core

struct Material {
    float shininess;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	vec3 color_diffuse1;
	vec3 color_specular1;
	bool useTexture;
};

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
  
	float constant;
    float linear;
    float quadratic; 

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 16

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int activePointLights = 0;

vec3 materialDiffuse;
vec3 materialSpecular;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32/*mat.sh*/);
    // combine results
    vec3 ambient  = light.ambient  * materialDiffuse;
    vec3 diffuse  = light.diffuse  * diff * materialDiffuse;
    vec3 specular = light.specular * spec * materialSpecular;
    //return (ambient + diffuse);
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32/*mat.sh*/);

	float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

	vec3 ambient  = light.ambient  * materialDiffuse;
    vec3 diffuse  = light.diffuse  * diff * materialDiffuse;
    vec3 specular = light.specular * spec * materialSpecular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
	if(material.useTexture)
	{
		materialDiffuse = vec3(texture(material.texture_diffuse1, TexCoords));
		materialSpecular = vec3(texture(material.texture_specular1, TexCoords));
	}
	else
	{
		materialDiffuse = material.color_diffuse1;
		materialSpecular = material.color_specular1;
	}
		

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 result = CalculateDirectionalLight(directionalLight, Normal, viewDir);

	for(int i = 0; i < activePointLights; ++i)
		result+=CalculatePointLight(pointLights[i], viewDir);

	FragColor = vec4(result, 1.0);
	//FragColor = vec4(material.color_diffuse1, 1.0);
}