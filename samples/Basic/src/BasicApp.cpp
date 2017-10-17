#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderImGui.h"
#include "CinderRemoteImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

    int mIntVar;
    string mStringVar;
};

void BasicApp::setup()
{
    mIntVar = 100;
    mStringVar = "String Input";

    ui::initialize();
    remoteui::initialize( "0.0.0.0", 7002 );
    remoteui::setEnabled( true );
}

void BasicApp::mouseDown( MouseEvent event )
{
}

void BasicApp::update()
{
    ui::DragInt( "Int", &mIntVar );
    ui::InputText( "String", &mStringVar );
}

void BasicApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( BasicApp, RendererGl )
