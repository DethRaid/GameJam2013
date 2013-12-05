varying vec3 eyeNormal;
varying vec3 cameraDir;

uniform vec3 diffuseUpload;

void main() {
	float colorFac = 1.0 - dot( eyeNormal, cameraDir );
	gl_FragColor = vec4( diffuseUpload, 1 );//vec4( eyeNormal, 1 );// * colorFac;
}