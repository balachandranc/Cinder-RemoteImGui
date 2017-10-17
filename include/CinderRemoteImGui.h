#pragma once

#include "cinder/app/App.h"

using std::string;

namespace remoteui
{
void    initialize( string localAddress, uint16_t websocketPort );
void    update();
void    draw();
bool    isEnabled();
void    setEnabled( bool enable );
} // namespace remoteui