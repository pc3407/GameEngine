#pragma once

#include <assert.h>
#include <windows.h>
#include <crtdbg.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <dxgi1_2.h>
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#include <DirectXMath.h>
using namespace DirectX;

#define SAFE_RELEASE(p)     { if(p) { (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p)      { if(p) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAR(p){ if(p) { delete [] (p); (p) = NULL; } }