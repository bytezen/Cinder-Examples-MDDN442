#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicAppMDDNApp : public AppBasic {
  public:
	// Cinder will always call this function whenever the user drags the mouse
	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	// Cinder calls this function 30 times per second by default
	void draw();
    
	// This will maintain a list of points which we will draw line segments between
	list<Vec2f>		mPoints;
    
	void setup();
	void mouseUp( MouseEvent event );	
	void update();
    
    bool mouseDownHandler( MouseEvent event );
    Color mPressedColor, mDefaultColor, mCurrentColor;
};

void BasicAppMDDNApp::setup()
{
    mDefaultColor = Color::black();
    mCurrentColor = mDefaultColor;
    mPressedColor = Color( CM_HSV, Vec3f( 0.45f,0.10f, 0.45f) );
    registerMouseDown( this, &BasicAppMDDNApp::mouseDownHandler );
}

void BasicAppMDDNApp::mouseUp( MouseEvent event )
{
    mCurrentColor = mDefaultColor;
}

bool BasicAppMDDNApp::mouseDownHandler( MouseEvent event ) 
{
    mCurrentColor = mPressedColor;
    return true;
}

void BasicAppMDDNApp::mouseDrag( MouseEvent event )
{
	// add wherever the user drags to the end of our list of points
	mPoints.push_back( event.getPos() );
}

void BasicAppMDDNApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'f' )
		setFullScreen( ! isFullScreen() );
}



void BasicAppMDDNApp::update()
{
}

void BasicAppMDDNApp::draw()
{
	gl::setMatricesWindow( getWindowSize() );
	// this pair of lines is the standard way to clear the screen in OpenGL
	gl::clear( mCurrentColor );
    
	// We'll set the color to an orange color
	glColor3f( 1.0f, 0.5f, 0.25f );
	
	// now tell OpenGL we've got a series of points it should draw lines between
	glBegin( GL_LINE_STRIP );
	// iterate across our list of points, and pass each one to OpenGL
	for( list<Vec2f>::iterator pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter ) {
		glVertex2f( *pointIter );
	}
	// tell OpenGL to actually draw the lines now
	glEnd();
}


CINDER_APP_BASIC( BasicAppMDDNApp, RendererGl )
