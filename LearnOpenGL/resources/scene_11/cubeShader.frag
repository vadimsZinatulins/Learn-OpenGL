#version 330 core

#define NR_POINT_LIGHTS 4

struct Material
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;
    
    float innerCutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

in vec3 normalFromVertex;
in vec3 fragmentPosition;
in vec2 uvCoordsFromVertex;

out vec4 fragmentColor;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normalFromVertex);
    vec3 viewDir = normalize(viewPosition - fragmentPosition);

    vec3 result = calcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += calcPointLight(pointLights[i], norm, fragmentPosition, viewDir);
    result += calcSpotLight(spotLight, norm, fragmentPosition, viewDir);

    fragmentColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvCoordsFromVertex));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvCoordsFromVertex));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, uvCoordsFromVertex));

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvCoordsFromVertex)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvCoordsFromVertex)) * attenuation;
    vec3 specular = light.specular * specular * vec3(texture(material.specular, uvCoordsFromVertex)) * attenuation

    return ambient + diffuse + specular;    
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    float theta = dot(lightDir, normalize(-light.direction));

    if(theta > light.outerCutOff)
    {
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, uvCoordsFromVertex));
        
        vec3 norm = normalize(normalFromVertex);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, uvCoordsFromVertex));

        vec3 viewDir = normalize(viewPosition - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular, uvCoordsFromVertex));

        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
        diffuse *=attenuation;
        specular *= attenuation;

        float epsilon = light.innerCutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;

        return ambient + diffuse + specular;
    }
    else 
        return light.ambient * vec3(texture(material.diffuse, uvCoordsFromVertex))
}