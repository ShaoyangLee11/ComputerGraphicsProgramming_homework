#version 430

layout(location=0) in vec3 Position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;

void main(void){
	gl_Position = proj_matrix * mv_matrix * vec4(Position,1.0);
	varyingColor = vec4(Position,1.0) * 0.5 + vec4(0.5,0.5,0.5,0.5);
}
