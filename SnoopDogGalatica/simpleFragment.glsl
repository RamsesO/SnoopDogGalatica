/* 
SimpleFragment.glsl

Fragment shader with color input and output.

Mike Barnes
8/16/2014
*/

# version 330 core

// uniform float Shininess;
// uniform float Strength;
uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 EyeDirection;
uniform vec3 LightPosition; // point light position
uniform vec3 SLightPosition; // spot light position

uniform float PStrength;
uniform float DStrength;

uniform float SStrength;
uniform vec3 ConeDirection;
uniform float SpotCosCutoff;
uniform float SpotExponent;

in vec4 Color;
in vec3 Normal;
in vec4 Position;

out vec4 FragColor;

vec4 spotlight(){
	float Shininess = 1.0f;
	vec3 sLightColor = vec3(0.0f, 1.0f, 1.0f); //RED SPOT LIGHT!!
	vec3 lightDirection = SLightPosition - vec3(Position);
	float lightDistance = length(lightDirection);
	lightDirection = lightDirection/lightDistance;

	//no atteunation

	float spotCos = dot(lightDirection, -ConeDirection);

	vec3 halfVector = normalize(lightDirection + EyeDirection);

	float diffuse = max(0.0, dot(Normal, lightDirection));
	float specular = max(0.0, dot(Normal, halfVector));

	if(diffuse == 0.0)
		specular = 0.0;
	else  
		specular = pow(specular, Shininess) * SStrength;

	vec3 scatteredLight = Ambient + sLightColor * diffuse;
	vec3 reflectedLight = sLightColor * specular;
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));

	//return vec4(rgb, Color.a);
	return vec4(0, 0, 0, 0);
}


vec4 pointlight(){
	// vec3 Ambient = vec3(0.2f, 0.2f, 0.2f);
	// vec3 LightColor = vec3(1.0f, 1.0f, 1.0f);
	float Shininess = 0.5f;
	//float Strength = 0.2f;
	
	vec3 lightDirection = normalize(LightPosition - vec3(Position));
	float lightDistance = length(lightDirection);

	vec3 halfVector = normalize(lightDirection + EyeDirection);
	float diffuse = max(0.0, dot(Normal, lightDirection));
	float specular = max(0.0, dot(Normal, halfVector));

	if(diffuse == 0.0){
		specular = 0.0;
	}
	else
		specular = pow(specular, Shininess) * PStrength;

	vec3 scatteredLight =  Ambient + LightColor * diffuse;
	vec3 reflectedLight = LightColor * PStrength;
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	return vec4(rgb, Color.a);
	
}
vec4 directionlight(){
	// vec3 Ambient = vec3(0.2f, 0.2f, 0.2f);
	vec3 lightColor = vec3(1.0f, 1.0f, 0.0f);
	float Shininess = 0.5f;
	//float Strength = 0.1f;
	
	vec3 lightDirection = normalize(EyeDirection);

	vec3 halfVector = normalize(lightDirection + EyeDirection);
	float diffuse = max(0.0f, dot(Normal, lightDirection));
	float specular = max(0.0f, dot(Normal, halfVector));

	if(diffuse == 0.0){
		specular = 0.0f;
		//diffuse = 0.7f;
		//LightColor = vec3(0.0f, 0.0f, 1.0f);
	}
	else{
		specular = pow(specular, Shininess) * DStrength;
	}

	vec3 scatteredLight =  Ambient + lightColor * diffuse;
	vec3 reflectedLight = lightColor * DStrength;
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	return vec4(rgb, Color.a);

}
void main(){
	FragColor += directionlight();
	FragColor += pointlight();
	FragColor += spotlight();

}