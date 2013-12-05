uniform sampler2D tex;

varying vec4 texCoord;

void main() {
	gl_FragColor = texture2D( tex, texCoord.st );
}