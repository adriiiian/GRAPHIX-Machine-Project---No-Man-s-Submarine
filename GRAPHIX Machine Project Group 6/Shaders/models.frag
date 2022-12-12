#version 330 core //version

uniform sampler2D tex0;
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


uniform vec3 pointLightPos;
uniform vec3 pointLightColor;

uniform vec3 pointAmbientColor;

uniform float pointSpecStr;
uniform float pointSpecPhong;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

out vec4 FragColor;

void main(){

	vec3 normal = normalize(normCoord);

	// DIRECTION LIGHT
	vec3 lightDir = normalize(-lightDirection);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 diffuse = diff * lightColor;

	vec3 ambientCol = ambientStr * ambientColor;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.1f), specPhong);

	vec3 specCol = spec * specStr * lightColor;

	//vec3 result = specCol + diffuse + ambientCol;

	// POINT LIGHT
	vec3 pointLightDir = normalize(pointLightPos - fragPos);

	float pointDiff = max(dot(normal, pointLightDir), 0.0);

	vec3 pointDiffuse = pointDiff * pointLightColor;

	vec3 pointAmbientCol = pointAmbientStr * pointAmbientColor;

	vec3 pointViewDir = normalize(cameraPos - fragPos);
	vec3 pointReflectDir = reflect(-pointLightDir, normal);

	float pointSpec = pow(max(dot(pointReflectDir, pointViewDir), 0.1f), pointSpecPhong);

	vec3 pointSpecCol = pointSpec * pointSpecStr * pointLightColor;

	//result += pointSpecCol + pointDiffuse + pointAmbientCol;

	// Gets the distance of the light position and the fragment.
	float distance = length(pointLightPos - fragPos);
	// Gets the intensity by computing the inverse of the distance with the source squared.
	float intensity = 1.0 / (1.0 + 0.01 * distance + 0.001 * (distance * distance));
	//float intensity = 1.0 / (1.0 + 0.25 * distance);
	pointSpecCol *= intensity;
	pointDiffuse *= intensity;
	pointAmbientCol *= intensity;

	pointSpecCol *= texture(tex0, texCoord);
	pointDiffuse *= texture(tex0, texCoord);
	pointAmbientCol *= texture(tex0, texCoord);

	specCol *= texture(tex0, texCoord);
	diffuse *= texture(tex0, texCoord);
	ambientCol *= texture(tex0, texCoord);

	vec3 result = specCol + diffuse + ambientCol;
	result += pointSpecCol + pointDiffuse + pointAmbientCol;

	//FragColor = vec4(pointSpecCol + pointDiffuse + pointAmbientCol) * vec4(specCol + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);
	//FragColor = vec4(specCol + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);
	//FragColor = (vec4(pointSpecCol + pointDiffuse + pointAmbientCol) * texture(tex0, texCoord))  + (vec4(specCol + diffuse + ambientCol, 1.0) * texture(tex0, texCoord));
	FragColor = vec4(result, 1.0);
}