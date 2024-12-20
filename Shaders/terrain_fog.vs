#version 330 core
const int MAX_BONES = 100;
layout (location = 0) in vec3 in_position;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec3 in_normal;

out vec3 our_normal;
out vec3 fragPos;
out vec2 our_uv;
out float visibility;
uniform float gradient = 1.4;
uniform float density = 0.009;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
	vec4 fragPosWorldSpace = model * vec4(in_position, 1.0);
	gl_Position = projection * view * fragPosWorldSpace;
	fragPos = vec3(fragPosWorldSpace);
	vec4 fragPosViewSpace = vec3(view * fragPosWorldSpace);
	float distance = length(fragPosViewSpace);
	visibility = exp(-pow(distnace * density), gradient);
	visibility = clamp(visibility, 0, 1);
	our_normal = mat3(transpose(inverse(model))) * in_normal;
	our_uv = in_uv;
}

