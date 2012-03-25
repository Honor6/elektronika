/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"export.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	PROGRESS.CPP				(c)	YoY'05						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"progress.h"
#include						"interface.h"
#include						"resource.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL ACI						Aprogress::CI=ACI("Aprogress", GUID(0xAE57E515,0x00001150), &Aobject::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Aprogress::Aprogress(char *name, Aobject *L, int x, int y, Aresobj *o) : Aobject(name, L, x, y, 4, 4)
{
	bmp=new Abitmap(o);
	ow=bmp->w;
	oh=bmp->h/2;
	val=0.f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Aprogress::Aprogress(char *name, Aobject *L, int x, int y, int type) : Aobject(name, L, x, y, 4, 4)
{
	switch(type)
	{
		default:
		case typeNORMAL:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PROGRESS001), "PNG");
			bmp=new Abitmap(&o);
		}
		break;
	}
	ow=bmp->w;
	oh=bmp->h/2;
	size(ow, oh);
	val=0.f;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL Aprogress::~Aprogress()
{
	if(bmp)
		delete(bmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ADLL void Aprogress::paint(Abitmap *b)
{
	if(bmp)
	{
		int	nx=(int)(val*ow);
		b->set(nx, 0, nx, 0, ow, oh, bmp);
		b->set(0, 0, 0, oh, nx, oh, bmp); 
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////