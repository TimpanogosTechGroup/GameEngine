#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 vertexColor;
in vec2 texCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos; // Camera position
uniform sampler2D texture1;

void main()
{
    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    //float specularStrength = 2.5;
    //vec3 viewDir = normalize(viewPos - FragPos); // If specular seems to be showing up on the wrong side, remember the camera position and actual location are in opposite directions
    //vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //float spec = 1;
    //vec3 specular = specularStrength * spec * lightColor;

	//vec3 halfwayDir = normalize(lightDir + viewDir);  
 //   spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	//vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse) * vertexColor;
    //FragColor = vec4(result, 1.0);
	FragColor = vec4(result, 1.0);
	//FragColor = vec4(vertexColor, 1.0);
}