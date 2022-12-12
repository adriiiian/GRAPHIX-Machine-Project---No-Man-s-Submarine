#version 330 core //version

uniform sampler2D tex0;
uniform sampler2D norm_tex;

uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 lightColorDir;

uniform float ambientStrDir;
uniform vec3 ambientColorDir;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

void main(){
	
	vec4 pixelColor = texture(tex0, texCoord);
	vec3 normal = texture(norm_tex, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	//vec3 normal = normalize(normCoord);
	vec3 lightDir = normalize(-lightDirection);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 diffuse = diff * lightColor;

	vec3 ambientCol = ambientStr * ambientColor;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.1f), specPhong);

	vec3 specCol = spec * specStr * lightColor;



	FragColor = vec4(specCol + diffuse + ambientCol, 1.0) * pixelColor;
}