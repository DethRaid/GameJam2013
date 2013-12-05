#include "stdafx.h"
#include "Camera.h"

Camera::Camera(void) {
	fov = 60;
	nearClip = 0.01f;
	farClip = 1000;
	setPosition( Vector3( 22.4572, -12.2379, 12.7525 ) );
	setRotation( Vector3( 28, -48, -.1 ) );
	//setPosition( 0, -75, 0 );
	//setRotation( Vector3( 90, 0, 0 ) );
	glDisable( GL_CULL_FACE );
}

Camera::~Camera(void) {}

Camera::Camera( float newFOV, int newScreenX, int newScreenY, Vector3 pos, Vector3 rot ) : transform( pos, rot ) {
	fov = newFOV;
	screenX = newScreenX;
	screenY = newScreenY;
	aspectRatio = float(screenX)/float(screenY);
	nearClip = 0.01f;
	farClip = 1000;
	setPosition( Vector3( 22.4572, -12.2379, 12.7525 ) );
	setRotation( Vector3( 28, -48, -.1 ) );
	genMatrixes();
}

void Camera::setPosition( Vector3 pos ) {
	transform.setPosition( pos );
	genMatrixes();
}

void Camera::setPosition( float newX, float newY, float newZ ) {
	transform.setPosition( newX, newY, newZ );
	genMatrixes();
}

void Camera::moveBy( Vector3 dist ) {
	transform.moveBy( dist );
	genMatrixes();
}

void Camera::setRotation( Vector3 rot ) {
	transform.setRotation( rot );
	genMatrixes();
}

void Camera::rotateBy( Vector3 rot ) {
	transform.rotate( rot );
	genMatrixes();
}

void Camera::lookAt( Vector3 pos ) {
	camTarget = pos;
	gluLookAt( transform.getPosition().getX(), transform.getPosition().getY(), transform.getPosition().getZ(),
		camTarget.getX(), camTarget.getY(), camTarget.getZ(),
		0, 1, 0 );
	GLfloat *matrixPointer = new GLfloat[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, matrixPointer );
	projectionMatrix = floatsToMatrix( matrixPointer );
	glGetFloatv( GL_PROJECTION_MATRIX, matrixPointer );
	viewMatrix = floatsToMatrix( matrixPointer );
}

void Camera::setFarClip( float newFarClip ) {
	farClip = newFarClip;
	genMatrixes();
}

void Camera::setNearClip( float newNearClip ) {
	nearClip = newNearClip;
	genMatrixes();
}

void Camera::setFOV( float newFOV ) {
	fov = newFOV;
	genMatrixes();
}

void Camera::setAspectRatio( float newAR ) {
	aspectRatio = newAR;
	genMatrixes();
}

void Camera::setScreenX( int newScreenX ){
	screenX = newScreenX;
	aspectRatio = float(screenX)/float(screenY);
	genMatrixes();
}

void Camera::setScreenY( int newScreenY ) {
	screenY = newScreenY;
	aspectRatio = float(screenX)/float(screenY);
	genMatrixes();
}

void Camera::genMatrixes() {
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	gluPerspective( fov, aspectRatio, 0.01f, 100 );
	GLfloat *matrixPointer = new GLfloat[16];
	for ( int i = 0; i < 16; i++ ) {
		matrixPointer[i] = 0;
	}
	glGetFloatv( GL_MODELVIEW_MATRIX, matrixPointer );
	projectionMatrix = floatsToMatrix( matrixPointer );
	//projectionMatrix.a1 = atan( fov/2 )/aspectRatio;
	//projectionMatrix.b2 = atan( fov/2 );
	//projectionMatrix.c3 = farClip / (farClip - nearClip);
	//projectionMatrix.c4 = 1;
	//projectionMatrix.d3 = (farClip * nearClip)/(farClip - nearClip);

	glLoadIdentity();
	glTranslatef( transform.getPosition().getX(), transform.getPosition().getY(), transform.getPosition().getZ() );
	glGetFloatv( GL_MODELVIEW_MATRIX, matrixPointer );
	viewMatrix = floatsToMatrix( matrixPointer );
	//viewMatrix.a4 = transform.getPosition().getX();
	//viewMatrix.b4 = transform.getPosition().getY();
	//viewMatrix.c4 = transform.getPosition().getZ();
	glPopMatrix();
}

void Camera::setMatricies() {
	glMatrixMode( GL_MODELVIEW );
	glLoadMatrixf( matrixToFloats( viewMatrix ) );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( matrixToFloats( projectionMatrix ) );
}

void Camera::setActive() {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( fov, float(screenX)/float(screenY), 0.01, 1000 );
	glViewport( 0, 0, screenX, screenY );
}

void Camera::prepare() {
	Vector3 position = transform.getPosition();
	Vector3 rotation = transform.getRotation();
	glRotatef( rotation.getX(), 1, 0, 0 );
	glRotatef( rotation.getY(), 0, 1, 0 );
	glRotatef( rotation.getZ(), 0, 0, 1 );
	glTranslatef( -position.getX(), position.getY(), -position.getZ() );
}

Vector3 Camera::screenToWorldPoint( Vector3 mousePos ) {
	//OpenGL code. Producing weird results
	GLdouble retX, retY, retZ;
	int viewPort[] = {0, 0, screenX, screenY};
	const float *modelMatrix = matrixToFloats( viewMatrix );
	const float *projMatrix = matrixToFloats( projectionMatrix );
	GLdouble *dModelMatrix = new GLdouble[16];
	GLdouble *dProjMatrix = new GLdouble[16];
	for( int i = 0; i < 16; i++ ) {
		dModelMatrix[i] = modelMatrix[i];
		dProjMatrix[i] = projMatrix[i];
	}
	gluUnProject( mousePos.getX(), mousePos.getY(), mousePos.getZ(),
		dModelMatrix, dProjMatrix, viewPort,
		&retX, &retY, &retZ );

	//My code. It's better.
	float msx = 2 * float(mousePos.getX())/float(screenX) - 1;
	float msy = 1 - 2 * float(mousePos.getY())/float(screenY);

	aiMatrix4x4 inv = (projectionMatrix * viewMatrix).Inverse();
	float newX = msx*inv.a1;
	float newY = msy*inv.b2;

	return Vector3( newX, 0, newY );
}

Transform& Camera::getTransform() {
	return transform;
}

aiMatrix4x4& Camera::getProjectionMatrix() {
	return projectionMatrix;
}

aiMatrix4x4& Camera::getViewMatrix() {
	return viewMatrix;
}