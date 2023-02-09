
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include "EffekseerForDXLib.h"

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _lpInstance; }
	virtual int GetKey1P() { return _gKey1P; }
	virtual int GetTrg1P() { return _gTrg1P; }
	virtual int GetKey2P() { return _gKey2P; }
	virtual int GetTrg2P() { return _gTrg2P; }
	virtual int GetKeyEf() { return _gKeyEf; }
	virtual int GetTrgEf() { return _gTrgEf; }

protected:
	static	ApplicationBase	*_lpInstance;

	int		_gKey1P, _gTrg1P;
	int		_gKey2P, _gTrg2P;
	int   _gKeyEf, _gTrgEf;

	ModeServer* _serverMode;

};
