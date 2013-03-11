#include "cinder/ObjLoader.h"
#include "cinder/app/AppBasic.h"
//This must be defined after AppBasic
#include "cinder/Arcball.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/params/Params.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "cinder/Camera.h"
#include "cinder/gl/Vbo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/*
    Uncomment one of these below to run that example

        helloworld:             basic shader example
        helloworld_color:       basic example with color passed in from OpenGL gl_Color
        helloworld_uniform:     basic example with color passed in through a uniform variable
        flatten:                modify the z coordinate of the vertex to flatten the image
*/

//#define _use_helloworld
#define _use_helloworld_color
//#define _use_helloworld_uniform
//#define _use_flatten
//#define _use_flatten_wiggle


class BasicShaderApp : public AppBasic {
public:
	void prepareSettings(Settings *settings);
	void setup();
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );    
	void resize( ResizeEvent event );
	void update();
	void draw();
	
private:
	void saveFrame();
	params::InterfaceGl mParams;
	
	bool 		mDoSave;
	CameraPersp mCam;
	Vec3f		mEye, mTarget;
    Color       mKettleColor;
    
	Arcball			mArcball;    
	TriMesh			mMesh;
	gl::VboMesh		mVBO;
	gl::GlslProg	mShader;    
    
};

void BasicShaderApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize( 1024, 768 );
	settings->setTitle("BasicShader");
}

void BasicShaderApp::setup()
{
    //load up an obj file into a mesh
	ObjLoader loader( (DataSourceRef)loadResource( RES_TEAPOT_OBJ ) );
    loader.load( &mMesh );
    //read it into a VBO that we can push to the GPU...    
    mVBO = gl::VboMesh( mMesh);    
        
    //Load up some shaders
#ifdef _use_helloworld
	mShader = gl::GlslProg( loadResource( RES_HELLOWORLD_VERT ), loadResource( RES_HELLOWORLD_FRAG ) );    
#endif
    
#ifdef _use_helloworld_uniform
	mShader = gl::GlslProg( loadResource( RES_HELLOWORLD_UNI_VERT ), loadResource( RES_HELLOWORLD_UNI_FRAG ) );    
#endif

#ifdef _use_helloworld_color
	mShader = gl::GlslProg( loadResource( RES_HELLOWORLD_COLOR_VERT ), loadResource( RES_HELLOWORLD_COLOR_FRAG ) );    
#endif
    
#ifdef _use_flatten
	mShader = gl::GlslProg( loadResource( RES_FLATTEN_VERT ), loadResource( RES_FLATTEN_FRAG ) );        
#endif
    
#ifdef _use_flatten_wiggle
	mShader = gl::GlslProg( loadResource( RES_FLATTEN_WIGGLE_VERT ), loadResource( RES_FLATTEN_WIGGLE_FRAG ) );        
#endif
    
    

    //bind the shader to the GPU
    mShader.bind();
    
	mDoSave = false;
    
	mParams = params::InterfaceGl( "Settings", Vec2i( 200, 200 ) );
	
	mParams.addParam( "Camera X", &mEye.x, "step=1" );
	mParams.addParam( "Camera Y", &mEye.y, "step=1" );
	mParams.addParam( "Camera Z", &mEye.z, "step=1" );
	mParams.addParam( "Target X", &mTarget.x, "step=1" );
	mParams.addParam( "Target Y", &mTarget.y, "step=1" );
	mParams.addParam( "Target Z", &mTarget.z, "step=1" );
    
#ifdef _use_helloworld_color
    mParams.addParam( "Color", &mKettleColor );
#endif
	mEye = Vec3f( 0, 0, -200.0f );
	mTarget = Vec3f( 0, 0, 0 );
	mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 5000.0f );    
	
    mCam.lookAt( mEye, mTarget, -Vec3f::yAxis() );	
    
    mKettleColor = Color::white();
    

}

void BasicShaderApp::keyDown( KeyEvent event )
{
	switch( event.getChar() ){
		case 's':
			mDoSave = true;
			break;
		case 'f':
			setFullScreen( !isFullScreen() );
			break;
		default:
		break;
	}
}

void BasicShaderApp::mouseDown( MouseEvent event )
{
    mArcball.mouseDown( event.getPos() );    
}

void BasicShaderApp::mouseDrag( MouseEvent event )
{
    mArcball.mouseDrag( event.getPos() );    
}


void BasicShaderApp::resize( ResizeEvent event )
{   
	mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 5000.0f );
	mArcball.setWindowSize( getWindowSize() );
	mArcball.setCenter( Vec2f( getWindowWidth() / 2.0f, getWindowHeight() / 2.0f ) );
	mArcball.setRadius( 150 );
    
}

void BasicShaderApp::update()
{
	mCam.lookAt( mEye, mTarget, -Vec3f::yAxis() );
}

void BasicShaderApp::draw()
{
	gl::clear( Color::black() ); 
	gl::setMatrices( mCam );
	
	// draw interface
	params::InterfaceGl::draw();
	
	if( mDoSave )
	{	// save non-conflicting image
		// includes interface to record parameters
		saveFrame();
		mDoSave = false;
	}
    
    
    gl::color( Color(1,1,0) ); //Color::white() );
#ifdef _use_helloworld_color
    gl::color( mKettleColor );    
#endif

    mShader.bind();
    
#ifdef _use_helloworld_uniform         
    Vec2i pos = getMousePos();
    float nx = lerp(0.f, 1.f, float( pos.x )/ getWindowWidth() );    
    float ny = lerp(0.f, 1.f, float( pos.y )/ getWindowHeight() );   
    
    Vec2f gobbedygook(nx,ny);
    mShader.uniform("nmouse", gobbedygook );   
#endif

    gl::pushMatrices();
    gl::rotate( mArcball.getQuat() );
    gl::draw( mVBO );
    gl::popMatrices();
    mShader.unbind();
     
//     */
    
    /*
    // Set color through OpenGL state
    gl::color( clr ); //Color::white() );
    */
    
    
    /* 
     //basic hello world
    mShader.bind();
	gl::pushMatrices();
    gl::rotate( mArcball.getQuat() );
    
    gl::draw( mVBO );
    gl::popMatrices();
    mShader.unbind();
     */
    
}

void BasicShaderApp::saveFrame()
{
	// path works for me, might not for you
//	writeImage( getUniquePath( getAppPath() + "../../../../../../screengrabs/BasicShader.png" ), copyWindowSurface() );
}


CINDER_APP_BASIC( BasicShaderApp, RendererGl )
