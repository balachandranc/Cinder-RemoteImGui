#include "CinderRemoteImGui.h"

#include "cinder/Log.h"

#ifdef _WIN32
#include <winsock2.h>
#endif

#ifdef __APPLE__
#include <unistd.h>
#endif

#include "CinderImGui.h"
#include "imgui.h"
#include "imgui_remote.h"
#define VCANVAS_WIDTH  8192
#define VCANVAS_HEIGHT 8192

namespace {

class RUI
{
public:
    RUI();
    bool    isEnabled;
    ci::signals::Connection connPostDraw, connUpdate;
};

RUI::RUI()
{
    isEnabled = false;
}

static RUI sInstance;
}

namespace remoteui
{

void initialize( string localAddress, uint16_t websocketPort )
{
    ImGui::RemoteInit( localAddress.c_str(), (int) websocketPort );
}

void update()
{
    ImGui::RemoteUpdate();
    
    ImGui::RemoteInput input;
    if( ImGui::RemoteGetInput( input ) ) {
        ImGuiIO& io = ImGui::GetIO();
        for( int i = 0; i < 256; i++ ) {
            io.KeysDown[ i ] = input.KeysDown[ i ];
        }
        io.KeyCtrl = input.KeyCtrl;
        io.KeyShift = input.KeyShift;
        io.MousePos = input.MousePos;
        io.MouseDown[ 0 ] = ( input.MouseButtons & 1 );
        io.MouseDown[ 1 ] = ( input.MouseButtons & 2 ) != 0;
        io.MouseWheel += input.MouseWheelDelta / 1.0f;
    }
}

void draw()
{
    auto data = ImGui::GetDrawData();
    ImGui::RemoteDraw( data->CmdLists, data->CmdListsCount );
}

bool isEnabled()
{
    return sInstance.isEnabled;
}

void setEnabled( bool enable )
{
    if( sInstance.isEnabled == enable )
        return;
    if( enable ) {
        sInstance.connPostDraw = ci::app::getWindow()->getSignalPostDraw().connect( draw );
        sInstance.connUpdate = ci::app::App::get()->getSignalUpdate().connect( update );
    }
    else {
        sInstance.connPostDraw.disconnect();
        sInstance.connUpdate.disconnect();
    }
    sInstance.isEnabled = enable;
}

} // namespace remoteui