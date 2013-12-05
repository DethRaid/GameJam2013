varying vec3 eyeNormal;
varying vec3 cameraDir;

uniform vec3 cameraPos;

void main() {
	eyeNormal = normalize( gl_NormalMatrix * gl_Normal );
	gl_Position = ftransform();
	cameraDir = cameraPos - gl_Position.xyz;
}