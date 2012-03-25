/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	EFFECT3D.CPP				(c)	YoY'03						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						<d3d9.h>
#include						"effect3d.h"
#include						"table.h"
#include						"elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Aeffect3d::CI		= ACI("Aeffect3d",		GUID(0xE4EC7600,0x00009020), &Aobject::CI, 0, NULL);
EDLL ACI						Aeffect3dInfo::CI	= ACI("Aeffect3dInfo",	GUID(0xE4EC7600,0x00009021), &Aplugz::CI, 0, NULL);

EDLL ACI						Ainput3d::CI		= ACI("Ainput3d",		GUID(0xE4EC7600,0x00009022), &Aobject::CI, 0, NULL);
EDLL ACI						Ainput3dInfo::CI	= ACI("Ainput3dInfo",	GUID(0xE4EC7600,0x00009023), &Aplugz::CI, 0, NULL);

EDLL ACI						Aef3dSound::CI		= ACI("Aed3dSound",		GUID(0xE4EC7600,0x00009024), &Anode::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aeffect3d::Aeffect3d(QIID qiid, char *name, class Aobject *f, int x, int y) : Aobject(name, f, x, y, effect3dWIDTH, effect3dHEIGHT)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aeffect3d::~Aeffect3d()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Ainput3d::Ainput3d(QIID qiid, char *name, class Aobject *f, int x, int y) : Aobject(name, f, x, y, input3dWIDTH, input3dHEIGHT)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Ainput3d::~Ainput3d()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aef3dSound::Aef3dSound() : Anode("ef3dSound")
{
	memset(smpL, 0, sizeof(smpL));
	memset(smpR, 0, sizeof(smpR));
	memset(basL, 0, sizeof(smpL));
	memset(basR, 0, sizeof(smpR));
	memset(medL, 0, sizeof(smpL));
	memset(medR, 0, sizeof(smpR));
	memset(treL, 0, sizeof(smpL));
	memset(treR, 0, sizeof(smpR));
	bass=medium=treble=0.f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aef3dSound::~Aef3dSound()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aef3dInfo::Aef3dInfo()
{
	d3d=NULL;
	time=0;
	dtime=0;
	beat=0;
	dbeat=0;
	
	bm=blendFADE;
	
	power=0.f;
	color=0xffffffff;
	colorBoost=false;

	memset(in, 0, sizeof(in));	
	sound=NULL;
	
	input=NULL;
	effect=NULL;
	
	inputs=null;
	effects=null;
	current=-1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aef3dInfo::~Aef3dInfo()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////