#version 330 core
out vec4 FragColor;
  
//in vec3 ourColor;
in vec2 TexCoord;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixValue;

void main()
{
	vec4 tex = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), mixValue);

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = mix(tex, vec4(result, 1.0), 0.7);
}