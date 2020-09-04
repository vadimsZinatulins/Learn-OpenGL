#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct Light
{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 normalFromVertex;
in vec3 fragmentPosition;
in vec2 uvCoordsFromVertex;

out vec4 fragmentColor;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvCoordsFromVertex));
    
    vec3 norm = normalize(normalFromVertex);
    vec3 lightDir = normalize(light.position - fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvCoordsFromVertex));

    vec3 viewDir = normalize(viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, uvCoordsFromVertex));

    float distance = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    ambient *= attenuation;
    diffuse *=attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    fragmentColor = vec4(result, 1.0);
}
