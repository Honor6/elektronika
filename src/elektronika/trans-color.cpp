/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	TRANS-COLOR.CPP				(c)	YoY'01						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"trans-color.h"
#include						"resource.h"
#include						<math.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACI								AtranscolorInfo::CI	= ACI("AtranscolorInfo",	GUID(0x11111112,0xA0000000), &AtransitionInfo::CI, 0, NULL);
ACI								Atranscolor::CI		= ACI("Atranscolor",		GUID(0x11111112,0xA0000001), &Atransition::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int						count=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void init()
{
	count++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void end()
{
	count--;
	if(count==0)
	{
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Atranscolor::Atranscolor(QIID qiid, char *name, Aobject *f, int x, int y) : Atransition(qiid, name, f, x, y)
{
	char	str[1024];
	init();

	sprintf(str, "%s/key", name);
	ck=new Aselcolor(MKQIID(qiid, 0xa5bc76b91e777158), str, this, 52, 40);
	ck->setTooltips("chroma key");
	ck->set(0xff000000);
	ck->show(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Atranscolor::~Atranscolor()
{
	delete(ck);
	end();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atranscolor::notify(Anode *o, int event, dword p)
{
	return Aobject::notify(o, event, p);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Atranscolor::paint(Abitmap *b)
{
/*
	Afont	*f=alib.getFont(fontCONFIDENTIAL14);
	b->boxfa(0, 0, pos.w, pos.h, 0xff000000, 0.1f);
	f->set(b, 10, 10, "COLOR TRANSITION", 0xff404040);
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atranscolor::save(class Afile *f)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atranscolor::load(class Afile *f)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Atranscolor::settings(bool emergency)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Atranscolor::action(Abitmap *out, Abitmap *b0, Abitmap *b1, float cross, int src, float power, Abitmap *in[8])
{
	int		w=out->w;
	int		h=out->h;
	bool	bInv=(src!=0);
	dword	ck=this->ck->get();
	float	fade=power;

	if(!bInv)
	{
		if(b1)
			out->set(0, 0, b1, bitmapNORMAL, bitmapNORMAL);
		else
			out->boxf(0, 0, w, h, 0xff000000);
		if(b0)
			chroma(out, b0, ck, 1.f-cross, fade);
	}
	else
	{
		if(b0)
			out->set(0, 0, b0, bitmapNORMAL, bitmapNORMAL);
		else
			out->boxf(0, 0, w, h, 0xff000000);
		if(b1)
			chroma(out, b1, ck, cross, fade);
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Atranscolor::chroma(Abitmap *out, Abitmap *in, dword ck, float value, float fade)
{
	int		w=out->w;
	int		h=out->h;
	int		x,y;
	dword	*s=in->body32;
	dword	*d=out->body32;
	byte	rk,gk,bk;

	colorRGB(&rk, &gk, &bk, ck);

	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++)
		{
			byte	r,g,b;
			float	r0,g0,b0;

			colorRGB(&r, &g, &b, *s);

			float k=2.f;
			r0=k*(float)((int)r-(int)(256-rk))/256.f;
			g0=k*(float)((int)g-(int)(256-gk))/256.f;
			b0=k*(float)((int)b-(int)(256-bk))/256.f;

			float vd=(float)(sqrt((float)r0*(float)r0+(float)g0*(float)g0+(float)b0*(float)b0)*fade);

			int	a=mini(maxi((int)((value-pow(vd, 3.f))*256.f), 0), 256);
			int	a0=256-a;

			{
				byte	rd,gd,bd;
				colorRGB(&rd, &gd, &bd, *d);
				*d=color32(((int)r*a+(int)rd*a0)>>8, ((int)g*a+(int)gd*a0)>>8, ((int)b*a+(int)bd*a0)>>8);
			}

			s++;
			d++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Atransition * AtranscolorInfo::create(QIID qiid, char *name, Aobject *father, int x, int y)
{
	return new Atranscolor(qiid, name, father, x, y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aplugz * transcolorGetInfo()
{
	return new AtranscolorInfo("chroma key", &Atranscolor::CI, "chroma key", "chroma key");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////