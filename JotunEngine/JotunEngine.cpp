// JotunEngine.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "JotunEngine.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
void EnableOpenGL( HWND hWnd, HDC *hDC, HGLRC *hRC );
void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC );
void				makeFullscreen();
void				initOpenGL();
void				renderStartScreen();
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void				init();
void				update();
void				drawSplashScreen();
void				draw();
void				makeMoreNikkies( int num );

enum MISSILEMODE {
	reg = 0,
	throwy = 1,
	big = 2,
	timey = 3,
	nuke = 4
};

HGLRC hRC;
HWND hWnd;
HDC hDC;
HINSTANCE hInstance;

GLuint shadowMapGLID;
GLuint shadowFBOGLID;

int width, height, nikkiesNeeded, nikkyDeaths;
std::vector<Nikky*> nikkies;
std::vector<Missile*> missiles;
std::vector<Explosion*> explosions;
std::ofstream out( "debug.txt" );
Camera mainCamera;
RenderMesh *console;
ConsoleLight *lights;
Terrain *terrain;
MissileMarker *p1, *p2;
int p1mMode, p2mMode;
float timer;
bool startScreen;
Nikky *nicholas;
RenderMesh *_floor;
TemporalWarpField *tWF;

void init() {
	startScreen = true;
	lights = new ConsoleLight[5];
	for( int i = 0; i < 5; i++ ) {
		lights[i] = ConsoleLight( i+1 ) ;
	}
	p1mMode = MISSILEMODE::reg;
	p2mMode = MISSILEMODE::reg;
	nikkiesNeeded = 4;
	makeFullscreen();
	terrain = new Terrain();
	console = new RenderMesh( "Console.obj", "Diffuse" );
	TextureList::addTexture( "Console.png" );
	console->giveTex( TextureList::getTextureByName( "Console.png" ) );
	_floor = new RenderMesh( "Plane.obj", "Diffuse" );
	TextureList::addTexture( "Blot.png" );
	_floor->giveTex( TextureList::getTextureByName( "Blot.png" ) );
	p1 = new MissileMarker( 0 );
	p2 = new MissileMarker( 1 );
	out<<"Initialized stuff\n";
	makeMoreNikkies( nikkiesNeeded );
	nicholas = new Nikky();
	PlaySound( L"NikkyIntro.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT );
	timer = 0;
}

float camFOV = 70;

void renderStartScreen() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( camFOV, 1.7, 0.01, 20 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	if( timer < 3 ) {
		glTranslatef( 0, -1, -1.2 );
		glRotatef( -135, 0, 1, 0 );
	} else {
		glTranslatef( 0, -1.5, -.35 );
		glRotatef( 45, 0, 1, 0 );
	}
	nicholas->setShader();
	_floor->draw();
	nicholas->draw();
	glPopMatrix();
}

void updateStartScreen() {
	Time::update();
	timer += Time::deltaTime;
	if( timer < 3 ) {
		camFOV -= 0.025;
	} 
}

void initOpenGL() {
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
	glClearDepth( 1.0 );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glEnable( GL_LIGHTING );
	glShadeModel( GL_SMOOTH );
	glViewport( 0, 0, width, height );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void drawSplashScreen() {
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	Shaders::getShaderByName( "Diffuse" )->bind();
	TextureList::addTexture( "Splash.png" );
	TextureList::getTextureByName( "Splash.png" )->bind();
	glMatrixMode( GL_PROJECTION );
	glOrtho(-1, 1, -1, 1, 0.01, 3 );
	glColor4f( 1, 0, 0, 1 );
	glBegin( GL_QUADS );
		glTexCoord2i( 0, 0 );
		glVertex3i( -1, -1, -1 );
		glTexCoord2i( 0, 1 );
		glVertex3i( -1, 1, -1 );
		glTexCoord2i( 1, 1 );
		glVertex3i( 1, 1, -1 );
		glTexCoord2i( 1, 0 );
		glVertex3i( 1, -1, -1 );
	glEnd();
}

void makeMoreNikkies( int num ) {
	for( ; num > 0; num-- ) {
		nikkies.push_back( NikkySpawner::newNikky() );
	}
}

void update() {
	lights[nikkyDeaths/50].activate();
	Time::update();
	timer += Time::deltaTime;
	if( timer > 20 ) {
		makeMoreNikkies( nikkiesNeeded );
		nikkiesNeeded++;
		if( nikkiesNeeded > 15 ) {
			nikkiesNeeded = 15;
		}
		timer = 0;
	}
	if( tWF != NULL ) {
		for( Nikky *n : nikkies ) {
			if( Vector3::distance( n->getTransform().getPosition(), 
				tWF->getTransform().getPosition() ) <
				tWF->getRange() ) {
					n->getTransform().moveBy( Vector3( .5581/2, 0, -.8297/2 ) * Time::deltaTime );
			}
		}
	}
	p1->update();
	p2->update();
	//player0 uses m to fire, player 1 uses e
	if( Input::z ) {
		p1mMode = 0;
	} else if( Input::x ) {
		p1mMode = 1;
	} else if( Input::c ) {
		p1mMode = 2;
	} else if( Input::v ) {
		p1mMode = 3;
	} else if( Input::b ) {
		p1mMode = 4;
	}
	if( Input::r || Input::n ) {
		lights[p1mMode].deselect();
		p1mMode++;
		if( p1mMode == 5 ) {
			p1mMode = 0;
		}
		if( p1mMode > nikkyDeaths/50 ) {
			p1mMode  = nikkyDeaths/50;
		}
		lights[p1mMode].deselect();
	}
	if( Input::m ) {
		Missile *m;
		if( p1mMode == MISSILEMODE::reg ) {
			m = new Missile( p1->getTransform().getPosition() );
			missiles.push_back( m );
		} else if( p1mMode == MISSILEMODE::throwy ){
			m = new ThrowyMissile( p1->getTransform().getPosition() );
		} else if( p1mMode == MISSILEMODE::big ){
			m = new BigMissile( p1->getTransform().getPosition() );
		} else if( p1mMode == MISSILEMODE::timey ){
			m =  new TimeyMissile( p1->getTransform().getPosition() );
		}  else if( p1mMode == MISSILEMODE::nuke ){
			m = new NuclearMissile( p1->getTransform().getPosition() );
		} 
		missiles.push_back( m );
	}
	if( Input::e ) {
		Missile *m;
		if( p1mMode == MISSILEMODE::reg ) {
			m = new Missile( p2->getTransform().getPosition() );
		} else if( p1mMode == MISSILEMODE::throwy ) {
			m = new ThrowyMissile( p2->getTransform().getPosition() );
		} else if( p1mMode == MISSILEMODE::big ) {
			m = new BigMissile( p2->getTransform().getPosition() );
		} else if( p1mMode == MISSILEMODE::timey ){
			m = new TimeyMissile( p1->getTransform().getPosition() );
		}  else if( p1mMode == MISSILEMODE::nuke ){
			m = new NuclearMissile( p1->getTransform().getPosition() );
		} 
		missiles.push_back( m );
	}
	for( int i = 0; i < nikkies.size(); i++ ) {
		nikkies[i]->update();
		Vector3 nikkyPos = nikkies[i]->getTransform().getPosition();
		int j;
		if( nikkyPos.getX() > 65 || nikkyPos.getX() < -65 ||
			nikkyPos.getZ() > 65 || nikkyPos.getZ() < -65 ||
			nikkyPos.getY() < -10 || nikkies[i]->getHealth() < 0 ) {
			Nikky *n = nikkies[i];
			nikkies.erase( nikkies.begin() + i );
			delete n;
			nikkyDeaths++;
		}
	}
	for( int i = 0; i < missiles.size(); i++ ) {
		missiles[i]->update();
		if( missiles[i]->getTransform().getPosition().getY() < 0 ) {
			Missile *m = missiles[i];
			explosions.push_back( new Explosion( m->getTransform().getPosition() ) );

			Vector3 boomPos = m->getTransform().getPosition();
			Vector3 distToNikky;
			for( Nikky *n : nikkies ) {
				distToNikky = Vector3( n->getTransform().getPosition().getX() - boomPos.getX(),
					n->getTransform().getPosition().getY() - boomPos.getY(),
					n->getTransform().getPosition().getZ() - boomPos.getZ() );
				if( distToNikky.magnitude() < m->getRange() ) {
					n->loseHealth( m->getDamage() * distToNikky.magnitude()/m->getRange() );
					n->giveForce( distToNikky.normalized() * m->getForce() );
				}
			}

			if( m->type == MISSILEMODE::timey ) {
				tWF = new TemporalWarpField( m->getTransform().getPosition() );
			}
			missiles.erase( missiles.begin() + i );
			//delete m;
			PlaySound( L"/Explosion.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT );
		}
	}
	for( int i = 0; i < explosions.size(); i++ ) {
		explosions[i]->update();
		if( explosions[i]->getTimer() > 2 ) {
			Explosion *e = explosions[i];
			explosions.erase( explosions.begin() + i );
			delete e;
		}
	}
}

void draw() {
	glEnable( GL_DEPTH_TEST );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	mainCamera.setActive();

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glScaled( 0.1, 0.1, 0.1 );
	mainCamera.prepare();

	terrain->draw();
	for( int i = 0; i < 5; i++ ) {
		lights[i].draw();
	}
	console->draw();

	for( RenderMesh *rm : nikkies ) {
		if( rm != NULL ) {
			rm->setShader();
			rm->draw();
		}
	}
	glDisable( GL_CULL_FACE );
	for( Missile *m : missiles ) {
		if( m != NULL ) {
			m->setShader();
			m->draw();
		}
	}
	glDisable( GL_DEPTH_TEST );
	for( Explosion *e : explosions ) {
		if( e != NULL ) {
			e->draw();
		}
	}
	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	p1->draw( mainCamera.getTransform().getPosition() );
	p2->draw( mainCamera.getTransform().getPosition() );
	glPopMatrix();
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow )
{
    WNDCLASS wc;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW ); 
    wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"Jotun Engine";
    RegisterClass( &wc );
	makeFullscreen();
    hWnd = CreateWindow( L"Jotun Engine", L"Jotun Engine",
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      -8, -32, width+16, height+40,
      NULL, NULL, hInstance, NULL );
    EnableOpenGL( hWnd, &hDC, &hRC );
	initOpenGL();
	drawSplashScreen();
	init();
	ShowCursor( false );
	Time::init();
	glClearColor( 1, 1, 1, 0 );
	timer = 0;
	bool firstRender = true;
	if( !PlaySound( L"NikkyIntro.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT ) ) {
				out<<"The sound dunn failed\n";
			} else {
				out<<"The sound played?\n";
			}
    while( !bQuit )
    {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
            if( msg.message == WM_QUIT ) {
                bQuit = TRUE;
			} else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
            }
		}
		if( startScreen ) {
			updateStartScreen();
			renderStartScreen();
			if( firstRender ) {
				timer = 0.0f;
				firstRender = false;
			}	else if( timer > 5 ) {
				startScreen = false;
				timer = 0;
			}
		} else  {
			glClearColor( 0, 1, 1, 0 );
			update();
			draw();
		}
		Sleep( 1 );
		SwapBuffers( hDC );
	}
	DisableOpenGL( hWnd, hDC, hRC );
	DestroyWindow( hWnd );
	return (int) msg.wParam;
}

DEVMODE getCurDeviceMode() {
	DEVMODE deviceMode;
	int maxWidth = -1;
	EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &deviceMode );
	return deviceMode;
}

void makeFullscreen() {
	DEVMODE dmScreenSettings = getCurDeviceMode();
	width = dmScreenSettings.dmPelsWidth;
	height = dmScreenSettings.dmPelsHeight;
	mainCamera.setScreenX( width );
	mainCamera.setScreenY( height );
	out<<"Set screen width and height to " <<width <<", " <<height <<"\n";
	ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN );
	ShowCursor( false );
}

void EnableOpenGL( HWND hWnd, HDC *hDC, HGLRC *hRC )
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC( hWnd );
    ZeroMemory( &pfd, sizeof(pfd) );
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( *hDC, &pfd );
    SetPixelFormat( *hDC, iFormat, &pfd );
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
	glewInit();
}

void DisableOpenGL( HWND hWnd, HDC hDC, HGLRC hRC )
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void clearKeys() {
	Input::a = false;
	Input::b = false;
	Input::c = false;
	Input::d = false;
	Input::e = false;
	Input::f = false;
	Input::g = false;
	Input::h = false;
	Input::i = false;
	Input::j = false;
	Input::k = false;
	Input::l = false;
	Input::m = false;
	Input::n = false;
	Input::o = false;
	Input::p = false;
	Input::q = false;
	Input::r = false;
	Input::s = false;
	Input::t = false;
	Input::u = false;
	Input::v = false;
	Input::w = false;
	Input::x = false;
	Input::y = false;
	Input::z = false;
	Input::enter = false;
	Input::up = false;
	Input::down = false;
	Input::right = false;
	Input::left = false;
	Input::mouse0 = false;
	Input::mouse1 = false;
	Input::mouse2 = false;
	Input::mouseWheelIn = false;
	Input::mouseWheelOut = false;
}

void onKeyDown( int key ) {
	clearKeys();
	out<<"Key " <<key <<" pressed\n";
	switch( key ) {
	case 'A':
		Input::a = true;
		break;
	case 'B':
		Input::b = true;
		break;
	case 'C':
		Input::c = true;
		break;
	case 'D':
		Input::d = true;
		break;
	case 'E':
		Input::e = true;
		break;
	case 'F':
		Input::f = true;
		break;
	case 'G':
		Input::g = true;
		break;
	case 'H':
		Input::h = true;
		break;
	case 'I':
		Input::i = true;
		break;
	case 'J':
		Input::j = true;
		break;
	case 'K':
		Input::k = true;
		break;
	case 'L':
		Input::l = true;
		break;
	case 'M':
		Input::m = true;
		break;
	case 'N':
		Input::n = true;
		break;
	case 'O':
		Input::o = true;
		break;
	case 'P':
		Input::p = true;
		break;
	case 'Q':
		Input::q = true;
		break;
	case 'R':
		Input::r = true;
		break;
	case 'S':
		Input::s = true;
		break;
	case 'T':
		Input::t = true;
		break;
	case 'U':
		Input::u = true;
		break;
	case 'V':
		Input::v = true;
		break;
	case 'W':
		Input::w = true;
		break;
	case 'X':
		Input::x = true;
		break;
	case 'Y':
		Input::y = true;
		break;
	case 'Z':
		Input::z = true;
		break;
	case VK_UP:
		Input::up = true;
		break;
	case VK_DOWN:
		Input::down = true;
		break;
	case VK_RIGHT:
		Input::right = true;
		break;
	case VK_LEFT:
		Input::left = true;
		break;
	case VK_RETURN:
		Input::enter = true;
		break;
	}
}

void onKeyUp( int key ) {
	switch( key ) {
	case 'A':
		Input::a = false;
		break;
	case 'B':
		Input::b = false;
		break;
	case 'C':
		Input::c = false;
		break;
	case 'D':
		Input::d = false;
		break;
	case 'E':
		Input::e = false;
		break;
	case 'F':
		Input::f = false;
		break;
	case 'G':
		Input::g = false;
		break;
	case 'H':
		Input::h = false;
		break;
	case 'I':
		Input::i = false;
		break;
	case 'J':
		Input::j = false;
		break;
	case 'K':
		Input::k = false;
		break;
	case 'L':
		Input::l = false;
		break;
	case 'M':
		Input::m = false;
		break;
	case 'N':
		Input::n = false;
		break;
	case 'O':
		Input::o = false;
		break;
	case 'P':
		Input::p = false;
		break;
	case 'Q':
		Input::q = false;
		break;
	case 'R':
		Input::r = false;
		break;
	case 'S':
		Input::s = false;
		break;
	case 'T':
		Input::t = false;
		break;
	case 'U':
		Input::u = false;
		break;
	case 'V':
		Input::v = false;
		break;
	case 'W':
		Input::w = false;
		break;
	case 'X':
		Input::x = false;
		break;
	case 'Y':
		Input::y = false;
		break;
	case 'Z':
		Input::z = false;
		break;
	case VK_UP:
		Input::up = false;
		break;
	case VK_DOWN:
		Input::down = false;
		break;
	case VK_RIGHT:
		Input::right = false;
		break;
	case VK_LEFT:
		Input::left = false;
		break;
	case VK_RETURN:
		Input::enter = false;
		break;
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	PVOID pulScrollLines = NULL;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUTBOX ), hWnd, About );
			break;
		case IDM_EXIT:
			DestroyWindow( hWnd );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
		break;
	case WM_KEYDOWN:
		out<<"Registering a key press\n";
		if( wParam ==  VK_ESCAPE ) {
			PostQuitMessage( 0 );
			break;
		} else {
			onKeyDown( wParam );
			break;
		}
	case WM_KEYUP:
		onKeyUp( wParam );
		break;
	case WM_LBUTTONDOWN:
		Input::mouse0 = true;
		break;
	case WM_LBUTTONUP:
		Input::mouse0 = false;
		break;
	case WM_MBUTTONDOWN:
		Input::mouse2 = true;
		break;
	case WM_MBUTTONUP:
		Input::mouse2 = true;
		break;
	case WM_RBUTTONDOWN:
		Input::mouse1 = true;
		break;
	case WM_RBUTTONUP:
		Input::mouse1 = false;
		break;
	case WM_MOUSEMOVE:
		Input::mousePosition.setX( GET_X_LPARAM( lParam ) );
		Input::mousePosition.setY( GET_Y_LPARAM( lParam ) );
		break;
	Input::mouseWheelIn = false;
	Input::mouseWheelOut = false;
	case WM_MOUSEWHEEL:
		SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, pulScrollLines, 0);
		if( &pulScrollLines > 0 ) {
			Input::mouseWheelIn = true;
		} else if( &pulScrollLines < 0 ) {
			Input::mouseWheelOut = true;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}