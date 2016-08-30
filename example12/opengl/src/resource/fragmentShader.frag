#version 330 core

in vec3 Normal;
in vec3 fragPos;
 
out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 lightColor;
uniform vec3 objectColor; 

void main() 
{
	//ambient
	float ambientStrenth = 0.1;
	vec3 ambient = ambientStrenth * lightColor;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflecDir, viewDir), 0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	color = vec4(result,1); 
}